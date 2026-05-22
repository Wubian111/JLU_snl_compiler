#ifndef SNL_PARSER_H
#define SNL_PARSER_H

#include "snl_ast.h"
#include "snl_token.h"

#include <stdexcept>
#include <string>
#include <vector>

// 当语法分析器遇到致命错误时抛出的异常。
class ParseFailure : public std::runtime_error {
public:
  explicit ParseFailure(const std::string& msg);
};

// 语法分析器包装类。
// 它把词法阶段产生的 token 流交给 Bison 生成的 LALR 分析器，最终构造 AST。
class Parser {
public:
  explicit Parser(const std::vector<Token>& tokenStream);

  // 启动语法分析，成功时返回程序根节点。
  ProgramNode parse_program();

  // 获取分析阶段收集到的语法错误。
  const std::vector<std::string>& get_errors() const;

private:
  const std::vector<Token>& tokens; // 词法阶段输出的 token 流。
  std::vector<std::string> errors;  // 语法错误列表。
};

#endif
