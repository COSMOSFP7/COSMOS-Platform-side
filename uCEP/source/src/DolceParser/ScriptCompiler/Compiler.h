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

#ifndef _SOL_CEP_COMPILER_H_
#define _SOL_CEP_COMPILER_H_
 
#include <stdio.h>

class Parser;
class SymbolTable;
class ASTree;
class SymbolResolver;
class SemanticAnalyzer;
class Optimizer;
class ErrorList;

/*!
	\brief Declares a Compiler environment, including lexer/parser,
		symbol table, error list etc.
	
	This allows multiple instances of the a Dolce compiler in the same
	program. Lex/Yacc related modules have been accomodated to suppor this
	(via ParserContext).
*/
class Compiler
{
public:

	Compiler(ErrorList* const _errList);
	~Compiler();
	
	int compile(FILE* _in);
#ifdef CEP_DEBUG
	void dump();
#endif

	SymbolTable* const getSymbolTable() { return mSymbolTable; }
	Parser* const getParser() { return mParser; } 
	ErrorList* const getErrorList() { return mErrorList; }
        
        SymbolTable* mSymbolTable;   ///RP: was private;  but for the memory leak has changed
        ASTree* mTree;
	
protected:
	
	Compiler(const Compiler& rhs)	{}
	
	Compiler& operator= (const Compiler &rhs)	{ return *this; }
	
       
private:

	Parser* mParser;
	SymbolResolver* mSymbolResolver;
	SemanticAnalyzer* mAnalyzer;
	Optimizer* mOptimizer;
	ErrorList* mErrorList;	
	
};

#endif 

