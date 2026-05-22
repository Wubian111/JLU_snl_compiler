#include "snl_lexer.h"

#include "snl_generated_lexer.h"

#include <utility>

SNLLexer::SNLLexer(std::string sourceCode)
    : src(std::move(sourceCode)) {}

std::vector<Token> SNLLexer::tokenize() {
  // 每次重新分析前先清空旧错误，保证该对象可重复使用。
  errors.clear();

  // 真正的扫描逻辑由 Flex 生成，这里只做输入封装和错误转存。
  return snl_flex_tokenize(src, errors);
}

const std::vector<std::string>& SNLLexer::get_errors() const {
  return errors;
}
