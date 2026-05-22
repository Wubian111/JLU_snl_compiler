// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "snl_parser_generated.h"


// Unqualified %code blocks.
#line 30 "grammar/snl_parser.y"

#include <sstream>
#include <utility>

namespace snl {

// 辅助函数：创建一个基础 TypeSpec 节点并设好行号
static TypeSpecPtr make_type(TypeSpecKind kind, int line) {
  auto type = std::make_shared<TypeSpec>();
  type->kind = kind;
  type->line = line;
  return type;
}

// 辅助函数：将被解析成词法的数字字符串转成 int 整型
static int parse_int(const Token& tok) {
  try {
    return std::stoi(tok.Sem);
  } catch (...) {
    return 0; // 若转换失败默认返回 0
  }
}

// 辅助函数：构造一个“变量访问”类型的表达式节点
static ExprPtr make_variable_expr(const Token& tok) {
  auto expr = std::make_unique<Expr>();
  expr->kind = ExprKind::Variable;
  expr->line = tok.Lineshow;
  expr->name = tok.Sem;
  return expr;
}

// 辅助函数：构造一个二元操作符表达式节点并连接其左右操作数
static ExprPtr make_op_expr(const Token& op, ExprPtr left, ExprPtr right) {
  auto expr = std::make_unique<Expr>();
  expr->kind = ExprKind::Op;
  expr->line = op.Lineshow;
  expr->op = op.Lex;
  expr->left = std::move(left);
  expr->right = std::move(right);
  return expr;
}

// 辅助函数：构造一条指定语句类型的空白语句节点
static StmtPtr make_stmt(StmtKind kind, int line) {
  auto stmt = std::make_unique<Stmt>();
  stmt->kind = kind;
  stmt->line = line;
  return stmt;
}

// 自定义词法拉取函数 (yylex)
// 它代替了传统的 flex 集成，改为从外部预先分好的 Token 队列中按顺序取出 Token 供给 Bison 语法分析
static BisonParser::symbol_type yylex(ParserDriver& driver) {
  Token tok = driver.pos < driver.tokens.size()
                  ? driver.tokens[driver.pos++]
                  : Token{driver.lookahead.Lineshow, TK_EOF_TOKEN, ""};
  driver.lookahead = tok;
  
  // 将我们自定义的 LexType 枚举映射进 Bison 生成的各 make_XXX 对应标志返回
  switch (tok.Lex) {
    case TK_PROGRAM: return BisonParser::make_PROGRAM(tok);
    case TK_PROCEDURE: return BisonParser::make_PROCEDURE(tok);
    case TK_TYPE: return BisonParser::make_TYPE(tok);
    case TK_VAR: return BisonParser::make_VAR(tok);
    case TK_IF: return BisonParser::make_IF(tok);
    case TK_THEN: return BisonParser::make_THEN(tok);
    case TK_ELSE: return BisonParser::make_ELSE(tok);
    case TK_FI: return BisonParser::make_FI(tok);
    case TK_WHILE: return BisonParser::make_WHILE(tok);
    case TK_DO: return BisonParser::make_DO(tok);
    case TK_ENDWH: return BisonParser::make_ENDWH(tok);
    case TK_BEGIN: return BisonParser::make_BEGIN_K(tok);
    case TK_END: return BisonParser::make_END_K(tok);
    case TK_READ: return BisonParser::make_READ(tok);
    case TK_WRITE: return BisonParser::make_WRITE(tok);
    case TK_ARRAY: return BisonParser::make_ARRAY(tok);
    case TK_OF: return BisonParser::make_OF(tok);
    case TK_RECORD: return BisonParser::make_RECORD(tok);
    case TK_RETURN: return BisonParser::make_RETURN(tok);
    case TK_INTEGER: return BisonParser::make_INTEGER(tok);
    case TK_CHAR: return BisonParser::make_CHAR(tok);
    case TK_ID: return BisonParser::make_ID(tok);
    case TK_INTC: return BisonParser::make_INTC(tok);
    case TK_CHARC: return BisonParser::make_CHARC(tok);
    case TK_ASSIGN: return BisonParser::make_ASSIGN(tok);
    case TK_EQ: return BisonParser::make_EQ(tok);
    case TK_LT: return BisonParser::make_LT(tok);
    case TK_PLUS: return BisonParser::make_PLUS(tok);
    case TK_MINUS: return BisonParser::make_MINUS(tok);
    case TK_STAR: return BisonParser::make_STAR(tok);
    case TK_DIV: return BisonParser::make_DIV(tok);
    case TK_LPAREN: return BisonParser::make_LPAREN(tok);
    case TK_RPAREN: return BisonParser::make_RPAREN(tok);
    case TK_LBRACKET: return BisonParser::make_LBRACKET(tok);
    case TK_RBRACKET: return BisonParser::make_RBRACKET(tok);
    case TK_DOT: return BisonParser::make_DOT(tok);
    case TK_DOTDOT: return BisonParser::make_DOTDOT(tok);
    case TK_COMMA: return BisonParser::make_COMMA(tok);
    case TK_SEMI: return BisonParser::make_SEMI(tok);
    case TK_COLON: return BisonParser::make_COLON(tok);
    case TK_ERROR: return BisonParser::make_ERROR_TOKEN(tok);
    case TK_EOF_TOKEN: return BisonParser::make_YYEOF();
  }
  return BisonParser::make_ERROR_TOKEN(tok);
}

// 错误汇报钩子：当 Bison 解析过程中发现无法匹配语法的状态时，生成错误消息
void BisonParser::error(const std::string&) {
  const Token& tok = driver.lookahead;
  std::ostringstream os;
  os << "第 " << tok.Lineshow << " 行：语法错误，当前 Token 为 "
     << get_token_name(tok.Lex);
  if (!tok.Sem.empty()) os << "('" << tok.Sem << "')";
  driver.errors.push_back(os.str());
}

}  // namespace snl

#line 166 "src/snl_parser_generated.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 8 "grammar/snl_parser.y"
namespace snl {
#line 240 "src/snl_parser_generated.cpp"

