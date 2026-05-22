#ifndef SNL_GENERATED_LEXER_H
#define SNL_GENERATED_LEXER_H

#include "snl_token.h"

#include <string>
#include <vector>

std::vector<Token> snl_flex_tokenize(const std::string& source,
                                     std::vector<std::string>& errors);

#endif
