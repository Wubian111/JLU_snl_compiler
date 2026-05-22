/* ====== Bison 骨架及基础配置 ====== */
/* 使用 C++ LALR(1) 骨架生成原生 C++ 类的解析器 */
%skeleton "lalr1.cc"
%require "3.0"
/* 生成 `snl_parser_generated.h` 头文件供外部使用 */
%defines
/* 将生成的 BisonParser 类及所有相关类型放置在 snl 命名空间下 */
%define api.namespace {snl}
/* 设置生成的 C++ 类的名字 */
%define api.parser.class {BisonParser}
/* 使用 type-safe 的 variant 作为所有 Token 和规约符号的语义值类型，取代传统的 C 语言 union */
%define api.value.type variant
/* 开启 C++ 的 Token 构造函数支持 (如 make_PROGRAM(tok))，这让我们直接传递 C++ 对象变得更安全 */
%define api.token.constructor
/* 当语法分析探测出错时，提供更详尽(verbose)的错误提示以辅助调试 */
%define parse.error verbose

/* 定义解析器外部驱动状态参数传入，将词法分析得到的自定义 Driver 连入 yylex 及解析环境中 */
%parse-param { snl::ParserDriver& driver }
%lex-param { snl::ParserDriver& driver }

%code requires {
#include "snl_parser_driver.h"

#include <memory>
#include <string>
#include <vector>
}

%code {
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
}

/* ====== 终结符 (Token) 定义 ====== */
/* 将下面这些关键字的 Token 绑定到包含行号和词法信息的 <Token> 语义值上 */
%token <Token> PROGRAM PROCEDURE TYPE VAR IF THEN ELSE FI WHILE DO ENDWH
%token <Token> BEGIN_K END_K READ WRITE ARRAY OF RECORD RETURN INTEGER CHAR
/* 标识符及常量 */
%token <Token> ID INTC CHARC
/* 符号与界符 */
%token <Token> ASSIGN EQ LT PLUS MINUS STAR DIV LPAREN RPAREN LBRACKET RBRACKET
%token <Token> DOT DOTDOT COMMA SEMI COLON ERROR_TOKEN

/* ====== 非终结符 (Non-Terminal) 类型绑定 ====== */
/* 核心语法树节点绑定，如 'program' 规则化简后生成一个 <ProgramNode> 将向上传递 */
%type <ProgramNode> program
%type <DeclPart> declare_part
%type <std::vector<TypeDecl>> type_dec type_decl_list
%type <TypeDecl> type_decl
%type <std::vector<VarDecl>> var_dec var_decl_list
%type <VarDecl> var_decl
%type <std::vector<ProcDecl>> proc_dec
%type <ProcDecl> proc_decl
%type <std::vector<ParamDecl>> param_dec_list param_dec_list_opt
%type <ParamDecl> param
%type <TypeSpecPtr> type_name base_type base_or_array_type array_type record_type
%type <std::vector<FieldDecl>> field_list
%type <FieldDecl> field_decl
%type <std::vector<std::string>> id_list
%type <std::vector<StmtPtr>> program_body stmt_list stmt_seq
%type <StmtPtr> statement if_statement while_statement read_statement write_statement
%type <StmtPtr> return_statement id_statement
%type <std::vector<ExprPtr>> actual_param_list actual_param_list_opt
%type <ExprPtr> rel_exp exp term factor variable
%type <std::vector<VarAccess>> access_list
%type <VarAccess> access
%type <Token> rel_op add_op mul_op

/* 语法分析最初开始的符号 (文网的根) */
%start translation_unit

%%

/* ::= 翻译单元：整棵 AST 的顶层挂载点，解析结束后将结果移交给 driver */
translation_unit:
  program { driver.result = std::move($1); }
;

/* ::= 主要程序结构 (program id declare_part begin ... end .) */
program:
  PROGRAM ID declare_part program_body DOT
  {
    ProgramNode program;
    program.line = $1.Lineshow;   // 记录所在的行号
    program.name = $2.Sem;        // 主程序名称，如 'program main'
    program.decls = std::move($3); // 将收集到的所有声明（类型、变量、子过程）移交给根节点
    program.body = std::move($4);  // 将收集到的所有主程序语句序列装载进来
    $$ = std::move(program);      // 将构造好的 AST 根节点赋值给当前规约符号 program
  }
;