  /// Build a parser object.
  BisonParser::BisonParser (snl::ParserDriver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  BisonParser::~BisonParser ()
  {}

  BisonParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  BisonParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  BisonParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  BisonParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  BisonParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  BisonParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  BisonParser::symbol_kind_type
  BisonParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  BisonParser::stack_symbol_type::stack_symbol_type ()
  {}

  BisonParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_declare_part: // declare_part
        value.YY_MOVE_OR_COPY< DeclPart > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        value.YY_MOVE_OR_COPY< ExprPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.YY_MOVE_OR_COPY< FieldDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< ParamDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.YY_MOVE_OR_COPY< ProcDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< ProgramNode > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        value.YY_MOVE_OR_COPY< StmtPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
      case symbol_kind::S_PROCEDURE: // PROCEDURE
      case symbol_kind::S_TYPE: // TYPE
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_THEN: // THEN
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FI: // FI
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_DO: // DO
      case symbol_kind::S_ENDWH: // ENDWH
      case symbol_kind::S_BEGIN_K: // BEGIN_K
      case symbol_kind::S_END_K: // END_K
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_WRITE: // WRITE
      case symbol_kind::S_ARRAY: // ARRAY
      case symbol_kind::S_OF: // OF
      case symbol_kind::S_RECORD: // RECORD
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INTC: // INTC
      case symbol_kind::S_CHARC: // CHARC
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_DOTDOT: // DOTDOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_ERROR_TOKEN: // ERROR_TOKEN
      case symbol_kind::S_rel_op: // rel_op
      case symbol_kind::S_add_op: // add_op
      case symbol_kind::S_mul_op: // mul_op
        value.YY_MOVE_OR_COPY< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.YY_MOVE_OR_COPY< TypeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        value.YY_MOVE_OR_COPY< TypeSpecPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_access: // access
        value.YY_MOVE_OR_COPY< VarAccess > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.YY_MOVE_OR_COPY< VarDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        value.YY_MOVE_OR_COPY< std::vector<ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_list: // field_list
        value.YY_MOVE_OR_COPY< std::vector<FieldDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        value.YY_MOVE_OR_COPY< std::vector<ParamDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        value.YY_MOVE_OR_COPY< std::vector<ProcDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        value.YY_MOVE_OR_COPY< std::vector<StmtPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.YY_MOVE_OR_COPY< std::vector<TypeDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_access_list: // access_list
        value.YY_MOVE_OR_COPY< std::vector<VarAccess> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.YY_MOVE_OR_COPY< std::vector<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_id_list: // id_list
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  BisonParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_declare_part: // declare_part
        value.move< DeclPart > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        value.move< ExprPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< FieldDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ParamDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.move< ProcDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< ProgramNode > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        value.move< StmtPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
      case symbol_kind::S_PROCEDURE: // PROCEDURE
      case symbol_kind::S_TYPE: // TYPE
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_THEN: // THEN
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FI: // FI
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_DO: // DO
      case symbol_kind::S_ENDWH: // ENDWH
      case symbol_kind::S_BEGIN_K: // BEGIN_K
      case symbol_kind::S_END_K: // END_K
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_WRITE: // WRITE
      case symbol_kind::S_ARRAY: // ARRAY
      case symbol_kind::S_OF: // OF
      case symbol_kind::S_RECORD: // RECORD
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INTC: // INTC
      case symbol_kind::S_CHARC: // CHARC
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_DOTDOT: // DOTDOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_ERROR_TOKEN: // ERROR_TOKEN
      case symbol_kind::S_rel_op: // rel_op
      case symbol_kind::S_add_op: // add_op
      case symbol_kind::S_mul_op: // mul_op
        value.move< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< TypeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        value.move< TypeSpecPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_access: // access
        value.move< VarAccess > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< VarDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        value.move< std::vector<ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_list: // field_list
        value.move< std::vector<FieldDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        value.move< std::vector<ParamDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        value.move< std::vector<ProcDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        value.move< std::vector<StmtPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.move< std::vector<TypeDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_access_list: // access_list
        value.move< std::vector<VarAccess> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.move< std::vector<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_id_list: // id_list
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  BisonParser::stack_symbol_type&
  BisonParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_declare_part: // declare_part
        value.copy< DeclPart > (that.value);
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        value.copy< ExprPtr > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.copy< FieldDecl > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.copy< ParamDecl > (that.value);
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.copy< ProcDecl > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< ProgramNode > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        value.copy< StmtPtr > (that.value);
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
      case symbol_kind::S_PROCEDURE: // PROCEDURE
      case symbol_kind::S_TYPE: // TYPE
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_THEN: // THEN
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FI: // FI
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_DO: // DO
      case symbol_kind::S_ENDWH: // ENDWH
      case symbol_kind::S_BEGIN_K: // BEGIN_K
      case symbol_kind::S_END_K: // END_K
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_WRITE: // WRITE
      case symbol_kind::S_ARRAY: // ARRAY
      case symbol_kind::S_OF: // OF
      case symbol_kind::S_RECORD: // RECORD
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INTC: // INTC
      case symbol_kind::S_CHARC: // CHARC
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_DOTDOT: // DOTDOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_ERROR_TOKEN: // ERROR_TOKEN
      case symbol_kind::S_rel_op: // rel_op
      case symbol_kind::S_add_op: // add_op
      case symbol_kind::S_mul_op: // mul_op
        value.copy< Token > (that.value);
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.copy< TypeDecl > (that.value);
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        value.copy< TypeSpecPtr > (that.value);
        break;

      case symbol_kind::S_access: // access
        value.copy< VarAccess > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.copy< VarDecl > (that.value);
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        value.copy< std::vector<ExprPtr> > (that.value);
        break;

      case symbol_kind::S_field_list: // field_list
        value.copy< std::vector<FieldDecl> > (that.value);
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        value.copy< std::vector<ParamDecl> > (that.value);
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        value.copy< std::vector<ProcDecl> > (that.value);
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        value.copy< std::vector<StmtPtr> > (that.value);
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.copy< std::vector<TypeDecl> > (that.value);
        break;

      case symbol_kind::S_access_list: // access_list
        value.copy< std::vector<VarAccess> > (that.value);
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.copy< std::vector<VarDecl> > (that.value);
        break;

      case symbol_kind::S_id_list: // id_list
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  BisonParser::stack_symbol_type&
  BisonParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_declare_part: // declare_part
        value.move< DeclPart > (that.value);
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        value.move< ExprPtr > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< FieldDecl > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.move< ParamDecl > (that.value);
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.move< ProcDecl > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< ProgramNode > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        value.move< StmtPtr > (that.value);
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
      case symbol_kind::S_PROCEDURE: // PROCEDURE
      case symbol_kind::S_TYPE: // TYPE
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_THEN: // THEN
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FI: // FI
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_DO: // DO
      case symbol_kind::S_ENDWH: // ENDWH
      case symbol_kind::S_BEGIN_K: // BEGIN_K
      case symbol_kind::S_END_K: // END_K
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_WRITE: // WRITE
      case symbol_kind::S_ARRAY: // ARRAY
      case symbol_kind::S_OF: // OF
      case symbol_kind::S_RECORD: // RECORD
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INTC: // INTC
      case symbol_kind::S_CHARC: // CHARC
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_DOTDOT: // DOTDOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_ERROR_TOKEN: // ERROR_TOKEN
      case symbol_kind::S_rel_op: // rel_op
      case symbol_kind::S_add_op: // add_op
      case symbol_kind::S_mul_op: // mul_op
        value.move< Token > (that.value);
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< TypeDecl > (that.value);
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        value.move< TypeSpecPtr > (that.value);
        break;

      case symbol_kind::S_access: // access
        value.move< VarAccess > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< VarDecl > (that.value);
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        value.move< std::vector<ExprPtr> > (that.value);
        break;

      case symbol_kind::S_field_list: // field_list
        value.move< std::vector<FieldDecl> > (that.value);
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        value.move< std::vector<ParamDecl> > (that.value);
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        value.move< std::vector<ProcDecl> > (that.value);
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        value.move< std::vector<StmtPtr> > (that.value);
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.move< std::vector<TypeDecl> > (that.value);
        break;

      case symbol_kind::S_access_list: // access_list
        value.move< std::vector<VarAccess> > (that.value);
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.move< std::vector<VarDecl> > (that.value);
        break;

      case symbol_kind::S_id_list: // id_list
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  BisonParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  BisonParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  BisonParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  BisonParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  BisonParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  BisonParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  BisonParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  BisonParser::debug_level_type
  BisonParser::debug_level () const
  {
    return yydebug_;
  }

  void
  BisonParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  BisonParser::state_type
  BisonParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  BisonParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  BisonParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  BisonParser::operator() ()
  {
    return parse ();
  }

  int
  BisonParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_declare_part: // declare_part
        yylhs.value.emplace< DeclPart > ();
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        yylhs.value.emplace< ExprPtr > ();
        break;

      case symbol_kind::S_field_decl: // field_decl
        yylhs.value.emplace< FieldDecl > ();
        break;

      case symbol_kind::S_param: // param
        yylhs.value.emplace< ParamDecl > ();
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        yylhs.value.emplace< ProcDecl > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< ProgramNode > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        yylhs.value.emplace< StmtPtr > ();
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
      case symbol_kind::S_PROCEDURE: // PROCEDURE
      case symbol_kind::S_TYPE: // TYPE
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_THEN: // THEN
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_FI: // FI
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_DO: // DO
      case symbol_kind::S_ENDWH: // ENDWH
      case symbol_kind::S_BEGIN_K: // BEGIN_K
      case symbol_kind::S_END_K: // END_K
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_WRITE: // WRITE
      case symbol_kind::S_ARRAY: // ARRAY
      case symbol_kind::S_OF: // OF
      case symbol_kind::S_RECORD: // RECORD
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_INTC: // INTC
      case symbol_kind::S_CHARC: // CHARC
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_DIV: // DIV
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_DOTDOT: // DOTDOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_SEMI: // SEMI
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_ERROR_TOKEN: // ERROR_TOKEN
      case symbol_kind::S_rel_op: // rel_op
      case symbol_kind::S_add_op: // add_op
      case symbol_kind::S_mul_op: // mul_op
        yylhs.value.emplace< Token > ();
        break;

      case symbol_kind::S_type_decl: // type_decl
        yylhs.value.emplace< TypeDecl > ();
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        yylhs.value.emplace< TypeSpecPtr > ();
        break;

      case symbol_kind::S_access: // access
        yylhs.value.emplace< VarAccess > ();
        break;

      case symbol_kind::S_var_decl: // var_decl
        yylhs.value.emplace< VarDecl > ();
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        yylhs.value.emplace< std::vector<ExprPtr> > ();
        break;

      case symbol_kind::S_field_list: // field_list
        yylhs.value.emplace< std::vector<FieldDecl> > ();
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        yylhs.value.emplace< std::vector<ParamDecl> > ();
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        yylhs.value.emplace< std::vector<ProcDecl> > ();
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        yylhs.value.emplace< std::vector<StmtPtr> > ();
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        yylhs.value.emplace< std::vector<TypeDecl> > ();
        break;

      case symbol_kind::S_access_list: // access_list
        yylhs.value.emplace< std::vector<VarAccess> > ();
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        yylhs.value.emplace< std::vector<VarDecl> > ();
        break;

      case symbol_kind::S_id_list: // id_list
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // translation_unit: program
#line 192 "grammar/snl_parser.y"
          { driver.result = std::move(yystack_[0].value.as < ProgramNode > ()); }
#line 1357 "src/snl_parser_generated.cpp"
    break;

  case 3: // program: PROGRAM ID declare_part program_body DOT
#line 198 "grammar/snl_parser.y"
  {
    ProgramNode program;
    program.line = yystack_[4].value.as < Token > ().Lineshow;   // 记录所在的行号
    program.name = yystack_[3].value.as < Token > ().Sem;        // 主程序名称，如 'program main'
    program.decls = std::move(yystack_[2].value.as < DeclPart > ()); // 将收集到的所有声明（类型、变量、子过程）移交给根节点
    program.body = std::move(yystack_[1].value.as < std::vector<StmtPtr> > ());  // 将收集到的所有主程序语句序列装载进来
    yylhs.value.as < ProgramNode > () = std::move(program);      // 将构造好的 AST 根节点赋值给当前规约符号 program
  }
#line 1370 "src/snl_parser_generated.cpp"
    break;

  case 4: // declare_part: type_dec var_dec proc_dec
#line 211 "grammar/snl_parser.y"
  {
    DeclPart decls;
    decls.types = std::move(yystack_[2].value.as < std::vector<TypeDecl> > ());
    decls.vars = std::move(yystack_[1].value.as < std::vector<VarDecl> > ());
    decls.procs = std::move(yystack_[0].value.as < std::vector<ProcDecl> > ());
    yylhs.value.as < DeclPart > () = std::move(decls);
  }
#line 1382 "src/snl_parser_generated.cpp"
    break;

  case 5: // type_dec: %empty
#line 223 "grammar/snl_parser.y"
         { yylhs.value.as < std::vector<TypeDecl> > () = std::vector<TypeDecl>(); }
#line 1388 "src/snl_parser_generated.cpp"
    break;

  case 6: // type_dec: TYPE type_decl_list
#line 224 "grammar/snl_parser.y"
                      { yylhs.value.as < std::vector<TypeDecl> > () = std::move(yystack_[0].value.as < std::vector<TypeDecl> > ()); }
#line 1394 "src/snl_parser_generated.cpp"
    break;

  case 7: // type_decl_list: type_decl
#line 229 "grammar/snl_parser.y"
            { yylhs.value.as < std::vector<TypeDecl> > ().push_back(std::move(yystack_[0].value.as < TypeDecl > ())); }
#line 1400 "src/snl_parser_generated.cpp"
    break;

  case 8: // type_decl_list: type_decl_list type_decl
#line 231 "grammar/snl_parser.y"
  { yystack_[1].value.as < std::vector<TypeDecl> > ().push_back(std::move(yystack_[0].value.as < TypeDecl > ())); yylhs.value.as < std::vector<TypeDecl> > () = std::move(yystack_[1].value.as < std::vector<TypeDecl> > ()); }
#line 1406 "src/snl_parser_generated.cpp"
    break;

  case 9: // type_decl: ID EQ type_name SEMI
#line 237 "grammar/snl_parser.y"
  {
    TypeDecl decl;
    decl.line = yystack_[3].value.as < Token > ().Lineshow;
    decl.name = yystack_[3].value.as < Token > ().Sem;
    decl.type = std::move(yystack_[1].value.as < TypeSpecPtr > ());
    yylhs.value.as < TypeDecl > () = std::move(decl);
  }
#line 1418 "src/snl_parser_generated.cpp"
    break;

  case 10: // var_dec: %empty
#line 248 "grammar/snl_parser.y"
         { yylhs.value.as < std::vector<VarDecl> > () = std::vector<VarDecl>(); }
#line 1424 "src/snl_parser_generated.cpp"
    break;

  case 11: // var_dec: VAR var_decl_list
#line 249 "grammar/snl_parser.y"
                    { yylhs.value.as < std::vector<VarDecl> > () = std::move(yystack_[0].value.as < std::vector<VarDecl> > ()); }
#line 1430 "src/snl_parser_generated.cpp"
    break;

  case 12: // var_decl_list: var_decl
#line 253 "grammar/snl_parser.y"
           { yylhs.value.as < std::vector<VarDecl> > ().push_back(std::move(yystack_[0].value.as < VarDecl > ())); }
#line 1436 "src/snl_parser_generated.cpp"
    break;

  case 13: // var_decl_list: var_decl_list var_decl
#line 254 "grammar/snl_parser.y"
                         { yystack_[1].value.as < std::vector<VarDecl> > ().push_back(std::move(yystack_[0].value.as < VarDecl > ())); yylhs.value.as < std::vector<VarDecl> > () = std::move(yystack_[1].value.as < std::vector<VarDecl> > ()); }
#line 1442 "src/snl_parser_generated.cpp"
    break;

  case 14: // var_decl: type_name id_list SEMI
#line 260 "grammar/snl_parser.y"
  {
    VarDecl decl;
    decl.line = yystack_[2].value.as < TypeSpecPtr > () ? yystack_[2].value.as < TypeSpecPtr > ()->line : 1;
    decl.type = std::move(yystack_[2].value.as < TypeSpecPtr > ());
    decl.names = std::move(yystack_[1].value.as < std::vector<std::string> > ());
    yylhs.value.as < VarDecl > () = std::move(decl);
  }
#line 1454 "src/snl_parser_generated.cpp"
    break;

  case 15: // proc_dec: %empty
#line 271 "grammar/snl_parser.y"
         { yylhs.value.as < std::vector<ProcDecl> > () = std::vector<ProcDecl>(); }
#line 1460 "src/snl_parser_generated.cpp"
    break;

  case 16: // proc_dec: proc_dec proc_decl
#line 272 "grammar/snl_parser.y"
                     { yystack_[1].value.as < std::vector<ProcDecl> > ().push_back(std::move(yystack_[0].value.as < ProcDecl > ())); yylhs.value.as < std::vector<ProcDecl> > () = std::move(yystack_[1].value.as < std::vector<ProcDecl> > ()); }
#line 1466 "src/snl_parser_generated.cpp"
    break;

  case 17: // proc_decl: PROCEDURE ID LPAREN param_dec_list_opt RPAREN SEMI declare_part program_body
#line 278 "grammar/snl_parser.y"
  {
    ProcDecl proc;
    proc.line = yystack_[7].value.as < Token > ().Lineshow;
    proc.name = yystack_[6].value.as < Token > ().Sem;
    proc.params = std::move(yystack_[4].value.as < std::vector<ParamDecl> > ());
    proc.decls = std::move(yystack_[1].value.as < DeclPart > ());
    proc.body = std::move(yystack_[0].value.as < std::vector<StmtPtr> > ());
    yylhs.value.as < ProcDecl > () = std::move(proc);
  }
#line 1480 "src/snl_parser_generated.cpp"
    break;

  case 18: // proc_decl: PROCEDURE ID LPAREN param_dec_list_opt RPAREN SEMI declare_part program_body SEMI
#line 288 "grammar/snl_parser.y"
  { // 兼容 procedure ... end; 后带有可选分号的情况
    ProcDecl proc;
    proc.line = yystack_[8].value.as < Token > ().Lineshow;
    proc.name = yystack_[7].value.as < Token > ().Sem;
    proc.params = std::move(yystack_[5].value.as < std::vector<ParamDecl> > ());
    proc.decls = std::move(yystack_[2].value.as < DeclPart > ());
    proc.body = std::move(yystack_[1].value.as < std::vector<StmtPtr> > ());
    yylhs.value.as < ProcDecl > () = std::move(proc);
  }
#line 1494 "src/snl_parser_generated.cpp"
    break;

  case 19: // param_dec_list_opt: %empty
#line 302 "grammar/snl_parser.y"
         { yylhs.value.as < std::vector<ParamDecl> > () = std::vector<ParamDecl>(); }
#line 1500 "src/snl_parser_generated.cpp"
    break;

  case 20: // param_dec_list_opt: param_dec_list
#line 303 "grammar/snl_parser.y"
                 { yylhs.value.as < std::vector<ParamDecl> > () = std::move(yystack_[0].value.as < std::vector<ParamDecl> > ()); }
#line 1506 "src/snl_parser_generated.cpp"
    break;

  case 21: // param_dec_list: param
#line 308 "grammar/snl_parser.y"
        { yylhs.value.as < std::vector<ParamDecl> > ().push_back(std::move(yystack_[0].value.as < ParamDecl > ())); }
#line 1512 "src/snl_parser_generated.cpp"
    break;

  case 22: // param_dec_list: param_dec_list SEMI param
#line 310 "grammar/snl_parser.y"
  { yystack_[2].value.as < std::vector<ParamDecl> > ().push_back(std::move(yystack_[0].value.as < ParamDecl > ())); yylhs.value.as < std::vector<ParamDecl> > () = std::move(yystack_[2].value.as < std::vector<ParamDecl> > ()); }
#line 1518 "src/snl_parser_generated.cpp"
    break;

  case 23: // param: type_name id_list
#line 316 "grammar/snl_parser.y"
  { // 值传递参数
    ParamDecl param;
    param.line = yystack_[1].value.as < TypeSpecPtr > () ? yystack_[1].value.as < TypeSpecPtr > ()->line : 1;
    param.type = std::move(yystack_[1].value.as < TypeSpecPtr > ());
    param.names = std::move(yystack_[0].value.as < std::vector<std::string> > ());
    yylhs.value.as < ParamDecl > () = std::move(param);
  }
#line 1530 "src/snl_parser_generated.cpp"
    break;

  case 24: // param: VAR type_name id_list
#line 324 "grammar/snl_parser.y"
  { // 引用传递参数 (带有 var 前缀)
    ParamDecl param;
    param.line = yystack_[2].value.as < Token > ().Lineshow;
    param.byRef = true;
    param.type = std::move(yystack_[1].value.as < TypeSpecPtr > ());
    param.names = std::move(yystack_[0].value.as < std::vector<std::string> > ());
    yylhs.value.as < ParamDecl > () = std::move(param);
  }
#line 1543 "src/snl_parser_generated.cpp"
    break;

  case 25: // type_name: base_type
#line 336 "grammar/snl_parser.y"
            { yylhs.value.as < TypeSpecPtr > () = std::move(yystack_[0].value.as < TypeSpecPtr > ()); }
#line 1549 "src/snl_parser_generated.cpp"
    break;

  case 26: // type_name: array_type
#line 337 "grammar/snl_parser.y"
             { yylhs.value.as < TypeSpecPtr > () = std::move(yystack_[0].value.as < TypeSpecPtr > ()); }
#line 1555 "src/snl_parser_generated.cpp"
    break;

  case 27: // type_name: record_type
#line 338 "grammar/snl_parser.y"
              { yylhs.value.as < TypeSpecPtr > () = std::move(yystack_[0].value.as < TypeSpecPtr > ()); }
#line 1561 "src/snl_parser_generated.cpp"
    break;

  case 28: // type_name: ID
#line 340 "grammar/snl_parser.y"
  {
    auto type = make_type(TypeSpecKind::Named, yystack_[0].value.as < Token > ().Lineshow);
    type->name = yystack_[0].value.as < Token > ().Sem;
    yylhs.value.as < TypeSpecPtr > () = std::move(type);
  }
#line 1571 "src/snl_parser_generated.cpp"
    break;

  case 29: // base_type: INTEGER
#line 349 "grammar/snl_parser.y"
          { yylhs.value.as < TypeSpecPtr > () = make_type(TypeSpecKind::Integer, yystack_[0].value.as < Token > ().Lineshow); }
#line 1577 "src/snl_parser_generated.cpp"
    break;

  case 30: // base_type: CHAR
#line 350 "grammar/snl_parser.y"
       { yylhs.value.as < TypeSpecPtr > () = make_type(TypeSpecKind::Char, yystack_[0].value.as < Token > ().Lineshow); }
#line 1583 "src/snl_parser_generated.cpp"
    break;

  case 31: // base_or_array_type: base_type
#line 355 "grammar/snl_parser.y"
            { yylhs.value.as < TypeSpecPtr > () = std::move(yystack_[0].value.as < TypeSpecPtr > ()); }
#line 1589 "src/snl_parser_generated.cpp"
    break;

  case 32: // base_or_array_type: array_type
#line 356 "grammar/snl_parser.y"
             { yylhs.value.as < TypeSpecPtr > () = std::move(yystack_[0].value.as < TypeSpecPtr > ()); }
#line 1595 "src/snl_parser_generated.cpp"
    break;

  case 33: // array_type: ARRAY LBRACKET INTC DOTDOT INTC RBRACKET OF base_type
#line 362 "grammar/snl_parser.y"
  {
    auto type = make_type(TypeSpecKind::Array, yystack_[7].value.as < Token > ().Lineshow);
    type->low = parse_int(yystack_[5].value.as < Token > ());
    type->high = parse_int(yystack_[3].value.as < Token > ());
    type->elementType = std::move(yystack_[0].value.as < TypeSpecPtr > ());
    yylhs.value.as < TypeSpecPtr > () = std::move(type);
  }
#line 1607 "src/snl_parser_generated.cpp"
    break;

  case 34: // record_type: RECORD field_list END_K
#line 374 "grammar/snl_parser.y"
  {
    auto type = make_type(TypeSpecKind::Record, yystack_[2].value.as < Token > ().Lineshow);
    type->fields = std::move(yystack_[1].value.as < std::vector<FieldDecl> > ());
    yylhs.value.as < TypeSpecPtr > () = std::move(type);
  }
#line 1617 "src/snl_parser_generated.cpp"
    break;

  case 35: // field_list: %empty
#line 383 "grammar/snl_parser.y"
         { yylhs.value.as < std::vector<FieldDecl> > () = std::vector<FieldDecl>(); }
#line 1623 "src/snl_parser_generated.cpp"
    break;

  case 36: // field_list: field_list field_decl
#line 384 "grammar/snl_parser.y"
                        { yystack_[1].value.as < std::vector<FieldDecl> > ().push_back(std::move(yystack_[0].value.as < FieldDecl > ())); yylhs.value.as < std::vector<FieldDecl> > () = std::move(yystack_[1].value.as < std::vector<FieldDecl> > ()); }
#line 1629 "src/snl_parser_generated.cpp"
    break;

  case 37: // field_decl: base_or_array_type id_list SEMI
#line 389 "grammar/snl_parser.y"
  {
    FieldDecl field;
    field.line = yystack_[2].value.as < TypeSpecPtr > () ? yystack_[2].value.as < TypeSpecPtr > ()->line : 1;
    field.type = std::move(yystack_[2].value.as < TypeSpecPtr > ());
    field.names = std::move(yystack_[1].value.as < std::vector<std::string> > ());
    yylhs.value.as < FieldDecl > () = std::move(field);
  }
#line 1641 "src/snl_parser_generated.cpp"
    break;

  case 38: // id_list: ID
#line 400 "grammar/snl_parser.y"
     { yylhs.value.as < std::vector<std::string> > ().push_back(yystack_[0].value.as < Token > ().Sem); }
#line 1647 "src/snl_parser_generated.cpp"
    break;

  case 39: // id_list: id_list COMMA ID
#line 401 "grammar/snl_parser.y"
                   { yystack_[2].value.as < std::vector<std::string> > ().push_back(yystack_[0].value.as < Token > ().Sem); yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ()); }
#line 1653 "src/snl_parser_generated.cpp"
    break;

