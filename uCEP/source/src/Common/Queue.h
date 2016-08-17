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


#ifndef QUEUE_H
#define	QUEUE_H

#include <string>

class Queue {

public:
    Queue();

    virtual ~Queue();
    
    struct Item
    {
        std::string msg;
	
	Item* next;
    };
    
    void push(std::string _msg);
	
    std::string pop();	
    
    Item* front() { return mHead; }

    
private:
    Item *mHead, *mQueue;
    
};

#endif	/* QUEUE_H */

