/* ====== Flex 配置选项 ====== */
/* noyywrap: 不使用 yywrap()。当扫描到 EOF 时认为全部结束。
   nounput, noinput: 禁用 unput 和 input 函数以避免未使用警告。
   never-interactive: 告诉 Flex 此扫描器始终读取非交互式文件流，优化读取性能。
   prefix="snl_": 更改 Flex 默认生成的函数和结构名前缀 (如 yytext -> snl_text，yylex -> snl_lex)，避免与其他解析器冲突。 */
%option noyywrap nounput noinput never-interactive prefix="snl_"

%{
#include "snl_generated_lexer.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

// 全局状态变量，用于在 Flex 分析期间维护当前行号和输出的目标容器
static int currentLine = 1;
static std::vector<Token>* tokenOutput = nullptr;
static std::vector<std::string>* errorOutput = nullptr;

// 辅助函数：将字符串转换为小写（SNL 对大小写不敏感）
static std::string lower_copy(const char* text) {
  std::string s(text);
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return s;
}

// 辅助函数：统计多行注释中的换行符数量，以保证行号准确
static int count_newlines(const char* text) {
  int count = 0;
  for (const char* p = text; *p; ++p) {
    if (*p == '\n') ++count;
  }
  return count;
}

// 辅助函数：识别小写后的字符串是否是关键字，否则作为标识符（ID）
static LexType keyword_type(const std::string& text) {
  if (text == "program") return TK_PROGRAM;
  if (text == "procedure") return TK_PROCEDURE;
  if (text == "type") return TK_TYPE;
  if (text == "var") return TK_VAR;
  if (text == "if") return TK_IF;
  if (text == "then") return TK_THEN;
  if (text == "else") return TK_ELSE;
  if (text == "fi") return TK_FI;
  if (text == "while") return TK_WHILE;
  if (text == "do") return TK_DO;
  if (text == "endwh") return TK_ENDWH;
  if (text == "begin") return TK_BEGIN;
  if (text == "end") return TK_END;
  if (text == "read") return TK_READ;
  if (text == "write") return TK_WRITE;
  if (text == "array") return TK_ARRAY;
  if (text == "of") return TK_OF;
  if (text == "record") return TK_RECORD;
  if (text == "return") return TK_RETURN;
  if (text == "integer") return TK_INTEGER;
  if (text == "char") return TK_CHAR;
  return TK_ID; // 如果不是上述任何关键字，则它是标识符
}

// 辅助函数：向词法流中添加一个无特殊值的标记 (Token)
static void add_token(LexType type, const char* text) {
  tokenOutput->push_back(Token{currentLine, type, std::string(text)});
}

// 辅助函数：向词法流中添加一个拥有语义值的标记（例如标识符、常数）
static void add_token_with_value(int line, LexType type, const std::string& text) {
  tokenOutput->push_back(Token{line, type, text});
}

// 辅助函数：记录词法错误，同时向 Token 序列中插入 TK_ERROR 保证后续解析不崩溃
static void add_error(int line, const std::string& sem, const std::string& message) {
  std::ostringstream os;
  os << "第 " << line << " 行：" << message;
  if (!sem.empty()) os << "，附近 Token 为 '" << sem << "'";
  errorOutput->push_back(os.str());
  tokenOutput->push_back(Token{line, TK_ERROR, sem});
}
%}

%%
[ \t\r]+                         ; /* 忽略所有空白字符 */
\n                               { ++currentLine; } /* 遇到换行符时，增加当前行号计数 */
\{([^}\n]|\n)*\}                 { currentLine += count_newlines(yytext); } /* 匹配多行注释 {}，计算其中的换行符 */
\}                               { add_error(currentLine, yytext, "多余的注释结束符"); yyterminate(); } /* 匹配到没有前驱的 }，报错退出 */
\{([^}\n]|\n)*                   { add_error(currentLine, "{", "注释未闭合"); currentLine += count_newlines(yytext); yyterminate(); } /* 匹配到文件末尾还未闭合的注释 */
[A-Za-z][A-Za-z0-9_]*            { /* 匹配标识符或关键字 */
                                   std::string text = lower_copy(yytext);
                                   add_token(keyword_type(text), yytext);
                                 }
[0-9]+[A-Za-z_][A-Za-z0-9_]*     { add_error(currentLine, yytext, "非法整数常量"); yyterminate(); } /* 以数字开头的标识符视为非法 */
[0-9]+                           { add_token(TK_INTC, yytext); } /* 匹配整数常量 */
'[^'\n]'                         { /* 匹配单个字符的字符常量，如 'a' */
                                   std::string text(yytext + 1, yytext + yyleng - 1);
                                   add_token_with_value(currentLine, TK_CHARC, text);
                                 }
'[^'\n]*'                        { /* 匹配长度大于 1 的字符常量（如 'adc'），报错 */
                                   std::string text(yytext + 1, yytext + yyleng - 1);
                                   if (!text.empty()) text.pop_back();
                                   add_error(currentLine, text, "字符常量必须且只能包含一个字符");
                                   yyterminate();
                                 }
'[^'\n]*                         { add_error(currentLine, yytext, "字符常量未闭合"); yyterminate(); } /* 匹配少了一半单引号的字符常量 */
":="                             { add_token(TK_ASSIGN, yytext); }  /* 赋值符号 */
".."                             { add_token(TK_DOTDOT, yytext); }  /* 数组范围符 */
"="                              { add_token(TK_EQ, yytext); }
"<"                              { add_token(TK_LT, yytext); }
"+"                              { add_token(TK_PLUS, yytext); }
"-"                              { add_token(TK_MINUS, yytext); }
"*"                              { add_token(TK_STAR, yytext); }
"/"                              { add_token(TK_DIV, yytext); }
"("                              { add_token(TK_LPAREN, yytext); }
")"                              { add_token(TK_RPAREN, yytext); }
"["                              { add_token(TK_LBRACKET, yytext); }
"]"                              { add_token(TK_RBRACKET, yytext); }
"."                              { add_token(TK_DOT, yytext); }
","                              { add_token(TK_COMMA, yytext); }
";"                              { add_token(TK_SEMI, yytext); }
":"                              { add_token(TK_COLON, yytext); }
.                                { add_error(currentLine, yytext, "无法识别的字符"); yyterminate(); } /* 捕获任何没有预定义的特殊非法字符 */
<<EOF>>                          { tokenOutput->push_back(Token{currentLine, TK_EOF_TOKEN, ""}); yyterminate(); } /* 达到文件末尾，发送 EOF Token */
%%

// Flex 初始化及主入口函数：接收源代码字符串，返回 Token 流
std::vector<Token> snl_flex_tokenize(const std::string& source,
                                     std::vector<std::string>& errors) {
  std::vector<Token> tokens;
  currentLine = 1;         // 重置行号
  tokenOutput = &tokens;   // 绑定输出目标
  errorOutput = &errors;

  // 将字符串装载到 Flex 内存缓冲区中进行扫描
  YY_BUFFER_STATE buffer = snl__scan_bytes(source.data(),
                                           static_cast<int>(source.size()));
  snl_lex();               // 启动词法分析
  snl__delete_buffer(buffer); // 清理内存

  tokenOutput = nullptr;
  errorOutput = nullptr;
  return tokens;
}