  case 40: // program_body: BEGIN_K stmt_list END_K
#line 406 "grammar/snl_parser.y"
                          { yylhs.value.as < std::vector<StmtPtr> > () = std::move(yystack_[1].value.as < std::vector<StmtPtr> > ()); }
#line 1659 "src/snl_parser_generated.cpp"
    break;

  case 41: // stmt_list: %empty
#line 411 "grammar/snl_parser.y"
         { yylhs.value.as < std::vector<StmtPtr> > () = std::vector<StmtPtr>(); }
#line 1665 "src/snl_parser_generated.cpp"
    break;

  case 42: // stmt_list: stmt_seq
#line 412 "grammar/snl_parser.y"
           { yylhs.value.as < std::vector<StmtPtr> > () = std::move(yystack_[0].value.as < std::vector<StmtPtr> > ()); }
#line 1671 "src/snl_parser_generated.cpp"
    break;

  case 43: // stmt_seq: statement
#line 417 "grammar/snl_parser.y"
            { yylhs.value.as < std::vector<StmtPtr> > ().push_back(std::move(yystack_[0].value.as < StmtPtr > ())); }
#line 1677 "src/snl_parser_generated.cpp"
    break;

  case 44: // stmt_seq: stmt_seq SEMI statement
#line 418 "grammar/snl_parser.y"
                          { yystack_[2].value.as < std::vector<StmtPtr> > ().push_back(std::move(yystack_[0].value.as < StmtPtr > ())); yylhs.value.as < std::vector<StmtPtr> > () = std::move(yystack_[2].value.as < std::vector<StmtPtr> > ()); }
#line 1683 "src/snl_parser_generated.cpp"
    break;

