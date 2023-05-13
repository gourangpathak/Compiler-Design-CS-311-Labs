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
#line 1 "1904119_parser.y"

    // Including all the required standard libraries.
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    // Declaring the standard parser related functions.
    int yylex(void);
    int yyerror(char*);

    // Declaring the character arrays ( Similar to strings ) to store the Type & expression.
    char cur_type[50];
    char cur_exp[100] ="";

    // Initialising the counters.
    int cnt = 0;
    int stCnt = 0;

    // Defining the file pointer.
    FILE *fp;

    // Custom Data Structure to represent the symbol table's entry.
    struct st_entry{
        char variable[100];
        char type[50]; 
        double eVal;
        int    irName; 
    }; 

    // Declaring the symbol table using above defined custom data structure.
    struct st_entry symbol_table[100];

    // Defining the array of strings to store the LLVM code being generated. Its corresponding index pointer is i.
    char fBuffer[100*100][100*100]; 
    int i=0;
    
    // Declaring the functions that convert to LLVM IR language.
    void allocInstr();
    void loadInstr(int name,struct st_entry var);
    void storeInstr(int ir1,int ir2,char* t1,char* t2,double eVal);
    void addInstr(int ir1,int ir2,char* t1,char* t2,double e1,double e2);
    void subInstr(int ir1,int ir2,char* t1,char* t2,double e1,double e2);
    void mulInstr(int ir1,int ir2,char* t1,char* t2,double e1,double e2);

    // Declaring the functions that insertEntry & fetch entries from symbol table.
    void insertEntry(char* var);
    struct st_entry getEntry(char* var);

    // Declaring the functions that perform type checking of given expression.
    char* typeChecker(char* v1,char* v2);
    int deepTypeChecker(char* v1,char* v2);
    
    // Declaring the functions that add the conditional expressions and do BackPatching to fill the labels.
    int condExpAdder(double e1, char *exp1, int ir1, double e2, char *exp2, int ir2, char op);
    void doBackPatch(int cnt, int lbl, int list[] );

    // Declaring the functions that add the stub code.
    void starter();
    void ender();

#line 131 "1904119_parser.tab.c"

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
#ifndef YY_YY_1904119_PARSER_TAB_H_INCLUDED
# define YY_YY_1904119_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NOT = 258,
    AND = 259,
    OR = 260,
    BEG = 261,
    END = 262,
    SEMICOLON = 263,
    IF = 264,
    ELSE = 265,
    ELSEIF = 266,
    COMMA = 267,
    WHILE = 268,
    RETURN = 269,
    RELOP = 270,
    ID = 271,
    INT_CONST = 272,
    FLOAT_CONST = 273,
    INT = 274,
    DOUBLE = 275,
    CHAR = 276
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 63 "1904119_parser.y"


    double fval;
    int    ival;
    char   sval[20];

    struct eStruct
    {
        char variable[100];
        char type[20]; 
        double eVal;
        int    irName; 
        
        // For boolean expressions, we have True & False Lists.
        struct blList
        {
            int ele[50];
            int cnt;
        } TRUE_List, FALSE_List;

    } eval;

    struct stmtStruct
    {   
        // For statements, we have Next list.
        struct slist    
        {
            int ele[50];
            int cnt;
        } nxtLst;
    } stmtVal;
    

#line 239 "1904119_parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_1904119_PARSER_TAB_H_INCLUDED  */



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
#define YYLAST   95

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  104

#define YYUNDEFTOK  2
#define YYMAXUTOK   276


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
      26,    27,     4,     5,     2,     6,     2,     3,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      19,    20,    21,    22,    23,    24,    25
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   113,   113,   113,   117,   117,   117,   119,   119,   121,
     126,   127,   128,   130,   130,   132,   132,   134,   134,   135,
     137,   139,   139,   141,   142,   142,   144,   154,   189,   224,
     228,   264,   265,   267,   280,   285,   291,   290,   319,   319,
     319,   321,   323,   325,   327,   340,   340,   342,   343,   343,
     343,   344,   346
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'/'", "'*'", "'+'", "'-'", "NOT", "AND",
  "OR", "BEG", "END", "SEMICOLON", "IF", "ELSE", "ELSEIF", "COMMA",
  "WHILE", "RETURN", "RELOP", "ID", "INT_CONST", "FLOAT_CONST", "INT",
  "DOUBLE", "CHAR", "'('", "')'", "'='", "'{'", "'}'", "'>'", "$accept",
  "prog", "$@1", "funcDef", "$@2", "$@3", "argList", "arg", "type",
  "declList", "decl", "$@4", "varList", "$@5", "sList", "sLists", "stmt",
  "assnStmt", "exp", "TERM", "FACTOR", "ifStmt", "$@6", "el", "else_coll",
  "elseIf", "M", "rexp", "bexp", "whileStmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,    47,    42,    43,    45,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,    40,    41,    61,   123,
     125,    62
};
# endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -42,     5,   -11,   -42,   -42,   -42,   -42,   -42,   -42,    -2,
     -42,   -17,   -11,    -1,    23,    32,    50,   -11,   -42,   -11,
     -42,   -42,    41,   -42,    36,    49,    51,    48,   -42,    67,
     -42,   -42,   -42,   -42,   -42,    63,    68,    12,    12,    26,
     -42,    -9,   -42,   -42,    12,   -42,   -42,   -42,    12,    -4,
      46,   -42,   -42,     8,    13,    39,   -42,    36,    54,    16,
      26,    26,    26,    26,    26,    26,    12,    12,   -42,    71,
     -42,   -42,   -42,    46,    46,    62,    62,   -42,   -42,   -42,
     -42,    72,    -9,    -9,    73,   -42,   -42,    74,    55,    76,
      57,   -42,   -42,   -42,    -9,    12,    77,    28,   -42,    58,
      -9,    59,    55,   -42
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    10,    11,    12,     3,     4,     0,
       5,     0,     8,     0,     0,     0,     0,     0,     9,     0,
       7,    15,    22,    14,     0,     0,     0,     0,    13,     0,
      20,    43,    23,    24,    25,    19,     0,     0,     0,     0,
       6,    22,    17,    16,     0,    33,    34,    35,     0,    46,
      29,    32,    48,     0,     0,     0,    21,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    43,     0,
      26,    18,    47,    27,    28,    45,    44,    31,    30,    49,
      50,     0,    22,    22,     0,    36,    52,     0,    40,     0,
       0,    37,    38,    39,    22,     0,     0,     0,    41,     0,
      22,     0,    40,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,   -42,   -42,   -42,   -42,    75,     1,   -42,
      69,   -42,    33,   -42,   -41,    52,   -42,   -42,   -32,    11,
       9,   -42,   -42,    -8,   -42,   -42,    27,   -42,   -38,   -42
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     7,     9,    11,    13,    14,    15,    22,
      23,    24,    36,    57,    29,    30,    31,    32,    49,    50,
      51,    33,    87,    91,    92,    93,    41,    52,    53,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      54,    60,    61,     8,    25,     3,    58,    55,    26,    12,
      59,    27,     4,     5,     6,    62,    66,    67,    10,    44,
      21,    66,    67,    21,    66,    67,    16,    63,    79,    80,
      75,    76,    45,    46,    47,    68,    66,    67,    48,    17,
      69,    84,    85,    72,    60,    61,    45,    46,    47,    64,
      65,    70,    18,    96,    25,    99,    35,    97,    26,   101,
      19,    27,    66,    67,     4,     5,     6,    60,    61,    89,
      90,    73,    74,    77,    78,    37,    39,    38,    40,    42,
      43,    82,    83,    95,    86,    88,    94,   100,    98,   102,
      71,    28,    20,    56,   103,    81
};

