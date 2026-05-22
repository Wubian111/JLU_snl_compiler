#ifndef SNL_SEMANTIC_H
#define SNL_SEMANTIC_H

#include "snl_ast.h"

#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <vector>

// 语义分析阶段内部使用的类型类别。
// 相比语法树中的 TypeSpec，这里是解析并展开后的“语义类型”。
enum class TypeKind { Integer, Char, Boolean, Array, Record, Void, Error };

struct Type;
using TypePtr = std::shared_ptr<Type>;

// 记录类型中单个字段的语义信息。
struct FieldInfo {
  int line = 1; // 字段声明所在行号。
  TypePtr type; // 字段的语义类型。
};

// 语义分析阶段的类型对象。
// 它承载类型比较所需的结构化信息，例如数组范围和记录字段表。
struct Type {
  TypeKind kind = TypeKind::Error;         // 类型类别。
  int low = 0;                             // 数组下界。
  int high = 0;                            // 数组上界。
  TypePtr elementType;                     // 数组元素类型。
  std::map<std::string, FieldInfo> fields; // 记录字段映射表。
};

// 符号表项目的类别。
enum class SymKind { Type, Var, Proc };

// 过程参数的语义信息。
struct ParamInfo {
  std::string name; // 参数名。
  TypePtr type;     // 参数类型。
  bool byRef = false; // 是否为引用参数。
};

// 符号表中的一项。
struct Symbol {
  SymKind kind = SymKind::Var;   // 当前符号代表类型、变量还是过程。
  std::string name;              // 符号名。
  TypePtr type;                  // 符号关联类型。
  std::vector<ParamInfo> params; // 当符号是过程时，保存其参数列表。
  int line = 1;                  // 声明出现的行号。
};

// 作用域节点。
// 语义分析器通过 parent 指针形成作用域链，实现嵌套过程中的标识符查找。
struct Scope {
  std::string name;                      // 作用域名称，通常是“全局”或某个过程名。
  int level = 0;                         // 嵌套层级，越深表示越内层。
  Scope* parent = nullptr;               // 父作用域指针。
  std::map<std::string, Symbol> symbols; // 当前作用域中的符号集合。
};

// 语义分析器负责三类核心工作：
// 1. 建立和维护符号表。
// 2. 检查类型一致性、标识符合法性、参数匹配等语义规则。
// 3. 输出结构化符号表。
class SemanticAnalyzer : public AstVisitor {
public:
  SemanticAnalyzer();

  // 以程序根节点为入口执行完整语义检查。
  void analyze(const ProgramNode& program);

  // 返回累计的语义错误列表。
  const std::vector<std::string>& get_errors() const;

  // 将各层作用域中的符号整理输出，便于验证分析结果。
  void print_symbol_table(std::ostream& out) const;

  // Visitor 分发函数。
  void visit(const ProgramNode& node) override;
  void visit(const ProcDecl& node) override;
  void visit(const Stmt& node) override;
  void visit(const Expr& node) override;
  void visit(const TypeSpec& node) override;

private:
  // 表达式求值结果。
  // 语义分析不执行真正运行时求值，但会记录类型、左值属性和常量属性。
  struct ExprResult {
    TypePtr type;
    bool isVariable = false;
    bool isConstInt = false;
    int constInt = 0;
  };

  std::vector<std::unique_ptr<Scope>> scopes; // 记录所有作用域，便于最终打印。
  Scope* current = nullptr;                   // 当前正在分析的作用域。
  std::vector<std::string> errors;           // 收集到的语义错误。
  TypePtr intType;                           // 内建 integer 类型。
  TypePtr charType;                          // 内建 char 类型。
  TypePtr boolType;                          // 比较表达式生成的布尔类型。
  TypePtr voidType;                          // 过程返回的占位类型。
  TypePtr errorType;                         // 错误恢复用的哨兵类型。
  ExprResult lastExpr;                       // Visitor 遍历时暂存最近一次表达式结果。

  // 创建内建类型对象。
  static TypePtr make_builtin(TypeKind kind);

  // 进入/退出一层作用域。
  void push_scope(const std::string& name);
  void pop_scope();

  // 统一记录一条语义错误。
  void report(int line, const std::string& message);

  // 向当前作用域插入符号；若重名则报错。
  bool insert_symbol(const Symbol& sym);

  // 按静态作用域规则查找符号。
  Symbol* lookup(const std::string& name);
  Symbol* lookup_current(const std::string& name);

  // 把内部枚举和值转成可展示文本。
  static std::string symbol_kind_name(SymKind kind);
  std::string type_to_string(const TypePtr& type) const;

  // 判断两个语义类型是否兼容。
  bool same_type(const TypePtr& a, const TypePtr& b) const;

  // 将语法树中的类型说明解析为语义类型。
  TypePtr resolve_type_spec(const TypeSpecPtr& spec);
  TypePtr resolve_type_spec(const TypeSpec& spec);

  // 把参数声明展开成按顺序排列的一维参数表。
  std::vector<ParamInfo> flatten_params(const std::vector<ParamDecl>& decls);

  // 处理一整块声明区。
  void process_decl_part(const DeclPart& decls);

  // 递归分析过程体。
  void analyze_proc(const ProcDecl& proc);

  // 顺序分析语句列表。
  void analyze_stmt_list(const std::vector<StmtPtr>& list);
  void analyze_stmt(const Stmt& stmt);

  // 针对 read / call 单独做规则检查。
  void analyze_read(const Stmt& stmt);
  void analyze_call(const Stmt& stmt);

  // 计算表达式的语义属性。
  ExprResult eval_expr(const Expr& expr);
  ExprResult eval_op(const Expr& expr);
  ExprResult eval_variable(const Expr& expr);
};

#endif
