#ifndef SNL_PARSER_DRIVER_H
#define SNL_PARSER_DRIVER_H

#include "snl_ast.h"
#include "snl_token.h"

#include <string>
#include <vector>

namespace snl {

class ParserDriver {
public:
  explicit ParserDriver(const std::vector<Token>& tokenStream)
      : tokens(tokenStream) {}

  const std::vector<Token>& tokens;
  size_t pos = 0;
  Token lookahead;
  ProgramNode result;
  std::vector<std::string> errors;
};

}  // namespace snl

#endif
