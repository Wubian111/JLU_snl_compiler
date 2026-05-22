#include "snl_semantic.h"

#include <algorithm>
#include <ostream>
#include <sstream>

SemanticAnalyzer::SemanticAnalyzer() {
  // 初始化所有内建类型对象，后续分析过程中直接复用这些共享实例。
  intType = make_builtin(TypeKind::Integer);
  charType = make_builtin(TypeKind::Char);
  boolType = make_builtin(TypeKind::Boolean);
  voidType = make_builtin(TypeKind::Void);
  errorType = make_builtin(TypeKind::Error);
  lastExpr = ExprResult{errorType, false, false, 0};
}

void SemanticAnalyzer::analyze(const ProgramNode& program) {
  program.accept(*this);
}

const std::vector<std::string>& SemanticAnalyzer::get_errors() const {
  return errors;
}

// 按作用域层次输出符号表，便于检查类型、变量和过程是否正确入表。
void SemanticAnalyzer::print_symbol_table(std::ostream& out) const {
  out << "===== 符号表 =====\n";
  for (const auto& scopePtr : scopes) {
    const Scope& scope = *scopePtr;
    out << "作用域：" << scope.name << "（层次 " << scope.level << "）\n";
    for (const auto& item : scope.symbols) {
      const Symbol& sym = item.second;
      out << "  " << sym.name << " : " << symbol_kind_name(sym.kind);
      if (sym.kind == SymKind::Proc) {
        out << " 参数(";
        for (size_t i = 0; i < sym.params.size(); ++i) {
          if (i) out << ", ";
          out << (sym.params[i].byRef ? "var " : "值参 ")
              << sym.params[i].name << ": "
              << type_to_string(sym.params[i].type);
        }
        out << ")";
      } else {
        out << " " << type_to_string(sym.type);
      }
      out << " [第 " << sym.line << " 行]\n";
    }
  }
}

void SemanticAnalyzer::visit(const ProgramNode& node) {
  // 全局程序先创建最外层作用域，再处理声明区和主语句序列。
  push_scope("全局");
  process_decl_part(node.decls);
  analyze_stmt_list(node.body);
}

// 过程节点的 Visitor 入口，转交给专门的分析函数处理。
void SemanticAnalyzer::visit(const ProcDecl& node) {
  analyze_proc(node);
}

// 语句节点的 Visitor 入口。
void SemanticAnalyzer::visit(const Stmt& node) {
  analyze_stmt(node);
}

// 表达式节点的 Visitor 入口，并保存最近一次求值结果。
void SemanticAnalyzer::visit(const Expr& node) {
  lastExpr = eval_expr(node);
}

// 类型节点的 Visitor 入口，将语法类型转换成语义类型。
void SemanticAnalyzer::visit(const TypeSpec& node) {
  lastExpr.type = resolve_type_spec(node);
}

// 创建一个只带种类信息的内建类型对象。
TypePtr SemanticAnalyzer::make_builtin(TypeKind kind) {
  auto type = std::make_shared<Type>();
  type->kind = kind;
  return type;
}

// 压入一层新作用域，用于过程体或全局分析。
void SemanticAnalyzer::push_scope(const std::string& name) {
  auto scope = std::make_unique<Scope>();
  scope->name = name;
  scope->parent = current;
  scope->level = current ? current->level + 1 : 0;
  current = scope.get();
  scopes.push_back(std::move(scope));
}

// 回退到父作用域。
void SemanticAnalyzer::pop_scope() {
  if (current) current = current->parent;
}

// 统一格式记录一条语义错误。
void SemanticAnalyzer::report(int line, const std::string& message) {
  std::ostringstream os;
  os << "第 " << line << " 行：" << message;
  errors.push_back(os.str());
}

// 尝试向当前作用域插入符号；若名称冲突则报错。
bool SemanticAnalyzer::insert_symbol(const Symbol& sym) {
  if (current->symbols.find(sym.name) != current->symbols.end()) {
    report(sym.line, "标识符重复定义 '" + sym.name + "'");
    return false;
  }
  current->symbols[sym.name] = sym;
  return true;
}