/* ::= 声明段 (包含可能出现的三大声明部分：类型声明、变量声明、子过程声明) */
declare_part:
  type_dec var_dec proc_dec
  {
    DeclPart decls;
    decls.types = std::move($1);
    decls.vars = std::move($2);
    decls.procs = std::move($3);
    $$ = std::move(decls);
  }
;

/* ============ 类型声明 ============ */
type_dec:
  /* 空产生式：不包含任何类型声明 */
  %empty { $$ = std::vector<TypeDecl>(); }
| TYPE type_decl_list { $$ = std::move($2); }
;

type_decl_list:
  /* 单个类型声明 */
  type_decl { $$.push_back(std::move($1)); }
| type_decl_list type_decl /* 递归的多个类型声明 */
  { $1.push_back(std::move($2)); $$ = std::move($1); }
;

/* ::= 单条类型别名声明，例如：type myInt = integer; */
type_decl:
  ID EQ type_name SEMI
  {
    TypeDecl decl;
    decl.line = $1.Lineshow;
    decl.name = $1.Sem;
    decl.type = std::move($3);
    $$ = std::move(decl);
  }
;

/* ============ 变量声明 ============ */
var_dec:
  %empty { $$ = std::vector<VarDecl>(); }
| VAR var_decl_list { $$ = std::move($2); }
;

var_decl_list:
  var_decl { $$.push_back(std::move($1)); }
| var_decl_list var_decl { $1.push_back(std::move($2)); $$ = std::move($1); }
;

/* ::= 单条变量声明，例如：integer x, y; 或者 record/array 的匿名声明 */
var_decl:
  type_name id_list SEMI
  {
    VarDecl decl;
    decl.line = $1 ? $1->line : 1;
    decl.type = std::move($1);
    decl.names = std::move($2);
    $$ = std::move(decl);
  }
;

/* ============ 过程/函数声明 ============ */
proc_dec:
  %empty { $$ = std::vector<ProcDecl>(); }
| proc_dec proc_decl { $1.push_back(std::move($2)); $$ = std::move($1); }
;

/* ::= 定义一个 procedure 及其嵌套声明 */
proc_decl:
  PROCEDURE ID LPAREN param_dec_list_opt RPAREN SEMI declare_part program_body
  {
    ProcDecl proc;
    proc.line = $1.Lineshow;
    proc.name = $2.Sem;
    proc.params = std::move($4);
    proc.decls = std::move($7);
    proc.body = std::move($8);
    $$ = std::move(proc);
  }
| PROCEDURE ID LPAREN param_dec_list_opt RPAREN SEMI declare_part program_body SEMI
  { // 兼容 procedure ... end; 后带有可选分号的情况
    ProcDecl proc;
    proc.line = $1.Lineshow;
    proc.name = $2.Sem;
    proc.params = std::move($4);
    proc.decls = std::move($7);
    proc.body = std::move($8);
    $$ = std::move(proc);
  }
;

/* ============ 参数声明 ============ */
param_dec_list_opt:
  /* 形参列表是可选的 */
  %empty { $$ = std::vector<ParamDecl>(); }
| param_dec_list { $$ = std::move($1); }
;

param_dec_list:
  /* 单个参数声明 */
  param { $$.push_back(std::move($1)); }
| param_dec_list SEMI param /* 分号分隔的多个参数声明，例如：integer x; char y */
  { $1.push_back(std::move($3)); $$ = std::move($1); }
;

/* ::= 单个参数声明项：可以是值传递，也可以是带 VAR 关键字的引用传递 */
param:
  type_name id_list
  { // 值传递参数
    ParamDecl param;
    param.line = $1 ? $1->line : 1;
    param.type = std::move($1);
    param.names = std::move($2);
    $$ = std::move(param);
  }
| VAR type_name id_list
  { // 引用传递参数 (带有 var 前缀)
    ParamDecl param;
    param.line = $1.Lineshow;
    param.byRef = true;
    param.type = std::move($2);
    param.names = std::move($3);
    $$ = std::move(param);
  }
;

/* ============ 类型的种类推导 ============ */
type_name:
  base_type { $$ = std::move($1); }
| array_type { $$ = std::move($1); }
| record_type { $$ = std::move($1); }
| ID /* 用户自定义类型，对应于符号表中记录的 type 别名 */
  {
    auto type = make_type(TypeSpecKind::Named, $1.Lineshow);
    type->name = $1.Sem;
    $$ = std::move(type);
  }
