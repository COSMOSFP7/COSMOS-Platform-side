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


#include "Stack.h"

#include "../../Types/TValue.h"

Stack::Stack()
{
	mSP = 0;
	mHead = 0;
	
}


Stack::~Stack()
{
	
	while(pop())
		;
		
}



	
	
void Stack::push(const TValue& _val)
{
#ifdef CEP_DEBUG
	printf("Stack::push | %s\n", _val.asString());
#endif	

	Item* newItem = new Item();
	
	newItem->val = new TValue(_val);
	
	newItem->prev = mHead;
	mHead = newItem;
}	



	
bool Stack::pop(TValue* val_)
{
	if(mHead)
	{
		if(val_)
		{
			*val_ = *(mHead->val);
			
#ifdef CEP_DEBUG
			printf("Stack::pop | %s\n", val_->asString());
#endif	
		}
			
		Item* curr = mHead;
		
		mHead = mHead->prev;

		delete curr->val;
		delete curr;
		
		return true;
	}
	
	return false;
}

TValue* Stack::peek()
{
	if(mHead)
	{
#ifdef CEP_DEBUG
		printf("Stack::peek | %s\n", mHead->val->asString());
#endif		
		return mHead->val;
	}
	
	return 0;
}



