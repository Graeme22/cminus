/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "scanType.h"
#include "ast.h"
#include "exp.h"
#include "var.h"
#include "fun.h"
#include "stmt.h"
#include "parser.tab.h"

extern int yylex();
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern AST *tree;

void yyerror(const char *msg) {
	printf("Error: %s while parsing `%s` on line %d.\n", msg, yytext, yylineno);
}

#line 93 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOLCONST = 258,
    NUMCONST = 259,
    CHARCONST = 260,
    STRINGCONST = 261,
    ID = 262,
    IF = 263,
    WHILE = 264,
    FOR = 265,
    STATIC = 266,
    INT = 267,
    BOOL = 268,
    CHAR = 269,
    IN = 270,
    ELSE = 271,
    RETURN = 272,
    BREAK = 273,
    EQ = 274,
    ADDASS = 275,
    SUBASS = 276,
    DIVASS = 277,
    MULASS = 278,
    LEQ = 279,
    GEQ = 280,
    NEQ = 281,
    DEC = 282,
    INC = 283,
    ADD = 284,
    SUB = 285,
    LT = 286,
    GT = 287,
    MUL = 288,
    DIV = 289,
    MOD = 290,
    RAND = 291,
    ASS = 292,
    AND = 293,
    OR = 294,
    NOT = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "parser.y"

	TokenData *tokenData;
	AST *ast;

#line 191 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
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


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

#define YYUNDEFTOK  2
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      46,    47,     2,     2,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    41,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    54,    60,    64,    74,    80,    85,    91,
      95,   100,   104,   110,   114,   119,   123,   127,   137,   141,
     146,   151,   155,   159,   164,   170,   174,   179,   183,   193,
     197,   202,   206,   210,   214,   218,   222,   227,   231,   236,
     240,   245,   250,   255,   259,   264,   268,   273,   277,   282,
     286,   291,   295,   300,   304,   309,   319,   324,   328,   332,
     336,   340,   344,   348,   353,   357,   362,   366,   371,   375,
     380,   384,   389,   393,   397,   401,   405,   409,   414,   418,
     423,   427,   432,   436,   441,   445,   449,   454,   458,   463,
     467,   471,   476,   480,   485,   489,   494,   498,   502,   507,
     512,   517,   521,   525,   530,   534,   538,   542
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOLCONST", "NUMCONST", "CHARCONST",
  "STRINGCONST", "ID", "IF", "WHILE", "FOR", "STATIC", "INT", "BOOL",
  "CHAR", "IN", "ELSE", "RETURN", "BREAK", "EQ", "ADDASS", "SUBASS",
  "DIVASS", "MULASS", "LEQ", "GEQ", "NEQ", "DEC", "INC", "ADD", "SUB",
  "LT", "GT", "MUL", "DIV", "MOD", "RAND", "ASS", "AND", "OR", "NOT",
  "';'", "','", "':'", "'['", "']'", "'('", "')'", "'{'", "'}'", "$accept",
  "declarationList", "declaration", "varDeclaration",
  "scopedVarDeclaration", "varDeclList", "varDeclInitialize", "varDeclId",
  "typeSpecifier", "funDeclaration", "params", "paramList",
  "paramTypeList", "paramIdList", "paramId", "statement", "matched",
  "unmatched", "expressionStmt", "compoundStmt", "localDeclarations",
  "statementList", "matchedSelectionStmt", "unmatchedSelectionStmt",
  "matchedIterationStmt", "unmatchedIterationStmt", "returnStmt",
  "breakStmt", "expression", "simpleExpression", "andExpression",
  "unaryRelExpression", "relExpression", "relop", "sumExpression", "sumop",
  "mulExpression", "mulop", "unaryExpression", "unaryop", "factor",
  "mutable", "immutable", "call", "args", "argList", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    59,    44,    58,    91,    93,    40,    41,   123,   125
};
# endif