;

/* 基本标量类型 */
base_type:
  INTEGER { $$ = make_type(TypeSpecKind::Integer, $1.Lineshow); }
| CHAR { $$ = make_type(TypeSpecKind::Char, $1.Lineshow); }
;

/* 结构体字段可以使用的类型 (限制不能套 record) */
base_or_array_type:
  base_type { $$ = std::move($1); }
| array_type { $$ = std::move($1); }
;

/* ::= 数组类型，例如 array [1..10] of integer */
array_type:
  ARRAY LBRACKET INTC DOTDOT INTC RBRACKET OF base_type
  {
    auto type = make_type(TypeSpecKind::Array, $1.Lineshow);
    type->low = parse_int($3);
    type->high = parse_int($5);
    type->elementType = std::move($8);
    $$ = std::move(type);
  }
;

/* ::= 记录(结构体)类型，例如 record integer x; end */
record_type:
  RECORD field_list END_K
  {
    auto type = make_type(TypeSpecKind::Record, $1.Lineshow);
    type->fields = std::move($2);
    $$ = std::move(type);
  }
;

/* 记录当中的字段列表 */
field_list:
  %empty { $$ = std::vector<FieldDecl>(); }
| field_list field_decl { $1.push_back(std::move($2)); $$ = std::move($1); }
;

field_decl:
  base_or_array_type id_list SEMI
  {
    FieldDecl field;
    field.line = $1 ? $1->line : 1;
    field.type = std::move($1);
    field.names = std::move($2);
    $$ = std::move(field);
  }
;

/* 通用 ID 列表产生式，例如：x, y, z */
id_list:
  ID { $$.push_back($1.Sem); }
| id_list COMMA ID { $1.push_back($3.Sem); $$ = std::move($1); }
;

/* ============ 主执行体 ============ */
program_body:
  BEGIN_K stmt_list END_K { $$ = std::move($2); }
;

stmt_list:
  /* 代码块中可以没有任何语句 */
  %empty { $$ = std::vector<StmtPtr>(); }
| stmt_seq { $$ = std::move($1); }
;

/* 语句序列：用分号分割或结尾 */
stmt_seq:
  statement { $$.push_back(std::move($1)); }
| stmt_seq SEMI statement { $1.push_back(std::move($3)); $$ = std::move($1); }
| stmt_seq SEMI { $$ = std::move($1); } // 兼容最后一个语句存在随尾分号
;

/* 各种语句类型大一统路由 */
statement:
  if_statement { $$ = std::move($1); }
| while_statement { $$ = std::move($1); }
| read_statement { $$ = std::move($1); }
| write_statement { $$ = std::move($1); }
| return_statement { $$ = std::move($1); }
| id_statement { $$ = std::move($1); }
;

/* ::= 条件控制语句：if <cond> then <stmts> else <stmts> fi */
if_statement:
  IF rel_exp THEN stmt_list ELSE stmt_list FI
  {
    auto stmt = make_stmt(StmtKind::If, $1.Lineshow);
    stmt->cond = std::move($2);        // 条件判断
    stmt->thenPart = std::move($4);    // true 分支
    stmt->elsePart = std::move($6);    // false 分支
    $$ = std::move(stmt);
  }
;

/* ::= 循环控制语句：while <cond> do <stmts> endwh */
while_statement:
  WHILE rel_exp DO stmt_list ENDWH
  {
    auto stmt = make_stmt(StmtKind::While, $1.Lineshow);
    stmt->cond = std::move($2);        // 循环条件
    stmt->body = std::move($4);        // 循环体序列
    $$ = std::move(stmt);
  }
;

/* ::= 键盘读取：read(x) */
read_statement:
  READ LPAREN ID RPAREN
  {
    auto stmt = make_stmt(StmtKind::Read, $1.Lineshow);
    stmt->name = $3.Sem;               // 读取目标变量名
    $$ = std::move(stmt);
  }
;

/* ::= 控制台输出：write(exp) */
write_statement:
  WRITE LPAREN exp RPAREN
  {
    auto stmt = make_stmt(StmtKind::Write, $1.Lineshow);
    stmt->expr = std::move($3);        // 被输出求值的表达式
    $$ = std::move(stmt);
  }
;

