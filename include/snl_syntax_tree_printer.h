#ifndef SNL_SYNTAX_TREE_PRINTER_H
#define SNL_SYNTAX_TREE_PRINTER_H

#include "snl_ast.h"

#include <iosfwd>
#include <string>

// 语法树打印器。
// 它以课程常见的树形文本格式输出 AST，便于展示 parser 的分析结果。
class SyntaxTreePrinter : public AstVisitor {
public:
  explicit SyntaxTreePrinter(std::ostream& output);

  // 对外统一入口，打印整个程序的语法树。
  void print(const ProgramNode& program);

  // Visitor 分发函数，分别负责不同节点的树形输出。
  void visit(const ProgramNode& node) override;
  void visit(const ProcDecl& node) override;
  void visit(const Stmt& node) override;
  void visit(const Expr& node) override;
  void visit(const TypeSpec& node) override;

private:
  std::ostream& out;
  int indent = 0; // 当前缩进层级，用于树形排版。

  // 输出当前缩进层数对应的空格。
  void print_indent();

  // 将类型节点压缩成一行摘要，便于在树上展示。
  std::string type_summary(const TypeSpecPtr& type) const;
  std::string type_summary(const TypeSpec& type) const;

  // 把变量访问链拼成可读名字，例如 `arr[...].field`。
  std::string variable_suffix(const Expr& expr) const;

  // 打印声明区中的类型、变量和过程定义。
  void print_decls(const DeclPart& decls);

  // 打印一组顺序语句。
  void print_stmt_list(const std::vector<StmtPtr>& list);

  // 记录类型额外展开字段明细，便于展示 record 内部结构。
  void print_type_detail(const TypeSpecPtr& type);
};

// 便捷函数：直接把一棵 AST 输出到指定流。
void print_syntax_tree(const ProgramNode& program, std::ostream& out);

#endif