Symbol* SemanticAnalyzer::lookup(const std::string& name) {
  // 从当前作用域开始逐层向外查找，符合静态作用域规则。
  for (Scope* scope = current; scope != nullptr; scope = scope->parent) {
    auto it = scope->symbols.find(name);
    if (it != scope->symbols.end()) return &it->second;
  }
  return nullptr;
}

Symbol* SemanticAnalyzer::lookup_current(const std::string& name) {
  auto it = current->symbols.find(name);
  return it == current->symbols.end() ? nullptr : &it->second;
}

// 把符号类别枚举转换成可读中文名称。
std::string SemanticAnalyzer::symbol_kind_name(SymKind kind) {
  switch (kind) {
    case SymKind::Type: return "类型";
    case SymKind::Var: return "变量";
    case SymKind::Proc: return "过程";
  }
  return "未知";
}

// 把内部语义类型还原成可展示的字符串。
std::string SemanticAnalyzer::type_to_string(const TypePtr& type) const {
  if (!type) return "<空>";
  switch (type->kind) {
    case TypeKind::Integer: return "整数";
    case TypeKind::Char: return "字符";
    case TypeKind::Boolean: return "bool";
    case TypeKind::Void: return "void";
    case TypeKind::Error: return "<错误>";
    case TypeKind::Array:
      return "数组[" + std::to_string(type->low) + ".." +
             std::to_string(type->high) + "] 的 " +
             type_to_string(type->elementType);
    case TypeKind::Record: {
      std::string s = "记录{";
      bool first = true;
      for (const auto& field : type->fields) {
        if (!first) s += ", ";
        first = false;
        s += field.first + ":" + type_to_string(field.second.type);
      }
      return s + "}";
    }
  }
  return "<未知>";
}

bool SemanticAnalyzer::same_type(const TypePtr& a, const TypePtr& b) const {
  if (!a || !b) return false;

  // 错误类型作为哨兵存在时，直接放行，避免一处错误导致级联报错。
  if (a->kind == TypeKind::Error || b->kind == TypeKind::Error) return true;
  if (a->kind != b->kind) return false;

  switch (a->kind) {
    case TypeKind::Integer:
    case TypeKind::Char:
    case TypeKind::Boolean:
    case TypeKind::Void:
      return true;
    case TypeKind::Array:
      return a->low == b->low && a->high == b->high &&
             same_type(a->elementType, b->elementType);
    case TypeKind::Record:
      if (a->fields.size() != b->fields.size()) return false;
      for (const auto& field : a->fields) {
        auto it = b->fields.find(field.first);
        if (it == b->fields.end()) return false;
        if (!same_type(field.second.type, it->second.type)) return false;
      }
      return true;
    case TypeKind::Error:
      return true;
  }
  return false;
}

TypePtr SemanticAnalyzer::resolve_type_spec(const TypeSpecPtr& spec) {
  if (!spec) return errorType;
  return resolve_type_spec(*spec);
}

// 递归解析语法树中的类型说明，生成后续检查可直接使用的语义类型。
TypePtr SemanticAnalyzer::resolve_type_spec(const TypeSpec& spec) {
  switch (spec.kind) {
    case TypeSpecKind::Integer:
      return intType;
    case TypeSpecKind::Char:
      return charType;
    case TypeSpecKind::Named: {
      Symbol* sym = lookup(spec.name);
      if (!sym) {
        report(spec.line, "类型标识符未声明 '" + spec.name + "'");
        return errorType;
      }
      if (sym->kind != SymKind::Type) {
        report(spec.line, "'" + spec.name + "' 不是类型标识符");
        return errorType;
      }
      return sym->type;
    }
    case TypeSpecKind::Array: {
      auto type = std::make_shared<Type>();
      type->kind = TypeKind::Array;
      type->low = spec.low;
      type->high = spec.high;
      if (spec.low > spec.high) {
        report(spec.line, "数组下界大于上界");
      }
      type->elementType = resolve_type_spec(spec.elementType);
      return type;
    }
    case TypeSpecKind::Record: {
      auto type = std::make_shared<Type>();
      type->kind = TypeKind::Record;
      for (const auto& field : spec.fields) {
        TypePtr fieldType = resolve_type_spec(field.type);
        for (const auto& name : field.names) {
          if (type->fields.find(name) != type->fields.end()) {
            report(field.line, "记录域重复定义 '" + name + "'");
            continue;
          }
          type->fields[name] = FieldInfo{field.line, fieldType};
        }
      }
      return type;
    }
  }
  return errorType;
}

