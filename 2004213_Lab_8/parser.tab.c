/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

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

#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
int yylex(void);
int yyerror(char *);
void write_init_lines();
void write_closing_lines();

// A structure for the entry in the symbol table which stores the name of the variable along with its type
struct entry {
    char var_name[50];
    char var_type[10];
    int num;
};

// A temprory string to copy type
char temp[200];

// A variable to store the size of the table
int size_of_table = 0;
int count = 0;

// An Array of type entry of size 200
struct entry symbol_table[200];

// Signature for the method to add an element to the table
void ADD(char *name, char *type);


// Signature for the method to get an element to the table
int GET(char *name);

char* check_type(char* a,char* b);
FILE * fptr;

#line 108 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_BOOL = 5,                       /* BOOL  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_INT_CONST = 7,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 8,                /* FLOAT_CONST  */
  YYSYMBOL_SEMICOLON = 9,                  /* SEMICOLON  */
  YYSYMBOL_COMMA = 10,                     /* COMMA  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELIF = 12,                      /* ELIF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_NOT = 16,                       /* NOT  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_RELOP = 19,                     /* RELOP  */
  YYSYMBOL_20_ = 20,                       /* '('  */
  YYSYMBOL_21_ = 21,                       /* ')'  */
  YYSYMBOL_22_ = 22,                       /* '{'  */
  YYSYMBOL_23_ = 23,                       /* '}'  */
  YYSYMBOL_24_ = 24,                       /* '='  */
  YYSYMBOL_25_ = 25,                       /* '+'  */
  YYSYMBOL_26_ = 26,                       /* '-'  */
  YYSYMBOL_27_ = 27,                       /* '*'  */
  YYSYMBOL_28_ = 28,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 29,                  /* $accept  */
  YYSYMBOL_prog = 30,                      /* prog  */
  YYSYMBOL_31_1 = 31,                      /* $@1  */
  YYSYMBOL_funcDef = 32,                   /* funcDef  */
  YYSYMBOL_33_2 = 33,                      /* $@2  */
  YYSYMBOL_argList = 34,                   /* argList  */
  YYSYMBOL_arg = 35,                       /* arg  */
  YYSYMBOL_type = 36,                      /* type  */
  YYSYMBOL_declList = 37,                  /* declList  */
  YYSYMBOL_decl = 38,                      /* decl  */
  YYSYMBOL_39_3 = 39,                      /* $@3  */
  YYSYMBOL_varList = 40,                   /* varList  */
  YYSYMBOL_41_4 = 41,                      /* $@4  */
  YYSYMBOL_stmtList = 42,                  /* stmtList  */
  YYSYMBOL_stmt = 43,                      /* stmt  */
  YYSYMBOL_assignStmt = 44,                /* assignStmt  */
  YYSYMBOL_EXP = 45,                       /* EXP  */
  YYSYMBOL_TERM = 46,                      /* TERM  */
  YYSYMBOL_FACTOR = 47,                    /* FACTOR  */
  YYSYMBOL_ifStmt = 48,                    /* ifStmt  */
  YYSYMBOL_bExp = 49,                      /* bExp  */
  YYSYMBOL_whileStmt = 50,                 /* whileStmt  */
  YYSYMBOL_elseIfStmt = 51,                /* elseIfStmt  */
  YYSYMBOL_elseStmt = 52,                  /* elseStmt  */
  YYSYMBOL_forStmt = 53                    /* forStmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   142

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   274


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      20,    21,    27,    25,     2,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,    23,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    59,    62,    62,    64,    64,    67,    70,
      70,    70,    72,    72,    75,    75,    78,    78,    85,    95,
      95,    97,    97,    97,    97,    97,    97,    99,   125,   126,
     186,   193,   194,   195,   204,   217,   220,   225,   227,   227,
     227,   227,   227,   229,   231,   231,   233,   235
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INT", "BOOL",
  "FLOAT", "INT_CONST", "FLOAT_CONST", "SEMICOLON", "COMMA", "IF", "ELIF",
  "ELSE", "AND", "OR", "NOT", "WHILE", "FOR", "RELOP", "'('", "')'", "'{'",
  "'}'", "'='", "'+'", "'-'", "'*'", "'/'", "$accept", "prog", "$@1",
  "funcDef", "$@2", "argList", "arg", "type", "declList", "decl", "$@3",
  "varList", "$@4", "stmtList", "stmt", "assignStmt", "EXP", "TERM",
  "FACTOR", "ifStmt", "bExp", "whileStmt", "elseIfStmt", "elseStmt",
  "forStmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -61,    13,    29,   -61,   -61,   -61,   -61,   -61,    15,   -61,
       2,    29,    10,    38,    61,    49,    29,   -61,    29,   -61,
     -61,    87,    51,    75,    60,    83,    92,    97,     3,   -61,
     -61,    31,   -61,   -61,   -61,   -61,    29,   101,   -61,   106,
       9,     9,   121,   -61,   -61,   107,   108,   -61,   118,   -61,
     -61,   -61,    -2,    91,   -61,    85,   109,    48,   -10,    -6,
       9,     9,    87,    75,   -61,   106,   106,   106,   106,     9,
     106,     9,     9,   110,   111,    93,    37,    36,   -61,    91,
      91,   -61,   -61,    72,    95,   -61,   -61,    87,    87,   128,
     112,   -61,   -61,    39,    52,   113,    87,   -61,   -61,   106,
      65,    90,   122,   114,   116,    87,    87,    74,    78,   -61,
     -61
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    10,     9,    11,     3,     0,     4,
       0,     7,     0,     0,     0,     0,     0,     8,    13,     6,
      14,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,    13,    16,    15,     0,
       0,     0,     0,     5,    19,     0,     0,    12,     0,    34,
      35,    36,     0,    30,    33,    34,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    28,
      29,    31,    32,     0,    38,    39,    40,     0,     0,     0,
       0,    46,    41,     0,     0,     0,     0,    37,    43,     0,
       0,     0,    44,     0,     0,     0,     0,     0,     0,    47,
      45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,   -61,   -61,   -61,   123,     1,   104,   -61,
     -61,    79,   -61,   -60,   -28,    99,   -38,    57,    58,   -61,
     -31,   -61,   -61,   -61,   -61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     7,    10,    12,    13,    14,    21,    22,
      23,    38,    48,    28,    29,    30,    57,    53,    54,    31,
      58,    32,    33,    34,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    52,    77,     8,    71,    72,    24,    64,    71,    72,
      59,    73,    55,     3,    25,    74,    50,    51,     9,    20,
      26,    27,    11,    65,    66,    56,    43,    93,    94,    75,
      76,    15,    84,     4,     5,     6,   100,    20,    83,    24,
      85,    86,    24,    45,    46,   107,   108,    25,    16,    44,
      25,    71,    72,    26,    27,    24,    26,    27,    90,    91,
      36,   101,    97,    25,    17,    44,    44,    70,    24,    26,
      27,    18,    44,    65,    66,    98,    25,    24,    37,    44,
      44,    24,    26,    27,    39,    25,    71,    72,   102,    25,
      24,    26,    27,    92,   -42,    26,    27,   109,    25,   -42,
     -42,   110,    89,    40,    26,    27,   -42,    71,    72,    49,
     -18,   103,    41,    50,    51,    65,    66,    42,    67,    68,
      65,    66,    79,    80,    24,    81,    82,    61,    63,    69,
      62,    95,    87,    88,    96,   104,   105,    99,   106,    19,
      47,    60,    78
};

static const yytype_int8 yycheck[] =
{
      28,    39,    62,     2,    14,    15,     3,     9,    14,    15,
      41,    21,     3,     0,    11,    21,     7,     8,     3,    18,
      17,    18,    20,    25,    26,    16,    23,    87,    88,    60,
      61,    21,    70,     4,     5,     6,    96,    36,    69,     3,
      71,    72,     3,    12,    13,   105,   106,    11,    10,    77,
      11,    14,    15,    17,    18,     3,    17,    18,    21,    23,
       9,    99,    23,    11,     3,    93,    94,    19,     3,    17,
      18,    22,   100,    25,    26,    23,    11,     3,     3,   107,
     108,     3,    17,    18,    24,    11,    14,    15,    23,    11,
       3,    17,    18,    21,     9,    17,    18,    23,    11,    14,
      15,    23,     9,    20,    17,    18,    21,    14,    15,     3,
       9,    21,    20,     7,     8,    25,    26,    20,    27,    28,
      25,    26,    65,    66,     3,    67,    68,    20,    10,    20,
      22,     3,    22,    22,    22,    13,    22,    24,    22,    16,
      36,    42,    63
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    30,    31,     0,     4,     5,     6,    32,    36,     3,
      33,    20,    34,    35,    36,    21,    10,     3,    22,    35,
      36,    37,    38,    39,     3,    11,    17,    18,    42,    43,
      44,    48,    50,    51,    52,    53,     9,     3,    40,    24,
      20,    20,    20,    23,    43,    12,    13,    37,    41,     3,
       7,     8,    45,    46,    47,     3,    16,    45,    49,    49,
      44,    20,    22,    10,     9,    25,    26,    27,    28,    20,
      19,    14,    15,    21,    21,    49,    49,    42,    40,    46,
      46,    47,    47,    49,    45,    49,    49,    22,    22,     9,
      21,    23,    21,    42,    42,     3,    22,    23,    23,    24,
      42,    45,    23,    21,    13,    22,    22,    42,    42,    23,
      23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    29,    31,    30,    33,    32,    34,    34,    35,    36,
      36,    36,    37,    37,    39,    38,    41,    40,    40,    42,
      42,    43,    43,    43,    43,    43,    43,    44,    45,    45,
      45,    46,    46,    46,    47,    47,    47,    48,    49,    49,
      49,    49,    49,    50,    51,    51,    52,    53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,    10,     3,     0,     2,     1,
       1,     1,     3,     0,     0,     3,     0,     4,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     3,
       1,     3,     3,     1,     1,     1,     1,     7,     3,     3,
       3,     4,     1,     7,     8,    12,     5,    12
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 59 "parser.y"
       { write_init_lines(); }
#line 1219 "parser.tab.c"
    break;

  case 3: /* prog: $@1 funcDef  */