  case 45: // stmt_seq: stmt_seq SEMI
#line 419 "grammar/snl_parser.y"
                { yylhs.value.as < std::vector<StmtPtr> > () = std::move(yystack_[1].value.as < std::vector<StmtPtr> > ()); }
#line 1689 "src/snl_parser_generated.cpp"
    break;

  case 46: // statement: if_statement
#line 424 "grammar/snl_parser.y"
               { yylhs.value.as < StmtPtr > () = std::move(yystack_[0].value.as < StmtPtr > ()); }
#line 1695 "src/snl_parser_generated.cpp"
    break;

  case 47: // statement: while_statement
#line 425 "grammar/snl_parser.y"
                  { yylhs.value.as < StmtPtr > () = std::move(yystack_[0].value.as < StmtPtr > ()); }
#line 1701 "src/snl_parser_generated.cpp"
    break;

  case 48: // statement: read_statement
#line 426 "grammar/snl_parser.y"
                 { yylhs.value.as < StmtPtr > () = std::move(yystack_[0].value.as < StmtPtr > ()); }
#line 1707 "src/snl_parser_generated.cpp"
    break;

  case 49: // statement: write_statement
#line 427 "grammar/snl_parser.y"
                  { yylhs.value.as < StmtPtr > () = std::move(yystack_[0].value.as < StmtPtr > ()); }
#line 1713 "src/snl_parser_generated.cpp"
    break;