std::vector<ParamInfo> SemanticAnalyzer::flatten_params(const std::vector<ParamDecl>& decls) {
  // 语法树中一个 ParamDecl 可能声明多个同类型参数，这里将其展开成一维列表。
  std::vector<ParamInfo> params;
  for (const auto& decl : decls) {
    TypePtr type = resolve_type_spec(decl.type);
    for (const auto& name : decl.names) {
      params.push_back(ParamInfo{name, type, decl.byRef});
    }
  }
  return params;
}

// 按“类型、变量、过程”的顺序处理一个声明区，并递归分析过程体。
void SemanticAnalyzer::process_decl_part(const DeclPart& decls) {
  // 先插入类型，再插入变量，再插入过程，这样后续声明可引用前面定义的名称。
  for (const auto& decl : decls.types) {
    TypePtr type = resolve_type_spec(decl.type);
    Symbol sym;
    sym.kind = SymKind::Type;
    sym.name = decl.name;
    sym.type = type;
    sym.line = decl.line;
    insert_symbol(sym);
  }

  for (const auto& decl : decls.vars) {
    TypePtr type = resolve_type_spec(decl.type);
    for (const auto& name : decl.names) {
      Symbol sym;
      sym.kind = SymKind::Var;
      sym.name = name;
      sym.type = type;
      sym.line = decl.line;
      insert_symbol(sym);
    }
  }

  for (const auto& proc : decls.procs) {
    Symbol sym;
    sym.kind = SymKind::Proc;
    sym.name = proc.name;
    sym.line = proc.line;
    sym.type = voidType;
    sym.params = flatten_params(proc.params);
    insert_symbol(sym);
  }

  // 过程签名先入表，再递归分析过程体，支持过程互相调用。
  for (const auto& proc : decls.procs) {
    proc.accept(*this);
  }
}

// 进入过程作用域，注入参数后分析其局部声明和语句体。
void SemanticAnalyzer::analyze_proc(const ProcDecl& proc) {
  Symbol* procSym = lookup_current(proc.name);
  std::vector<ParamInfo> params = procSym && procSym->kind == SymKind::Proc
                                      ? procSym->params
                                      : flatten_params(proc.params);

  push_scope("过程 " + proc.name);

  // 形参在过程体内本质上按局部变量使用，因此也作为变量插入当前作用域。
  for (const auto& param : params) {
    Symbol sym;
    sym.kind = SymKind::Var;
    sym.name = param.name;
    sym.type = param.type;
    sym.line = proc.line;
    insert_symbol(sym);
  }

  process_decl_part(proc.decls);
  analyze_stmt_list(proc.body);
  pop_scope();
}

// 顺序分析语句列表中的每个非空语句。
void SemanticAnalyzer::analyze_stmt_list(const std::vector<StmtPtr>& list) {
  for (const auto& stmt : list) {
    if (stmt) stmt->accept(*this);
  }
}

