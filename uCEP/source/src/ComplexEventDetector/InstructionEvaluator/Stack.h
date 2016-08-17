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

	

#ifndef _SOL_CEP_STACK_H_
#define _SOL_CEP_STACK_H_

#include "../../Types/TValue.h"

/*!
	\brief Implements a stack for TValue
*/
class Stack
{
public:
	Stack();
					
	~Stack();
	
	struct Item
	{
		TValue* val; // refernce to local copy
	
		Item* prev;
		Item* next;
	};
	
		
	void push(const TValue& _val);
	
	bool pop(TValue* val_ = 0);
	
	TValue* peek();
	
protected:

private:

	Item* mHead;
	unsigned long mSP;
	
};





#endif