#line 59 "parser.y"
                                       { write_closing_lines(); printf("Accepted\n");}
#line 1225 "parser.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 62 "parser.y"
                  {fprintf(fptr, "define i32 @main() #0 {\n"); ADD((yyvsp[0].intval), (yyvsp[-1].stringval));}
#line 1231 "parser.tab.c"
    break;

  case 5: /* funcDef: type ID $@2 '(' argList ')' '{' declList stmtList '}'  */
#line 62 "parser.y"
                                                                                                                       {fprintf(fptr, "ret i32 0\n}\n");}
#line 1237 "parser.tab.c"
    break;

  case 8: /* arg: type ID  */
#line 67 "parser.y"
              { ADD((yyvsp[0].intval), (yyvsp[-1].stringval)); }
#line 1243 "parser.tab.c"
    break;

  case 9: /* type: BOOL  */
#line 70 "parser.y"
            {strcpy((yyval.stringval), (yyvsp[0].intval));}
#line 1249 "parser.tab.c"
    break;

  case 10: /* type: INT  */
#line 70 "parser.y"
                                    {strcpy((yyval.stringval), (yyvsp[0].intval));}
#line 1255 "parser.tab.c"
    break;

  case 11: /* type: FLOAT  */
#line 70 "parser.y"
                                                              {strcpy((yyval.stringval), (yyvsp[0].floatval));}
