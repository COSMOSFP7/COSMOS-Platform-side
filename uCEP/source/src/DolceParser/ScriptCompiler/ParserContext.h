/**
  Copyright (C) 2016 ATOS
 
    This file is part of BCEP.

    BCEP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BCEP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BCEP.  If not, see <http://www.gnu.org/licenses/>.
 
  Authors:
  ATOS ARI
  
 */
/* 
	Compiler framework for Dolce
*/
#ifndef _SOL_CEP_COMPILER_CONTEXT_H_
#define _SOL_CEP_COMPILER_CONTEXT_H_
 
class Parser;

/*!
	\brief Context used to operate multiple instances 
		of lex/yacc parsers in a thread safe manner.
		
	Based on information found in:
	
	http://www.lemoda.net/c/reentrant-parser/index.html
	
*/
struct ParserContext
{
	void* scanner;
	
	Parser* parser;
	
	int line;
	int col;
};


#endif 

