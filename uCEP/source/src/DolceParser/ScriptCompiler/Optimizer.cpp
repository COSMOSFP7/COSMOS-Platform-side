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
#include "Optimizer.h"


///#include <stdio.h>
#include <assert.h>



Optimizer::Optimizer()
{
	init();
}

Optimizer::~Optimizer()
{
}


void Optimizer::init()
{
	int i = 0;
	mStages[i++] = &Optimizer::stage1;
	mStages[i++] = &Optimizer::stage2;
	
	mStages[i++] = 0;
	
	// just in case we haven't crashed already due to out-of-bounds init above
	assert(i <= KMaxStage); 

}


void Optimizer::optimize(	const ASTree* _tree, 
							const SymbolTable* _symTab,
							const Program* _program)
{
	int i = 0;
	
	while(mStages[i] != 0)
	{
		(*this.*mStages[i])(1,3);
		i++;
	}
}



