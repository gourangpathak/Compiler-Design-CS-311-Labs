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
#line 1 "1904119_parser.y"
  
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yylex(void);
    int yyerror(char*);
    int cnt = 0;
    int stCnt = 0;

    char cur_type[10];
    char cur_exp[50] ="";
    struct st_entry{
        char variable[50];
        char type[10]; 
        double expval;
        int irName;
    };
    struct st_entry symbol_table[50];

    void insert(char* var);
    char* typeChecker(char* var1,char* var2);
    int deepTypeChecker(char* var1,char* var2);
    struct st_entry fetch_entry(char* var);

    FILE *fp;
    void write_begin_lines();
    void write_end_lines();

    void write_alloc_instr();
    void write_load_instr(int name,struct st_entry var);
    void write_add_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2);
    void write_sub_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2);
    void write_mul_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2);
    void write_store_instr(int ir_var1,int ir_var2,char* type1,char* type2,double expval);


#line 109 "1904119_parser.tab.c"

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

#include "1904119_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_3_ = 3,                         /* '+'  */
  YYSYMBOL_4_ = 4,                         /* '-'  */
  YYSYMBOL_5_ = 5,                         /* '/'  */
  YYSYMBOL_6_ = 6,                         /* '*'  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_INTEGER_CONSTANT = 8,           /* INTEGER_CONSTANT  */
  YYSYMBOL_DOUBLE_CONSTANT = 9,            /* DOUBLE_CONSTANT  */
  YYSYMBOL_INT = 10,                       /* INT  */
  YYSYMBOL_DOUBLE = 11,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 12,                      /* CHAR  */
  YYSYMBOL_SEMICOLON = 13,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 14,                     /* COMMA  */
  YYSYMBOL_BEG = 15,                       /* BEG  */
  YYSYMBOL_END = 16,                       /* END  */
  YYSYMBOL_ASSIGN = 17,                    /* ASSIGN  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELIF = 19,                      /* ELIF  */
  YYSYMBOL_ELSE = 20,                      /* ELSE  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_WHILE = 24,                     /* WHILE  */
  YYSYMBOL_RETURN = 25,                    /* RETURN  */
  YYSYMBOL_RELOP = 26,                     /* RELOP  */
  YYSYMBOL_INVALID = 27,                   /* INVALID  */
  YYSYMBOL_28_ = 28,                       /* '('  */
  YYSYMBOL_29_ = 29,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_prog = 31,                      /* prog  */
  YYSYMBOL_32_1 = 32,                      /* $@1  */
  YYSYMBOL_funcDef = 33,                   /* funcDef  */
  YYSYMBOL_34_2 = 34,                      /* $@2  */
  YYSYMBOL_35_3 = 35,                      /* $@3  */
  YYSYMBOL_argList = 36,                   /* argList  */
  YYSYMBOL_arg = 37,                       /* arg  */
  YYSYMBOL_type = 38,                      /* type  */
  YYSYMBOL_declList = 39,                  /* declList  */
  YYSYMBOL_decl = 40,                      /* decl  */
  YYSYMBOL_41_4 = 41,                      /* $@4  */
  YYSYMBOL_varList = 42,                   /* varList  */
  YYSYMBOL_43_5 = 43,                      /* $@5  */
  YYSYMBOL_stmtList = 44,                  /* stmtList  */
  YYSYMBOL_stmt = 45,                      /* stmt  */
  YYSYMBOL_assignStmt = 46,                /* assignStmt  */
  YYSYMBOL_47_6 = 47,                      /* $@6  */
  YYSYMBOL_EXP = 48,                       /* EXP  */
  YYSYMBOL_TERM = 49,                      /* TERM  */
  YYSYMBOL_FACTOR = 50,                    /* FACTOR  */
  YYSYMBOL_ifStmt = 51,                    /* ifStmt  */
  YYSYMBOL_bExp = 52,                      /* bExp  */
  YYSYMBOL_whileStmt = 53,                 /* whileStmt  */
  YYSYMBOL_elseIfStmt = 54,                /* elseIfStmt  */
  YYSYMBOL_elseStmt = 55                   /* elseStmt  */
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
#define YYLAST   118

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  45
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  95

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


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
      28,    29,     6,     3,     2,     4,     2,     5,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    66,    66,    66,    68,    68,    68,    70,    70,    72,
      74,    74,    74,    76,    76,    78,    78,    81,    80,    82,
      84,    84,    86,    86,    86,    86,    86,    89,    88,    99,
     130,   162,   164,   192,   193,   195,   206,   210,   212,   214,
     216,   216,   216,   218,   220,   222
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
  "\"end of file\"", "error", "\"invalid token\"", "'+'", "'-'", "'/'",
  "'*'", "ID", "INTEGER_CONSTANT", "DOUBLE_CONSTANT", "INT", "DOUBLE",
  "CHAR", "SEMICOLON", "COMMA", "BEG", "END", "ASSIGN", "IF", "ELIF",
  "ELSE", "AND", "OR", "NOT", "WHILE", "RETURN", "RELOP", "INVALID", "'('",
  "')'", "$accept", "prog", "$@1", "funcDef", "$@2", "$@3", "argList",
  "arg", "type", "declList", "decl", "$@4", "varList", "$@5", "stmtList",
  "stmt", "assignStmt", "$@6", "EXP", "TERM", "FACTOR", "ifStmt", "bExp",
  "whileStmt", "elseIfStmt", "elseStmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -43,    11,    39,   -43,   -43,   -43,   -43,   -43,   -43,     7,
     -43,   -12,    39,    -8,    10,    19,    27,    39,   -43,    39,
     -43,   -43,    28,   -43,    47,    44,    51,    53,    74,    65,
     -43,    -1,   -43,   -43,   -43,   -43,   -43,   -43,    83,    92,
      60,    48,    48,    84,    48,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,     4,    31,   -43,    73,     6,    -9,    12,    46,
      77,    47,    60,    60,    94,    60,    60,    48,    60,    48,
      48,    96,    97,   -43,    98,   -43,    31,    31,   -43,   -43,
     -43,    88,     4,   -43,   -43,    84,    84,    84,   -43,    56,
      66,    76,   -43,   -43,   -43
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    10,    11,    12,     3,     4,     0,
       5,     0,     8,     0,     0,     0,     0,     0,     9,     0,
       7,    15,     0,    14,     0,     0,     0,     0,     0,     0,
      13,     0,    21,    22,    23,    24,    25,    26,    19,     0,
       0,     0,     0,     0,     0,     6,    20,    17,    16,    35,
      36,    37,    27,    31,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    18,    29,    30,    28,    33,
      32,     0,    39,    40,    41,     0,     0,     0,    42,     0,
       0,     0,    38,    44,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   -43,   -43,   -43,   -43,   -43,    99,     3,   -43,
      93,   -43,    57,   -43,   -42,   -31,   -43,   -43,   -37,    15,
      22,   -43,   -40,   -43,   -43,   -43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     7,     9,    11,    13,    14,    15,    22,
      23,    24,    39,    61,    31,    32,    33,    64,    56,    53,
      54,    34,    57,    35,    36,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      46,    59,    58,    52,    60,     8,    25,    62,    63,    62,
      63,     3,    69,    70,    10,    45,    12,    26,    27,    28,
      71,    16,    21,    29,    17,    21,    18,    81,    46,    83,
      84,    82,    68,    69,    70,    25,    65,    66,     4,     5,
       6,    72,    19,    89,    90,    91,    26,    27,    28,     4,
       5,     6,    29,    25,    38,    49,    50,    51,    46,    46,
      46,    40,    73,    25,    26,    27,    28,    49,    50,    51,
      29,    55,    92,    25,    26,    27,    28,    76,    77,    41,
      29,    42,    93,    25,    26,    27,    28,    79,    80,    43,
      29,    25,    94,    44,    26,    27,    28,    47,    69,    70,
      29,    67,    26,    27,    28,    48,    74,    78,    29,    69,
      70,    85,    86,    87,     0,    30,    20,    88,    75
};