/* ::= 返回语句：return(exp) */
return_statement:
  RETURN LPAREN exp RPAREN
  {
    auto stmt = make_stmt(StmtKind::Return, $1.Lineshow);
    stmt->expr = std::move($3);
    $$ = std::move(stmt);
  }
;

/* ::= 过程调用( f(x,y) ) 或者是变量赋值( a := 2 ) */
/* 因它们都以标识符(ID)开头，为了避免 LALR 的归约冲突，在此层合二为一 */
id_statement:
  ID LPAREN actual_param_list_opt RPAREN
  { // 过程调用分支
    auto stmt = make_stmt(StmtKind::Call, $1.Lineshow);
    stmt->name = $1.Sem;               // 目标函数名称
    stmt->args = std::move($3);        // 传递的实参
    $$ = std::move(stmt);
  }
| variable ASSIGN exp
  { // 赋值操作分支
    auto stmt = make_stmt(StmtKind::Assign, $1 ? $1->line : 1);
    stmt->lhs = std::move($1);         // 左值 (可能是 x，或者 array 元素和 record 成员)
    stmt->expr = std::move($3);        // 右侧将被计算的赋值表达式
    $$ = std::move(stmt);
  }
;

/* ============ 表达式解析 ============ */
actual_param_list_opt:
  %empty { $$ = std::vector<ExprPtr>(); }
| actual_param_list { $$ = std::move($1); }
;

actual_param_list:
  exp { $$.push_back(std::move($1)); }
| actual_param_list COMMA exp { $1.push_back(std::move($3)); $$ = std::move($1); }
;

/* ::= 关系/逻辑表达式层 (只允许算术表达式两侧夹一个关系运算符) */
rel_exp:
  exp rel_op exp { $$ = make_op_expr($2, std::move($1), std::move($3)); }
;

rel_op:
  LT { $$ = $1; } // 小于 <
| EQ { $$ = $1; } // 等于 =
;

/* ::= 算术加减层 (利用左递归确保左结合性，以及低于乘除的优先级) */
exp:
  term { $$ = std::move($1); }
| exp add_op term { $$ = make_op_expr($2, std::move($1), std::move($3)); }
;

add_op:
  PLUS { $$ = $1; }  // 加 +
| MINUS { $$ = $1; } // 减 -
;

/* ::= 算术乘除层 (左结合，优先级高于加减) */
term:
  factor { $$ = std::move($1); }
| term mul_op factor { $$ = make_op_expr($2, std::move($1), std::move($3)); }
;

mul_op:
  STAR { $$ = $1; } // 乘 *
| DIV { $$ = $1; }  // 除 /
;

/* ::= 原子因子：括号表达式、整数常量、字符常量、变量 */
factor:
  LPAREN exp RPAREN { $$ = std::move($2); }
| INTC
  {
    auto expr = std::make_unique<Expr>();
    expr->kind = ExprKind::IntConst;
    expr->line = $1.Lineshow;
    expr->intValue = parse_int($1);
    $$ = std::move(expr);
  }
| CHARC
  {
    auto expr = std::make_unique<Expr>();
    expr->kind = ExprKind::CharConst;
    expr->line = $1.Lineshow;
    expr->charValue = $1.Sem.empty() ? '\0' : $1.Sem[0];
    $$ = std::move(expr);
  }
| variable { $$ = std::move($1); }
;

/* ============ 变量访问解析 ============ */
/* 变量可能仅仅是个纯ID，也可能是 a[1].b[2] 这种复合结构 */
variable:
  ID access_list
  {
    auto expr = make_variable_expr($1);
    expr->access = std::move($2);
    $$ = std::move(expr);
  }
;

/* 不断递归，支持深层嵌套的属性访问 */
access_list:
  %empty { $$ = std::vector<VarAccess>(); }
| access_list access { $1.push_back(std::move($2)); $$ = std::move($1); }
;

/* 两种访问方式：中括号[Index]对应数组，点(.Field)对应记录 */
access:
  LBRACKET exp RBRACKET
  { // 数组下标访问
    VarAccess access;
    access.kind = VarAccess::Kind::Index;
    access.line = $1.Lineshow;
    access.index = std::move($2);
    $$ = std::move(access);
  }
| DOT ID
  { // 结构体成员引用
    VarAccess access;
    access.kind = VarAccess::Kind::Field;
    access.line = $1.Lineshow;
    access.fieldName = $2.Sem;
    $$ = std::move(access);
  }
;

%%