  case 50: // statement: return_statement
#line 428 "grammar/snl_parser.y"
                   { yylhs.value.as < StmtPtr > () = std::move(yystack_[0].value.as < StmtPtr > ()); }
#line 1719 "src/snl_parser_generated.cpp"
    break;

  case 51: // statement: id_statement
#line 429 "grammar/snl_parser.y"
               { yylhs.value.as < StmtPtr > () = std::move(yystack_[0].value.as < StmtPtr > ()); }
#line 1725 "src/snl_parser_generated.cpp"
    break;

  case 52: // if_statement: IF rel_exp THEN stmt_list ELSE stmt_list FI
#line 435 "grammar/snl_parser.y"
  {
    auto stmt = make_stmt(StmtKind::If, yystack_[6].value.as < Token > ().Lineshow);
    stmt->cond = std::move(yystack_[5].value.as < ExprPtr > ());        // 条件判断
    stmt->thenPart = std::move(yystack_[3].value.as < std::vector<StmtPtr> > ());    // true 分支
    stmt->elsePart = std::move(yystack_[1].value.as < std::vector<StmtPtr> > ());    // false 分支
    yylhs.value.as < StmtPtr > () = std::move(stmt);
  }
#line 1737 "src/snl_parser_generated.cpp"
    break;

  case 53: // while_statement: WHILE rel_exp DO stmt_list ENDWH
#line 447 "grammar/snl_parser.y"
  {
    auto stmt = make_stmt(StmtKind::While, yystack_[4].value.as < Token > ().Lineshow);
    stmt->cond = std::move(yystack_[3].value.as < ExprPtr > ());        // 循环条件
    stmt->body = std::move(yystack_[1].value.as < std::vector<StmtPtr> > ());        // 循环体序列
    yylhs.value.as < StmtPtr > () = std::move(stmt);
  }
#line 1748 "src/snl_parser_generated.cpp"
    break;

