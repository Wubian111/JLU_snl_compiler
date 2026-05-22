#include "snl_mips_generator.h"

#include <algorithm>
#include <cctype>
#include <ostream>
#include <sstream>

MipsGenerator::MipsGenerator(std::ostream& output)
    : out(output) {}

// 从程序根节点开始生成整份 MIPS 汇编。
void MipsGenerator::generate(const ProgramNode& program) {
  program.accept(*this);
}

// 返回生成阶段累计的错误信息。
const std::vector<std::string>& MipsGenerator::get_errors() const {
  return errors;
}

void MipsGenerator::visit(const ProgramNode& node) {
  // 生成主程序前先建立全局类型和变量环境。
  push_type_scope();
  push_var_scope();
  add_type_aliases(node.decls);
  collect_proc_signatures(node.decls);
  collect_global_decls(node.decls);

  out << "# SNL 32 位 MIPS 汇编：" << node.name << "\n";
  out << ".data\n";
  for (const auto& item : globals) {
    const VarInfo& var = item.second;
    out << var.label << ": .space " << storage_words(var.type) * 4 << "\n";
  }

  out << "\n.text\n";
  out << ".globl main\n";
  out << "main:\n";
  gen_stmt_list(node.body);
  out << "  li $v0, 10\n";
  out << "  syscall\n";

  // 主程序之后继续输出所有过程定义。
  for (const auto& proc : node.decls.procs) {
    emit_proc(proc);
  }

  pop_var_scope();
  pop_type_scope();
}

void MipsGenerator::visit(const ProcDecl& node) {
  emit_proc(node);
}

// 语句节点的 Visitor 入口。
void MipsGenerator::visit(const Stmt& node) {
  gen_stmt(node);
}

// 表达式节点的 Visitor 入口。
void MipsGenerator::visit(const Expr& node) {
  gen_expr(node);
}

// 类型节点在该阶段不直接输出代码，但保留 Visitor 接口以保持统一。
void MipsGenerator::visit(const TypeSpec&) {}

// 统一记录一条代码生成错误。
void MipsGenerator::report(int line, const std::string& message) {
  std::ostringstream os;
  os << "第 " << line << " 行：MIPS 生成：" << message;
  errors.push_back(os.str());
}

// 生成带递增编号的唯一标签。
std::string MipsGenerator::new_label(const std::string& prefix) {
  return prefix + "_" + std::to_string(labelCounter++);
}

std::string MipsGenerator::safe_label(const std::string& name) {
  // MIPS 标签只保留字母、数字和下划线，非法字符统一替换掉。
  std::string label;
  for (unsigned char c : name) {
    if (std::isalnum(c) || c == '_') label += static_cast<char>(c);
    else label += '_';
  }
  if (label.empty() || std::isdigit(static_cast<unsigned char>(label[0]))) {
    label = "_" + label;
  }
  return label;
}

void MipsGenerator::push_type_scope() {
  typeScopes.emplace_back();
}

// 退出一层类型作用域。
void MipsGenerator::pop_type_scope() {
  if (!typeScopes.empty()) typeScopes.pop_back();
}

// 把当前声明区中的类型别名加入类型环境。
void MipsGenerator::add_type_aliases(const DeclPart& decls) {
  for (const auto& decl : decls.types) {
    typeScopes.back()[decl.name] = resolve_type(decl.type);
  }
}

// 按作用域链查找类型别名。
bool MipsGenerator::lookup_type_alias(const std::string& name, MipsType& type) const {
  for (auto it = typeScopes.rbegin(); it != typeScopes.rend(); ++it) {
    auto found = it->find(name);
    if (found != it->end()) {
      type = found->second;
      return true;
    }
  }
  return false;
}

// 进入一层变量作用域。
void MipsGenerator::push_var_scope() {
  varScopes.emplace_back();
}

// 退出一层变量作用域。
void MipsGenerator::pop_var_scope() {
  if (!varScopes.empty()) varScopes.pop_back();
}

// 按作用域链查找变量布局信息。
bool MipsGenerator::lookup_var(const std::string& name, VarInfo& info) const {
  for (auto it = varScopes.rbegin(); it != varScopes.rend(); ++it) {
    auto found = it->find(name);
    if (found != it->end()) {
      info = found->second;
      return true;
    }
  }
  return false;
}

// 收集全局变量，为 data 段分配标签和空间。
void MipsGenerator::collect_global_decls(const DeclPart& decls) {
  for (const auto& decl : decls.vars) {
    MipsType type = resolve_type(decl.type);
    for (const auto& name : decl.names) {
      VarInfo info;
      info.storage = VarInfo::Storage::Global;
      info.label = "var_" + safe_label(name);
      info.type = type;
      globals[name] = info;
      varScopes.back()[name] = info;
    }
  }
}

