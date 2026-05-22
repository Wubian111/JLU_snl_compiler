// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file include/snl_parser_generated.h
 ** Define the snl::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_INCLUDE_SNL_PARSER_GENERATED_H_INCLUDED
# define YY_YY_INCLUDE_SNL_PARSER_GENERATED_H_INCLUDED
// "%code requires" blocks.
#line 22 "grammar/snl_parser.y"

#include "snl_parser_driver.h"

#include <memory>
#include <string>
#include <vector>

#line 57 "include/snl_parser_generated.h"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 8 "grammar/snl_parser.y"
namespace snl {
#line 187 "include/snl_parser_generated.h"




  /// A Bison parser.
  class BisonParser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // declare_part
      char dummy1[sizeof (DeclPart)];

      // rel_exp
      // exp
      // term
      // factor
      // variable
      char dummy2[sizeof (ExprPtr)];

      // field_decl
      char dummy3[sizeof (FieldDecl)];

      // param
      char dummy4[sizeof (ParamDecl)];

      // proc_decl
      char dummy5[sizeof (ProcDecl)];

      // program
      char dummy6[sizeof (ProgramNode)];

      // statement
      // if_statement
      // while_statement
      // read_statement
      // write_statement
      // return_statement
      // id_statement
      char dummy7[sizeof (StmtPtr)];

      // PROGRAM
      // PROCEDURE
      // TYPE
      // VAR
      // IF
      // THEN
      // ELSE
      // FI
      // WHILE
      // DO
      // ENDWH
      // BEGIN_K
      // END_K
      // READ
      // WRITE
      // ARRAY
      // OF
      // RECORD
      // RETURN
      // INTEGER
      // CHAR
      // ID
      // INTC
      // CHARC
      // ASSIGN
      // EQ
      // LT
      // PLUS
      // MINUS
      // STAR
      // DIV
      // LPAREN
      // RPAREN
      // LBRACKET
      // RBRACKET
      // DOT
      // DOTDOT
      // COMMA
      // SEMI
      // COLON
      // ERROR_TOKEN
      // rel_op
      // add_op
      // mul_op
      char dummy8[sizeof (Token)];

      // type_decl
      char dummy9[sizeof (TypeDecl)];

      // type_name
      // base_type
      // base_or_array_type
      // array_type
      // record_type
      char dummy10[sizeof (TypeSpecPtr)];

      // access
      char dummy11[sizeof (VarAccess)];

      // var_decl
      char dummy12[sizeof (VarDecl)];

      // actual_param_list_opt
      // actual_param_list
      char dummy13[sizeof (std::vector<ExprPtr>)];

      // field_list
      char dummy14[sizeof (std::vector<FieldDecl>)];

      // param_dec_list_opt
      // param_dec_list
      char dummy15[sizeof (std::vector<ParamDecl>)];

      // proc_dec
      char dummy16[sizeof (std::vector<ProcDecl>)];

      // program_body
      // stmt_list
      // stmt_seq
      char dummy17[sizeof (std::vector<StmtPtr>)];

      // type_dec
      // type_decl_list
      char dummy18[sizeof (std::vector<TypeDecl>)];

      // access_list
      char dummy19[sizeof (std::vector<VarAccess>)];

      // var_dec
      // var_decl_list
      char dummy20[sizeof (std::vector<VarDecl>)];