  case 54: // read_statement: READ LPAREN ID RPAREN
#line 458 "grammar/snl_parser.y"
  {
    auto stmt = make_stmt(StmtKind::Read, yystack_[3].value.as < Token > ().Lineshow);
    stmt->name = yystack_[1].value.as < Token > ().Sem;               // 读取目标变量名
    yylhs.value.as < StmtPtr > () = std::move(stmt);
  }
#line 1758 "src/snl_parser_generated.cpp"
    break;

  case 55: // write_statement: WRITE LPAREN exp RPAREN
#line 468 "grammar/snl_parser.y"
  {
    auto stmt = make_stmt(StmtKind::Write, yystack_[3].value.as < Token > ().Lineshow);
    stmt->expr = std::move(yystack_[1].value.as < ExprPtr > ());        // 被输出求值的表达式
    yylhs.value.as < StmtPtr > () = std::move(stmt);
  }
#line 1768 "src/snl_parser_generated.cpp"
    break;

  case 56: // return_statement: RETURN LPAREN exp RPAREN
#line 478 "grammar/snl_parser.y"
  {
    auto stmt = make_stmt(StmtKind::Return, yystack_[3].value.as < Token > ().Lineshow);
    stmt->expr = std::move(yystack_[1].value.as < ExprPtr > ());
    yylhs.value.as < StmtPtr > () = std::move(stmt);
  }
#line 1778 "src/snl_parser_generated.cpp"
    break;

  case 57: // id_statement: ID LPAREN actual_param_list_opt RPAREN
#line 489 "grammar/snl_parser.y"
  { // 过程调用分支
    auto stmt = make_stmt(StmtKind::Call, yystack_[3].value.as < Token > ().Lineshow);
    stmt->name = yystack_[3].value.as < Token > ().Sem;               // 目标函数名称
    stmt->args = std::move(yystack_[1].value.as < std::vector<ExprPtr> > ());        // 传递的实参
    yylhs.value.as < StmtPtr > () = std::move(stmt);
  }
#line 1789 "src/snl_parser_generated.cpp"
    break;

  case 58: // id_statement: variable ASSIGN exp
#line 496 "grammar/snl_parser.y"
  { // 赋值操作分支
    auto stmt = make_stmt(StmtKind::Assign, yystack_[2].value.as < ExprPtr > () ? yystack_[2].value.as < ExprPtr > ()->line : 1);
    stmt->lhs = std::move(yystack_[2].value.as < ExprPtr > ());         // 左值 (可能是 x，或者 array 元素和 record 成员)
    stmt->expr = std::move(yystack_[0].value.as < ExprPtr > ());        // 右侧将被计算的赋值表达式
    yylhs.value.as < StmtPtr > () = std::move(stmt);
  }
#line 1800 "src/snl_parser_generated.cpp"
    break;

  case 59: // actual_param_list_opt: %empty
#line 506 "grammar/snl_parser.y"
         { yylhs.value.as < std::vector<ExprPtr> > () = std::vector<ExprPtr>(); }
#line 1806 "src/snl_parser_generated.cpp"
    break;

  case 60: // actual_param_list_opt: actual_param_list
#line 507 "grammar/snl_parser.y"
                    { yylhs.value.as < std::vector<ExprPtr> > () = std::move(yystack_[0].value.as < std::vector<ExprPtr> > ()); }
#line 1812 "src/snl_parser_generated.cpp"
    break;

  case 61: // actual_param_list: exp
#line 511 "grammar/snl_parser.y"
      { yylhs.value.as < std::vector<ExprPtr> > ().push_back(std::move(yystack_[0].value.as < ExprPtr > ())); }
#line 1818 "src/snl_parser_generated.cpp"
    break;

  case 62: // actual_param_list: actual_param_list COMMA exp
#line 512 "grammar/snl_parser.y"
                              { yystack_[2].value.as < std::vector<ExprPtr> > ().push_back(std::move(yystack_[0].value.as < ExprPtr > ())); yylhs.value.as < std::vector<ExprPtr> > () = std::move(yystack_[2].value.as < std::vector<ExprPtr> > ()); }
#line 1824 "src/snl_parser_generated.cpp"
    break;

  case 63: // rel_exp: exp rel_op exp
#line 517 "grammar/snl_parser.y"
                 { yylhs.value.as < ExprPtr > () = make_op_expr(yystack_[1].value.as < Token > (), std::move(yystack_[2].value.as < ExprPtr > ()), std::move(yystack_[0].value.as < ExprPtr > ())); }
#line 1830 "src/snl_parser_generated.cpp"
    break;

  case 64: // rel_op: LT
#line 521 "grammar/snl_parser.y"
     { yylhs.value.as < Token > () = yystack_[0].value.as < Token > (); }
#line 1836 "src/snl_parser_generated.cpp"
    break;

  case 65: // rel_op: EQ
#line 522 "grammar/snl_parser.y"
     { yylhs.value.as < Token > () = yystack_[0].value.as < Token > (); }
#line 1842 "src/snl_parser_generated.cpp"
    break;

  case 66: // exp: term
#line 527 "grammar/snl_parser.y"
       { yylhs.value.as < ExprPtr > () = std::move(yystack_[0].value.as < ExprPtr > ()); }
#line 1848 "src/snl_parser_generated.cpp"
    break;

  case 67: // exp: exp add_op term
#line 528 "grammar/snl_parser.y"
                  { yylhs.value.as < ExprPtr > () = make_op_expr(yystack_[1].value.as < Token > (), std::move(yystack_[2].value.as < ExprPtr > ()), std::move(yystack_[0].value.as < ExprPtr > ())); }
#line 1854 "src/snl_parser_generated.cpp"
    break;

  case 68: // add_op: PLUS
#line 532 "grammar/snl_parser.y"
       { yylhs.value.as < Token > () = yystack_[0].value.as < Token > (); }
#line 1860 "src/snl_parser_generated.cpp"
    break;

  case 69: // add_op: MINUS
#line 533 "grammar/snl_parser.y"
        { yylhs.value.as < Token > () = yystack_[0].value.as < Token > (); }
#line 1866 "src/snl_parser_generated.cpp"
    break;