#line 1261 "parser.tab.c"
    break;

  case 14: /* $@3: %empty  */
#line 75 "parser.y"
            {strcpy(temp, (yyvsp[0].stringval));}
#line 1267 "parser.tab.c"
    break;

  case 16: /* $@4: %empty  */
#line 78 "parser.y"
             {
    if (!strcmp(temp, "int")) {
        fprintf(fptr, "%%%d = alloca i32, align 4\n", size_of_table);
    }
    else {
        fprintf(fptr, "%%%d = alloca double, align 8\n", size_of_table);
    }
}
#line 1280 "parser.tab.c"
    break;

  case 17: /* varList: ID $@4 COMMA varList  */
#line 85 "parser.y"
                {ADD((yyvsp[-3].intval), temp);}
#line 1286 "parser.tab.c"
    break;

  case 18: /* varList: ID  */
#line 85 "parser.y"
                                      {
    ADD((yyvsp[0].intval), temp);
    if (!strcmp(temp, "int")) {
        fprintf(fptr, "%%%d = alloca i32, align 4\n", size_of_table);
    }
    else {
        fprintf(fptr, "%%%d = alloca double, align 8\n", size_of_table);
    }
    }
#line 1300 "parser.tab.c"
    break;

  case 27: /* assignStmt: ID '=' EXP SEMICOLON  */