static const yytype_int8 yycheck[] =
{
      38,     5,     6,     2,    13,     0,    44,    39,    17,    26,
      48,    20,    23,    24,    25,    19,     8,     9,    20,     7,
      19,     8,     9,    22,     8,     9,    27,    31,    66,    67,
      62,    63,    20,    21,    22,    27,     8,     9,    26,    16,
      27,    82,    83,    27,     5,     6,    20,    21,    22,     3,
       4,    12,    20,    94,    13,    27,    20,    95,    17,   100,
      10,    20,     8,     9,    23,    24,    25,     5,     6,    14,
      15,    60,    61,    64,    65,    26,    28,    26,    11,    16,
      12,    10,    10,    26,    11,    11,    10,    29,    11,    30,
      57,    22,    17,    41,   102,    68
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,    34,     0,    23,    24,    25,    35,    40,    36,
      20,    37,    26,    38,    39,    40,    27,    16,    20,    10,
      39,    40,    41,    42,    43,    13,    17,    20,    42,    46,
      47,    48,    49,    53,    61,    20,    44,    26,    26,    28,
      11,    58,    16,    12,     7,    20,    21,    22,    26,    50,
      51,    52,    59,    60,    60,    50,    47,    45,    60,    60,
       5,     6,    19,    31,     3,     4,     8,     9,    27,    27,
      12,    44,    27,    51,    51,    50,    50,    52,    52,    60,
      60,    58,    10,    10,    46,    46,    11,    54,    11,    14,
      15,    55,    56,    57,    10,    26,    46,    60,    11,    27,
      29,    46,    30,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    34,    33,    36,    37,    35,    38,    38,    39,
      40,    40,    40,    41,    41,    43,    42,    45,    44,    44,
      46,    47,    47,    48,    48,    48,    49,    50,    50,    50,
      51,    51,    51,    52,    52,    52,    54,    53,    55,    55,
      55,    56,    57,    58,    59,    59,    59,    60,    60,    60,
      60,    60,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     0,    11,     3,     0,     2,
       1,     1,     1,     2,     1,     0,     4,     0,     4,     1,
       1,     3,     0,     1,     1,     1,     4,     3,     3,     1,
       3,     3,     1,     1,     1,     1,     0,    10,     1,     1,
       0,     4,     8,     0,     3,     3,     1,     3,     1,     3,
       3,     2,     7
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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
# undef YYSTACK_RELOCATE
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
  case 2:
#line 113 "1904119_parser.y"
       { starter(); }
#line 1479 "1904119_parser.tab.c"
    break;

  case 3:
#line 115 "1904119_parser.y"
       { ender(); }
#line 1485 "1904119_parser.tab.c"
    break;

  case 4:
#line 117 "1904119_parser.y"
               { strcpy(cur_type,(yyvsp[0].sval));  }
#line 1491 "1904119_parser.tab.c"
    break;

  case 5:
#line 117 "1904119_parser.y"
                                            {  insertEntry((yyvsp[0].sval)); }
#line 1497 "1904119_parser.tab.c"
    break;

  case 9:
#line 121 "1904119_parser.y"
               {  
                  insertEntry((yyvsp[0].sval));
                  strcpy(cur_type,(yyvsp[-1].sval));
              }
#line 1506 "1904119_parser.tab.c"
    break;

  case 10:
#line 126 "1904119_parser.y"
                { strcpy((yyval.sval),(yyvsp[0].sval)); }
#line 1512 "1904119_parser.tab.c"
    break;

  case 11:
#line 127 "1904119_parser.y"
                { strcpy((yyval.sval),(yyvsp[0].sval)); }
#line 1518 "1904119_parser.tab.c"
    break;

  case 12:
#line 128 "1904119_parser.y"
                { strcpy((yyval.sval),(yyvsp[0].sval)); }
#line 1524 "1904119_parser.tab.c"
    break;

  case 15:
#line 132 "1904119_parser.y"
            { strcpy(cur_type,(yyvsp[0].sval)); }
#line 1530 "1904119_parser.tab.c"
    break;

  case 17:
#line 134 "1904119_parser.y"
                   { insertEntry((yyvsp[-1].sval)); allocInstr();}
#line 1536 "1904119_parser.tab.c"
    break;

  case 19:
#line 135 "1904119_parser.y"
                   { insertEntry((yyvsp[0].sval)); allocInstr(); }
#line 1542 "1904119_parser.tab.c"
    break;

  case 21:
#line 139 "1904119_parser.y"
                       {  doBackPatch((yyvsp[-2].stmtVal).nxtLst.cnt, (yyvsp[-1].ival), (yyvsp[-2].stmtVal).nxtLst.ele); }
#line 1548 "1904119_parser.tab.c"
    break;

  case 22:
#line 139 "1904119_parser.y"
                                                                              { }
#line 1554 "1904119_parser.tab.c"
    break;

  case 23:
#line 141 "1904119_parser.y"
                { (yyval.stmtVal) = (yyvsp[0].stmtVal); }
#line 1560 "1904119_parser.tab.c"
    break;

  case 24:
#line 142 "1904119_parser.y"
                  { (yyval.stmtVal) = (yyvsp[0].stmtVal); }
#line 1566 "1904119_parser.tab.c"
    break;

  case 26:
#line 145 "1904119_parser.y"
            {   
                struct st_entry tmp = getEntry((yyvsp[-3].sval));

                if ( deepTypeChecker((yyvsp[-3].sval),(yyvsp[-1].eval).type) == 1 )
                    storeInstr(tmp.irName, (yyvsp[-1].eval).irName, tmp.type, (yyvsp[-1].eval).type, (yyvsp[-1].eval).eVal);

                (yyval.stmtVal).nxtLst.cnt = 0;
            }
#line 1579 "1904119_parser.tab.c"
    break;

  case 27:
#line 154 "1904119_parser.y"
                   {

          // Note that, LHS of the expression "a+b" can be accessed using $1 and RHS can be accessed using $3.

          // If both sides have same type and they are constants, we can compute the value of expression and update.   
          if ( (strcmp((yyvsp[-2].eval).type, (yyvsp[0].eval).type)==0 ) && ( strcmp((yyvsp[-2].eval).type,"INT_CONST")==0  || strcmp((yyvsp[-2].eval).type,"DOUBLE_CONST") ) ) {
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal + (yyvsp[0].eval).eVal;
          }

          // If LHS is DOUBLE_CONST and RHS is INT_CONST, we convert right to double & do the computation.  
          else if((strcmp((yyvsp[-2].eval).type,"DOUBLE_CONST")==0 && strcmp((yyvsp[0].eval).type,"INT_CONST")==0)){
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal + (yyvsp[0].eval).eVal*1.0;
          }

          // If LHS is INT_CONST and RHS is DOUBLE_CONST, we convert left to double & do the computation.
          else if((strcmp((yyvsp[-2].eval).type,"INT_CONST")==0 && strcmp((yyvsp[0].eval).type,"DOUBLE_CONST")==0)){
              strcpy((yyval.eval).type,(yyvsp[0].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal*1.0 + (yyvsp[0].eval).eVal;
          }

          // In other cases, we call our typeChecker function to do the matching and then we write LLVM code for Add instruction.  
          else{

            // Update type.  
            strcpy((yyval.eval).type,typeChecker((yyvsp[-2].eval).type, (yyvsp[0].eval).type)); 
            
            // Call add instruction writing function.
            addInstr((yyvsp[-2].eval).irName,(yyvsp[0].eval).irName,(yyvsp[-2].eval).type,(yyvsp[0].eval).type,(yyvsp[-2].eval).eVal,(yyvsp[0].eval).eVal); 
            
            (yyval.eval).irName = stCnt-1;
          }
      }
#line 1618 "1904119_parser.tab.c"
    break;

  case 28:
#line 189 "1904119_parser.y"
                     {
          
          // Note that, LHS of the expression "a-b" can be accessed using $1 and RHS can be accessed using $3.

          // If both sides have same type and they are constants, we can compute the value of expression and update.   
          if ( (strcmp((yyvsp[-2].eval).type, (yyvsp[0].eval).type)==0 ) && ( strcmp((yyvsp[-2].eval).type,"INT_CONST")==0  || strcmp((yyvsp[-2].eval).type,"DOUBLE_CONST") ) ) {
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal - (yyvsp[0].eval).eVal;
          }

          // If LHS is DOUBLE_CONST and RHS is INT_CONST, we convert right to double & do the computation.  
          else if((strcmp((yyvsp[-2].eval).type,"DOUBLE_CONST")==0 && strcmp((yyvsp[0].eval).type,"INT_CONST")==0)){
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal - (yyvsp[0].eval).eVal*1.0;
          }

          // If LHS is INT_CONST and RHS is DOUBLE_CONST, we convert left to double & do the computation.
          else if((strcmp((yyvsp[-2].eval).type,"INT_CONST")==0 && strcmp((yyvsp[0].eval).type,"DOUBLE_CONST")==0)){
              strcpy((yyval.eval).type,(yyvsp[0].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal*1.0 - (yyvsp[0].eval).eVal;
          }

          // In other cases, we call our typeChecker function to do the matching and then we write LLVM code for Add instruction.  
          else{

            // Update type.  
            strcpy((yyval.eval).type,typeChecker((yyvsp[-2].eval).type, (yyvsp[0].eval).type)); 
            
            // Call sub instruction writing function.
            subInstr((yyvsp[-2].eval).irName,(yyvsp[0].eval).irName,(yyvsp[-2].eval).type,(yyvsp[0].eval).type,(yyvsp[-2].eval).eVal,(yyvsp[0].eval).eVal); 
            
            (yyval.eval).irName = stCnt-1;
          }
        }
#line 1657 "1904119_parser.tab.c"
    break;

  case 29:
#line 224 "1904119_parser.y"
             { 
          (yyval.eval) = (yyvsp[0].eval);
        }
#line 1665 "1904119_parser.tab.c"
    break;

  case 30:
#line 229 "1904119_parser.y"
        { 
            
          // Note that, LHS of the expression "a-b" can be accessed using $1 and RHS can be accessed using $3.

          // If both sides have same type and they are constants, we can compute the value of expression and update.   
          if ( (strcmp((yyvsp[-2].eval).type, (yyvsp[0].eval).type)==0 ) && ( strcmp((yyvsp[-2].eval).type,"INT_CONST")==0  || strcmp((yyvsp[-2].eval).type,"DOUBLE_CONST") ) ) {
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal - (yyvsp[0].eval).eVal;
          }

          // If LHS is DOUBLE_CONST and RHS is INT_CONST, we convert right to double & do the computation.  
          else if((strcmp((yyvsp[-2].eval).type,"DOUBLE_CONST")==0 && strcmp((yyvsp[0].eval).type,"INT_CONST")==0)){
              strcpy((yyval.eval).type,(yyvsp[-2].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal - (yyvsp[0].eval).eVal*1.0;
          }

          // If LHS is INT_CONST and RHS is DOUBLE_CONST, we convert left to double & do the computation.
          else if((strcmp((yyvsp[-2].eval).type,"INT_CONST")==0 && strcmp((yyvsp[0].eval).type,"DOUBLE_CONST")==0)){
              strcpy((yyval.eval).type,(yyvsp[0].eval).type);
              (yyval.eval).eVal= (yyvsp[-2].eval).eVal*1.0 - (yyvsp[0].eval).eVal;
          }

          // In other cases, we call our typeChecker function to do the matching and then we write LLVM code for Add instruction.  
          else{

            // Update type.  
            strcpy((yyval.eval).type,typeChecker((yyvsp[-2].eval).type, (yyvsp[0].eval).type)); 
            
            // Call sub instruction writing function.
            subInstr((yyvsp[-2].eval).irName,(yyvsp[0].eval).irName,(yyvsp[-2].eval).type,(yyvsp[0].eval).type,(yyvsp[-2].eval).eVal,(yyvsp[0].eval).eVal); 
            
            (yyval.eval).irName = stCnt-1;
          }

        }
#line 1705 "1904119_parser.tab.c"
    break;

  case 31:
#line 264 "1904119_parser.y"
                          { strcpy((yyval.eval).type,typeChecker((yyvsp[-2].eval).type,(yyvsp[0].eval).type));  }
#line 1711 "1904119_parser.tab.c"
    break;

  case 32:
#line 265 "1904119_parser.y"
                          {  (yyval.eval) = (yyvsp[0].eval); }
#line 1717 "1904119_parser.tab.c"
    break;

  case 33:
#line 267 "1904119_parser.y"
            { 
              // Creating a temporary symbol table entry.  
              struct st_entry tmp = getEntry((yyvsp[0].sval)); 
              strcpy((yyval.eval).type,tmp.type);       
              strcpy((yyval.eval).variable,tmp.variable); 
          
              (yyval.eval).irName = stCnt;      stCnt++;
              (yyval.eval).eVal = tmp.eVal; 

              // Calling the load instruction writing function.  
              loadInstr((yyval.eval).irName,tmp);
            }
#line 1734 "1904119_parser.tab.c"
    break;

  case 34:
#line 280 "1904119_parser.y"
                    {   
                (yyval.eval).eVal = atof((yyvsp[0].sval)); 
                strcpy((yyval.eval).type,"INT_CONST"); 
            }
#line 1743 "1904119_parser.tab.c"
    break;

  case 35:
#line 285 "1904119_parser.y"
                      {   
                (yyval.eval).eVal = atof((yyvsp[0].sval)); 
                strcpy((yyval.eval).type,"DOUBLE_CONST"); 
            }
#line 1752 "1904119_parser.tab.c"
    break;

  case 36:
#line 291 "1904119_parser.y"
              {

            // Inserting the LLVM code into the File Buffer using corresponding pointer.
            sprintf(fBuffer[i],"\n\tbr label %%%d",stCnt);  i++;
            sprintf(fBuffer[i],"\n%d:",stCnt); i++;
            stCnt++;

        }
#line 1765 "1904119_parser.tab.c"
    break;

  case 37:
#line 300 "1904119_parser.y"
              {   

            // Updating the next List of IF statement by merging accordingly.

            // Updating nxtLst with FALSE_List of boolean expression.
            for(int i=0; i< (yyvsp[-7].eval).FALSE_List.cnt; i<i++){
                (yyval.stmtVal).nxtLst.ele[i]=(yyvsp[-7].eval).FALSE_List.ele[i];
                (yyval.stmtVal).nxtLst.cnt++;
            }
            
            // Updating nxtLst with nxtLst of statement. 
            for(int i=0;i< (yyvsp[-3].stmtVal).nxtLst.cnt;i++){
                (yyval.stmtVal).nxtLst.ele[(yyval.stmtVal).nxtLst.cnt+i]=(yyvsp[-3].stmtVal).nxtLst.ele[i];
                (yyval.stmtVal).nxtLst.cnt++;
            }

        }
#line 1787 "1904119_parser.tab.c"
    break;

  case 43:
#line 325 "1904119_parser.y"
        { (yyval.ival) = stCnt; }
#line 1793 "1904119_parser.tab.c"
    break;

  case 44:
#line 328 "1904119_parser.y"
     {  // We took a specific example where ">" is the RELOP used between the expressions.

        // We know for (a > b), we get 2 conditional statements that will be added to the LLVM Code. They are 1. if (a>b) goto_ 2. goto_
        // Let's add them using the helper function "condExpAdder"
        condExpAdder((yyvsp[-2].eval).eVal, (yyvsp[-2].eval).type, (yyvsp[-2].eval).irName, (yyvsp[0].eval).eVal, (yyvsp[0].eval).type, (yyvsp[0].eval).irName, '>'); 

        // Updating the FALSE_List
        (yyval.eval).FALSE_List.cnt = 0;   
        (yyval.eval).FALSE_List.ele[0] = i-2;
        (yyval.eval).FALSE_List.cnt++;
     }
#line 1809 "1904119_parser.tab.c"
    break;

  case 47:
#line 342 "1904119_parser.y"
                   { (yyval.eval) = (yyvsp[-1].eval); }
#line 1815 "1904119_parser.tab.c"
    break;

  case 51:
#line 344 "1904119_parser.y"
                   { (yyval.eval) = (yyvsp[0].eval); }
#line 1821 "1904119_parser.tab.c"
    break;

  case 52:
#line 346 "1904119_parser.y"
                                            {  (yyval.stmtVal) = (yyvsp[-1].stmtVal); }
#line 1827 "1904119_parser.tab.c"
    break;


#line 1831 "1904119_parser.tab.c"

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
#line 348 "1904119_parser.y"


void starter()
{   
    // Helper function that adds the stub code at the beginning of LLVM code.
    fp = fopen("1904119_output.ll","w");

    fprintf(fp,"; ModuleID = \'1904119_parser.c\'\nsource_filename = \"1904119_parser.c\"\ntarget datalayout = \"e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"\ntarget triple = \"x86_64-pc-windows-msvc19.27.29111\"\n\n; Function Attrs: noinline nounwind optnone uwtable\ndefine dso_local i32 @main() #0 {");
}

void ender()
{   // Helper function that adds the stub code at the ending of LLVM code.

    // Note that we have used array buffer to get the LLVM code using BackPatching. Now, Let's push in all the data from buffer to the file.
    for(int line =0; line < i; line++){
        fputs(fBuffer[line],fp);
    }

    for(int j=0;j<cnt;j++){
        printf("| \t%s\t\t%s\t   |\n",symbol_table[j].variable,symbol_table[j].type);
    }

    int req = symbol_table[cnt-1].irName;
    
    fprintf(fp, "\n\tret i32 %d", req);
    fprintf(fp,"\n}\n\nattributes #0 = { noinline nounwind optnone uwtable \"disable-tail-calls\"=\"false\" \"frame-pointer\"=\"none\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n\n!llvm.module.flags = !{!0, !1}\n!llvm.ident = !{!2}\n\n!0 = !{i32 1, !\"wchar_size\", i32 2}\n!1 = !{i32 7, !\"PIC Level\", i32 2}\n!2 = !{!\"clang version 12.0.1\"}");
}

void insertEntry(char* var){
    // Helper function for Inserting the variable & its type into the symbol table. 
    // If it is already exists, print an error message and return.

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
    
    // Incrementing the counters.
    stCnt++;
    cnt++;
}


struct st_entry getEntry(char* var){        
    // Helper function that gets the entry from the symbol table if the variable exists.

    struct st_entry helper, tmp;
    int flag=0;
    for(int i=0;i<cnt;i++){

        // If the variable name matches:
        if(strcmp(symbol_table[i].variable,var)==0){
            helper = symbol_table[i];
            flag=1;
            break;
        }
    }

    // If variable is not found we show an error as follows & return temporary/dummy entry:
    if(!flag){
        printf("----------> ERROR : Undeclared variable %s is encntered.                       <----------\n",var);
        strcpy(tmp.variable,"NULL");
        strcpy(tmp.type,"NULL");
        return tmp;
    }

    return helper ; 
}

int notATypeItself(char* var){
    // Helper function that returns 1/True if the var itself is not a type itself. 

    return strcmp(var, "int")!=0 && strcmp(var,"INT_CONST")!=0 && strcmp(var,"double")!=0 && strcmp(var,"DOUBLE_CONST")!=0 && strcmp(var,"NULL")!=0;
}

int encodeType(char* type){
    // Helper function that encodes the given type to an Integer.

    if (strcmp(type, "int") == 0){
        return 1;
    }
    if (strcmp(type, "INT_CONST") == 0){
        return 2;
    }
    if (strcmp(type, "double") == 0){
        return 3;
    }
    if (strcmp(type, "DOUBLE_CONST") == 0){
        return 4;
    }
    if (strcmp(type, "NULL") == 0){
        return 0;
    }
}

int doubleCheck(int enc_type1, int enc_type2){
    // Helper function that returns 1 if the encoding of the types should result in a type of "double".

    if (enc_type1 == 3 && enc_type2 == 4 || enc_type1 == 4 && enc_type2 == 3)
        return 1;
    else if (enc_type1 == 3 && enc_type2 == 2 || enc_type1 == 2 && enc_type2 == 3)
        return 1;
    else if (enc_type1 == 4 && enc_type2 == 1 || enc_type1 == 1 && enc_type2 == 4)
        return 1;
    return 0;
}

char* typeChecker(char *v1, char *v2){
    // Helper function that computes the type of expression formed using v1 (LHS) & v2 (RHS) matches.

    // If v1(LHS) is itself a type, we encode it directly.
    // Otherwise, We check the symbol table entry of v1 and fetch it's type & then encode the type using helper function.

    int enc_type1, enc_type2;

    if(notATypeItself(v1)){
        struct st_entry temp= getEntry(v1);
        enc_type1 = encodeType(temp.type);
    }
    else{
        enc_type1 = encodeType(v1);
    }

    // We do similar process as v1 for v2(RHS). 
    if(notATypeItself(v2)){
        struct st_entry temp = getEntry(v2);
        enc_type2 = encodeType(temp.type);
    }
    else{
        enc_type2 = encodeType(v2);
    }

    // Now, lets define the type of expression.

    if(  ( enc_type1 == 1 && enc_type2 == 2) || ( enc_type1 == 2 && enc_type2 == 1) )
        return "int";

     // If any 1 variable is not declared, type of expression cant be defined. So, we set NULL.    
    else if (enc_type1 == 0 || enc_type2 == 0)   
        return "NULL";

    // If both are INT_CONST, resulting expression is also INT_CONST.
    else if (enc_type1 == 2 && enc_type2 == 2)
        return "INT_CONST";

    // If both are DOUBLE_CONST, resulting expression is also DOUBLE_CONST.
    else if(enc_type1 == 4 && enc_type2 == 4)
        return "DOUBLE_CONST"; 

    else if (doubleCheck(enc_type1, enc_type2))
        return "double";
    
    else if(enc_type1 == enc_type2 && enc_type1 == 1)
        return "int";    
    
    else if(enc_type1 == enc_type2 && enc_type1 == 3)
        return "double";
    
    else
        return "double";
}

int deepTypeChecker(char *v1, char *v2){
    // Helper function that returns 1 the type of expression formed using v1 (LHS) & v2 (RHS) matches.

    // If v1 (LHS) is itself a type, we encode it directly.
    // Otherwise, We check the symbol table entry of v1 and fetch it's type & then encode the type using helper function.

    int enc_type1, enc_type2;

    if(notATypeItself(v1)){
        struct st_entry temp= getEntry(v1);
        enc_type1 = encodeType(temp.type);
    }
    else{
        enc_type1 = encodeType(v1);
    }

    // We do similar process as v1 for v2(RHS). 
    if(notATypeItself(v2)){
        struct st_entry temp = getEntry(v2);
        enc_type2 = encodeType(temp.type);
    }
    else{
        enc_type2 = encodeType(v2);
    }

    // Representing type_constant as type.
    if (enc_type1 ==2) enc_type1 = 1; 
    if (enc_type1 ==4) enc_type1 = 3; 
    if (enc_type2 ==2) enc_type2 = 1; 
    if (enc_type2 ==4) enc_type2 = 3; 

    // If LHS has double, irrespective of RHS, we can match. So, we return 1.
    if(enc_type1 == 3){
        return 1;
    }

    // If both types are matching. we return 1.
    if( enc_type1 == enc_type2 ){
        return 1;
    }

    // If any one type is undefined, we can return 0.
    else if ( enc_type1 == 0 || enc_type2 == 0 ){
        printf("----------> ERROR : Types of LHS & RHS didn't match due to undeclared variable! <----------\n");
        return 0;
    }

    // In other cases, we return 0.
    else{
        printf("----------> ERROR : Types of LHS & RHS didn't match!                            <----------\n");
        return 0;
    }
}


void allocInstr(){
    // Helper function that generates & stores the LLVM code WHEN ALLOATION is done.

    if(strcmp(cur_type,"int")==0){

        // Storing into buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%%%d = alloca i32, align 4",stCnt-1); i++;
    }

    if(strcmp(cur_type,"double")==0){

        // Storing into buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = alloca double, align 8",'%',stCnt-1); i++;
    }
}

void loadInstr(int name,struct st_entry var){
    // Helper function that generates & stores the LLVM code WHEN ALLOATION is done.
    
    if(strcmp(var.type,"int")==0){
        sprintf(fBuffer[i],"\n\t%c%d =  load i32, i32* %c%d, align 4",'%',name,'%',var.irName); i++;
    }

    if(strcmp(var.type,"double")==0){
        sprintf(fBuffer[i],"\n\t%c%d = load double, double* %c%d, align 8",'%',name,'%',var.irName); i++;
    }
}


void addHelperINT(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is INT_CONST.

    // If t1 is of INT_CONST.
    if (t1 == 2 ){
        if(t2 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = add nsw i32 %c%d,%d",'%',stCnt,'%',ir2,(int)e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
    }

    // If t2 is of INT_CONST.
    if (t2 == 2 ){
        if(t1 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = add nsw i32 %c%d,%d",'%',stCnt,'%',ir1,(int)e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
    }
}

void addHelperDOUBLE(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is DOUBLE_CONST.

    // If t1 is of DOUBLE_CONST.
    if (t1 == 4){
        if (t2 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',stCnt-1,e1); i++;
        }
    }

    // If t2 is of DOUBLE_CONST.
    if (t2 == 4){
        if (t1 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',stCnt-1,e2); i++;
        }
    }
}

void addInstr( int ir1, int ir2, char* t1, char* t2, double e1, double e2 ){
    // Helper function that generates the LLVM Code for the add instruction and stores into the file buffer.

    int enc_t1 = encodeType(t1), enc_t2 = encodeType(t2);
    
    // If both types are int, we can straight away store the code.
    if ( enc_t1 == 1 && enc_t2 == 1 ){

        // Storing add instr(int) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = add nsw i32 %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }
    
    // If both types are double, we can straight away store the code too.
    else if(  enc_t1 == 3 && enc_t2 == 3 ){

        // Storing add instr(double) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }

    // If one of the type is INT_CONST
    else if(  enc_t1 == 2 || enc_t2 == 2 ){
        addHelperINT(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    // If one of the type is DOUBLE_CONST
    else if( enc_t1 == 4 || enc_t2 == 4 ){
        addHelperDOUBLE(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    else if( enc_t1 != enc_t2  && enc_t1 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    }

    else if( enc_t1 != enc_t2  && enc_t2 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',ir1,'%',stCnt-1); i++;
    }
    stCnt++;
}


void subHelperINT(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is INT_CONST.

    // If t1 is of INT_CONST.
    if (t1 == 2 ){
        if(t2 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = sub nsw i32 %c%d,%d",'%',stCnt,'%',ir2,(int)e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
    }

    // If t2 is of INT_CONST.
    if (t2 == 2 ){
        if(t1 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = sub nsw i32 %c%d,%d",'%',stCnt,'%',ir1,(int)e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
    }
}

void subHelperDOUBLE(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is DOUBLE_CONST.

    // If t1 is of DOUBLE_CONST.
    if (t1 == 4){
        if (t2 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',stCnt-1,e1); i++;
        }
    }

    // If t2 is of DOUBLE_CONST.
    if (t2 == 4){
        if (t1 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',stCnt-1,e2); i++;
        }
    }
}

void subInstr( int ir1, int ir2, char* t1, char* t2, double e1, double e2 ){
    // Helper function that generates the LLVM Code for the add instruction and stores into the file buffer.

    int enc_t1 = encodeType(t1), enc_t2 = encodeType(t2);
    
    // If both types are int, we can straight away store the code.
    if ( enc_t1 == 1 && enc_t2 == 1 ){

        // Storing sub instr(int) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = sub nsw i32 %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }
    
    // If both types are double, we can straight away store the code too.
    else if(  enc_t1 == 3 && enc_t2 == 3 ){

        // Storing sub instr(double) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }

    // If one of the type is INT_CONST
    else if(  enc_t1 == 2 || enc_t2 == 2 ){
        subHelperINT(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    // If one of the type is DOUBLE_CONST
    else if( enc_t1 == 4 || enc_t2 == 4 ){
        subHelperDOUBLE(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    else if( enc_t1 != enc_t2  && enc_t1 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    }

    else if( enc_t1 != enc_t2  && enc_t2 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',ir1,'%',stCnt-1); i++;
    }
    stCnt++;
}

void mulHelperINT(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is INT_CONST.

    // If t1 is of INT_CONST.
    if (t1 == 2 ){
        if(t2 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = mul nsw i32 %c%d,%d",'%',stCnt,'%',ir2,(int)e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
    }

    // If t2 is of INT_CONST.
    if (t2 == 2 ){
        if(t1 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = mul nsw i32 %c%d,%d",'%',stCnt,'%',ir1,(int)e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
    }
}

void mulHelperDOUBLE(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is DOUBLE_CONST.

    // If t1 is of DOUBLE_CONST.
    if (t1 == 4){
        if (t2 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',stCnt-1,e1); i++;
        }
    }

    // If t2 is of DOUBLE_CONST.
    if (t2 == 4){
        if (t1 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',stCnt-1,e2); i++;
        }
    }
}

void mulInstr( int ir1, int ir2, char* t1, char* t2, double e1, double e2 ){
    // Helper function that generates the LLVM Code for the mul instruction and stores into the file buffer.

    int enc_t1 = encodeType(t1), enc_t2 = encodeType(t2);
    
    // If both types are int, we can straight away store the code.
    if ( enc_t1 == 1 && enc_t2 == 1 ){

        // Storing mul instr(int) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = mul nsw i32 %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }
    
    // If both types are double, we can straight away store the code too.
    else if(  enc_t1 == 3 && enc_t2 == 3 ){

        // Storing mul instr(double) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }

    // If one of the type is INT_CONST
    else if(  enc_t1 == 2 || enc_t2 == 2 ){
        mulHelperINT(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    // If one of the type is DOUBLE_CONST
    else if( enc_t1 == 4 || enc_t2 == 4 ){
        mulHelperDOUBLE(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    else if( enc_t1 != enc_t2  && enc_t1 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    }

    else if( enc_t1 != enc_t2  && enc_t2 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',ir1,'%',stCnt-1); i++;
    }
    stCnt++;
}

void storeInstr(int ir1,int ir2,char* t1,char* t2,double eVal){
    // Helper function that generates the LLVM Code for the store instruction and stores into the file buffer.

    int enc_t1 = encodeType(t1), enc_t2 = encodeType(t2);

    if(enc_t2 == 2){
        if(enc_t1 == 3){
            sprintf(fBuffer[i],"\n\tstore double %f, double* %c%d, align 4",eVal,'%',ir1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\tstore i32 %d, i32* %c%d, align 4",(int)eVal,'%',ir1); i++;
        }
    }
    else if(enc_t2 == 4){
        sprintf(fBuffer[i],"\n\tstore double %f, double* %c%d, align 8",eVal,'%',ir1); i++;
    }
    else if( enc_t1 == 1 && enc_t2 == 1 ){
        sprintf(fBuffer[i],"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',ir2,'%',ir1); i++;
    }
    else if(enc_t1 == 3 && enc_t2 == 3){
        sprintf(fBuffer[i],"\n\tstore double %c%d, double* %c%d, align 8",'%',ir2,'%',ir1); i++;
    }
    else if( enc_t1 != enc_t2 && enc_t1 == 1 ){
        sprintf(fBuffer[i],"\n\t%c%d = fptosi double %c%d  to i32",'%',stCnt,'%',ir2); i++;
        stCnt++;
        sprintf(fBuffer[i],"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',stCnt-1,'%',ir1); i++;
    }
    else if( enc_t1 != enc_t2 && enc_t2 == 1 ){
        sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
        stCnt++;
        sprintf(fBuffer[i],"\n\tstore double %c%d, double* %c%d, align 8",'%',stCnt-1,'%',ir1); i++;
    }
}


void ceh_int(double e1, double e2, int ir1, int ir2){
    // If both are of Integer Type.

    // Storing the icmp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = icmp sgt i32 %c%d,%c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    
    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');  i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i. 
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void ceh_int_cons(double e1, double e2, int ir1, int ir2){
    // If both are of IntegerConstant Type.

    // Storing the icmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = icmp sgt i32  %d,%d",'%',stCnt,(int)e1,(int)e2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void ceh_double(double e1, double e2, int ir1, int ir2){
    // If both are of Double Type.

    // Storing the fcmp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',stCnt,'%',ir1,'%',ir2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');   i++;

    stCnt++;
    // Storing the new line with symbol table count & incrementing the i. 
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void ceh_double_cons(double e1, double e2, int ir1, int ir2){
    // If both are of DoubleConstant Type.

    // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %d,%f",'%',stCnt,'%',e1,e2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void condExpHelper_same(char *exp1, double e1, double e2, int ir1, int ir2){
    // Helper function that gets invoked when the types of exp1 and exp2 are same inside condExpAdder function.

    if (strcmp(exp1, "int") == 0){
        ceh_int(e1, e2, ir1, ir2);
    }
    else if (strcmp(exp1, "double") == 0){
        ceh_double(e1, e2, ir1, ir2);
    }
    else if (strcmp(exp1, "INT_CONST") == 0){
        ceh_int_cons(e1, e2, ir1, ir2);
    }
    else if (strcmp(exp1, "DOUBLE_CONST") == 0){
        ceh_double_cons(e1, e2, ir1, ir2);
    }
}


void dc_1_int_cons(double e1, double e2){
     // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %d,%d",'%',stCnt,'%',(int)e1,e2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;

    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void dc_2_int_cons(double e1, double e2){
    // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %d,%f",'%',stCnt,'%',e1,(int)e2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;

    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void diffCons(char *exp1, double e1, double e2){
    // Helper function that gets invoked when the types of exp1 and exp2 are both Constant types but not same.
    if (strcmp(exp1, "INT_CONST" ) == 0){
        dc_1_int_cons(e1, e2);
    }
    else{
        dc_2_int_cons(e1, e2);
    }
}


void  dc_2_int(int ir1, int ir2){
    // If exp1 is of INT type and exp2 is of DOUBLE type.

    // Storing the sitofp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%%%d = sitofp i32 %%%d to double",stCnt,ir1); i++;
    stCnt++;
    
    // Storing the fcmp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    
    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void  dc_1_int(int ir1, int ir2){
    // If exp1 is of INT type and exp2 is of DOUBLE type.
     
    // Storing the sitofp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%%%d = sitofp i32 %%%d to double",stCnt,ir1); i++;
    stCnt++;
    
    // Storing the fcmp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    
    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void diff(char *exp1, int ir1, int ir2){
    // Helper function that gets invoked when the types of exp1 and exp2 are both NOT Constant types but not same.
    if (strcmp(exp1, "int" ) == 0){
        dc_1_int(ir1, ir2);
    }
    else{
        dc_2_int(ir1, ir2);
    }
}

void rem_cases(double e1, char *exp1, int ir1, double e2, char *exp2, int ir2, char op){
    // Helper function that takes care of non trivial cases that happen in condExpAdder function and 
    // stores the LLVM IR code accordingly into the file buffer.
    
    // If exp1 is of DOUBLE type and exp2 is of INT_CONST type.
    if( strcmp(exp2, "INT_CONST") == 0 && strcmp(exp1, "double") == 0)
    {
        // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%f ",'%',stCnt,'%',ir1,e2); i++;
        
        // Storing the br i1 statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
        // Storing the new line with symbol table count & incrementing the i.
        stCnt++; sprintf(fBuffer[i],"\n%d:",stCnt); i++;
        stCnt++;
    }

    // If exp1 is of INT type and exp2 is of DOUBLE_CONST type.
    else if( strcmp(exp1, "int") == 0 && strcmp(exp2, "DOUBLE_CONST") == 0)
    {   
        // Storing the sitofp statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%%%d = sitofp i32 %%%d to double",stCnt,ir1); i++;
        stCnt++;

        // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%f ",'%',stCnt,'%',stCnt-1,e2); i++;
        
        // Storing the br i1 statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
        
        stCnt++;
        // Storing the new line with symbol table count & incrementing the i.
        sprintf(fBuffer[i],"\n%d:",stCnt); i++;
        stCnt++;
    }

    // If exp1 is of INT_CONST type and exp2 is of DOUBLE type.
    else if((strcmp(exp1, "INT_CONST")==0) && (strcmp(exp2, "double")==0))
    {   
        // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',stCnt,e1,ir2); i++;

        // Storing the br i1 statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');  i++;
        
        stCnt++;
        // Storing the new line with symbol table count & incrementing the i.
        sprintf(fBuffer[i],"\n%d:",stCnt);  i++;
        stCnt++;
    }

    // If exp1 is of DOUBLE_CONST type and exp2 is of INT type.
    else if((strcmp(exp1, "DOUBLE_CONST")==0) && (strcmp(exp2, "int")==0))
    {
        // Storing the sitofp statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%%%d = sitofp i32 %%%d to double",stCnt,ir2); i++;
        stCnt++;
        
        // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',stCnt,e1,stCnt-1); i++;

        // Storing the br i1 statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
        
        stCnt++;
        // Storing the new line with symbol table count & incrementing the i.
        sprintf(fBuffer[i],"\n%d:",stCnt); i++;
        stCnt++;
    }
}

int condExpAdder(double e1, char *exp1, int ir1, double e2, char *exp2, int ir2, char op){
    // Helper function that adds the conditional expressions which are required in the BackPatching process.

    if(op == '>'){

        // Since we are concerned about only when the expression is exp1 > exp2, We take all possible cases of types in LHS & RHS
        // and store the corresponding LLVM Code into the buffer for future use.
        
        // If both are of INT_CONST Type.
        if(  strcmp(exp1, exp2) == 0 && strcmp(exp1, "INT_CONST") == 0 ){
            condExpHelper_same(exp1, e1, e2, ir1, ir2);
        }

        // If both are of Integer Type.
        else if(  strcmp(exp1, exp2) == 0 && strcmp(exp1, "int") == 0 ){
            condExpHelper_same(exp1, e1, e2, ir1, ir2);
        }
        
        // If exp1 is of INT type variable but exp2 is INT_CONST.
        else if((strcmp(exp1, "int")==0) && (strcmp(exp2, "INT_CONST")==0))
        {
            // Storing the icmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\t%c%d = icmp sgt i32  %c%d,%d",'%',stCnt,'%',ir1,(int)e2);   i++;
           
            // Storing the br i1 statement to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');  i++;
            
            stCnt++;
            // Storing the new line with symbol table count & incrementing the i. 
            sprintf(fBuffer[i],"\n%d:",stCnt);  i++;
            stCnt++;
        }
        
        // If exp1 is of INT_CONST but exp2 is of INT type variable.
        else if((strcmp(exp1, "INT_CONST")==0) && (strcmp(exp2, "int")==0))
        {
            // Storing the icmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\t%c%d = icmp sgt i32  %d,%%%d",'%',stCnt,(int)e1,ir2);  i++;

            // Storing the br i1 statement to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');  i++;
            
            stCnt++;
            // Storing the new line with symbol table count & incrementing the i. 
            sprintf(fBuffer[i],"\n%d:",stCnt);     i++;
            stCnt++;
        }

        // If both are of Double Type.
        else if(  strcmp(exp1, exp2) == 0 && strcmp(exp1, "double") == 0 ){
            condExpHelper_same(exp1, e1, e2, ir1, ir2);
        }

        // If both are of DOUBLE_CONST Type.
        else if(  strcmp(exp1, exp2) == 0 && strcmp(exp1, "DOUBLE_CONST") == 0 ){
            condExpHelper_same(exp1, e1, e2, ir1, ir2);
        }

        // If exp1 is of DOUBLE type variable but exp2 is DOUBLE_CONST.
        else if((strcmp(exp2, "DOUBLE_CONST")==0) && (strcmp(exp1, "double")==0))
        {
            // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%f",'%',stCnt,'%',ir1,e2); i++;

            // Storing the br i1 statement to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
            
            // Storing the new line with symbol table count & incrementing the i. 
            stCnt++; sprintf(fBuffer[i],"\n%d:",stCnt); i++;
            stCnt++;
        }

        // If exp2 is of DOUBLE type variable & exp1 is of DOUBLE_CONST.
        else if((strcmp(exp1, "DOUBLE_CONST")==0) && (strcmp(exp2, "double")==0))
        {
            // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',stCnt,e1,ir2); i++;

            // Storing the br i1 statement to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
            
            stCnt++;
            // Storing the new line with symbol table count & incrementing the i. 
            sprintf(fBuffer[i],"\n%d:",stCnt); i++;
            stCnt++;
        }

        // If exp1 is of DOUBLE_CONST type and exp2 is of INT_CONST type.
        else if((strcmp(exp1, "DOUBLE_CONST")==0) && (strcmp(exp2, "INT_CONST")==0))
        {   
            diffCons(exp1, e1, e2);
        }

        // If exp1 is of INT_CONST type and exp2 is of DOUBLE_CONST type.
        else if((strcmp(exp1, "INT_CONST")==0) && (strcmp(exp2, "DOUBLE_CONST")==0))
        {       
            diffCons(exp1, e1, e2);
        }

        // If exp2 is of INT type and exp1 is of DOUBLE type.
        else if( strcmp(exp2, "int") == 0 &&  strcmp(exp1, "double") == 0 )
        {
            diff(exp1, ir1, ir2);
        }

        // If exp1 is of INT type and exp2 is of DOUBLE type.
        else if( strcmp(exp1, "int") == 0 &&  strcmp(exp2, "double") == 0 )
        {
            diff(exp1, ir1, ir2);
        }

        // Now lets deal with remaining cases.
        else{
            rem_cases(e1, exp1, ir1, e2, exp2, ir2, op );
        }
    }
}

void doBackPatch(int lcnt, int lbl, int list[]){
    // Helper function that does the job of BackPatching and fills the target labels in our LLVM code buffer accordingly.

    // Iterate over each index j to use list[j]
    for( int j = 0; j < lcnt; j++ ){
        
        // Finding the location (ind) to put the label.
        int pcnt = 0, ind = 0;
        for(; ; ind++){
            if (pcnt == 3) break;
            if ( fBuffer[list[j]][ind] == '%' ) 
                pcnt++;
        }

        // Updating the LLVM code in the buffer with the labels accordingly.
        sprintf(&fBuffer[list[j]][ind],"%d",lbl-1);
    }
}

int main(int argc, char **argv) {
	yyparse();
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("|   variable              type     | \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for(int j=0;j<cnt;j++){
        printf("| \t%s\t\t%s\t   |\n",symbol_table[j].variable,symbol_table[j].type);
    }
}

int yyerror(char *s){
    fprintf(stderr, "error : %s\n", s);
}