#define YYPACT_NINF (-133)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      98,   -39,  -133,  -133,  -133,   151,  -133,  -133,    19,  -133,
      95,  -133,  -133,   -25,     8,  -133,    16,    61,    35,    42,
    -133,    92,    95,  -133,    99,   138,    70,    77,  -133,    85,
      95,    78,    73,    84,  -133,  -133,  -133,  -133,  -133,    76,
    -133,  -133,  -133,   138,   138,    90,   100,  -133,  -133,   156,
     119,  -133,   143,  -133,    88,  -133,  -133,  -133,    91,    61,
      93,   109,   110,    94,   116,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   118,    90,
       7,  -133,  -133,    85,   138,  -133,   113,   138,   138,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,   143,   143,  -133,
    -133,  -133,   143,  -133,   138,  -133,  -133,   138,   138,   154,
    -133,   121,  -133,    51,  -133,   138,   138,   138,   138,  -133,
    -133,   138,  -133,  -133,   120,   124,  -133,   100,  -133,    41,
     119,  -133,   125,    -2,     1,   157,  -133,    95,  -133,    99,
       6,  -133,  -133,  -133,  -133,  -133,  -133,   138,  -133,    85,
      85,   162,    99,    38,  -133,  -133,  -133,  -133,   161,  -133,
    -133,   136,    75,  -133,    85,    85,  -133,  -133,  -133,  -133,
    -133
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    15,    16,    17,     0,     3,     4,     0,     5,
      21,     1,     2,    13,     0,    10,    11,     0,     0,    20,
      23,     0,    21,     6,     0,     0,    27,    24,    26,     0,
       0,     0,     0,    13,     9,   107,   104,   105,   106,    94,
      89,    90,    91,     0,     0,    12,    65,    67,    69,    71,
      79,    83,     0,    88,    93,    92,    97,    98,     0,     0,
       0,     0,     0,     0,     0,    40,    43,    19,    29,    30,
      31,    32,    33,    37,    34,    38,    35,    36,     0,    63,
      93,    22,    14,     0,   101,    68,     0,     0,     0,    76,
      72,    75,    77,    80,    81,    73,    74,     0,     0,    84,
      85,    86,     0,    87,     0,    28,    25,     0,     0,     0,
      53,     0,    55,    45,    39,     0,     0,     0,     0,    62,
      61,     0,    18,   103,     0,   100,    96,    64,    66,    70,
      78,    82,     0,     0,     0,     0,    54,     0,    42,     0,
       0,    57,    58,    60,    59,    56,    99,     0,    95,     0,
       0,     0,     0,     0,    41,    44,   102,    47,    29,    49,
      51,     0,     0,     8,     0,     0,     7,    46,    48,    50,
      52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,   185,  -133,  -133,  -114,   167,  -133,     0,  -133,
     170,  -133,   163,  -133,   135,   -80,  -132,  -107,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -43,   -23,
     108,   -35,  -133,  -133,   101,  -133,   102,  -133,   -46,  -133,
    -133,   -21,  -133,  -133,  -133,  -133,  -133
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,   138,    14,    15,    16,    17,     9,
      18,    19,    20,    27,    28,    67,    68,    69,    70,    71,
     113,   140,    72,    73,    74,    75,    76,    77,    78,    79,
      46,    47,    48,    97,    49,    98,    50,   102,    51,    52,
      53,    80,    55,    56,   124,   125,    57
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       8,    86,    45,   122,    54,     8,   103,    10,    85,    35,
      36,    37,    38,    39,    60,    61,    62,   158,   159,    21,
     111,    22,    54,    63,    64,   153,    13,   115,   116,   117,
     118,    54,   167,   169,   119,   120,    40,    87,   162,    41,
      87,   123,    42,   160,   121,   149,    43,    65,   150,    23,
      24,   104,    44,   128,    66,   154,   131,   168,   170,    25,
     155,   132,   137,     2,     3,     4,    54,    54,    26,   157,
      93,    94,   141,   142,   143,   144,    54,    54,   145,   163,
      24,    54,    29,    30,   133,   134,    54,    54,    35,    36,
      37,    38,    39,    60,    61,    62,    31,    35,    36,    37,
      38,    39,    63,    64,   156,     1,    33,     2,     3,     4,
       2,     3,     4,   139,    58,    40,   166,    24,    41,    59,
      83,    42,    84,    82,    40,    43,    65,    41,    21,    87,
      42,    44,   104,    66,    43,   110,   105,   152,    88,   107,
      44,    35,    36,    37,    38,    39,    35,    36,    37,    38,
      39,    11,    99,   100,   101,   108,   109,   112,     1,   114,
     126,   135,   136,     2,     3,     4,   147,   146,    40,   161,
     148,    41,   151,    40,    42,    89,    41,   164,    43,    42,
      90,    91,    92,   165,    44,    93,    94,    95,    96,    44,
      12,    34,    32,    81,   106,   127,     0,     0,   129,     0,
     130
};

