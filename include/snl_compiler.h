#ifndef SNL_COMPILER_H
#define SNL_COMPILER_H

#include "snl_ast.h"
#include "snl_token.h"

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

// 编译器外观类（Facade）。
// 它把词法、语法、语义和目标代码生成四个阶段串成一条完整流水线，
class SNLCompiler {
public:
  // 运行完整编译流程。
  // 返回 0 表示成功，非 0 表示在某个阶段出现错误并提前终止。
  int run(const std::string& sourcePath, std::ostream& out, std::ostream& err,
          const std::string& mipsOutputPath = "");

private:
  // 前端阶段的中间结果。
  // 词法阶段输出 token 序列，语法阶段在此基础上补充 AST 根节点。
  struct FrontendResult {
    std::vector<Token> tokens;
    std::unique_ptr<ProgramNode> program;
  };

  // 将源文件完整读入内存，供后续阶段统一处理。
  static bool read_file(const std::string& path, std::string& content);

  // Phase 1: 词法分析，输出 token 流。
  static bool run_lexical_phase(const std::string& sourceCode,
                                const std::string& sourceName,
                                FrontendResult& result,
                                std::ostream& out,
                                std::ostream& err);

  // Phase 2: 语法分析，输出 AST。
  static bool run_syntax_phase(FrontendResult& result,
                               std::ostream& out,
                               std::ostream& err);

  // Phase 3: 语义分析，构建符号表并执行类型检查。
  static bool run_semantic_phase(const ProgramNode& program,
                                 std::ostream& out,
                                 std::ostream& err);

  // Phase 4: 目标代码生成，输出 MIPS 汇编。
  static bool run_mips_phase(const ProgramNode& program,
                             const std::string& mipsOutputPath,
                             std::ostream& out,
                             std::ostream& err);

  // 统一格式输出某个阶段收集到的全部错误。
  static void print_error_block(const std::string& title,
                                const std::vector<std::string>& errors,
                                std::ostream& err);

  // 打印词法分析结果，便于展示 scanner 的输出。
  static void print_token_list(const std::vector<Token>& tokens,
                               const std::string& sourceName,
                               std::ostream& out);
};

#endif
