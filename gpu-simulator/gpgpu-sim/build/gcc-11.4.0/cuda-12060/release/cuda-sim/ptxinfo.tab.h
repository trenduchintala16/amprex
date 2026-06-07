/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_PTXINFO_HOME_TARA_AMPREX_GPU_SIMULATOR_GPGPU_SIM_BUILD_GCC_11_4_0_CUDA_12060_RELEASE_CUDA_SIM_PTXINFO_TAB_H_INCLUDED
# define YY_PTXINFO_HOME_TARA_AMPREX_GPU_SIMULATOR_GPGPU_SIM_BUILD_GCC_11_4_0_CUDA_12060_RELEASE_CUDA_SIM_PTXINFO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int ptxinfo_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_OPERAND = 258,
    HEADER = 259,
    INFO = 260,
    FUNC = 261,
    USED = 262,
    REGS = 263,
    BARRIERS = 264,
    COMPILETIME = 265,
    BYTES = 266,
    LMEM = 267,
    SMEM = 268,
    CMEM = 269,
    GMEM = 270,
    IDENTIFIER = 271,
    PLUS = 272,
    COMMA = 273,
    LEFT_SQUARE_BRACKET = 274,
    RIGHT_SQUARE_BRACKET = 275,
    COLON = 276,
    SEMICOLON = 277,
    QUOTE = 278,
    LINE = 279,
    WARNING = 280,
    FOR = 281,
    TEXTURES = 282,
    DUPLICATE = 283,
    FUNCTION = 284,
    VARIABLE = 285,
    FATAL = 286,
    PERIOD = 287,
    MS = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 41 "ptxinfo.y"

  int    int_value;
  char * string_value;

#line 96 "/home/tara/amprex/gpu-simulator/gpgpu-sim/build/gcc-11.4.0/cuda-12060/release/cuda-sim/ptxinfo.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int ptxinfo_parse (yyscan_t scanner, ptxinfo_data* ptxinfo);

#endif /* !YY_PTXINFO_HOME_TARA_AMPREX_GPU_SIMULATOR_GPGPU_SIM_BUILD_GCC_11_4_0_CUDA_12060_RELEASE_CUDA_SIM_PTXINFO_TAB_H_INCLUDED  */
