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


#include "Queue.h"

Queue::Queue() {
    mQueue = 0;
    mHead = 0;
}

Queue::~Queue() {
    
    while(pop().size()>0)
        ;
}

void Queue::push(std::string _msg)
{
	Item* newItem = new Item();
	
	newItem->msg = _msg;
	newItem->next = 0;

        if (mHead) 
            mQueue->next = newItem;
        else 
            mHead = newItem;
        
        mQueue = newItem;
}

std::string Queue::pop()
{
    std::string strToReturn;
    
    if(mHead) {
        
        if(mHead->msg.size()>0)
           strToReturn = mHead->msg;
        
        Item *curr = mHead;
        mHead = mHead->next;
///		delete curr->msg;
        delete curr;		
    }
	
    return strToReturn;
}

