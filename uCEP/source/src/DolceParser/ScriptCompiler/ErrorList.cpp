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
#include "ErrorList.h"

#include <stdio.h>
#include <string.h>
///#include <stdlib.h>
#include <stdarg.h>


ErrorList::ErrorList()
{
	mHead = 0;
	mCount = 0;
}


ErrorList::~ErrorList()
{
	Error* e = mHead;
	Error* prev = 0;

	while(e)
	{
		prev = e->prev;
		
		free(e->s);
		delete e;
		
		e = prev;
	}
}

void ErrorList::addError(const int _lineNum,
							const int _colNum,
							const char* _err,
							...)
{
	va_list args;

	static char msg[MAX_MSG_SIZE + 1];
	
	va_start(args, _err);
	vsnprintf(msg, MAX_MSG_SIZE, _err, args);
	va_end(args);

	// add it
	Error* e = new Error();
	
	e->l = _lineNum;
	e->c = _colNum;
	e->s = (char*)malloc(strlen(msg) + 1);
	strcpy(e->s, msg);
	
	e->prev = mHead;
	mHead = e;
	
	mCount++;

}

	
void ErrorList::print()
{
	ErrorListItr itr(this);
	
	Error* e = itr.first();

	while(e)
	{
#ifdef CEP_DEBUG
		fprintf(stdout, "Line %d: %s (CEP_DEBUG-MODE)\n", e->l, e->s);
#endif
		fprintf(stderr, "Line %d: %s\n", e->l, e->s);

		e = itr.next();
	}
	
	/*
	for(int i = 0; i < count; i++)
	{
#ifdef CEP_DEBUG
		fprintf(stdout, "Line %d: %s (CEP_DEBUG-MODE)\n", list[i].err->l, list[i].err->s);
#endif
		fprintf(stderr, "Line %d: %s\n", list[i].err->l, list[i].err->s);
	}
	*/
}


ErrorList::ErrList* ErrorList::createSortedList(int& count_)
{
	count_ = mCount;
	
	ErrList* list = (ErrList*)malloc(sizeof(ErrList) * count_);

	Error* e = mHead;
	
	int i = 0;
	while(e)
	{
		list[i++].err = e;
		e = e->prev;
	}
	
	qsort((void*)list, count_, sizeof(ErrList), comp);
	
	return list;
}





int ErrorList::comp(const void *v1, const void *v2)
{
	int first = ((ErrorList::ErrList*)v1)->err->l;
	int second = ((ErrorList::ErrList*)v2)->err->l;
	
	if(first > second)
		return 1;
	if(first < second)
		return -1;
	return 0;
}