// 对每类语句做相应的语义规则检查。
void SemanticAnalyzer::analyze_stmt(const Stmt& stmt) {
  switch (stmt.kind) {
    case StmtKind::Assign: {
      ExprResult lhs = eval_expr(*stmt.lhs);
      ExprResult rhs = eval_expr(*stmt.expr);
      if (!lhs.isVariable) {
        report(stmt.line, "赋值语句左端不是变量");
      }
      if (!same_type(lhs.type, rhs.type)) {
        report(stmt.line, "赋值类型不匹配："
                         + type_to_string(lhs.type) + " := "
                         + type_to_string(rhs.type));
      }
      break;
    }
    case StmtKind::Call:
      analyze_call(stmt);
      break;
    case StmtKind::If: {
      ExprResult cond = eval_expr(*stmt.cond);
      if (cond.type->kind != TypeKind::Boolean && cond.type->kind != TypeKind::Error) {
        report(stmt.line, "if 条件不是 bool 类型");
      }
      analyze_stmt_list(stmt.thenPart);
      analyze_stmt_list(stmt.elsePart);
      break;
    }
    case StmtKind::While: {
      ExprResult cond = eval_expr(*stmt.cond);
      if (cond.type->kind != TypeKind::Boolean && cond.type->kind != TypeKind::Error) {
        report(stmt.line, "while 条件不是 bool 类型");
      }
      analyze_stmt_list(stmt.body);
      break;
    }
    case StmtKind::Read:
      analyze_read(stmt);
      break;
    case StmtKind::Write: {
      ExprResult result = eval_expr(*stmt.expr);
      if (result.type->kind == TypeKind::Array || result.type->kind == TypeKind::Record) {
        report(stmt.line, "write 表达式不能是数组或记录");
      }
      break;
    }
    case StmtKind::Return:
      if (stmt.expr) eval_expr(*stmt.expr);
      break;
  }
}

// read 语句要求目标必须是已声明的普通变量。
void SemanticAnalyzer::analyze_read(const Stmt& stmt) {
  Symbol* sym = lookup(stmt.name);
  if (!sym) {
    report(stmt.line, "标识符未声明 '" + stmt.name + "'");
    return;
  }
  if (sym->kind != SymKind::Var) {
    report(stmt.line, "'" + stmt.name + "' 不是变量标识符");
    return;
  }
  if (sym->type->kind == TypeKind::Array || sym->type->kind == TypeKind::Record) {
    report(stmt.line, "read 变量不能是数组或记录");
  }
}

// 检查过程调用的名称、参数个数、参数类型和引用实参合法性。
void SemanticAnalyzer::analyze_call(const Stmt& stmt) {
  Symbol* sym = lookup(stmt.name);
  if (!sym) {
    report(stmt.line, "过程未声明 '" + stmt.name + "'");
    for (const auto& arg : stmt.args) eval_expr(*arg);
    return;
  }
  if (sym->kind != SymKind::Proc) {
    report(stmt.line, "'" + stmt.name + "' 不是过程标识符");
    for (const auto& arg : stmt.args) eval_expr(*arg);
    return;
  }
  if (stmt.args.size() != sym->params.size()) {
    report(stmt.line, "过程 '" + stmt.name + "' 需要 "
                      + std::to_string(sym->params.size()) + " 个实参，实际有 "
                      + std::to_string(stmt.args.size()) + " 个");
  }

  size_t n = std::min(stmt.args.size(), sym->params.size());
  for (size_t i = 0; i < stmt.args.size(); ++i) {
    ExprResult arg = eval_expr(*stmt.args[i]);
    if (i >= n) continue;

    const ParamInfo& param = sym->params[i];
    if (param.byRef && !arg.isVariable) {
      report(stmt.args[i]->line, "var 参数 '" + param.name + "' 需要变量实参");
    }
    if (!same_type(param.type, arg.type)) {
      report(stmt.args[i]->line, "参数 '" + param.name + "' 的实参类型不匹配");
    }
  }
}

// 计算表达式的类型、左值属性和常量属性。
SemanticAnalyzer::ExprResult SemanticAnalyzer::eval_expr(const Expr& expr) {
  switch (expr.kind) {
    case ExprKind::IntConst:
      return ExprResult{intType, false, true, expr.intValue};
    case ExprKind::CharConst:
      return ExprResult{charType, false, false, 0};
    case ExprKind::Variable:
      return eval_variable(expr);
    case ExprKind::Op:
      return eval_op(expr);
  }
  return ExprResult{errorType, false, false, 0};
}