#line 100 "parser.y"
            {
                // First Check if there is an entry in the table
                if (GET((yyvsp[-3].intval)) >= 0){
                    // If the type of the ID is int while that of Exp is bool or vice-versa, raise a warning
                    if (!strcmp(symbol_table[GET((yyvsp[-3].intval))].var_type, "int") && !strcmp((yyvsp[-1].stringval), "boolean")) printf("WARNING, Boolean assigned to Int\n");
                    else if(!strcmp(symbol_table[GET((yyvsp[-3].intval))].var_type, "boolean") && !strcmp((yyvsp[-1].stringval), "int")) printf("WARNING, Boolean assigned to Int\n");
                }

                if (!strcmp((yyvsp[-1].stringval).expType, "int_const")) {
                    int temp = (yyvsp[-1].stringval).expVal;
                    fprintf(fptr, "store i32 %d, i32* %%%d, align 4\n", temp, symbol_table[GET((yyvsp[-3].intval))].num);
                } 
                else if (!strcmp((yyvsp[-1].stringval).expType, "int")) {
                    fprintf(fptr, "store i32 %%%d, i32* %%%d, align 4\n", (yyvsp[-1].stringval).irName, symbol_table[GET((yyvsp[-3].intval))].num);
                }
                 else if (!strcmp((yyvsp[-1].stringval).expType, "double_const")) {
                    fprintf(fptr, "store double %.6e, double* %%%d, align 8\n", (yyvsp[-1].stringval).expVal, symbol_table[GET((yyvsp[-3].intval))].num);
                } 
                else {
                    fprintf(fptr, "store double %%%d, double* %%%d, align 8\n", (yyvsp[-1].stringval).irName, symbol_table[GET((yyvsp[-3].intval))].num);
                }
            }
#line 1327 "parser.tab.c"
    break;

  case 28: /* EXP: EXP '+' TERM  */
#line 125 "parser.y"
                    {strcpy((yyval.stringval), check_type((yyvsp[-2].stringval), (yyvsp[0].stringval)));}
#line 1333 "parser.tab.c"
    break;

  case 29: /* EXP: EXP '-' TERM  */
