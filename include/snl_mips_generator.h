#ifndef SNL_MIPS_GENERATOR_H
#define SNL_MIPS_GENERATOR_H

#include "snl_ast.h"

#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <vector>

// MIPS 代码生成器。
// 该类直接遍历 AST，把已经通过语义检查的程序翻译为面向 MARS 的 32 位 MIPS 汇编。
class MipsGenerator : public AstVisitor {
public:
  explicit MipsGenerator(std::ostream& output);

  // 生成完整程序的汇编代码。
  void generate(const ProgramNode& program);

  // 返回生成阶段累计的错误信息。
  const std::vector<std::string>& get_errors() const;

  // Visitor 分发函数。
  void visit(const ProgramNode& node) override;
  void visit(const ProcDecl& node) override;
  void visit(const Stmt& node) override;
  void visit(const Expr& node) override;
  void visit(const TypeSpec& node) override;

private:
  // 代码生成阶段内部使用的类型表示。
  // 这里更关心对象布局，例如占用字数、元素类型和字段偏移。
  struct MipsType {
    enum class Kind { Integer, Char, Array, Record, Unsupported };
    Kind kind = Kind::Unsupported;
    int low = 0;   // 数组下界。
    int high = 0;  // 数组上界。
    int words = 1; // 当前对象占用的机器字数。
    std::shared_ptr<MipsType> elementType; // 数组元素类型。
    struct FieldInfo {
      int offsetWords = 0;            // 字段相对记录首地址的偏移量，单位为字。
      std::shared_ptr<MipsType> type; // 字段类型。
    };
    std::map<std::string, FieldInfo> fields; // 记录字段布局。
  };

  // 变量在目标代码中的存储信息。
  struct VarInfo {
    enum class Storage { Global, FrameValue, FrameRef };
    Storage storage = Storage::Global; // 全局区、当前栈帧值对象、或引用参数。
    std::string label;                 // 全局变量标签名。
    int offset = 0;                    // 栈帧中的字节偏移。
    MipsType type;                     // 变量类型布局。
  };

  // 过程参数在目标代码中的传递信息。
  struct ParamCodeInfo {
    std::string name;
    bool byRef = false;
    int line = 1;
    int offset = 0; // 参数在当前过程栈帧中的偏移。
    MipsType type;
  };

  // 过程入口信息，供调用和定义两个阶段共享。
  struct ProcInfo {
    std::string label;
    std::vector<ParamCodeInfo> params;
    const ProcDecl* decl = nullptr;
  };

  std::ostream& out;                                        // 汇编输出流。
  std::vector<std::map<std::string, MipsType>> typeScopes;  // 类型别名作用域栈。
  std::vector<std::map<std::string, VarInfo>> varScopes;    // 变量作用域栈。
  std::map<std::string, VarInfo> globals;                   // 全局变量表。
  std::map<std::string, ProcInfo> procs;                    // 过程签名表。
  std::vector<std::string> errors;                          // 生成阶段错误。
  int labelCounter = 0;                                     // 自动标签编号。
  std::vector<std::string> returnLabels;                    // 当前过程返回跳转目标栈。

  // 记录生成错误并附带源代码行号。
  void report(int line, const std::string& message);

  // 生成唯一标签，并把任意标识符转成安全标签名。
  std::string new_label(const std::string& prefix);
  static std::string safe_label(const std::string& name);

  // 维护类型和变量两套作用域环境。
  void push_type_scope();
  void pop_type_scope();
  void add_type_aliases(const DeclPart& decls);
  bool lookup_type_alias(const std::string& name, MipsType& type) const;
  void push_var_scope();
  void pop_var_scope();
  bool lookup_var(const std::string& name, VarInfo& info) const;

  // 预收集全局对象和过程签名，为后续生成提供布局信息。
  void collect_global_decls(const DeclPart& decls);
  void collect_proc_signatures(const DeclPart& decls);

  // 生成单个过程及其局部变量布局。
  void emit_proc(const ProcDecl& proc);
  int add_local_vars(const DeclPart& decls);

  // 将语法树类型说明解析成目标代码布局类型。
  MipsType resolve_type(const TypeSpecPtr& spec);
  MipsType resolve_type(const TypeSpec& spec);
  int storage_words(const MipsType& type) const;

  // 各类语句和表达式的代码生成入口。
  void gen_stmt_list(const std::vector<StmtPtr>& list);
  void gen_stmt(const Stmt& stmt);
  void gen_assign(const Stmt& stmt);
  void gen_read(const Stmt& stmt);
  void gen_write(const Stmt& stmt);
  void gen_if(const Stmt& stmt);
  void gen_while(const Stmt& stmt);
  void gen_expr(const Expr& expr);
  void gen_binary_expr(const Expr& expr);

  // 计算左值地址，供赋值、传引用和数组/记录访问使用。
  void gen_address(const Expr& expr);

  // 用运行时栈临时保存中间值，避免表达式递归生成时覆盖寄存器。
  void push_t0();
  void pop_to(const std::string& reg);
};

#endif