void MipsGenerator::collect_proc_signatures(const DeclPart& decls) {
  // 提前收集过程签名，可以支持“先调用后定义”。
  for (const auto& proc : decls.procs) {
    ProcInfo info;
    info.label = "proc_" + safe_label(proc.name);
    info.decl = &proc;
    int offset = 8;
    for (const auto& param : proc.params) {
      MipsType type = resolve_type(param.type);
      for (const auto& name : param.names) {
        ParamCodeInfo p;
        p.name = name;
        p.byRef = param.byRef;
        p.line = param.line;
        p.offset = offset;
        p.type = type;
        offset += 4;
        info.params.push_back(p);
      }
    }
    procs[proc.name] = info;
    collect_proc_signatures(proc.decls);
  }
}

void MipsGenerator::emit_proc(const ProcDecl& proc) {
  auto procIt = procs.find(proc.name);
  if (procIt == procs.end()) {
    report(proc.line, "未知过程 '" + proc.name + "'");
    return;
  }

  push_type_scope();
  push_var_scope();
  add_type_aliases(proc.decls);

  // 参数进入过程体后，需要映射成当前栈帧里的可寻址对象。
  for (const auto& param : procIt->second.params) {
    VarInfo info;
    info.storage = param.byRef ? VarInfo::Storage::FrameRef
                               : VarInfo::Storage::FrameValue;
    info.offset = param.offset;
    info.type = param.type;
    varScopes.back()[param.name] = info;
  }

  int localWords = add_local_vars(proc.decls);
  std::string endLabel = new_label("proc_end");
  returnLabels.push_back(endLabel);

  out << "\n" << procIt->second.label << ":\n";
  // 典型过程序言：保存旧 fp / ra，建立新栈帧，再为局部变量预留空间。
  out << "  addiu $sp, $sp, -8\n";
  out << "  sw $fp, 0($sp)\n";
  out << "  sw $ra, 4($sp)\n";
  out << "  move $fp, $sp\n";
  if (localWords > 0) {
    out << "  addiu $sp, $sp, -" << localWords * 4 << "\n";
  }

  gen_stmt_list(proc.body);

  // 统一返回出口，所有 return 都跳到这里做尾声收尾。
  out << endLabel << ":\n";
  out << "  move $sp, $fp\n";
  out << "  lw $fp, 0($sp)\n";
  out << "  lw $ra, 4($sp)\n";
  out << "  addiu $sp, $sp, 8\n";
  out << "  jr $ra\n";

  returnLabels.pop_back();
  for (const auto& nested : proc.decls.procs) {
    emit_proc(nested);
  }
  pop_var_scope();
  pop_type_scope();
}

int MipsGenerator::add_local_vars(const DeclPart& decls) {
  // 局部变量放在 fp 以下，用负偏移访问。
  int nextOffset = 0;
  int localWords = 0;
  for (const auto& decl : decls.vars) {
    MipsType type = resolve_type(decl.type);
    int words = storage_words(type);
    for (const auto& name : decl.names) {
      localWords += words;
      nextOffset -= words * 4;
      VarInfo info;
      info.storage = VarInfo::Storage::FrameValue;
      info.offset = nextOffset;
      info.type = type;
      varScopes.back()[name] = info;
    }
  }
  return localWords;
}

// 指针版本包装，便于处理空类型节点。
MipsGenerator::MipsType MipsGenerator::resolve_type(const TypeSpecPtr& spec) {
  if (!spec) {
    MipsType t;
    return t;
  }
  return resolve_type(*spec);
}

// 递归把语法树类型转换成目标代码布局类型。
MipsGenerator::MipsType MipsGenerator::resolve_type(const TypeSpec& spec) {
  MipsType type;
  switch (spec.kind) {
    case TypeSpecKind::Integer:
      type.kind = MipsType::Kind::Integer;
      type.words = 1;
      break;
    case TypeSpecKind::Char:
      type.kind = MipsType::Kind::Char;
      type.words = 1;
      break;
    case TypeSpecKind::Named:
      if (!lookup_type_alias(spec.name, type)) {
        report(spec.line, "未知类型别名 '" + spec.name + "'");
      }
      break;
    case TypeSpecKind::Array:
      type.kind = MipsType::Kind::Array;
      type.low = spec.low;
      type.high = spec.high;
      type.elementType = std::make_shared<MipsType>(resolve_type(spec.elementType));
      type.words = (spec.high - spec.low + 1) * storage_words(*type.elementType);
      if (type.words < 1) type.words = 1;
      break;
    case TypeSpecKind::Record:
      type.kind = MipsType::Kind::Record;
      type.words = 0;
      for (const auto& field : spec.fields) {
        MipsType fieldType = resolve_type(field.type);
        int fieldWords = storage_words(fieldType);
        for (const auto& name : field.names) {
          MipsType::FieldInfo info;
          info.offsetWords = type.words;
          info.type = std::make_shared<MipsType>(fieldType);
          type.fields[name] = info;
          type.words += fieldWords;
        }
      }
      if (type.words < 1) type.words = 1;
      break;
  }
  return type;
}