static const yytype_int8 yycheck[] =
{
      31,    43,    42,    40,    44,     2,     7,     3,     4,     3,
       4,     0,    21,    22,     7,    16,    28,    18,    19,    20,
      29,    29,    19,    24,    14,    22,     7,    67,    59,    69,
      70,    68,    26,    21,    22,     7,     5,     6,    10,    11,
      12,    29,    15,    85,    86,    87,    18,    19,    20,    10,
      11,    12,    24,     7,     7,     7,     8,     9,    89,    90,
      91,    17,    16,     7,    18,    19,    20,     7,     8,     9,
      24,    23,    16,     7,    18,    19,    20,    62,    63,    28,
      24,    28,    16,     7,    18,    19,    20,    65,    66,    15,
      24,     7,    16,    28,    18,    19,    20,    14,    21,    22,
      24,    28,    18,    19,    20,    13,    29,    13,    24,    21,
      22,    15,    15,    15,    -1,    22,    17,    29,    61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,    32,     0,    10,    11,    12,    33,    38,    34,
       7,    35,    28,    36,    37,    38,    29,    14,     7,    15,
      37,    38,    39,    40,    41,     7,    18,    19,    20,    24,
      40,    44,    45,    46,    51,    53,    54,    55,     7,    42,
      17,    28,    28,    15,    28,    16,    45,    14,    13,     7,
       8,     9,    48,    49,    50,    23,    48,    52,    52,    44,
      52,    43,     3,     4,    47,     5,     6,    28,    26,    21,
      22,    29,    29,    16,    29,    42,    49,    49,    13,    50,
      50,    52,    48,    52,    52,    15,    15,    15,    29,    44,
      44,    44,    16,    16,    16
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    32,    31,    34,    35,    33,    36,    36,    37,
      38,    38,    38,    39,    39,    41,    40,    43,    42,    42,
      44,    44,    45,    45,    45,    45,    45,    47,    46,    48,
      48,    48,    49,    49,    49,    50,    50,    50,    51,    52,
      52,    52,    52,    53,    54,    55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     0,    11,     3,     0,     2,
       1,     1,     1,     2,     1,     0,     4,     0,     4,     1,
       2,     1,     1,     1,     1,     1,     1,     0,     5,     3,
       3,     1,     3,     3,     1,     1,     1,     1,     7,     3,
       3,     3,     4,     7,     7,     4
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
#line 66 "1904119_parser.y"
       { write_begin_lines(); }
#line 1210 "1904119_parser.tab.c"
    break;

  case 3: /* prog: $@1 funcDef  */
#line 66 "1904119_parser.y"
                                         { write_end_lines(); }
#line 1216 "1904119_parser.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 68 "1904119_parser.y"
               {strcpy(cur_type, (yyvsp[0].sval));}
#line 1222 "1904119_parser.tab.c"
    break;

  case 5: /* $@3: %empty  */
#line 68 "1904119_parser.y"
                                          { insert((yyvsp[0].sval)); }
#line 1228 "1904119_parser.tab.c"
    break;

  case 9: /* arg: type ID  */
#line 72 "1904119_parser.y"
              { strcpy(cur_type,(yyvsp[-1].sval)); insert((yyvsp[0].sval)); }
#line 1234 "1904119_parser.tab.c"
    break;

  case 10: /* type: INT  */
#line 74 "1904119_parser.y"
                {strcpy((yyval.sval),(yyvsp[0].sval));}
#line 1240 "1904119_parser.tab.c"
    break;

  case 11: /* type: DOUBLE  */
#line 74 "1904119_parser.y"
                                          {strcpy((yyval.sval),(yyvsp[0].sval));}
#line 1246 "1904119_parser.tab.c"
    break;

  case 12: /* type: CHAR  */
#line 74 "1904119_parser.y"
                                                                  {strcpy((yyval.sval),(yyvsp[0].sval));}
#line 1252 "1904119_parser.tab.c"
    break;

  case 15: /* $@4: %empty  */
#line 78 "1904119_parser.y"
                 { strcpy(cur_type,(yyvsp[0].sval)); }
#line 1258 "1904119_parser.tab.c"
    break;

  case 17: /* $@5: %empty  */
#line 81 "1904119_parser.y"
        { insert((yyvsp[-1].sval)); write_alloc_instr(); }
#line 1264 "1904119_parser.tab.c"
    break;

  case 19: /* varList: ID  */
#line 82 "1904119_parser.y"
             {insert((yyvsp[0].sval)); write_alloc_instr(); }
#line 1270 "1904119_parser.tab.c"
    break;

  case 27: /* $@6: %empty  */
#line 89 "1904119_parser.y"
            { 
                
                int check = deepTypeChecker((yyvsp[-2].sval), (yyvsp[0].eval).type);
                struct st_entry tmp= fetch_entry((yyvsp[-2].sval));
                if(check==1) {
                    write_store_instr(tmp.irName,(yyvsp[0].eval).irName,tmp.type,(yyvsp[0].eval).type,(yyvsp[0].eval).expval);
                }
                
            }
#line 1284 "1904119_parser.tab.c"
    break;

  case 29: /* EXP: EXP '+' TERM  */
#line 100 "1904119_parser.y"
      {   
          char inp1[50],inp2[50];
          if(strcmp((yyvsp[-2].eval).type,"int")!=0 || strcmp((yyvsp[-2].eval).type,"double")!=0 ) strcpy(inp1,(yyvsp[-2].eval).type);
          else strcpy(inp1,(yyvsp[-2].eval).variable);
          if(strcmp((yyvsp[0].eval).type,"int")!=0 || strcmp((yyvsp[0].eval).type,"double")!=0 ) strcpy(inp2,(yyvsp[0].eval).type);
          else strcpy(inp1,(yyvsp[0].eval).variable);

          if((strcmp((yyvsp[-2].eval).type,"IntConst")==0 && strcmp((yyvsp[0].eval).type,"IntConst")==0) || (strcmp((yyvsp[-2].eval).type,"DoubleConst")==0 && strcmp((yyvsp[0].eval).type,"DoubleConst")==0)  ) {
              (yyval.eval).expval= (yyvsp[-2].eval).expval + (yyvsp[0].eval).expval;
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
          }
          else if((strcmp((yyvsp[-2].eval).type,"IntConst")==0 && strcmp((yyvsp[0].eval).type,"DoubleConst")==0)){
              (yyval.eval).expval= (yyvsp[-2].eval).expval*1.0 + (yyvsp[0].eval).expval;
              strcpy((yyval.eval).type,(yyvsp[0].eval).type);
          }
          else if((strcmp((yyvsp[-2].eval).type,"DoubleConst")==0 && strcmp((yyvsp[0].eval).type,"IntConst")==0)){
              (yyval.eval).expval= (yyvsp[-2].eval).expval + (yyvsp[0].eval).expval*1.0;
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
          }
          
          if((strcmp((yyvsp[-2].eval).type,"IntConst")==0 && strcmp((yyvsp[0].eval).type,"IntConst")==0) || (strcmp((yyvsp[-2].eval).type,"DoubleConst")==0 && strcmp((yyvsp[0].eval).type,"DoubleConst")==0)  ) {
              (yyval.eval).expval= (yyvsp[-2].eval).expval + (yyvsp[0].eval).expval;
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
          }
          else{
            strcpy((yyval.eval).type,typeChecker(inp1,inp2)); 
            write_add_instr((yyvsp[-2].eval).irName,(yyvsp[0].eval).irName,(yyvsp[-2].eval).type,(yyvsp[0].eval).type,(yyvsp[-2].eval).expval,(yyvsp[0].eval).expval); 
            (yyval.eval).irName=stCnt-1;
          }
      }
#line 1319 "1904119_parser.tab.c"
    break;

  case 30: /* EXP: EXP '-' TERM  */
#line 130 "1904119_parser.y"
                     { 

            char inp1[50],inp2[50];
            if(strcmp((yyvsp[-2].eval).type,"int")!=0 || strcmp((yyvsp[-2].eval).type,"double")!=0 ) strcpy(inp1,(yyvsp[-2].eval).type);
            else strcpy(inp1,(yyvsp[-2].eval).variable);
            if(strcmp((yyvsp[0].eval).type,"int")!=0 || strcmp((yyvsp[0].eval).type,"double")!=0 ) strcpy(inp2,(yyvsp[0].eval).type);
            else strcpy(inp1,(yyvsp[0].eval).variable);

            if((strcmp((yyvsp[-2].eval).type,"IntConst")==0 && strcmp((yyvsp[0].eval).type,"IntConst")==0) || (strcmp((yyvsp[-2].eval).type,"DoubleConst")==0 && strcmp((yyvsp[0].eval).type,"DoubleConst")==0)  ) {
                (yyval.eval).expval= (yyvsp[-2].eval).expval - (yyvsp[0].eval).expval;
                strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
            }
            else if((strcmp((yyvsp[-2].eval).type,"IntConst")==0 && strcmp((yyvsp[0].eval).type,"DoubleConst")==0)){
                (yyval.eval).expval= (yyvsp[-2].eval).expval*1.0 - (yyvsp[0].eval).expval;
                strcpy((yyval.eval).type,(yyvsp[0].eval).type);
            }
            else if((strcmp((yyvsp[-2].eval).type,"DoubleConst")==0 && strcmp((yyvsp[0].eval).type,"IntConst")==0)){
                (yyval.eval).expval= (yyvsp[-2].eval).expval - (yyvsp[0].eval).expval*1.0;
                strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
            }

            if((strcmp((yyvsp[-2].eval).type,"IntConst")==0 && strcmp((yyvsp[0].eval).type,"IntConst")==0) || (strcmp((yyvsp[-2].eval).type,"DoubleConst")==0 && strcmp((yyvsp[0].eval).type,"DoubleConst")==0)  ) {
                (yyval.eval).expval= (yyvsp[-2].eval).expval - (yyvsp[0].eval).expval;
                strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
            }
            else{
            strcpy((yyval.eval).type,typeChecker(inp1,inp2)); 
            write_add_instr((yyvsp[-2].eval).irName,(yyvsp[0].eval).irName,(yyvsp[-2].eval).type,(yyvsp[0].eval).type,(yyvsp[-2].eval).expval,(yyvsp[0].eval).expval); 
            (yyval.eval).irName=stCnt-1;
            }

        }
#line 1356 "1904119_parser.tab.c"
    break;

  case 31: /* EXP: TERM  */
#line 162 "1904119_parser.y"
             {(yyval.eval)=(yyvsp[0].eval);}
#line 1362 "1904119_parser.tab.c"
    break;

  case 32: /* TERM: TERM '*' FACTOR  */
#line 165 "1904119_parser.y"
        {  
            
          char inp1[50],inp2[50];
          if(strcmp((yyvsp[-2].eval).type,"int")!=0 || strcmp((yyvsp[-2].eval).type,"double")!=0 ) strcpy(inp1,(yyvsp[-2].eval).type);
          else strcpy(inp1,(yyvsp[-2].eval).variable);
          if(strcmp((yyvsp[0].eval).type,"int")!=0 || strcmp((yyvsp[0].eval).type,"double")!=0 ) strcpy(inp2,(yyvsp[0].eval).type);
          else strcpy(inp1,(yyvsp[0].eval).variable);

          if((strcmp((yyvsp[-2].eval).type,"IntConst")==0 && strcmp((yyvsp[0].eval).type,"IntConst")==0) || (strcmp((yyvsp[-2].eval).type,"DoubleConst")==0 && strcmp((yyvsp[0].eval).type,"DoubleConst")==0)  ) {
              (yyval.eval).expval= (yyvsp[-2].eval).expval * (yyvsp[0].eval).expval;
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
          }
          else if((strcmp((yyvsp[-2].eval).type,"IntConst")==0 && strcmp((yyvsp[0].eval).type,"DoubleConst")==0)){
              (yyval.eval).expval= (yyvsp[-2].eval).expval*1.0 * (yyvsp[0].eval).expval;
              strcpy((yyval.eval).type,(yyvsp[0].eval).type);
          }
          else if((strcmp((yyvsp[-2].eval).type,"DoubleConst")==0 && strcmp((yyvsp[0].eval).type,"IntConst")==0)){
              (yyval.eval).expval= (yyvsp[-2].eval).expval * (yyvsp[0].eval).expval*1.0;
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
          }
          else{
            strcpy((yyval.eval).type,typeChecker(inp1,inp2)); 
            write_mul_instr((yyvsp[-2].eval).irName,(yyvsp[0].eval).irName,(yyvsp[-2].eval).type,(yyvsp[0].eval).type,(yyvsp[-2].eval).expval,(yyvsp[0].eval).expval); 
            (yyval.eval).irName=stCnt-1;
          }

        }
#line 1394 "1904119_parser.tab.c"
    break;

  case 33: /* TERM: TERM '/' FACTOR  */
#line 192 "1904119_parser.y"
                          {strcpy((yyval.eval).type,typeChecker((yyvsp[-2].eval).variable,(yyvsp[0].eval).variable));}
#line 1400 "1904119_parser.tab.c"
    break;

  case 34: /* TERM: FACTOR  */
#line 193 "1904119_parser.y"
                 {(yyval.eval)=(yyvsp[0].eval);}
#line 1406 "1904119_parser.tab.c"
    break;

  case 35: /* FACTOR: ID  */
#line 195 "1904119_parser.y"
            { 
              struct st_entry tmp = fetch_entry((yyvsp[0].sval)); 
              strcpy((yyval.eval).variable,tmp.variable); 
              strcpy((yyval.eval).type,tmp.type); 

              (yyval.eval).irName=stCnt;
              stCnt++;
              
              (yyval.eval).expval=tmp.expval; 
              write_load_instr((yyval.eval).irName,tmp);
            }
#line 1422 "1904119_parser.tab.c"
    break;

  case 36: /* FACTOR: INTEGER_CONSTANT  */
#line 207 "1904119_parser.y"
            {   strcpy((yyval.eval).type,"IntConst"); 
                (yyval.eval).expval=atof((yyvsp[0].sval));
            }
#line 1430 "1904119_parser.tab.c"
    break;

  case 37: /* FACTOR: DOUBLE_CONSTANT  */
#line 210 "1904119_parser.y"
                          {strcpy((yyval.eval).type,"DoubleConst"); (yyval.eval).expval=atof((yyvsp[0].sval)); }
#line 1436 "1904119_parser.tab.c"
    break;


#line 1440 "1904119_parser.tab.c"

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

#line 224 "1904119_parser.y"



struct st_entry fetch_entry(char* var){
    struct st_entry ans, tmp;
    int flag = 0;
    for(int i=0;i<cnt;i++){
        if(strcmp(symbol_table[i].variable,var) == 0){
            ans=symbol_table[i];
            flag=1;
            break;
        }
    }
    if(!flag){
        printf("----------> ERROR : Undeclared variable %s is encountered.                       <----------\n",var);
        strcpy(tmp.variable,"NULL");
        strcpy(tmp.type,"NULL");
        return tmp;
    }
    return ans;
}

void insert(char* var){
    // Inserting the variable & its type into the symbol table.

    for(int i=0;i<cnt;i++){
        if(strcmp(symbol_table[i].variable,var) == 0){      // If the variable name matched.
            if(strcmp(cur_type,symbol_table[i].type) == 0){ // If the type also matched.  
    
                printf("----------> ERROR : Redeclaration of the variable %s .                         <----------\n",var);
                return;
            }
            else{
                printf("----------> ERROR : Redeclaration of the variable %s with diff. data types.     <----------\n",var);
                return;
            }
        }
    }

    // Inserting the variable name and type into the symbol table.
    strcpy(symbol_table[cnt].variable,var);
    strcpy(symbol_table[cnt].type,cur_type);
    symbol_table[cnt].irName=stCnt;
    stCnt++;
    cnt++;
    return;
}

int deepTypeChecker(char *var1,char *var2){
    char type1[50],type2[50];
    if(strcmp(var1,"int")!=0 && strcmp(var1,"IntConst")!=0 && strcmp(var1,"double")!=0 && strcmp(var1,"DoubleConst")!=0 && strcmp(var1,"NULL")!=0 ){
        struct st_entry temp= fetch_entry(var1);
        strcpy(type1,temp.type);
        if(strcmp(type1,"IntConst")==0){
            strcpy(type1,"int");
        }
        else if(strcmp(type1,"DoubleConst")==0){
            strcpy(type1,"double");
        }
    }
    else{
        strcpy(type1,var1);
        if(strcmp(type1,"IntConst")==0){
            strcpy(type1,"int");
        }
        if(strcmp(type1,"DoubleConst")==0){
            strcpy(type1,"double");
        }
    }

    if(strcmp(var2,"int")!=0 &&  strcmp(var2,"IntConst")!=0 && strcmp(var2,"double")!=0 && strcmp(var2,"DoubleConst")!=0 && strcmp(var2,"NULL")!=0 ){
        struct st_entry temp= fetch_entry(var2);
        strcpy(type2,temp.type);
        if(strcmp(type2,"IntConst")==0){
            strcpy(type2,"int");
        }
        if(strcmp(type2,"DoubleConst")==0){
            strcpy(type2,"double");
        }
    }
    else{
        strcpy(type2,var2);
        if(strcmp(type2,"IntConst")==0){
            strcpy(type2,"int");
        }
        if(strcmp(type2,"DoubleConst")==0){
            strcpy(type2,"double");
        }
    }

    if(strcmp(type1,type2)==0 ){
        return 1;
    }
    else if (strcmp(type1,"NULL")==0 || strcmp( type2,"NULL")==0){
        printf("----------> ERROR : Types of LHS & RHS didn't match due to undeclared variable! <----------\n");
        return 0;
    }
    else{
        printf("----------> ERROR : Types of LHS & RHS didn't match!                            <----------\n");
        return 0;
    }
}


char* typeChecker(char *var1,char *var2){

    char type1[50],type2[50];
    if(strcmp(var1,"int")!=0 && strcmp(var1,"IntConst")!=0 && strcmp(var1,"double")!=0 && strcmp(var1,"DoubleConst")!=0 && strcmp(var1,"NULL")!=0){
        struct st_entry temp= fetch_entry(var1);
        strcpy(type1,temp.type);
    }
    else{
        strcpy(type1,var1);
    }

    if(strcmp(var2,"int")!=0 && strcmp(var2,"IntConst")!=0 &&  strcmp(var2,"double")!=0 &&  strcmp(var2,"DoubleConst")!=0 && strcmp(var2,"NULL")!=0){
        struct st_entry temp= fetch_entry(var2);
        strcpy(type2,temp.type);
    }
    else{
        strcpy(type2,var2);
    }

    if(strcmp(type1,"NULL")==0 || strcmp(type2,"NULL")==0 ){
        return "NULL";
    }
    else if(strcmp(type1,"IntConst")==0 && strcmp(type2,"IntConst")==0)
        return "IntConst";
    else if(strcmp(type1,"DoubleConst")==0 && strcmp(type2,"DoubleConst")==0)
        return "DoubleConst"; 
    else if(strcmp(type1,"int")==0 && strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 && strcmp(type2,"int")==0){
        return "int";
    }
    else if(strcmp(type1,"double")==0 && strcmp(type2,"DoubleConst")==0 || strcmp(type1,"DoubleConst")==0 && strcmp(type2,"double")==0) 
        return "double";
    else if(strcmp(type1,"double")==0 && strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 && strcmp(type2,"double")==0) 
        return "double";
    else if(strcmp(type1,"DoubleConst")==0 && strcmp(type2,"int")==0 || strcmp(type1,"int")==0 && strcmp(type2,"DoubleConst")==0){
        return "double";
    }
    else if(strcmp(type1,type2)==0){
        if(strcmp(type1,"int")==0 ){
            return "int";    
        }
        else{
            return "double";
        }
    }
    else{
        return "double";
    }
}


void write_begin_lines()
{   
    fp= fopen("1904119_output.ll","w");
    fprintf(fp,"; ModuleID = \'1.c\'\nsource_filename = \"1.c\"\ntarget datalayout = \"e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"\ntarget triple = \"x86_64-pc-windows-msvc19.27.29111\"\n\n; Function Attrs: noinline nounwind optnone uwtable\ndefine dso_local i32 @main() #0 {");
}

void write_end_lines()
{   
    fprintf(fp,"\n\tret i32 0\n}\n\nattributes #0 = { noinline nounwind optnone uwtable \"disable-tail-calls\"=\"false\" \"frame-pointer\"=\"none\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n\n!llvm.module.flags = !{!0, !1}\n!llvm.ident = !{!2}\n\n!0 = !{i32 1, !\"wchar_size\", i32 2}\n!1 = !{i32 7, !\"PIC Level\", i32 2}\n!2 = !{!\"clang version 12.0.1\"}");
}

void write_alloc_instr(){
    if(strcmp(cur_type,"int")==0){
        fprintf(fp,"\n\t%c%d = alloca i32, align 4",'%',stCnt-1);
    }
    if(strcmp(cur_type,"double")==0){
        fprintf(fp,"\n\t%c%d = alloca double, align 8",'%',stCnt-1);
    }
}

void write_load_instr(int name,struct st_entry var){
    if(strcmp(var.type,"int")==0){
        fprintf(fp,"\n\t%c%d =  load i32, i32* %c%d, align 4",'%',name,'%',var.irName);
    }
    if(strcmp(var.type,"double")==0){
        fprintf(fp,"\n\t%c%d = load double, double* %c%d, align 8",'%',name,'%',var.irName);
    }
}


void write_add_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        fprintf(fp,"\n\t%c%d = add nsw i32 %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        fprintf(fp,"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 ){
        if (strcmp(type1,"IntConst")==0 ){
            if(strcmp(type2,"int")==0)
                fprintf(fp,"\n\t%c%d = add nsw i32 %c%d,%d",'%',stCnt,'%',ir_var2,(int)exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            }
        }
        if (strcmp(type2,"IntConst")==0){
            if(strcmp(type1,"int")==0)
                fprintf(fp,"\n\t%c%d = add nsw i32 %c%d,%d",'%',stCnt,'%',ir_var1,(int)exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            }
        }
    }
    else if(strcmp(type2,"DoubleConst")==0 || strcmp(type1,"DoubleConst")==0){
        if (strcmp(type1,"DoubleConst")==0)
            if (strcmp(type2,"double")==0)
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val1);
            }
        if (strcmp(type2,"DoubleConst")==0)
            if(strcmp(type1,"double")==0)
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val2);
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir_var2);
        }
        if (strcmp(type2,"int")==0) {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',stCnt-1);
        }
    }
    stCnt++;
}


