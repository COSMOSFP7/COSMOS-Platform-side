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
///#include <stdio.h>


#include "Parser.h"
#include "ParserContext.h"

#include "ASTree.h"
#include "SymbolTable.h"
#include "ErrorList.h"

#include "../DolceCompilerCodes.h"





Parser::Parser(ErrorList* _errList)
{
	mErrorList = _errList;
}


Parser::~Parser()
{
}


#ifdef CEP_DEBUG

void Parser::print()
{
	if(mTree)
		mTree->print();
	else
		printf("No tree\n");
}
#endif

void* sxxx;



int Parser::parse(FILE* _in, ASTree* const _tree, SymbolTable* const _symTab)
{
	mTree = _tree;
	mSymbolTable = _symTab;


	int res;
	ParserContext* pc = new ParserContext();
	
	yylex_init(&pc->scanner);
	yyset_in(_in, pc->scanner);
	pc->parser = this;
	
	res = yyparse(pc);
	
	
	yylex_destroy(pc->scanner);	
	
//	printf("RES=%d\n", res);
	
	return res;
}