// 返回某个对象在内存中需要占用的机器字数。
int MipsGenerator::storage_words(const MipsType& type) const {
  return std::max(1, type.words);
}

// 顺序生成一个语句块中的全部语句。
void MipsGenerator::gen_stmt_list(const std::vector<StmtPtr>& list) {
  for (const auto& stmt : list) {
    if (stmt) stmt->accept(*this);
  }
}

// 根据语句种类分派到具体的生成逻辑。
void MipsGenerator::gen_stmt(const Stmt& stmt) {
  switch (stmt.kind) {
    case StmtKind::Assign:
      gen_assign(stmt);
      break;
    case StmtKind::Call: {
      auto procIt = procs.find(stmt.name);
      if (procIt == procs.end()) {
        report(stmt.line, "未知过程 '" + stmt.name + "'");
        return;
      }

      const ProcInfo& proc = procIt->second;

      // 调用约定：实参按从右到左压栈，便于被调过程按固定偏移访问。
      for (int i = static_cast<int>(proc.params.size()) - 1; i >= 0; --i) {
        out << "  addiu $sp, $sp, -4\n";
        if (i < static_cast<int>(stmt.args.size())) {
          if (proc.params[i].byRef) {
            if (stmt.args[i]->kind != ExprKind::Variable) {
              report(stmt.args[i]->line, "var 参数需要变量地址");
              out << "  li $t0, 0\n";
            } else {
              gen_address(*stmt.args[i]);
            }
          } else {
            gen_expr(*stmt.args[i]);
          }
        } else {
          out << "  li $t0, 0\n";
        }
        out << "  sw $t0, 0($sp)\n";
      }

      out << "  jal " << proc.label << "\n";
      if (!proc.params.empty()) {
        out << "  addiu $sp, $sp, " << proc.params.size() * 4 << "\n";
      }
      break;
    }
    case StmtKind::If:
      gen_if(stmt);
      break;
    case StmtKind::While:
      gen_while(stmt);
      break;
    case StmtKind::Read:
      gen_read(stmt);
      break;
    case StmtKind::Write:
      gen_write(stmt);
      break;
    case StmtKind::Return:
      if (stmt.expr) gen_expr(*stmt.expr);
      if (!returnLabels.empty()) {
        out << "  j " << returnLabels.back() << "\n";
      } else {
        out << "  li $v0, 10\n";
        out << "  syscall\n";
      }
      break;
  }
}

void MipsGenerator::gen_assign(const Stmt& stmt) {
  // 赋值先求左值地址，再求右值结果，最后把值写回内存。
  gen_address(*stmt.lhs);
  push_t0();
  gen_expr(*stmt.expr);
  pop_to("$t1");
  out << "  sw $t0, 0($t1)\n";
}

void MipsGenerator::gen_read(const Stmt& stmt) {
  VarInfo info;
  if (!lookup_var(stmt.name, info)) {
    report(stmt.line, "未知变量 '" + stmt.name + "'");
    return;
  }

  Expr var;
  var.kind = ExprKind::Variable;
  var.line = stmt.line;
  var.name = stmt.name;
  gen_address(var);
  out << "  move $t1, $t0\n";
  out << "  li $v0, 5\n";
  out << "  syscall\n";
  out << "  sw $v0, 0($t1)\n";
}

// write 语句通过 syscall 1 输出整数，并额外换行。
void MipsGenerator::gen_write(const Stmt& stmt) {
  gen_expr(*stmt.expr);
  out << "  move $a0, $t0\n";
  out << "  li $v0, 1\n";
  out << "  syscall\n";
  out << "  li $a0, 10\n";
  out << "  li $v0, 11\n";
  out << "  syscall\n";
}

// if 语句通过两个标签组织 then/else 控制流。
void MipsGenerator::gen_if(const Stmt& stmt) {
  std::string elseLabel = new_label("else");
  std::string endLabel = new_label("endif");
  gen_expr(*stmt.cond);
  out << "  beq $t0, $zero, " << elseLabel << "\n";
  gen_stmt_list(stmt.thenPart);
  out << "  j " << endLabel << "\n";
  out << elseLabel << ":\n";
  gen_stmt_list(stmt.elsePart);
  out << endLabel << ":\n";
}