void write_sub_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        fprintf(fp,"\n\t%c%d = sub nsw i32 %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        fprintf(fp,"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 ){
        if (strcmp(type1,"IntConst")==0 ){
            if(strcmp(type2,"int")==0)
                fprintf(fp,"\n\t%c%d = sub nsw i32 %c%d,%d",'%',stCnt,'%',ir_var2,(int)exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            }
        }
        if (strcmp(type2,"IntConst")==0){
            if(strcmp(type1,"int")==0)
                fprintf(fp,"\n\t%c%d = sub nsw i32 %c%d,%d",'%',stCnt,'%',ir_var1,(int)exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            }
        }
    }
    else if(strcmp(type2,"DoubleConst")==0 || strcmp(type1,"DoubleConst")==0){
        if (strcmp(type1,"DoubleConst")==0)
            if (strcmp(type2,"double")==0)
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val1);
            }
        if (strcmp(type2,"DoubleConst")==0)
            if(strcmp(type1,"double")==0)
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val2);
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir_var2);
        }
        if (strcmp(type2,"int")==0) {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',stCnt-1);
        }
    }
    stCnt++;
}


void write_mul_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        fprintf(fp,"\n\t%c%d = mul nsw i32 %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        fprintf(fp,"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 ){
        if (strcmp(type1,"IntConst")==0 ){
            if(strcmp(type2,"int")==0)
                fprintf(fp,"\n\t%c%d = mul nsw i32 %c%d,%d",'%',stCnt,'%',ir_var2,(int)exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            }
        }
        if (strcmp(type2,"IntConst")==0){
            if(strcmp(type1,"int")==0)
                fprintf(fp,"\n\t%c%d = mul nsw i32 %c%d,%d",'%',stCnt,'%',ir_var1,(int)exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            }
        }
    }
    else if(strcmp(type2,"DoubleConst")==0 || strcmp(type1,"DoubleConst")==0){
        if (strcmp(type1,"DoubleConst")==0)
            if (strcmp(type2,"double")==0)
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val1);
            }
        if (strcmp(type2,"DoubleConst")==0)
            if(strcmp(type1,"double")==0)
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val2);
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir_var2);
        }
        if (strcmp(type2,"int")==0) {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',stCnt-1);
        }
    }
    stCnt++;
}

