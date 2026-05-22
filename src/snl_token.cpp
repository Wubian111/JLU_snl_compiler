#include "snl_token.h"

// 将内部枚举翻译成人类可读的名字，主要用于打印 token 列表和报错信息。
std::string get_token_name(LexType type) {
  switch (type) {
    case TK_PROGRAM:   return "PROGRAM";
    case TK_PROCEDURE: return "PROCEDURE";
    case TK_TYPE:      return "TYPE";
    case TK_VAR:       return "VAR";
    case TK_IF:        return "IF";
    case TK_THEN:      return "THEN";
    case TK_ELSE:      return "ELSE";
    case TK_FI:        return "FI";
    case TK_WHILE:     return "WHILE";
    case TK_DO:        return "DO";
    case TK_ENDWH:     return "ENDWH";
    case TK_BEGIN:     return "BEGIN";
    case TK_END:       return "END";
    case TK_READ:      return "READ";
    case TK_WRITE:     return "WRITE";
    case TK_ARRAY:     return "ARRAY";
    case TK_OF:        return "OF";
    case TK_RECORD:    return "RECORD";
    case TK_RETURN:    return "RETURN";
    case TK_INTEGER:   return "INTEGER";
    case TK_CHAR:      return "CHAR";
    case TK_ID:        return "ID";
    case TK_INTC:      return "INTC";
    case TK_CHARC:     return "CHARC";
    case TK_ASSIGN:    return "ASSIGN";
    case TK_EQ:        return "EQ";
    case TK_LT:        return "LT";
    case TK_PLUS:      return "PLUS";
    case TK_MINUS:     return "MINUS";
    case TK_STAR:      return "STAR";
    case TK_DIV:       return "DIV";
    case TK_LPAREN:    return "LPAREN";
    case TK_RPAREN:    return "RPAREN";
    case TK_LBRACKET:  return "LBRACKET";
    case TK_RBRACKET:  return "RBRACKET";
    case TK_DOT:       return "DOT";
    case TK_DOTDOT:    return "DOTDOT";
    case TK_COMMA:     return "COMMA";
    case TK_SEMI:      return "SEMI";
    case TK_COLON:     return "COLON";
    case TK_EOF_TOKEN: return "EOF";
    default:           return "ERROR";
  }
}