// while 语句通过循环入口和出口标签形成回边。
void MipsGenerator::gen_while(const Stmt& stmt) {
  std::string beginLabel = new_label("while_begin");
  std::string endLabel = new_label("while_end");
  out << beginLabel << ":\n";
  gen_expr(*stmt.cond);
  out << "  beq $t0, $zero, " << endLabel << "\n";
  gen_stmt_list(stmt.body);
  out << "  j " << beginLabel << "\n";
  out << endLabel << ":\n";
}

// 生成表达式结果，并约定写入寄存器 $t0。
void MipsGenerator::gen_expr(const Expr& expr) {
  switch (expr.kind) {
    case ExprKind::IntConst:
      out << "  li $t0, " << expr.intValue << "\n";
      break;
    case ExprKind::CharConst:
      out << "  li $t0, " << static_cast<int>(expr.charValue) << "\n";
      break;
    case ExprKind::Variable:
      gen_address(expr);
      out << "  lw $t0, 0($t0)\n";
      break;
    case ExprKind::Op:
      gen_binary_expr(expr);
      break;
  }
}

void MipsGenerator::gen_binary_expr(const Expr& expr) {
  // 二元表达式递归生成时，用栈保存左操作数。
  gen_expr(*expr.left);
  push_t0();
  gen_expr(*expr.right);
  pop_to("$t1");
  switch (expr.op) {
    case TK_PLUS:
      out << "  add $t0, $t1, $t0\n";
      break;
    case TK_MINUS:
      out << "  sub $t0, $t1, $t0\n";
      break;
    case TK_STAR:
      out << "  mul $t0, $t1, $t0\n";
      break;
    case TK_DIV:
      out << "  div $t1, $t0\n";
      out << "  mflo $t0\n";
      break;
    case TK_LT:
      out << "  slt $t0, $t1, $t0\n";
      break;
    case TK_EQ:
      out << "  seq $t0, $t1, $t0\n";
      break;
    default:
      report(expr.line, "不支持的表达式运算符");
      out << "  li $t0, 0\n";
      break;
  }
}

void MipsGenerator::gen_address(const Expr& expr) {
  VarInfo info;
  if (!lookup_var(expr.name, info)) {
    report(expr.line, "未知变量 '" + expr.name + "'");
    out << "  li $t0, 0\n";
    return;
  }

  // 第一步先求出变量基地址。
  switch (info.storage) {
    case VarInfo::Storage::Global:
      out << "  la $t0, " << info.label << "\n";
      break;
    case VarInfo::Storage::FrameValue:
      out << "  addiu $t0, $fp, " << info.offset << "\n";
      break;
    case VarInfo::Storage::FrameRef:
      out << "  lw $t0, " << info.offset << "($fp)\n";
      break;
  }

  // 然后按访问链继续处理字段偏移或数组下标。
  MipsType currentType = info.type;
  for (const auto& access : expr.access) {
    if (access.kind == VarAccess::Kind::Field) {
      if (currentType.kind != MipsType::Kind::Record) {
        report(access.line, "被域选择的目标不是记录");
        continue;
      }
      auto field = currentType.fields.find(access.fieldName);
      if (field == currentType.fields.end() || !field->second.type) {
        report(access.line, "记录中不存在域 '" + access.fieldName + "'");
        continue;
      }
      int offsetBytes = field->second.offsetWords * 4;
      if (offsetBytes != 0) {
        out << "  addiu $t0, $t0, " << offsetBytes << "\n";
      }
      currentType = *field->second.type;
      continue;
    }

    if (currentType.kind != MipsType::Kind::Array || !currentType.elementType) {
      report(access.line, "被下标访问的目标不是数组");
      continue;
    }

    // 数组地址计算公式：
    // 基址 + (下标 - low) * 元素大小。
    push_t0();
    gen_expr(*access.index);
    out << "  addiu $t0, $t0, " << -currentType.low << "\n";
    int elemBytes = storage_words(*currentType.elementType) * 4;
    if (elemBytes == 4) {
      out << "  sll $t0, $t0, 2\n";
    } else {
      out << "  li $t2, " << elemBytes << "\n";
      out << "  mul $t0, $t0, $t2\n";
    }
    pop_to("$t1");
    out << "  add $t0, $t1, $t0\n";
    currentType = *currentType.elementType;
  }
}

void MipsGenerator::push_t0() {
  out << "  addiu $sp, $sp, -4\n";
  out << "  sw $t0, 0($sp)\n";
}

// 把栈顶临时值弹出到指定寄存器。
void MipsGenerator::pop_to(const std::string& reg) {
  out << "  lw " << reg << ", 0($sp)\n";
  out << "  addiu $sp, $sp, 4\n";
}
