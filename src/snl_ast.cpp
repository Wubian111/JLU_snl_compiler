#include "snl_ast.h"

// 下面几个 accept 函数是 Visitor 模式的分发点。
// 不同阶段只要实现自己的 AstVisitor，就能复用同一套 AST 结构。

void TypeSpec::accept(AstVisitor& visitor) const {
  visitor.visit(*this);
}

void Expr::accept(AstVisitor& visitor) const {
  visitor.visit(*this);
}

void Stmt::accept(AstVisitor& visitor) const {
  visitor.visit(*this);
}

void ProcDecl::accept(AstVisitor& visitor) const {
  visitor.visit(*this);
}

void ProgramNode::accept(AstVisitor& visitor) const {
  visitor.visit(*this);
}
