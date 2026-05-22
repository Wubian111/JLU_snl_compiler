#ifndef SNL_LEXER_H
#define SNL_LEXER_H

#include "snl_token.h"

#include <string>
#include <vector>

// 词法分析器的 C++ 包装层。
// 底层实际扫描逻辑由 Flex 生成，这个类负责把接口整理成项目中统一使用的形式。
class SNLLexer {
public:
  // 传入待分析的完整源代码文本。
  explicit SNLLexer(std::string sourceCode);

  // 执行词法分析并返回 token 序列。
  std::vector<Token> tokenize();

  // 获取词法分析阶段累计的错误信息。
  const std::vector<std::string>& get_errors() const;

private:
  std::string src;                 // 源代码缓冲区。
  std::vector<std::string> errors; // 词法错误列表。
};

#endif
