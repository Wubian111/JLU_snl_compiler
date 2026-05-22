#ifndef SNL_AST_H
#define SNL_AST_H

#include "snl_token.h"

#include <memory>
#include <string>
#include <vector>

class AstVisitor;

// 类型说明节点的种类。
// 它对应 SNL 中的内建类型、类型别名、数组类型和记录类型。
enum class TypeSpecKind { Integer, Char, Named, Array, Record };

struct TypeSpec;
using TypeSpecPtr = std::shared_ptr<TypeSpec>;

// 记录类型中的字段声明，例如 `integer x, y;`。
struct FieldDecl {
  int line = 1;                   // 字段声明所在行号。
  TypeSpecPtr type;               // 字段类型。
  std::vector<std::string> names; // 同一条字段声明中的多个字段名。
};

// 类型说明 AST 节点。
// 例如 `integer`、`array[1..10] of integer`、`record ... end` 都会归并到这里。
struct TypeSpec {
  TypeSpecKind kind = TypeSpecKind::Integer; // 当前类型说明的具体种类。
  int line = 1;                              // 类型说明出现的源代码行号。
  std::string name;                          // 当 kind=Named 时记录别名名称。
  int low = 0;                               // 数组下界。
  int high = 0;                              // 数组上界。
  TypeSpecPtr elementType;                   // 数组元素类型。
  std::vector<FieldDecl> fields;             // 记录类型的字段列表。

  // 统一 Visitor 入口，便于打印、语义分析和代码生成阶段复用。
  void accept(AstVisitor& visitor) const;
};

// 类型定义，例如 `type myInt = integer;`。
struct TypeDecl {
  int line = 1;
  std::string name; // 新定义的类型名。
  TypeSpecPtr type; // 实际映射到的类型说明。
};

// 变量声明，例如 `var x, y: integer;`。
struct VarDecl {
  int line = 1;
  TypeSpecPtr type;               // 变量类型。
  std::vector<std::string> names; // 同一条声明里的多个变量名。
};

// 形式参数声明，例如 `procedure p(var x: integer, y: char);`。
struct ParamDecl {
  int line = 1;
  bool byRef = false;             // 是否为 `var` 引用参数。
  TypeSpecPtr type;               // 参数类型。
  std::vector<std::string> names; // 参数名列表。
};

struct Expr;
using ExprPtr = std::unique_ptr<Expr>;

// 变量访问链中的一个步骤。
// 例如 `a[i].x` 会拆成“先下标访问，再字段访问”两段。
struct VarAccess {
  enum class Kind { Index, Field };
  Kind kind = Kind::Index;
  int line = 1;
  std::string fieldName; // 当 kind=Field 时记录字段名。
  ExprPtr index;         // 当 kind=Index 时记录下标表达式。
};

// 表达式节点的种类。
enum class ExprKind { Op, IntConst, CharConst, Variable };

// 表达式 AST 节点。
struct Expr {
  ExprKind kind = ExprKind::IntConst;
  int line = 1;
  LexType op = TK_ERROR;         // 当 kind=Op 时记录具体运算符。
  int intValue = 0;              // 整数常量值。
  char charValue = '\0';         // 字符常量值。
  std::string name;              // 当 kind=Variable 时记录变量名。
  std::vector<VarAccess> access; // 变量后续的数组/记录访问链。
  ExprPtr left;                  // 二元表达式左子树。
  ExprPtr right;                 // 二元表达式右子树。

  void accept(AstVisitor& visitor) const;
};

struct Stmt;
using StmtPtr = std::unique_ptr<Stmt>;

// 语句节点的种类。
enum class StmtKind { Assign, Call, If, While, Read, Write, Return };

// 语句 AST 节点。
struct Stmt {
  StmtKind kind = StmtKind::Assign;
  int line = 1;
  std::string name;               // 目标变量名或过程名。
  ExprPtr lhs;                    // 赋值语句左值。
  ExprPtr expr;                   // 赋值右侧、write 参数、return 值等主表达式。
  ExprPtr cond;                   // if / while 的条件表达式。
  std::vector<ExprPtr> args;      // 过程调用实参列表。
  std::vector<StmtPtr> thenPart;  // if 的 then 分支。
  std::vector<StmtPtr> elsePart;  // if 的 else 分支。
  std::vector<StmtPtr> body;      // while 或过程体中的语句序列。

  void accept(AstVisitor& visitor) const;
};

struct ProcDecl;

// 声明区块，统一承载 type / var / procedure 三类声明。
struct DeclPart {
  std::vector<TypeDecl> types;
  std::vector<VarDecl> vars;
  std::vector<ProcDecl> procs;
};

// 过程声明节点。
struct ProcDecl {
  int line = 1;
  std::string name;              // 过程名。
  std::vector<ParamDecl> params; // 形参列表。
  DeclPart decls;                // 局部声明区。
  std::vector<StmtPtr> body;     // 过程体语句序列。

  void accept(AstVisitor& visitor) const;
};

// 整个 SNL 程序的根节点。
struct ProgramNode {
  int line = 1;
  std::string name;          // 程序名。
  DeclPart decls;            // 全局声明区。
  std::vector<StmtPtr> body; // 主程序执行语句序列。

  void accept(AstVisitor& visitor) const;
};

// AST 访问者接口。
// 词法之后的多个阶段都用 Visitor 统一遍历 AST，避免在节点类中混入不同职责。
class AstVisitor {
public:
  virtual ~AstVisitor() = default;
  virtual void visit(const ProgramNode& node) = 0;
  virtual void visit(const ProcDecl& node) = 0;
  virtual void visit(const Stmt& node) = 0;
  virtual void visit(const Expr& node) = 0;
  virtual void visit(const TypeSpec& node) = 0;
};

#endif