  case 70: // term: factor
#line 538 "grammar/snl_parser.y"
         { yylhs.value.as < ExprPtr > () = std::move(yystack_[0].value.as < ExprPtr > ()); }
#line 1872 "src/snl_parser_generated.cpp"
    break;

  case 71: // term: term mul_op factor
#line 539 "grammar/snl_parser.y"
                     { yylhs.value.as < ExprPtr > () = make_op_expr(yystack_[1].value.as < Token > (), std::move(yystack_[2].value.as < ExprPtr > ()), std::move(yystack_[0].value.as < ExprPtr > ())); }
#line 1878 "src/snl_parser_generated.cpp"
    break;

  case 72: // mul_op: STAR
#line 543 "grammar/snl_parser.y"
       { yylhs.value.as < Token > () = yystack_[0].value.as < Token > (); }
#line 1884 "src/snl_parser_generated.cpp"
    break;

  case 73: // mul_op: DIV
#line 544 "grammar/snl_parser.y"
      { yylhs.value.as < Token > () = yystack_[0].value.as < Token > (); }
#line 1890 "src/snl_parser_generated.cpp"
    break;

  case 74: // factor: LPAREN exp RPAREN
#line 549 "grammar/snl_parser.y"
                    { yylhs.value.as < ExprPtr > () = std::move(yystack_[1].value.as < ExprPtr > ()); }
#line 1896 "src/snl_parser_generated.cpp"
    break;

  case 75: // factor: INTC
#line 551 "grammar/snl_parser.y"
  {
    auto expr = std::make_unique<Expr>();
    expr->kind = ExprKind::IntConst;
    expr->line = yystack_[0].value.as < Token > ().Lineshow;
    expr->intValue = parse_int(yystack_[0].value.as < Token > ());
    yylhs.value.as < ExprPtr > () = std::move(expr);
  }
#line 1908 "src/snl_parser_generated.cpp"
    break;

  case 76: // factor: CHARC
#line 559 "grammar/snl_parser.y"
  {
    auto expr = std::make_unique<Expr>();
    expr->kind = ExprKind::CharConst;
    expr->line = yystack_[0].value.as < Token > ().Lineshow;
    expr->charValue = yystack_[0].value.as < Token > ().Sem.empty() ? '\0' : yystack_[0].value.as < Token > ().Sem[0];
    yylhs.value.as < ExprPtr > () = std::move(expr);
  }
#line 1920 "src/snl_parser_generated.cpp"
    break;

  case 77: // factor: variable
#line 566 "grammar/snl_parser.y"
           { yylhs.value.as < ExprPtr > () = std::move(yystack_[0].value.as < ExprPtr > ()); }
#line 1926 "src/snl_parser_generated.cpp"
    break;

  case 78: // variable: ID access_list
#line 573 "grammar/snl_parser.y"
  {
    auto expr = make_variable_expr(yystack_[1].value.as < Token > ());
    expr->access = std::move(yystack_[0].value.as < std::vector<VarAccess> > ());
    yylhs.value.as < ExprPtr > () = std::move(expr);
  }
#line 1936 "src/snl_parser_generated.cpp"
    break;

  case 79: // access_list: %empty
#line 582 "grammar/snl_parser.y"
         { yylhs.value.as < std::vector<VarAccess> > () = std::vector<VarAccess>(); }
#line 1942 "src/snl_parser_generated.cpp"
    break;

  case 80: // access_list: access_list access
#line 583 "grammar/snl_parser.y"
                     { yystack_[1].value.as < std::vector<VarAccess> > ().push_back(std::move(yystack_[0].value.as < VarAccess > ())); yylhs.value.as < std::vector<VarAccess> > () = std::move(yystack_[1].value.as < std::vector<VarAccess> > ()); }
#line 1948 "src/snl_parser_generated.cpp"
    break;

  case 81: // access: LBRACKET exp RBRACKET
#line 589 "grammar/snl_parser.y"
  { // 数组下标访问
    VarAccess access;
    access.kind = VarAccess::Kind::Index;
    access.line = yystack_[2].value.as < Token > ().Lineshow;
    access.index = std::move(yystack_[1].value.as < ExprPtr > ());
    yylhs.value.as < VarAccess > () = std::move(access);
  }
#line 1960 "src/snl_parser_generated.cpp"
    break;

