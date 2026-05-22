#include "snl_syntax_tree_printer.h"

#include <iostream>

SyntaxTreePrinter::SyntaxTreePrinter(std::ostream& output)
    : out(output) {}

// 从程序根节点开始递归打印整棵语法树。
void SyntaxTreePrinter::print(const ProgramNode& program) {
  program.accept(*this);
}

// 打印程序根节点：程序头、声明区和主语句区。
void SyntaxTreePrinter::visit(const ProgramNode& node) {
  out << "ProK\n";
  indent++;
  print_indent();
  out << "PheadK " << node.name << "\n";
  print_decls(node.decls);
  print_stmt_list(node.body);
  indent--;
}

// 打印过程声明及其参数、局部声明和过程体。
void SyntaxTreePrinter::visit(const ProcDecl& node) {
  print_indent();
  out << "ProcDecK " << node.name << "\n";
  indent++;
  for (const auto& param : node.params) {
    print_indent();
    out << "DecK " << (param.byRef ? "var 参数：" : "值参数：")
        << type_summary(param.type);
    for (const auto& name : param.names) out << " " << name;
    out << "\n";
  }
  print_decls(node.decls);
  print_stmt_list(node.body);
  indent--;
}

// 根据语句类型选择不同的树形展示方式。
void SyntaxTreePrinter::visit(const Stmt& node) {
  print_indent();
  switch (node.kind) {
    case StmtKind::Assign:
      out << "StmtK Assign\n";
      indent++;
      node.lhs->accept(*this);
      node.expr->accept(*this);
      indent--;
      break;
    case StmtKind::Call:
      out << "StmtK Call " << node.name << "\n";
      indent++;
      for (const auto& arg : node.args) arg->accept(*this);
      indent--;
      break;
    case StmtKind::If:
      out << "StmtK If\n";
      indent++;
      node.cond->accept(*this);
      print_stmt_list(node.thenPart);
      print_stmt_list(node.elsePart);
      indent--;
      break;
    case StmtKind::While:
      out << "StmtK While\n";
      indent++;
      node.cond->accept(*this);
      print_stmt_list(node.body);
      indent--;
      break;
    case StmtKind::Read:
      out << "StmtK Read " << node.name << "\n";
      break;
    case StmtKind::Write:
      out << "StmtK Write\n";
      indent++;
      node.expr->accept(*this);
      indent--;
      break;
    case StmtKind::Return:
      out << "StmtK Return\n";
      indent++;
      node.expr->accept(*this);
      indent--;
      break;
  }
}

// 打印表达式节点，并在需要时递归展开子表达式。
void SyntaxTreePrinter::visit(const Expr& node) {
  print_indent();
  switch (node.kind) {
    case ExprKind::Op:
      out << "ExpK Op " << get_token_name(node.op) << "\n";
      indent++;
      node.left->accept(*this);
      node.right->accept(*this);
      indent--;
      break;
    case ExprKind::IntConst:
      out << "ExpK Const " << node.intValue << "\n";
      break;
    case ExprKind::CharConst:
      out << "ExpK Const '" << node.charValue << "'\n";
      break;
    case ExprKind::Variable:
      out << "ExpK " << variable_suffix(node) << " IdV\n";
      indent++;
      for (const auto& access : node.access) {
        if (access.kind == VarAccess::Kind::Index && access.index) {
          print_indent();
          out << "Index\n";
          indent++;
          access.index->accept(*this);
          indent--;
        }
      }
      indent--;
      break;
  }
}

// 单独打印类型节点摘要。
void SyntaxTreePrinter::visit(const TypeSpec& node) {
  print_indent();
  out << type_summary(node) << "\n";
}

// 输出与当前层级匹配的缩进空格。
void SyntaxTreePrinter::print_indent() {
  for (int i = 0; i < indent; ++i) out << "  ";
}

// 指针版本的类型摘要包装，便于处理空指针。
std::string SyntaxTreePrinter::type_summary(const TypeSpecPtr& type) const {
  if (!type) return "<空>";
  return type_summary(*type);
}

// 把类型说明压缩成一行文字，方便挂在树节点后面展示。
std::string SyntaxTreePrinter::type_summary(const TypeSpec& type) const {
  switch (type.kind) {
    case TypeSpecKind::Integer: return "IntegerK";
    case TypeSpecKind::Char: return "CharK";
    case TypeSpecKind::Named: return "IdK " + type.name;
    case TypeSpecKind::Array:
      return "ArrayK [" + std::to_string(type.low) + ".." +
             std::to_string(type.high) + "] 的 " +
             type_summary(type.elementType);
    case TypeSpecKind::Record: return "RecordK";
  }
  return "<未知>";
}

// 生成变量访问后缀，便于展示数组和记录访问链。
std::string SyntaxTreePrinter::variable_suffix(const Expr& expr) const {
  std::string result = expr.name;
  for (const auto& access : expr.access) {
    if (access.kind == VarAccess::Kind::Index) {
      result += "[...]";
    } else {
      result += "." + access.fieldName;
    }
  }
  return result;
}

// 依次打印类型声明、变量声明和过程声明。
void SyntaxTreePrinter::print_decls(const DeclPart& decls) {
  print_indent();
  out << "TypeK\n";
  indent++;
  for (const auto& decl : decls.types) {
    print_indent();
    out << "DecK " << decl.name << " = " << type_summary(decl.type) << "\n";
    if (decl.type && decl.type->kind == TypeSpecKind::Record) {
      indent++;
      print_type_detail(decl.type);
      indent--;
    }
  }
  indent--;

  print_indent();
  out << "VarK\n";
  indent++;
  for (const auto& decl : decls.vars) {
    print_indent();
    out << "DecK " << type_summary(decl.type);
    for (const auto& name : decl.names) out << " " << name;
    out << "\n";
  }
  indent--;

  for (const auto& proc : decls.procs) {
    proc.accept(*this);
  }
}

// 顺序打印一个语句块中的全部语句。
void SyntaxTreePrinter::print_stmt_list(const std::vector<StmtPtr>& list) {
  print_indent();
  out << "StmLK\n";
  indent++;
  for (const auto& stmt : list) {
    if (stmt) stmt->accept(*this);
  }
  indent--;
}

// 当类型是 record 时，进一步展开字段细节。
void SyntaxTreePrinter::print_type_detail(const TypeSpecPtr& type) {
  if (!type || type->kind != TypeSpecKind::Record) return;
  for (const auto& field : type->fields) {
    print_indent();
    out << "Field " << type_summary(field.type);
    for (const auto& name : field.names) out << " " << name;
    out << "\n";
  }
}

// 提供一个无须显式构造打印器对象的便捷接口。
void print_syntax_tree(const ProgramNode& program, std::ostream& out) {
  SyntaxTreePrinter printer(out);
  printer.print(program);
}
