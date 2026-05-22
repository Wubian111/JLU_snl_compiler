#include "snl_parser.h"

#include "snl_parser_driver.h"
#include "snl_parser_generated.h"

#include <utility>

ParseFailure::ParseFailure(const std::string& msg) : std::runtime_error(msg) {}

Parser::Parser(const std::vector<Token>& tokenStream)
    : tokens(tokenStream) {}

ProgramNode Parser::parse_program() {
  // Driver 是手写包装层，用来在 token 数组和 Bison 分析器之间传递上下文。
  snl::ParserDriver driver(tokens);
  try {
    snl::BisonParser parser(driver);

    // Bison 会不断回调 yylex，从 driver 中按顺序读取 token 并归约生成 AST。
    int status = parser.parse();

    errors = driver.errors;
    if (status != 0) {
      std::string message = errors.empty() ? "语法错误" : errors.front();
      throw ParseFailure(message);
    }
  } catch (const snl::BisonParser::syntax_error& ex) {
    errors = driver.errors;
    if (errors.empty()) errors.push_back(ex.what());
    throw ParseFailure(errors.front());
  } catch (const std::exception& ex) {
    errors = driver.errors;
    if (errors.empty()) errors.push_back(ex.what());
    throw ParseFailure(errors.front());
  }

  // 将构造好的程序根节点移动给调用方。
  return std::move(driver.result);
}

const std::vector<std::string>& Parser::get_errors() const {
  return errors;
}
