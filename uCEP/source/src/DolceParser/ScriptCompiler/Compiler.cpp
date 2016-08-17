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

#include "Compiler.h"

///#include <stdio.h>

#include "../../Common/Err.h"


#include "Parser.h"
#include "SymbolResolver.h"
#include "SemanticAnalyzer.h"
#include "Optimizer.h"
#include "ASTree.h"
#include "SymbolTable.h"
#include "ErrorList.h"


Compiler::Compiler(ErrorList* const _errList) : mErrorList(_errList)
{
	mParser = new Parser(_errList);
	mAnalyzer = 0;
}


Compiler::~Compiler()
{        
	delete mParser;        
}


int Compiler::compile(FILE* _in)
{
	int res = OK;
	
	mTree = new ASTree(ASTree::PRoot);
	mSymbolTable = new SymbolTable();

//	mOptimizer = new Optimizer();
	
	if(mParser->parse(_in, mTree, mSymbolTable))
	{
		return 1;
	}
	
//	mSymbolResolver = new SymbolResolver();
//	res |= mSymbolResolver->resolve(mTree, mSymbolTable, mErrorList);
	
#ifdef CEP_DEBUG
	mParser->print();
	mSymbolTable->print();
#endif
	
	mAnalyzer = new SemanticAnalyzer();
	res |= mAnalyzer->analyze(mTree, mSymbolTable, mErrorList);
	
#ifdef CEP_DEBUG
	mParser->print();
	mSymbolTable->print();
#endif

	//	delete mOptimizer;
//	delete mGenerator;

#ifdef CEP_DEBUG
	mErrorList->print();
#endif
	delete mAnalyzer;
		
	return res;
}

#ifdef CEP_DEBUG
void Compiler::dump()
{
	mParser->print();
}
#endif