void write_store_instr(int ir_var1,int ir_var2,char* type1,char* type2,double expval){
    if(strcmp(type2,"IntConst")==0){
        int new_expval=(int)expval;
        fprintf(fp,"\n\tstore i32 %d, i32* %c%d, align 4",new_expval,'%',ir_var1);
    }
    else if(strcmp(type2,"DoubleConst")==0){
        fprintf(fp,"\n\tstore double %f, double* %c%d, align 8",expval,'%',ir_var1);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        fprintf(fp,"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',ir_var2,'%',ir_var1);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        fprintf(fp,"\n\tstore double %c%d, double* %c%d, align 8",'%',ir_var2,'%',ir_var1);
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            fprintf(fp,"\n\t%c%d = fptosi double %c%d  to i32",'%',stCnt,'%',ir_var2);
            stCnt++;
            fprintf(fp,"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',stCnt-1,'%',ir_var1);
        }
        if (strcmp(type2,"int")==0) {
            fprintf(fp,"\n\t%c%d = fptosi i32 %c%d  to double",'%',stCnt,'%',ir_var1);
            stCnt++;
            fprintf(fp,"\n\tstore double %c%d, double* %c%d, align 8",'%',stCnt-1,'%',ir_var2);
        }
    }
}


int main(int argc, char **argv) {
	yyparse();
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("|   variable              type     | \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for(int i=0;i<cnt;i++){
        printf("| \t%s\t\t%s\t   |\n",symbol_table[i].variable,symbol_table[i].type);
    }
}

int yyerror(char *s){
    fprintf(stderr, "error : %s\n", s);
}