#line 126 "parser.y"
                    {strcpy((yyval.stringval), check_type((yyvsp[-2].stringval), (yyvsp[0].stringval)));
                if (!strcmp((yyvsp[-2].stringval).expType, "int_const") && !strcmp((yyvsp[0].stringval).expType, "int_const")) {
                    strcpy((yyval.stringval).expType, (yyvsp[-2].stringval).expType);
                    (yyval.stringval).irName = (yyvsp[-2].stringval).irName;
                    (yyval.stringval).expVal = (yyvsp[-2].stringval).expVal - (yyvsp[0].stringval).expVal;
                }
                else if (!strcmp((yyvsp[-2].stringval).expType, "double_const") && !strcmp((yyvsp[0].stringval).expType, "double_const")) {
                    strcpy((yyval.stringval).expType, (yyvsp[-2].stringval).expType);
                    (yyval.stringval).irName = (yyvsp[-2].stringval).irName;
                    (yyval.stringval).expVal = (yyvsp[-2].stringval).expVal - (yyvsp[0].stringval).expVal;
                }
                else if (!strcmp((yyvsp[-2].stringval).expType, "int") && !strcmp((yyvsp[0].stringval).expType, "int_const")) {
                    strcpy((yyval.stringval).expType, (yyvsp[-2].stringval).expType);
                    count++;
                    (yyval.stringval).irName = count;
                    int tempval = (yyvsp[0].stringval).expVal;
                    int tempir = (yyvsp[-2].stringval).irName;
                    fprintf(fptr, "%%%d = sub nsw i32 %%%d, %d\n", count, tempir, tempval);
                }
                else if (!strcmp((yyvsp[-2].stringval).expType, "double") && !strcmp((yyvsp[0].stringval).expType, "double_const")) {
                    strcpy((yyval.stringval).expType, (yyvsp[-2].stringval).expType);
                    count++;
                    (yyval.stringval).irName = count;
                    double tempval = (yyvsp[0].stringval).expVal;
                    int tempir = (yyvsp[-2].stringval).irName;
                    fprintf(fptr, "%%%d = fsub double %%%d, %.6e\n", count, tempir, tempval);
                }
                else if (!strcmp((yyvsp[-2].stringval).expType, "int_const") && !strcmp((yyvsp[0].stringval).expType, "int")) {
                    strcpy((yyval.stringval).expType, (yyvsp[0].stringval).expType);
                    count++;
                    (yyval.stringval).irName = count;
                    int tempval = (yyvsp[-2].stringval).expVal;
                    int tempir = (yyvsp[0].stringval).irName;
                    fprintf(fptr, "%%%d = sub nsw i32 %d, %%%d\n", count, tempval, tempir);
                }
                else if (!strcmp((yyvsp[-2].stringval).expType, "double_const") && !strcmp((yyvsp[0].stringval).expType, "double")) {
                    strcpy((yyval.stringval).expType, (yyvsp[0].stringval).expType);
                    count++;
                    (yyval.stringval).irName = count;
                    double tempval = (yyvsp[-2].stringval).expVal;
                    int tempir = (yyvsp[0].stringval).irName;
                    fprintf(fptr, "%%%d = fsub double %.6e, %%%d\n", count, tempval, tempir);
                }
                else if (!strcmp((yyvsp[-2].stringval).expType, "int") && !strcmp((yyvsp[0].stringval).expType, "int")) {
                    strcpy((yyval.stringval).expType, (yyvsp[-2].stringval).expType);
                    count++;
                    (yyval.stringval).irName = count;
                    int tempir1 = (yyvsp[-2].stringval).irName;
                    int tempir2 = (yyvsp[0].stringval).irName;
                    fprintf(fptr, "%%%d = sub nsw i32 %%%d, %%%d\n", count, tempir1, tempir2);
                }
                else if (!strcmp((yyvsp[-2].stringval).expType, "double") && !strcmp((yyvsp[0].stringval).expType, "double")) {
                    strcpy((yyval.stringval).expType, (yyvsp[-2].stringval).expType);
                    count++;
                    (yyval.stringval).irName = count;
                    int tempir1 = (yyvsp[-2].stringval).irName;
                    int tempir2 = (yyvsp[0].stringval).irName;
                    fprintf(fptr, "%%%d = fsub double %%%d, %%%d\n", count, tempir1, tempir2);
                }
    }
#line 1398 "parser.tab.c"
    break;

  case 30: /* EXP: TERM  */
#line 186 "parser.y"
           {strcpy((yyval.stringval), (yyvsp[0].stringval));
    strcpy((yyval.stringval).expType, (yyvsp[0].stringval).expType); 
    (yyval.stringval).expVal = (yyvsp[0].stringval).expVal;
    (yyval.stringval).irName = (yyvsp[0].stringval).irName;
    }
#line 1408 "parser.tab.c"
    break;

  case 31: /* TERM: TERM '*' FACTOR  */
#line 193 "parser.y"
                       {strcpy((yyval.stringval), check_type((yyvsp[-2].stringval), (yyvsp[0].stringval)));}
#line 1414 "parser.tab.c"
    break;

  case 32: /* TERM: TERM '/' FACTOR  */
#line 194 "parser.y"
                       {strcpy((yyval.stringval), check_type((yyvsp[-2].stringval), (yyvsp[0].stringval)));}
#line 1420 "parser.tab.c"
    break;

  case 33: /* TERM: FACTOR  */
#line 195 "parser.y"
              {strcpy((yyval.stringval), (yyvsp[0].stringval));
      strcpy((yyval.stringval).expType, (yyvsp[0].stringval).expType);
      (yyval.stringval).expVal = (yyvsp[0].stringval).expVal;
      (yyval.stringval).irName = (yyvsp[0].stringval).irName;
     }