static const yytype_int16 yycheck[] =
{
       0,    44,    25,    83,    25,     5,    52,    46,    43,     3,
       4,     5,     6,     7,     8,     9,    10,   149,   150,    44,
      63,    46,    43,    17,    18,   139,     7,    20,    21,    22,
      23,    52,   164,   165,    27,    28,    30,    39,   152,    33,
      39,    84,    36,   150,    37,    47,    40,    41,    47,    41,
      42,    44,    46,    88,    48,    49,   102,   164,   165,    43,
     140,   104,    11,    12,    13,    14,    87,    88,     7,   149,
      29,    30,   115,   116,   117,   118,    97,    98,   121,    41,
      42,   102,    47,    41,   107,   108,   107,   108,     3,     4,
       5,     6,     7,     8,     9,    10,     4,     3,     4,     5,
       6,     7,    17,    18,   147,     7,     7,    12,    13,    14,
      12,    13,    14,   113,    44,    30,    41,    42,    33,    42,
      47,    36,    46,    45,    30,    40,    41,    33,    44,    39,
      36,    46,    44,    48,    40,    41,    45,   137,    38,    46,
      46,     3,     4,     5,     6,     7,     3,     4,     5,     6,
       7,     0,    33,    34,    35,    46,    46,    41,     7,    41,
      47,     7,    41,    12,    13,    14,    42,    47,    30,     7,
      45,    33,    15,    30,    36,    19,    33,    16,    40,    36,
      24,    25,    26,    47,    46,    29,    30,    31,    32,    46,
       5,    24,    22,    30,    59,    87,    -1,    -1,    97,    -1,
      98
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    12,    13,    14,    51,    52,    53,    58,    59,
      46,     0,    52,     7,    55,    56,    57,    58,    60,    61,
      62,    44,    46,    41,    42,    43,     7,    63,    64,    47,
      41,     4,    60,     7,    56,     3,     4,     5,     6,     7,
      30,    33,    36,    40,    46,    79,    80,    81,    82,    84,
      86,    88,    89,    90,    91,    92,    93,    96,    44,    42,
       8,     9,    10,    17,    18,    41,    48,    65,    66,    67,
      68,    69,    72,    73,    74,    75,    76,    77,    78,    79,
      91,    62,    45,    47,    46,    81,    78,    39,    38,    19,
      24,    25,    26,    29,    30,    31,    32,    83,    85,    33,
      34,    35,    87,    88,    44,    45,    64,    46,    46,    46,
      41,    78,    41,    70,    41,    20,    21,    22,    23,    27,
      28,    37,    65,    78,    94,    95,    47,    80,    81,    84,
      86,    88,    78,    79,    79,     7,    41,    11,    54,    58,
      71,    78,    78,    78,    78,    78,    47,    42,    45,    47,
      47,    15,    58,    55,    49,    65,    78,    65,    66,    66,
      67,     7,    55,    41,    16,    47,    41,    66,    67,    66,
      67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    51,    52,    52,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    66,    66,    66,    66,    67,    67,    68,
      68,    69,    70,    70,    71,    71,    72,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    78,    78,    78,    78,
      78,    78,    78,    78,    79,    79,    80,    80,    81,    81,
      82,    82,    83,    83,    83,    83,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    87,    88,    88,    89,
      89,    89,    90,    90,    91,    91,    92,    92,    92,    93,
      94,    94,    95,    95,    96,    96,    96,    96
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     3,     4,     3,     3,
       1,     1,     3,     1,     4,     1,     1,     1,     6,     5,
       1,     0,     3,     1,     2,     3,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     4,     2,     0,     2,     0,     7,     5,     7,     5,
       7,     5,     7,     2,     3,     2,     3,     3,     3,     3,
       3,     2,     2,     1,     3,     1,     3,     1,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     1,     1,     4,
       1,     0,     3,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 51 "parser.y"
        {
		tree->append((yyvsp[0].ast));
	}
#line 1619 "parser.tab.c"
    break;

  case 3:
#line 55 "parser.y"
        {
		tree->append((yyvsp[0].ast));
		(yyvsp[0].ast)->isFirst = true;
	}
#line 1628 "parser.tab.c"
    break;

  case 4:
#line 61 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1636 "parser.tab.c"
    break;

  case 5:
#line 65 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1644 "parser.tab.c"
    break;

  case 6:
#line 75 "parser.y"
        {
		(yyval.ast) = (yyvsp[-1].ast);
		((Var *)(yyval.ast))->setTypeAndStatic((yyvsp[-2].tokenData)->tokenString, false);
	}
#line 1653 "parser.tab.c"
    break;

  case 7:
#line 81 "parser.y"
        {
		(yyval.ast) = (yyvsp[-1].ast);
		((Var *)(yyval.ast))->setTypeAndStatic((yyvsp[-2].tokenData)->tokenString, true);
	}
#line 1662 "parser.tab.c"
    break;

  case 8:
#line 86 "parser.y"
        {
		(yyval.ast) = (yyvsp[-1].ast);
		((Var *)(yyval.ast))->setTypeAndStatic((yyvsp[-2].tokenData)->tokenString, false);
	}
#line 1671 "parser.tab.c"
    break;

  case 9:
#line 92 "parser.y"
        {
		(yyval.ast)->append((yyvsp[0].ast));
	}
#line 1679 "parser.tab.c"
    break;

  case 10:
#line 96 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1687 "parser.tab.c"
    break;

  case 11:
#line 101 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1695 "parser.tab.c"
    break;

  case 12:
#line 105 "parser.y"
        {
		(yyval.ast) = (yyvsp[-2].ast);
		(yyval.ast)->addChild((yyvsp[0].ast), 0);
	}
#line 1704 "parser.tab.c"
    break;

  case 13:
#line 111 "parser.y"
        {
		(yyval.ast) = new Var((yyvsp[0].tokenData));
	}
#line 1712 "parser.tab.c"
    break;

  case 14:
#line 115 "parser.y"
        {
		(yyval.ast) = new Var((yyvsp[-3].tokenData), (yyvsp[-1].tokenData));
	}
#line 1720 "parser.tab.c"
    break;

  case 15:
#line 120 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 1728 "parser.tab.c"
    break;

  case 16:
#line 124 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 1736 "parser.tab.c"
    break;

  case 17:
#line 128 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 1744 "parser.tab.c"
    break;

  case 18:
#line 138 "parser.y"
        {
		(yyval.ast) = new FunDeclaration((yyvsp[-5].tokenData), (yyvsp[-4].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 1752 "parser.tab.c"
    break;

  case 19:
#line 142 "parser.y"
        {
		(yyval.ast) = new FunDeclaration((yyvsp[-4].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 1760 "parser.tab.c"
    break;

  case 20:
#line 147 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1768 "parser.tab.c"
    break;

  case 21:
#line 151 "parser.y"
        {
		(yyval.ast) = NULL;
	}
#line 1776 "parser.tab.c"
    break;

  case 22:
#line 156 "parser.y"
        {
		(yyval.ast)->append((yyvsp[0].ast));
	}
#line 1784 "parser.tab.c"
    break;

  case 23:
#line 160 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1792 "parser.tab.c"
    break;

  case 24:
#line 165 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
		((Var *)(yyval.ast))->setTypeAndStatic((yyvsp[-1].tokenData)->tokenString, false);
	}
#line 1801 "parser.tab.c"
    break;

  case 25:
#line 171 "parser.y"
        {
		(yyval.ast)->append((yyvsp[0].ast));
	}
#line 1809 "parser.tab.c"
    break;

  case 26:
#line 175 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1817 "parser.tab.c"
    break;

  case 27:
#line 180 "parser.y"
        {
		(yyval.ast) = new Par((yyvsp[0].tokenData), false);
	}
#line 1825 "parser.tab.c"
    break;

  case 28:
#line 184 "parser.y"
        {
		(yyval.ast) = new Par((yyvsp[-2].tokenData), true);
	}
#line 1833 "parser.tab.c"
    break;

  case 29:
#line 194 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1841 "parser.tab.c"
    break;

  case 30:
#line 198 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1849 "parser.tab.c"
    break;

  case 31:
#line 203 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1857 "parser.tab.c"
    break;

  case 32:
#line 207 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1865 "parser.tab.c"
    break;

  case 33:
#line 211 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1873 "parser.tab.c"
    break;

  case 34:
#line 215 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1881 "parser.tab.c"
    break;

  case 35:
#line 219 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1889 "parser.tab.c"
    break;

  case 36:
#line 223 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1897 "parser.tab.c"
    break;

  case 37:
#line 228 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1905 "parser.tab.c"
    break;

  case 38:
#line 232 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1913 "parser.tab.c"
    break;

  case 39:
#line 237 "parser.y"
        {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 1921 "parser.tab.c"
    break;

  case 40:
#line 241 "parser.y"
        {
		(yyval.ast) = NULL;
	}
#line 1929 "parser.tab.c"
    break;

  case 41:
#line 246 "parser.y"
        {
		(yyval.ast) = new CompoundStatement((yylsp[-3]).first_line, (yyvsp[-2].ast), (yyvsp[-1].ast));
	}
#line 1937 "parser.tab.c"
    break;

  case 42:
#line 251 "parser.y"
        {
		(yyval.ast)->append((yyvsp[0].ast));
	}
#line 1945 "parser.tab.c"
    break;

  case 43:
#line 255 "parser.y"
        {
		(yyval.ast) = new AST();
	}
#line 1953 "parser.tab.c"
    break;

  case 44:
#line 260 "parser.y"
        {
		(yyval.ast)->append((yyvsp[0].ast));
	}
#line 1961 "parser.tab.c"
    break;

  case 45:
#line 264 "parser.y"
        {
		(yyval.ast) = new AST();
	}
#line 1969 "parser.tab.c"
    break;

  case 46:
#line 269 "parser.y"
        {
		(yyval.ast) = new If((yylsp[-6]).first_line, (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 1977 "parser.tab.c"
    break;

  case 47:
#line 274 "parser.y"
        {
		(yyval.ast) = new If((yylsp[-4]).first_line, (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 1985 "parser.tab.c"
    break;

  case 48:
#line 278 "parser.y"
        {
		(yyval.ast) = new If((yylsp[-6]).first_line, (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 1993 "parser.tab.c"
    break;

  case 49:
#line 283 "parser.y"
        {
		(yyval.ast) = new While((yylsp[-4]).first_line, (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2001 "parser.tab.c"
    break;

  case 50:
#line 287 "parser.y"
        {
		(yyval.ast) = new For((yylsp[-6]).first_line, (yyvsp[-4].tokenData), (yyvsp[-2].tokenData), (yyvsp[0].ast));
	}
#line 2009 "parser.tab.c"
    break;

  case 51:
#line 292 "parser.y"
        {
		(yyval.ast) = new While((yylsp[-4]).first_line, (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2017 "parser.tab.c"
    break;

  case 52:
#line 296 "parser.y"
        {
		(yyval.ast) = new For((yylsp[-6]).first_line, (yyvsp[-4].tokenData), (yyvsp[-2].tokenData), (yyvsp[0].ast));
	}
#line 2025 "parser.tab.c"
    break;

  case 53:
#line 301 "parser.y"
        {
		(yyval.ast) = new Return((yylsp[-1]).first_line);
	}
#line 2033 "parser.tab.c"
    break;

  case 54:
#line 305 "parser.y"
        {
		(yyval.ast) = new Return((yylsp[-2]).first_line, (yyvsp[-1].ast));
	}
#line 2041 "parser.tab.c"
    break;

  case 55:
#line 310 "parser.y"
        {
		(yyval.ast) = new Break((yylsp[-1]).first_line);
	}
#line 2049 "parser.tab.c"
    break;

  case 56:
#line 320 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
		(yyvsp[-2].ast)->initialized = true;
	}
#line 2058 "parser.tab.c"
    break;

  case 57:
#line 325 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2066 "parser.tab.c"
    break;

  case 58:
#line 329 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2074 "parser.tab.c"
    break;

  case 59:
#line 333 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2082 "parser.tab.c"
    break;

  case 60:
#line 337 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2090 "parser.tab.c"
    break;

  case 61:
#line 341 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[0].tokenData), (yyvsp[-1].ast));
	}
#line 2098 "parser.tab.c"
    break;

  case 62:
#line 345 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[0].tokenData), (yyvsp[-1].ast));
	}
#line 2106 "parser.tab.c"
    break;

  case 63:
#line 349 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2114 "parser.tab.c"
    break;

  case 64:
#line 354 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2122 "parser.tab.c"
    break;

  case 65:
#line 358 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2130 "parser.tab.c"
    break;

  case 66:
#line 363 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2138 "parser.tab.c"
    break;

  case 67:
#line 367 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2146 "parser.tab.c"
    break;

  case 68:
#line 372 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[0].ast));
	}
#line 2154 "parser.tab.c"
    break;

  case 69:
#line 376 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2162 "parser.tab.c"
    break;

  case 70:
#line 381 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2170 "parser.tab.c"
    break;

  case 71:
#line 385 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2178 "parser.tab.c"
    break;

  case 72:
#line 390 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2186 "parser.tab.c"
    break;

  case 73:
#line 394 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2194 "parser.tab.c"
    break;

  case 74:
#line 398 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2202 "parser.tab.c"
    break;

  case 75:
#line 402 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2210 "parser.tab.c"
    break;

  case 76:
#line 406 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2218 "parser.tab.c"
    break;

  case 77:
#line 410 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2226 "parser.tab.c"
    break;

  case 78:
#line 415 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2234 "parser.tab.c"
    break;

  case 79:
#line 419 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2242 "parser.tab.c"
    break;

  case 80:
#line 424 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2250 "parser.tab.c"
    break;

  case 81:
#line 428 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2258 "parser.tab.c"
    break;

  case 82:
#line 433 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[-2].ast), (yyvsp[0].ast));
	}
#line 2266 "parser.tab.c"
    break;

  case 83:
#line 437 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2274 "parser.tab.c"
    break;

  case 84:
#line 442 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2282 "parser.tab.c"
    break;

  case 85:
#line 446 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2290 "parser.tab.c"
    break;

  case 86:
#line 450 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2298 "parser.tab.c"
    break;

  case 87:
#line 455 "parser.y"
        {
		(yyval.ast) = new Operation((yyvsp[-1].tokenData), (yyvsp[0].ast));
	}
#line 2306 "parser.tab.c"
    break;

  case 88:
#line 459 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2314 "parser.tab.c"
    break;

  case 89:
#line 464 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2322 "parser.tab.c"
    break;

  case 90:
#line 468 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2330 "parser.tab.c"
    break;

  case 91:
#line 472 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2338 "parser.tab.c"
    break;

  case 92:
#line 477 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2346 "parser.tab.c"
    break;

  case 93:
#line 481 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2354 "parser.tab.c"
    break;

  case 94:
#line 486 "parser.y"
        {
		(yyval.ast) = new VarAccess((yyvsp[0].tokenData));
	}
#line 2362 "parser.tab.c"
    break;

  case 95:
#line 490 "parser.y"
        {
		(yyval.ast) = new ArrayAccess((yylsp[-2]).first_line, (yyvsp[-3].ast), (yyvsp[-1].ast));
	}
#line 2370 "parser.tab.c"
    break;

  case 96:
#line 495 "parser.y"
        {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 2378 "parser.tab.c"
    break;

  case 97:
#line 499 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2386 "parser.tab.c"
    break;

  case 98:
#line 503 "parser.y"
        {
		(yyval.ast) = new Constant((yyvsp[0].tokenData));
	}
#line 2394 "parser.tab.c"
    break;

  case 99:
#line 508 "parser.y"
        {
		(yyval.ast) = new Call((yyvsp[-3].tokenData), (yyvsp[-1].ast));
	}
#line 2402 "parser.tab.c"
    break;

  case 100:
#line 513 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2410 "parser.tab.c"
    break;

  case 101:
#line 517 "parser.y"
        {
		(yyval.ast) = NULL;
	}
#line 2418 "parser.tab.c"
    break;

  case 102:
#line 522 "parser.y"
        {
		(yyval.ast)->append((yyvsp[0].ast));
	}
#line 2426 "parser.tab.c"
    break;

  case 103:
#line 526 "parser.y"
        {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 2434 "parser.tab.c"
    break;

  case 104:
#line 531 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2442 "parser.tab.c"
    break;

  case 105:
#line 535 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2450 "parser.tab.c"
    break;

  case 106:
#line 539 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2458 "parser.tab.c"
    break;

  case 107:
#line 543 "parser.y"
        {
		(yyval.tokenData) = (yyvsp[0].tokenData);
	}
#line 2466 "parser.tab.c"
    break;


#line 2470 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 547 "parser.y"
