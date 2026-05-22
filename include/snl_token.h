#ifndef SNL_TOKEN_H
#define SNL_TOKEN_H

#include <string>

// SNL 语言全部词法单元的枚举定义。
// 词法分析阶段会把源程序切分成这些记号，后续语法分析直接消费该枚举。
enum LexType {
  // 关键字。
  TK_PROGRAM = 1, TK_PROCEDURE, TK_TYPE, TK_VAR, TK_IF, TK_THEN, TK_ELSE, TK_FI,
  TK_WHILE, TK_DO, TK_ENDWH, TK_BEGIN, TK_END, TK_READ, TK_WRITE, TK_ARRAY,
  TK_OF, TK_RECORD, TK_RETURN, TK_INTEGER, TK_CHAR,

  // 标识符与常量。
  TK_ID,    // 标识符，例如变量名、类型名、过程名。
  TK_INTC,  // 整数字面量，例如 123。
  TK_CHARC, // 字符字面量，例如 'a'。

  // 运算符与界符。
  TK_ASSIGN,   // :=
  TK_EQ,       // =
  TK_LT,       // <
  TK_PLUS,     // +
  TK_MINUS,    // -
  TK_STAR,     // *
  TK_DIV,      // /
  TK_LPAREN,   // (
  TK_RPAREN,   // )
  TK_LBRACKET, // [
  TK_RBRACKET, // ]
  TK_DOT,      // .
  TK_DOTDOT,   // ..（数组范围）
  TK_COMMA,    // ,
  TK_SEMI,     // ;
  TK_COLON,    // :

  TK_ERROR,    // 词法错误标记。
  TK_EOF_TOKEN // 文件结束标记。
};

// 词法单元的统一表示。
// 该结构会在词法分析与语法分析之间传递，既保存类别，也保存原始词素和值所在行号。
struct Token {
  int Lineshow = 1;       // 当前 token 在源程序中的行号。
  LexType Lex = TK_ERROR; // token 的词法类别。
  std::string Sem;        // token 对应的原始语义串，例如标识符名或常量文本。
};

// 将枚举值转换成人可读的名称，便于打印词法结果和错误信息。
std::string get_token_name(LexType type);

#endif
