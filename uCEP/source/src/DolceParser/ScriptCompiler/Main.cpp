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
  
 */#include <stdio.h>
#include "ASTree.h"
#include "Compiler.h"


Parser* _SL_PARSER_;

extern int yydebug;


int main( int argc, const char* argv[] )
{
	//doTest();

	yydebug = 0;
	Compiler* compiler = new Compiler();
	
	_SL_PARSER_ = compiler->getParser();
	
	FILE* f = 0;
	
	if(argc > 1)
		f = fopen(argv[1],"r");
	else
		f = stdin;

	int res = compiler->compile(f);

	
	if(f != stdin)
		fclose(f);
		
#ifdef CEP_DEBUG
	compiler->dump();
#endif

//	delete compiler;
	
	if(res != 0)
	{
		printf("SOL/CEP: Compiler error\n");
	}
}