      // id_list
      char dummy21[sizeof (std::vector<std::string>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    PROGRAM = 258,                 // PROGRAM
    PROCEDURE = 259,               // PROCEDURE
    TYPE = 260,                    // TYPE
    VAR = 261,                     // VAR
    IF = 262,                      // IF
    THEN = 263,                    // THEN
    ELSE = 264,                    // ELSE
    FI = 265,                      // FI
    WHILE = 266,                   // WHILE
    DO = 267,                      // DO
    ENDWH = 268,                   // ENDWH
    BEGIN_K = 269,                 // BEGIN_K
    END_K = 270,                   // END_K
    READ = 271,                    // READ
    WRITE = 272,                   // WRITE
    ARRAY = 273,                   // ARRAY
    OF = 274,                      // OF
    RECORD = 275,                  // RECORD
    RETURN = 276,                  // RETURN
    INTEGER = 277,                 // INTEGER
    CHAR = 278,                    // CHAR
    ID = 279,                      // ID
    INTC = 280,                    // INTC
    CHARC = 281,                   // CHARC
    ASSIGN = 282,                  // ASSIGN
    EQ = 283,                      // EQ
    LT = 284,                      // LT
    PLUS = 285,                    // PLUS
    MINUS = 286,                   // MINUS
    STAR = 287,                    // STAR
    DIV = 288,                     // DIV
    LPAREN = 289,                  // LPAREN
    RPAREN = 290,                  // RPAREN
    LBRACKET = 291,                // LBRACKET
    RBRACKET = 292,                // RBRACKET
    DOT = 293,                     // DOT
    DOTDOT = 294,                  // DOTDOT
    COMMA = 295,                   // COMMA
    SEMI = 296,                    // SEMI
    COLON = 297,                   // COLON
    ERROR_TOKEN = 298              // ERROR_TOKEN
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 44, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_PROGRAM = 3,                           // PROGRAM
        S_PROCEDURE = 4,                         // PROCEDURE
        S_TYPE = 5,                              // TYPE
        S_VAR = 6,                               // VAR
        S_IF = 7,                                // IF
        S_THEN = 8,                              // THEN
        S_ELSE = 9,                              // ELSE
        S_FI = 10,                               // FI
        S_WHILE = 11,                            // WHILE
        S_DO = 12,                               // DO
        S_ENDWH = 13,                            // ENDWH
        S_BEGIN_K = 14,                          // BEGIN_K
        S_END_K = 15,                            // END_K
        S_READ = 16,                             // READ
        S_WRITE = 17,                            // WRITE
        S_ARRAY = 18,                            // ARRAY
        S_OF = 19,                               // OF
        S_RECORD = 20,                           // RECORD
        S_RETURN = 21,                           // RETURN
        S_INTEGER = 22,                          // INTEGER
        S_CHAR = 23,                             // CHAR
        S_ID = 24,                               // ID
        S_INTC = 25,                             // INTC
        S_CHARC = 26,                            // CHARC
        S_ASSIGN = 27,                           // ASSIGN
        S_EQ = 28,                               // EQ
        S_LT = 29,                               // LT
        S_PLUS = 30,                             // PLUS
        S_MINUS = 31,                            // MINUS
        S_STAR = 32,                             // STAR
        S_DIV = 33,                              // DIV
        S_LPAREN = 34,                           // LPAREN
        S_RPAREN = 35,                           // RPAREN
        S_LBRACKET = 36,                         // LBRACKET
        S_RBRACKET = 37,                         // RBRACKET
        S_DOT = 38,                              // DOT
        S_DOTDOT = 39,                           // DOTDOT
        S_COMMA = 40,                            // COMMA
        S_SEMI = 41,                             // SEMI
        S_COLON = 42,                            // COLON
        S_ERROR_TOKEN = 43,                      // ERROR_TOKEN
        S_YYACCEPT = 44,                         // $accept
        S_translation_unit = 45,                 // translation_unit
        S_program = 46,                          // program
        S_declare_part = 47,                     // declare_part
        S_type_dec = 48,                         // type_dec
        S_type_decl_list = 49,                   // type_decl_list
        S_type_decl = 50,                        // type_decl
        S_var_dec = 51,                          // var_dec
        S_var_decl_list = 52,                    // var_decl_list
        S_var_decl = 53,                         // var_decl
        S_proc_dec = 54,                         // proc_dec
        S_proc_decl = 55,                        // proc_decl
        S_param_dec_list_opt = 56,               // param_dec_list_opt
        S_param_dec_list = 57,                   // param_dec_list
        S_param = 58,                            // param
        S_type_name = 59,                        // type_name
        S_base_type = 60,                        // base_type
        S_base_or_array_type = 61,               // base_or_array_type
        S_array_type = 62,                       // array_type
        S_record_type = 63,                      // record_type
        S_field_list = 64,                       // field_list
        S_field_decl = 65,                       // field_decl
        S_id_list = 66,                          // id_list
        S_program_body = 67,                     // program_body
        S_stmt_list = 68,                        // stmt_list
        S_stmt_seq = 69,                         // stmt_seq
        S_statement = 70,                        // statement
        S_if_statement = 71,                     // if_statement
        S_while_statement = 72,                  // while_statement
        S_read_statement = 73,                   // read_statement
        S_write_statement = 74,                  // write_statement
        S_return_statement = 75,                 // return_statement
        S_id_statement = 76,                     // id_statement
        S_actual_param_list_opt = 77,            // actual_param_list_opt
        S_actual_param_list = 78,                // actual_param_list
        S_rel_exp = 79,                          // rel_exp
        S_rel_op = 80,                           // rel_op
        S_exp = 81,                              // exp
        S_add_op = 82,                           // add_op
        S_term = 83,                             // term
        S_mul_op = 84,                           // mul_op
        S_factor = 85,                           // factor
        S_variable = 86,                         // variable
        S_access_list = 87,                      // access_list
        S_access = 88                            // access
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_declare_part: // declare_part
        value.move< DeclPart > (std::move (that.value));
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        value.move< ExprPtr > (std::move (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< FieldDecl > (std::move (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ParamDecl > (std::move (that.value));
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.move< ProcDecl > (std::move (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< ProgramNode > (std::move (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        value.move< StmtPtr > (std::move (that.value));
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
        value.move< Token > (std::move (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< TypeDecl > (std::move (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        value.move< TypeSpecPtr > (std::move (that.value));
        break;

      case symbol_kind::S_access: // access
        value.move< VarAccess > (std::move (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< VarDecl > (std::move (that.value));
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        value.move< std::vector<ExprPtr> > (std::move (that.value));
        break;

      case symbol_kind::S_field_list: // field_list
        value.move< std::vector<FieldDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        value.move< std::vector<ParamDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        value.move< std::vector<ProcDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        value.move< std::vector<StmtPtr> > (std::move (that.value));
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.move< std::vector<TypeDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_access_list: // access_list
        value.move< std::vector<VarAccess> > (std::move (that.value));
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.move< std::vector<VarDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_id_list: // id_list
        value.move< std::vector<std::string> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DeclPart&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DeclPart& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ExprPtr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ExprPtr& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, FieldDecl&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const FieldDecl& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ParamDecl&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ParamDecl& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ProcDecl&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ProcDecl& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ProgramNode&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ProgramNode& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, StmtPtr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const StmtPtr& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Token&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Token& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TypeDecl&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TypeDecl& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TypeSpecPtr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TypeSpecPtr& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VarAccess&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VarAccess& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VarDecl&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VarDecl& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ExprPtr>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ExprPtr>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<FieldDecl>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<FieldDecl>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ParamDecl>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ParamDecl>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ProcDecl>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ProcDecl>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<StmtPtr>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<StmtPtr>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<TypeDecl>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<TypeDecl>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<VarAccess>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<VarAccess>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<VarDecl>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<VarDecl>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::string>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::string>& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_declare_part: // declare_part
        value.template destroy< DeclPart > ();
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        value.template destroy< ExprPtr > ();
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.template destroy< FieldDecl > ();
        break;

      case symbol_kind::S_param: // param
        value.template destroy< ParamDecl > ();
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.template destroy< ProcDecl > ();
        break;

      case symbol_kind::S_program: // program
        value.template destroy< ProgramNode > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        value.template destroy< StmtPtr > ();
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
        value.template destroy< Token > ();
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.template destroy< TypeDecl > ();
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        value.template destroy< TypeSpecPtr > ();
        break;

      case symbol_kind::S_access: // access
        value.template destroy< VarAccess > ();
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.template destroy< VarDecl > ();
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        value.template destroy< std::vector<ExprPtr> > ();
        break;

      case symbol_kind::S_field_list: // field_list
        value.template destroy< std::vector<FieldDecl> > ();
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        value.template destroy< std::vector<ParamDecl> > ();
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        value.template destroy< std::vector<ProcDecl> > ();
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        value.template destroy< std::vector<StmtPtr> > ();
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.template destroy< std::vector<TypeDecl> > ();
        break;

      case symbol_kind::S_access_list: // access_list
        value.template destroy< std::vector<VarAccess> > ();
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.template destroy< std::vector<VarDecl> > ();
        break;

      case symbol_kind::S_id_list: // id_list
        value.template destroy< std::vector<std::string> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return BisonParser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type(token_type (tok))
#else
      symbol_type (int tok)
        : super_type(token_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Token v)
        : super_type(token_type (tok), std::move (v))
#else
      symbol_type (int tok, const Token& v)
        : super_type(token_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    BisonParser (snl::ParserDriver& driver_yyarg);
    virtual ~BisonParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    BisonParser (const BisonParser&) = delete;
    /// Non copyable.
    BisonParser& operator= (const BisonParser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#else
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PROGRAM (Token v)
      {
        return symbol_type (token::PROGRAM, std::move (v));
      }
#else
      static
      symbol_type
      make_PROGRAM (const Token& v)
      {
        return symbol_type (token::PROGRAM, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PROCEDURE (Token v)
      {
        return symbol_type (token::PROCEDURE, std::move (v));
      }
#else
      static
      symbol_type
      make_PROCEDURE (const Token& v)
      {
        return symbol_type (token::PROCEDURE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE (Token v)
      {
        return symbol_type (token::TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_TYPE (const Token& v)
      {
        return symbol_type (token::TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VAR (Token v)
      {
        return symbol_type (token::VAR, std::move (v));
      }
#else
      static
      symbol_type
      make_VAR (const Token& v)
      {
        return symbol_type (token::VAR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (Token v)
      {
        return symbol_type (token::IF, std::move (v));
      }
#else
      static
      symbol_type
      make_IF (const Token& v)
      {
        return symbol_type (token::IF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THEN (Token v)
      {
        return symbol_type (token::THEN, std::move (v));
      }
#else
      static
      symbol_type
      make_THEN (const Token& v)
      {
        return symbol_type (token::THEN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (Token v)
      {
        return symbol_type (token::ELSE, std::move (v));
      }
#else
      static
      symbol_type
      make_ELSE (const Token& v)
      {
        return symbol_type (token::ELSE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FI (Token v)
      {
        return symbol_type (token::FI, std::move (v));
      }
#else
      static
      symbol_type
      make_FI (const Token& v)
      {
        return symbol_type (token::FI, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (Token v)
      {
        return symbol_type (token::WHILE, std::move (v));
      }
#else
      static
      symbol_type
      make_WHILE (const Token& v)
      {
        return symbol_type (token::WHILE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO (Token v)
      {
        return symbol_type (token::DO, std::move (v));
      }
#else
      static
      symbol_type
      make_DO (const Token& v)
      {
        return symbol_type (token::DO, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDWH (Token v)
      {
        return symbol_type (token::ENDWH, std::move (v));
      }
#else
      static
      symbol_type
      make_ENDWH (const Token& v)
      {
        return symbol_type (token::ENDWH, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BEGIN_K (Token v)
      {
        return symbol_type (token::BEGIN_K, std::move (v));
      }
#else
      static
      symbol_type
      make_BEGIN_K (const Token& v)
      {
        return symbol_type (token::BEGIN_K, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END_K (Token v)
      {
        return symbol_type (token::END_K, std::move (v));
      }
#else
      static
      symbol_type
      make_END_K (const Token& v)
      {
        return symbol_type (token::END_K, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_READ (Token v)
      {
        return symbol_type (token::READ, std::move (v));
      }
#else
      static
      symbol_type
      make_READ (const Token& v)
      {
        return symbol_type (token::READ, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WRITE (Token v)
      {
        return symbol_type (token::WRITE, std::move (v));
      }
#else
      static
      symbol_type
      make_WRITE (const Token& v)
      {
        return symbol_type (token::WRITE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARRAY (Token v)
      {
        return symbol_type (token::ARRAY, std::move (v));
      }
#else
      static
      symbol_type
      make_ARRAY (const Token& v)
      {
        return symbol_type (token::ARRAY, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OF (Token v)
      {
        return symbol_type (token::OF, std::move (v));
      }
#else
      static
      symbol_type
      make_OF (const Token& v)
      {
        return symbol_type (token::OF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RECORD (Token v)
      {
        return symbol_type (token::RECORD, std::move (v));
      }
#else
      static
      symbol_type
      make_RECORD (const Token& v)
      {
        return symbol_type (token::RECORD, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (Token v)
      {
        return symbol_type (token::RETURN, std::move (v));
      }
#else
      static
      symbol_type
      make_RETURN (const Token& v)
      {
        return symbol_type (token::RETURN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (Token v)
      {
        return symbol_type (token::INTEGER, std::move (v));
      }
#else
      static
      symbol_type
      make_INTEGER (const Token& v)
      {
        return symbol_type (token::INTEGER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR (Token v)
      {
        return symbol_type (token::CHAR, std::move (v));
      }
#else
      static
      symbol_type
      make_CHAR (const Token& v)
      {
        return symbol_type (token::CHAR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (Token v)
      {
        return symbol_type (token::ID, std::move (v));
      }
#else
      static
      symbol_type
      make_ID (const Token& v)
      {
        return symbol_type (token::ID, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTC (Token v)
      {
        return symbol_type (token::INTC, std::move (v));
      }
#else
      static
      symbol_type
      make_INTC (const Token& v)
      {
        return symbol_type (token::INTC, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHARC (Token v)
      {
        return symbol_type (token::CHARC, std::move (v));
      }
#else
      static
      symbol_type
      make_CHARC (const Token& v)
      {
        return symbol_type (token::CHARC, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (Token v)
      {
        return symbol_type (token::ASSIGN, std::move (v));
      }
#else
      static
      symbol_type
      make_ASSIGN (const Token& v)
      {
        return symbol_type (token::ASSIGN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQ (Token v)
      {
        return symbol_type (token::EQ, std::move (v));
      }
#else
      static
      symbol_type
      make_EQ (const Token& v)
      {
        return symbol_type (token::EQ, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LT (Token v)
      {
        return symbol_type (token::LT, std::move (v));
      }
#else
      static
      symbol_type
      make_LT (const Token& v)
      {
        return symbol_type (token::LT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (Token v)
      {
        return symbol_type (token::PLUS, std::move (v));
      }
#else
      static
      symbol_type
      make_PLUS (const Token& v)
      {
        return symbol_type (token::PLUS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (Token v)
      {
        return symbol_type (token::MINUS, std::move (v));
      }
#else
      static
      symbol_type
      make_MINUS (const Token& v)
      {
        return symbol_type (token::MINUS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR (Token v)
      {
        return symbol_type (token::STAR, std::move (v));
      }
#else
      static
      symbol_type
      make_STAR (const Token& v)
      {
        return symbol_type (token::STAR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV (Token v)
      {
        return symbol_type (token::DIV, std::move (v));
      }
#else
      static
      symbol_type
      make_DIV (const Token& v)
      {
        return symbol_type (token::DIV, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (Token v)
      {
        return symbol_type (token::LPAREN, std::move (v));
      }
#else
      static
      symbol_type
      make_LPAREN (const Token& v)
      {
        return symbol_type (token::LPAREN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (Token v)
      {
        return symbol_type (token::RPAREN, std::move (v));
      }
#else
      static
      symbol_type
      make_RPAREN (const Token& v)
      {
        return symbol_type (token::RPAREN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACKET (Token v)
      {
        return symbol_type (token::LBRACKET, std::move (v));
      }
#else
      static
      symbol_type
      make_LBRACKET (const Token& v)
      {
        return symbol_type (token::LBRACKET, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACKET (Token v)
      {
        return symbol_type (token::RBRACKET, std::move (v));
      }
#else
      static
      symbol_type
      make_RBRACKET (const Token& v)
      {
        return symbol_type (token::RBRACKET, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (Token v)
      {
        return symbol_type (token::DOT, std::move (v));
      }
#else
      static
      symbol_type
      make_DOT (const Token& v)
      {
        return symbol_type (token::DOT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOTDOT (Token v)
      {
        return symbol_type (token::DOTDOT, std::move (v));
      }
#else
      static
      symbol_type
      make_DOTDOT (const Token& v)
      {
        return symbol_type (token::DOTDOT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (Token v)
      {
        return symbol_type (token::COMMA, std::move (v));
      }
#else
      static
      symbol_type
      make_COMMA (const Token& v)
      {
        return symbol_type (token::COMMA, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMI (Token v)
      {
        return symbol_type (token::SEMI, std::move (v));
      }
#else
      static
      symbol_type
      make_SEMI (const Token& v)
      {
        return symbol_type (token::SEMI, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (Token v)
      {
        return symbol_type (token::COLON, std::move (v));
      }
#else
      static
      symbol_type
      make_COLON (const Token& v)
      {
        return symbol_type (token::COLON, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ERROR_TOKEN (Token v)
      {
        return symbol_type (token::ERROR_TOKEN, std::move (v));
      }
#else
      static
      symbol_type
      make_ERROR_TOKEN (const Token& v)
      {
        return symbol_type (token::ERROR_TOKEN, v);
      }
#endif


    class context
    {
    public:
      context (const BisonParser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const { return yyla_; }
      symbol_kind_type token () const { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const BisonParser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    BisonParser (const BisonParser&);
    /// Non copyable.
    BisonParser& operator= (const BisonParser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const signed char yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 131,     ///< Last index in yytable_.
      yynnts_ = 45,  ///< Number of nonterminal symbols.
      yyfinal_ = 5 ///< Termination state number.
    };


    // User arguments.
    snl::ParserDriver& driver;

  };

  inline
  BisonParser::symbol_kind_type
  BisonParser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
    };
    // Last valid token kind.
    const int code_max = 298;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  BisonParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_declare_part: // declare_part
        value.copy< DeclPart > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        value.copy< ExprPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.copy< FieldDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.copy< ParamDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.copy< ProcDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.copy< ProgramNode > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        value.copy< StmtPtr > (YY_MOVE (that.value));
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
        value.copy< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.copy< TypeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        value.copy< TypeSpecPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_access: // access
        value.copy< VarAccess > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.copy< VarDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        value.copy< std::vector<ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_list: // field_list
        value.copy< std::vector<FieldDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        value.copy< std::vector<ParamDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        value.copy< std::vector<ProcDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        value.copy< std::vector<StmtPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.copy< std::vector<TypeDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_access_list: // access_list
        value.copy< std::vector<VarAccess> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.copy< std::vector<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_id_list: // id_list
        value.copy< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  BisonParser::symbol_kind_type
  BisonParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  BisonParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  BisonParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_declare_part: // declare_part
        value.move< DeclPart > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_rel_exp: // rel_exp
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_variable: // variable
        value.move< ExprPtr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< FieldDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ParamDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.move< ProcDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
        value.move< ProgramNode > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_read_statement: // read_statement
      case symbol_kind::S_write_statement: // write_statement
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_id_statement: // id_statement
        value.move< StmtPtr > (YY_MOVE (s.value));
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
        value.move< Token > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< TypeDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_name: // type_name
      case symbol_kind::S_base_type: // base_type
      case symbol_kind::S_base_or_array_type: // base_or_array_type
      case symbol_kind::S_array_type: // array_type
      case symbol_kind::S_record_type: // record_type
        value.move< TypeSpecPtr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_access: // access
        value.move< VarAccess > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< VarDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_actual_param_list_opt: // actual_param_list_opt
      case symbol_kind::S_actual_param_list: // actual_param_list
        value.move< std::vector<ExprPtr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_list: // field_list
        value.move< std::vector<FieldDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param_dec_list_opt: // param_dec_list_opt
      case symbol_kind::S_param_dec_list: // param_dec_list
        value.move< std::vector<ParamDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_proc_dec: // proc_dec
        value.move< std::vector<ProcDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program_body: // program_body
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_seq: // stmt_seq
        value.move< std::vector<StmtPtr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_dec: // type_dec
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.move< std::vector<TypeDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_access_list: // access_list
        value.move< std::vector<VarAccess> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_var_dec: // var_dec
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.move< std::vector<VarDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_id_list: // id_list
        value.move< std::vector<std::string> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  inline
  BisonParser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  BisonParser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  BisonParser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  BisonParser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  BisonParser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  BisonParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  BisonParser::symbol_kind_type
  BisonParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  BisonParser::symbol_kind_type
  BisonParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

#line 8 "grammar/snl_parser.y"
} // snl
#line 2906 "include/snl_parser_generated.h"




#endif // !YY_YY_INCLUDE_SNL_PARSER_GENERATED_H_INCLUDED
