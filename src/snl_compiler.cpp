#include "snl_compiler.h"

#include "snl_lexer.h"
#include "snl_mips_generator.h"
#include "snl_parser.h"
#include "snl_semantic.h"
#include "snl_syntax_tree_printer.h"

#include <fstream>
#include <iomanip>
#include <sstream>

int SNLCompiler::run(const std::string& sourcePath, std::ostream& out, std::ostream& err,
                     const std::string& mipsOutputPath) {
  std::string sourceCode;
  // 第一步先把源文件完整读入内存，后续所有阶段共享这一份文本。
  if (!read_file(sourcePath, sourceCode)) {
    err << "错误：无法打开文件 '" << sourcePath << "'\n";
    return 1;
  }

  FrontendResult result;
  // 四个阶段按顺序串行执行，任何一步失败都立即终止。
  if (!run_lexical_phase(sourceCode, sourcePath, result, out, err)) return 1;
  if (!run_syntax_phase(result, out, err)) return 1;
  if (!run_semantic_phase(*result.program, out, err)) return 1;
  if (!run_mips_phase(*result.program, mipsOutputPath, out, err)) return 1;
  return 0;
}

bool SNLCompiler::read_file(const std::string& path, std::string& content) {
  // 依赖 ifstream 的 RAII 机制自动管理文件句柄。
  std::ifstream file(path);
  if (!file.is_open()) return false;

  // 利用字符串流一次性收集整个文件内容，便于后续词法分析统一处理。
  std::stringstream buffer;
  buffer << file.rdbuf();
  content = buffer.str();
  return true;
}

bool SNLCompiler::run_lexical_phase(const std::string& sourceCode,
                                    const std::string& sourceName,
                                    FrontendResult& result,
                                    std::ostream& out,
                                    std::ostream& err) {
  SNLLexer lexer(sourceCode);
  result.tokens = lexer.tokenize();
  print_token_list(result.tokens, sourceName, out);

  if (!lexer.get_errors().empty()) {
    print_error_block("词法错误", lexer.get_errors(), err);
    return false;
  }
  return true;
}

bool SNLCompiler::run_syntax_phase(FrontendResult& result,
                                   std::ostream& out,
                                   std::ostream& err) {
  try {
    Parser parser(result.tokens);
    // 语法分析成功后，得到整个程序对应的 AST 根节点。
    result.program = std::make_unique<ProgramNode>(parser.parse_program());
  } catch (const ParseFailure& ex) {
    err << "\n===== 语法错误 =====\n";
    err << ex.what() << "\n";
    return false;
  }

  out << "\n===== 语法树 =====\n";
  print_syntax_tree(*result.program, out);
  return true;
}

bool SNLCompiler::run_semantic_phase(const ProgramNode& program,
                                     std::ostream& out,
                                     std::ostream& err) {
  // 语义分析阶段负责建立符号表并做类型检查。
  SemanticAnalyzer semantic;
  semantic.analyze(program);
  out << "\n";
  semantic.print_symbol_table(out);

  if (!semantic.get_errors().empty()) {
    print_error_block("语义错误", semantic.get_errors(), err);
    return false;
  }

  out << "\n语义分析：无错误。\n";
  return true;
}

bool SNLCompiler::run_mips_phase(const ProgramNode& program,
                                 const std::string& mipsOutputPath,
                                 std::ostream& out,
                                 std::ostream& err) {
  // 没有传入输出路径时，说明本次只做前端分析。
  if (mipsOutputPath.empty()) return true;

  std::ofstream asmFile(mipsOutputPath);
  if (!asmFile.is_open()) {
    err << "错误：无法创建 MIPS 输出文件 '" << mipsOutputPath << "'\n";
    return false;
  }

  MipsGenerator generator(asmFile);
  generator.generate(program);
  asmFile.close();

  if (!generator.get_errors().empty()) {
    print_error_block("MIPS 生成错误", generator.get_errors(), err);
    return false;
  }

  out << "MIPS 汇编已生成：" << mipsOutputPath << "\n";
  return true;
}

void SNLCompiler::print_error_block(const std::string& title,
                                    const std::vector<std::string>& errors,
                                    std::ostream& err) {
  err << "\n===== " << title << " =====\n";
  for (const auto& message : errors) err << message << "\n";
}

void SNLCompiler::print_token_list(const std::vector<Token>& tokens,
                                   const std::string& sourceName,
                                   std::ostream& out) {
  out << "===== SNL 词法分析结果 =====\n";
  out << "源文件：" << sourceName << "\n";
  out << "---------------------------\n";
  size_t count = 0;
  for (const auto& tok : tokens) {
    if (tok.Lex == TK_EOF_TOKEN) continue;
    count++;
    out << "行号：" << std::left << std::setw(3) << tok.Lineshow
        << " | 词法：" << std::left << std::setw(10) << get_token_name(tok.Lex)
        << " | 语义值：" << tok.Sem << "\n";
  }
  out << "---------------------------\n";
  out << "共识别 " << count << " 个 Token。\n";
}