#line 1430 "parser.tab.c"
    break;

  case 34: /* FACTOR: ID  */
#line 204 "parser.y"
             {int idx = GET((yyvsp[0].intval)); if (idx != -1) {strcpy((yyval.stringval), symbol_table[idx].var_type);} else {strcpy((yyval.stringval), "Not Declared");}
strcpy((yyval.stringval).expType, symbol_table[symbol_table_lookup((yyvsp[0].intval))].type);
    if (!strcmp((yyval.stringval).expType, "int")) {
        count++;
        (yyval.stringval).irName = count;
        fprintf(fptr, "%%%d = load i32, i32* %%%d, align 4\n", count, symbol_table[GET((yyvsp[0].intval))].num);
    } 
    else {
        count++;
        (yyval.stringval).irName = count;
        fprintf(fptr, "%%%d = load double, double* %%%d, align 8\n", count, symbol_table[GET((yyvsp[0].intval))].num);
    }
}
#line 1448 "parser.tab.c"
    break;

  case 35: /* FACTOR: INT_CONST  */
#line 217 "parser.y"
                   {strcpy((yyval.stringval), "int");
       strcpy((yyval.stringval).expType, "int_const");
       }
#line 1456 "parser.tab.c"
    break;

  case 36: /* FACTOR: FLOAT_CONST  */
#line 220 "parser.y"
                     {strcpy((yyval.stringval), "float");
       strcpy((yyval.stringval).expType, "double_const"); 
       }
#line 1464 "parser.tab.c"
    break;


#line 1468 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 236 "parser.y"


// Method to Add an entry to the symbol table
void ADD(char *name, char *type) {
    // check if the symbol is alredy present
    int alredyPresent = 0;
    // Loop through the table
	for (int i=0; i<size_of_table; i++){
        // check If the variable is alredy present 
		if (strcmp(name, symbol_table[i].var_name) == 0) {
			alredyPresent = 1;
		}
	}
    // If variable not present
	if (alredyPresent == 0){
        // Add a new entry
		strcpy(symbol_table[size_of_table].var_name, name);
        strcpy(symbol_table[size_of_table].var_type, type);
        // Increment the size of the table
		size_of_table++;
	}
}

// Method to Get the index of an entry in the table
int GET(char *name) {
    // Iterate over the table
	for (int i=0; i<size_of_table; i++){
        // If found
		if (strcmp(name, symbol_table[i].var_name) == 0) {
            // return its index
			return i;
		}
	}
    printf("ERROR, Identifier %s not declared\n", name);
    // If not found return -1
    return -1;
}

void write_init_lines() {
    fprintf(fptr, "; ModuleID = 'out.ll'\nsource_filename = \"out.ll\"\ntarget datalayout = \"e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"\ntarget triple = \"x86_64-pc-linux-gnu\"\n\n; Function Attrs: noinline nounwind optnone uwtable\n");
}

void write_closing_lines() {
    fprintf(fptr, "\nattributes #0 = { noinline nounwind optnone uwtable \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"frame-pointer\"=\"all\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n\n");
    fprintf(fptr, "!llvm.module.flags = !{!0}\n!llvm.ident = !{!1}\n\n");
    fprintf(fptr, "!0 = !{i32 1, !\"wchar_size\", i32 4}\n!1 = !{!\"Debian clang version 11.0.1-2\"}");
    fclose(fptr);
}

int main(int argc, char **argv) {
    fptr = fopen("out.ll", "w");
	yyparse();
    // Print the symbol Table
    printf("\n================================  SYMBOL TABLE   ================================\n");
    for (int i=0; i<size_of_table; i++){
		printf("Symbol Name: %s, Symbol Type: %s\n", symbol_table[i].var_name, symbol_table[i].var_type);
}
}

// Ensure type checking 
char* check_type(char* a, char* b)
{
    if(!strcmp(a, b)) {
        return a;
    }
    else if(!strcmp(a, "Not Declared") || !strcmp(b, "Not Declared")) {
        return "Not Declared";
    }
    else {
        return "int";
    }

}

int yyerror(char *s) {
    fprintf(stderr, "Error occured %s\n", s);
}
