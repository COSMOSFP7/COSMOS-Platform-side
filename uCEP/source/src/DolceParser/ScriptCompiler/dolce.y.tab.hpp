/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_DOLCE_TAB_H_INCLUDED
# define YY_YY_DOLCE_TAB_H_INCLUDED
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
    POS = 258,
    AREA = 259,
    CHAR = 260,
    INT = 261,
    FLOAT = 262,
    STRING = 263,
    TIME = 264,
    DURATION = 265,
    AND_EOP = 266,
    OR_EOP = 267,
    AFTER_EOP = 268,
    DURING_EOP = 269,
    ABSENCE_UNARY_EOP = 270,
    EXTERNAL = 271,
    EVENT = 272,
    COMPLEX_EVENT = 273,
    MAP = 274,
    ACCEPT = 275,
    USE = 276,
    LASTS = 277,
    UNTIL = 278,
    PAYLOAD = 279,
    GROUP = 280,
    DETECT = 281,
    WHERE = 282,
    IN = 283,
    SUM_FUNC = 284,
    AVG_FUNC = 285,
    COUNT_FUNC = 286,
    DIFF_FUNC = 287,
    INAREA_FUNC = 288,
    IDENTIFIER = 289,
    INTEGER_CONSTANT = 290,
    FLOAT_CONSTANT = 291,
    AREA_CONSTANT = 292,
    STRING_LITERAL = 293,
    CHARACTER_CONSTANT = 294,
    POS_CONSTANT = 295,
    TIME_CONSTANT = 296,
    YEARS = 297,
    MONTHS = 298,
    WEEKS = 299,
    DAYS = 300,
    HOURS = 301,
    MINUTES = 302,
    SECONDS = 303,
    EQ_OP = 304,
    NE_OP = 305,
    GE_OP = 306,
    GT_OP = 307,
    LE_OP = 308,
    LT_OP = 309,
    OR_OP = 310,
    AND_OP = 311,
    ADD_OP = 312,
    SUB_OP = 313,
    MULT_OP = 314,
    DIV_OP = 315
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 93 "dolce.y" /* yacc.c:1909  */

	unsigned long a_number;
	float a_float;
	TAreaLiteral a_area;
	TPosLiteral a_pos;
	TTimeLiteral a_time;
	char a_char;
	char* a_string;
	TDurationUnit a_duration_unit;
	ASTree* a_tree;

#line 127 "dolce.tab.h" /* yacc.c:1909  */
};
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



int yyparse (ParserContext* scContext);

#endif /* !YY_YY_DOLCE_TAB_H_INCLUDED  */