// 分析运算表达式，并检查运算符与操作数类型是否匹配。
SemanticAnalyzer::ExprResult SemanticAnalyzer::eval_op(const Expr& expr) {
  ExprResult left = eval_expr(*expr.left);
  ExprResult right = eval_expr(*expr.right);

  if (expr.op == TK_PLUS || expr.op == TK_MINUS ||
      expr.op == TK_STAR || expr.op == TK_DIV) {
    if (left.type->kind != TypeKind::Integer && left.type->kind != TypeKind::Error) {
      report(expr.line, "算术运算符左操作数不是整数");
    }
    if (right.type->kind != TypeKind::Integer && right.type->kind != TypeKind::Error) {
      report(expr.line, "算术运算符右操作数不是整数");
    }

    // 如果两个操作数都是编译期常量，则顺手保留常量值，便于数组越界等检查复用。
    if (left.isConstInt && right.isConstInt) {
      int value = 0;
      switch (expr.op) {
        case TK_PLUS: value = left.constInt + right.constInt; break;
        case TK_MINUS: value = left.constInt - right.constInt; break;
        case TK_STAR: value = left.constInt * right.constInt; break;
        case TK_DIV: value = right.constInt == 0 ? 0 : left.constInt / right.constInt; break;
        default: break;
      }
      return ExprResult{intType, false, true, value};
    }
    return ExprResult{intType, false, false, 0};
  }

  if (expr.op == TK_LT) {
    if (left.type->kind != TypeKind::Integer && left.type->kind != TypeKind::Error) {
      report(expr.line, "'<' 左操作数不是整数");
    }
    if (right.type->kind != TypeKind::Integer && right.type->kind != TypeKind::Error) {
      report(expr.line, "'<' 右操作数不是整数");
    }
    return ExprResult{boolType, false, false, 0};
  }

  if (expr.op == TK_EQ) {
    if (!same_type(left.type, right.type)) {
      report(expr.line, "'=' 两侧操作数类型不兼容");
    }
    return ExprResult{boolType, false, false, 0};
  }

  return ExprResult{errorType, false, false, 0};
}

// 分析变量表达式，沿访问链检查数组下标和记录字段是否合法。
SemanticAnalyzer::ExprResult SemanticAnalyzer::eval_variable(const Expr& expr) {
  Symbol* sym = lookup(expr.name);
  if (!sym) {
    report(expr.line, "标识符未声明 '" + expr.name + "'");
    return ExprResult{errorType, true, false, 0};
  }
  if (sym->kind != SymKind::Var) {
    report(expr.line, "'" + expr.name + "' 不是变量标识符");
    return ExprResult{errorType, false, false, 0};
  }

  TypePtr type = sym->type;
  for (const auto& access : expr.access) {
    if (access.kind == VarAccess::Kind::Index) {
      ExprResult index = eval_expr(*access.index);
      if (type->kind != TypeKind::Array) {
        report(access.line, "被下标访问的对象不是数组");
        type = errorType;
        continue;
      }
      if (index.type->kind != TypeKind::Integer && index.type->kind != TypeKind::Error) {
        report(access.line, "数组下标不是整数");
      }
      if (index.isConstInt &&
          (index.constInt < type->low || index.constInt > type->high)) {
        report(access.line, "数组下标 " + std::to_string(index.constInt) +
                            " 越界，合法范围为 [" + std::to_string(type->low) +
                            ".." + std::to_string(type->high) + "]");
      }
      type = type->elementType;
    } else {
      if (type->kind != TypeKind::Record) {
        report(access.line, "被域选择的对象不是记录");
        type = errorType;
        continue;
      }
      auto it = type->fields.find(access.fieldName);
      if (it == type->fields.end()) {
        report(access.line, "记录中不存在域 '" + access.fieldName + "'");
        type = errorType;
        continue;
      }
      type = it->second.type;
    }
  }
  return ExprResult{type, true, false, 0};
}