  case 82: // access: DOT ID
#line 597 "grammar/snl_parser.y"
  { // 结构体成员引用
    VarAccess access;
    access.kind = VarAccess::Kind::Field;
    access.line = yystack_[1].value.as < Token > ().Lineshow;
    access.fieldName = yystack_[0].value.as < Token > ().Sem;
    yylhs.value.as < VarAccess > () = std::move(access);
  }
#line 1972 "src/snl_parser_generated.cpp"
    break;


#line 1976 "src/snl_parser_generated.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  BisonParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  BisonParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  BisonParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // BisonParser::context.
  BisonParser::context::context (const BisonParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  BisonParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  BisonParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  BisonParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char BisonParser::yypact_ninf_ = -96;

  const signed char BisonParser::yytable_ninf_ = -1;

  const signed char
  BisonParser::yypact_[] =
  {
       4,   -14,    16,   -96,    28,   -96,    13,    35,    45,    27,
      13,   -96,    18,    19,    36,   -96,    36,   -96,     2,     2,
      29,    33,    53,    54,    50,    48,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,    42,   -96,    55,   -96,   -96,   -96,   -96,
      36,   -96,    66,   -96,   -96,   -96,    88,    52,   -96,   -96,
     -96,     2,    86,    49,    -2,   -96,   -96,    83,    72,     2,
       2,     2,   -17,   -96,    18,     2,    73,    25,   -96,   -96,
      32,    75,   -96,   -96,    15,    18,   -96,   -96,   -96,   -96,
       2,     2,   -96,   -96,     2,    18,    62,    31,    40,    65,
      61,    51,     2,    78,   -96,   -96,    51,    64,   -96,   -96,
      66,   -96,   -96,    80,   -96,    71,   -96,    98,    51,    -2,
     -96,    95,   -96,   -96,   -96,   -96,     2,   -22,   -96,    84,
      43,   -96,     0,    18,   -96,    51,   -96,    74,   -96,    36,
      79,    69,   -96,    66,   105,    97,    66,    76,     0,    81,
     -96,    63,    81,    28,   -96,   -96,    35,    77,   -96
  };

  const signed char
  BisonParser::yydefact_[] =
  {
       0,     0,     0,     2,     5,     1,     0,     0,    10,     0,
       6,     7,    41,     0,     0,    15,     0,     8,     0,     0,
       0,     0,     0,    79,     0,    42,    43,    46,    47,    48,
      49,    50,    51,     0,     3,     0,    35,    29,    30,    28,
      11,    12,     0,    25,    26,    27,     4,     0,    79,    75,
      76,     0,     0,     0,    66,    70,    77,     0,     0,     0,
       0,    59,    78,    40,    45,     0,     0,     0,    13,    38,
       0,     0,    16,     9,     0,    41,    65,    64,    68,    69,
       0,     0,    72,    73,     0,    41,     0,     0,     0,     0,
      60,    61,     0,     0,    80,    44,    58,     0,    34,    31,
       0,    32,    36,     0,    14,     0,    74,     0,    63,    67,
      71,     0,    54,    55,    56,    57,     0,     0,    82,     0,
       0,    39,    19,    41,    53,    62,    81,     0,    37,     0,
       0,    20,    21,     0,     0,     0,     0,     0,     0,    23,
      52,     0,    24,     5,    22,    33,     0,    17,    18
  };

  const signed char
  BisonParser::yypgoto_[] =
  {
     -96,   -96,   -96,   -24,   -96,   -96,   110,   -96,   -96,    85,
     -96,   -96,   -96,   -96,   -15,   -16,   -65,   -96,    57,   -96,
     -96,   -96,   -95,   -20,   -71,   -96,    67,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   108,   -96,   -48,   -96,    47,
     -96,    46,   -11,   -96,   -96
  };

  const short
  BisonParser::yydefgoto_[] =
  {
      -1,     2,     3,     7,     8,    10,    11,    15,    40,    41,
      46,    72,   130,   131,   132,    42,    43,   100,    44,    45,
      67,   102,    70,    13,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    89,    90,    52,    80,    53,    81,    54,
      84,    55,    56,    62,    94
  };

  const unsigned char
  BisonParser::yytable_[] =
  {
      47,    33,    99,    74,   107,   120,   129,     1,    78,    79,
       4,    87,    88,    91,   111,   126,     5,    96,    35,    92,
      36,    93,    37,    38,    39,    18,    48,    49,    50,    19,
      82,    83,   108,     6,    20,    21,    51,     9,   139,    22,
      98,   142,    23,    35,   117,    78,    79,    37,    38,    12,
     106,    14,   134,    33,    35,    16,    36,    34,    37,    38,
      39,    78,    79,    58,    33,    63,   113,    59,   125,    65,
      78,    79,   103,   104,    33,   114,   145,    76,    77,    78,
      79,    78,    79,   103,   128,    37,    38,    60,    61,    64,
      69,    66,    71,    73,    75,    85,    86,   112,    97,   105,
     115,   116,   118,   119,   121,   122,   133,   123,   124,   127,
     138,   135,    33,   136,   137,   140,   141,   143,   148,   146,
      17,   103,   133,   144,   101,    68,   147,    57,   109,     0,
     110,    95
  };

  const short
  BisonParser::yycheck_[] =
  {
      16,    12,    67,    51,    75,   100,     6,     3,    30,    31,
      24,    59,    60,    61,    85,    37,     0,    65,    18,    36,
      20,    38,    22,    23,    24,     7,    24,    25,    26,    11,
      32,    33,    80,     5,    16,    17,    34,    24,   133,    21,
      15,   136,    24,    18,    92,    30,    31,    22,    23,    14,
      35,     6,   123,    64,    18,    28,    20,    38,    22,    23,
      24,    30,    31,    34,    75,    15,    35,    34,   116,    27,
      30,    31,    40,    41,    85,    35,   141,    28,    29,    30,
      31,    30,    31,    40,    41,    22,    23,    34,    34,    41,
      24,    36,     4,    41,     8,    12,    24,    35,    25,    24,
      35,    40,    24,    39,    24,    34,   122,     9,    13,    25,
      41,    37,   123,   129,    35,    10,    19,    41,    41,   143,
      10,    40,   138,   138,    67,    40,   146,    19,    81,    -1,
      84,    64
  };

  const signed char
  BisonParser::yystos_[] =
  {
       0,     3,    45,    46,    24,     0,     5,    47,    48,    24,
      49,    50,    14,    67,     6,    51,    28,    50,     7,    11,
      16,    17,    21,    24,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    86,    38,    18,    20,    22,    23,    24,
      52,    53,    59,    60,    62,    63,    54,    59,    24,    25,
      26,    34,    79,    81,    83,    85,    86,    79,    34,    34,
      34,    34,    87,    15,    41,    27,    36,    64,    53,    24,
      66,     4,    55,    41,    81,     8,    28,    29,    30,    31,
      80,    82,    32,    33,    84,    12,    24,    81,    81,    77,
      78,    81,    36,    38,    88,    70,    81,    25,    15,    60,
      61,    62,    65,    40,    41,    24,    35,    68,    81,    83,
      85,    68,    35,    35,    35,    35,    40,    81,    24,    39,
      66,    24,    34,     9,    13,    81,    37,    25,    41,     6,
      56,    57,    58,    59,    68,    37,    59,    35,    41,    66,
      10,    19,    66,    41,    58,    60,    47,    67,    41
  };

  const signed char
  BisonParser::yyr1_[] =
  {
       0,    44,    45,    46,    47,    48,    48,    49,    49,    50,
      51,    51,    52,    52,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    59,    60,
      60,    61,    61,    62,    63,    64,    64,    65,    66,    66,
      67,    68,    68,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    71,    72,    73,    74,    75,    76,    76,    77,
      77,    78,    78,    79,    80,    80,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    85,    85,    86,    87,
      87,    88,    88
  };

  const signed char
  BisonParser::yyr2_[] =
  {
       0,     2,     1,     5,     3,     0,     2,     1,     2,     4,
       0,     2,     1,     2,     3,     0,     2,     8,     9,     0,
       1,     1,     3,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     8,     3,     0,     2,     3,     1,     3,
       3,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     7,     5,     4,     4,     4,     4,     3,     0,
       1,     1,     3,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     3,     1,     1,     1,     2,     0,
       2,     3,     2
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const BisonParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "PROCEDURE",
  "TYPE", "VAR", "IF", "THEN", "ELSE", "FI", "WHILE", "DO", "ENDWH",
  "BEGIN_K", "END_K", "READ", "WRITE", "ARRAY", "OF", "RECORD", "RETURN",
  "INTEGER", "CHAR", "ID", "INTC", "CHARC", "ASSIGN", "EQ", "LT", "PLUS",
  "MINUS", "STAR", "DIV", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "DOT", "DOTDOT", "COMMA", "SEMI", "COLON", "ERROR_TOKEN", "$accept",
  "translation_unit", "program", "declare_part", "type_dec",
  "type_decl_list", "type_decl", "var_dec", "var_decl_list", "var_decl",
  "proc_dec", "proc_decl", "param_dec_list_opt", "param_dec_list", "param",
  "type_name", "base_type", "base_or_array_type", "array_type",
  "record_type", "field_list", "field_decl", "id_list", "program_body",
  "stmt_list", "stmt_seq", "statement", "if_statement", "while_statement",
  "read_statement", "write_statement", "return_statement", "id_statement",
  "actual_param_list_opt", "actual_param_list", "rel_exp", "rel_op", "exp",
  "add_op", "term", "mul_op", "factor", "variable", "access_list",
  "access", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  BisonParser::yyrline_[] =
  {
       0,   192,   192,   197,   210,   223,   224,   229,   230,   236,
     248,   249,   253,   254,   259,   271,   272,   277,   287,   302,
     303,   308,   309,   315,   323,   336,   337,   338,   339,   349,
     350,   355,   356,   361,   373,   383,   384,   388,   400,   401,
     406,   411,   412,   417,   418,   419,   424,   425,   426,   427,
     428,   429,   434,   446,   457,   467,   477,   488,   495,   506,
     507,   511,   512,   517,   521,   522,   527,   528,   532,   533,
     538,   539,   543,   544,   549,   550,   558,   566,   572,   582,
     583,   588,   596
  };

  void
  BisonParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  BisonParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 8 "grammar/snl_parser.y"
} // snl
#line 2543 "src/snl_parser_generated.cpp"

#line 606 "grammar/snl_parser.y"

