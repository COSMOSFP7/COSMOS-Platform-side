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
#ifndef _SOL_CEP_COMPILER_PARSER_H_
#define _SOL_CEP_COMPILER_PARSER_H_

///#include <stdio.h>
#include "SymbolTable.h"
#include "ParserContext.h"

class ASTree;
class ErrorList;


/* 
	External references to functions created
	by Flex/Bison, copy/pasted from the generated
	source code.
	
	Must be present to keep the compiler happy.
*/
extern int yylex_init(void** scanner);
extern int yylex_destroy(void* scanner);
extern int yyparse(ParserContext* _context);
extern void yyset_in(FILE * in_str, void* yyscanner );

/*!
	\brief Infrastructure for parsing a Dolce file
*/
class Parser
{
public:

	Parser(ErrorList* const _errList);
	~Parser();
	
	
	
	int parse(FILE* _in, ASTree* const _tree, SymbolTable* const _symTab);

	SymbolTable* getSymbolTable() { return mSymbolTable; }
	ASTree* getASTree() { return mTree; }

	void print();
	
	ErrorList* mErrorList;	// fixme: make protected/private.
	
protected:
	
	
private:
	ASTree* mTree;
	SymbolTable*  mSymbolTable;

};

#endif 

