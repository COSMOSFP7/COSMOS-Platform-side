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
	FIXME Candidate optimizations:

		- pre-evaluate formulas not involving variables or functions
		- detect similar calculator instruction sets and reduce them
		
		For this, we need at least the generated code
		
*/

#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include <stdio.h>

class ASTree;
class SymbolTable;
class Program;

class Optimizer
{
public:

	Optimizer();
	~Optimizer();
	
	void optimize(	const ASTree* _tree, 
					const SymbolTable* _symTab,
					const Program* _program);
	
	
protected:

	typedef int (Optimizer::*TOptimizerFunc)(int x, int z);
	
	static const int KMaxStage = 10;
	
	int stage1(int y, int z) { printf("Optimizing stage 1\n"); return 0; }
	int stage2(int y, int z) { printf("Optimizing stage 2\n"); return 0; };
		
	TOptimizerFunc mStages[KMaxStage]; /* !! MAKE SURE this is big enough */


	Optimizer(const Optimizer& rhs)	{}
	Optimizer& operator= (const Optimizer &rhs)	{ return *this; }
	

private:

	void init();
};

#endif 

