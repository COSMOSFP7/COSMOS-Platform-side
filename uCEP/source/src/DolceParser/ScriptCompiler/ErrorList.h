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
	Unified compiler error list 
*/
#ifndef _ERROR_LIST_H_
#define _ERROR_LIST_H_

#include <stdlib.h>
#include <assert.h>

/*!
	\brief Error list for use with Compiler
*/
class ErrorList
{
	friend class ErrorListItr;
public:

	ErrorList();
	
	~ErrorList();

	void addError(	const int _lineNum, 
					const int _colNum, 
					const char* _err,
					...);
	
	void print();
	
	bool hasError() const { return (mHead != 0); }
	
	//LL
	struct Error
	{
		int l;
		int c;
		char* s;
		
		struct Error* prev;
	};
	
	struct ErrList
	{
		int lineNum;
		
		Error* err;
	};

        Error* mHead;  ///RP: was 
        
protected:
	ErrorList(const ErrorList& rhs)	{}
	ErrorList& operator= (const ErrorList &rhs)	{ return *this; }
	
	ErrList* createSortedList(int& count_);
	
private:


	static const int MAX_MSG_SIZE = 256;

	

//	Error* mHead;           ///RP: to show more detail
	int mCount;
		
	static int comp(const void *v1, const void *v2);
};


//------------------------------------------------------------------------

/*
	Iterator for Error List.

	Permits independent iteration, e.g. from threads.
	
	Usage:
		ErrorListItr itr(errorListInstance);
		ErrorList::Error* err = itr.first();
		while(err)
		{
			err = itr.next();
		}
*/
class ErrorListItr
{
public:

	ErrorListItr(ErrorList* const _errList)
	{
		assert(_errList);
		
		mCurr = 0;
		
		mErrList = _errList->createSortedList(mCount);
	}
	
	
	~ErrorListItr()
	{
		free(mErrList);
	}
		
	
	ErrorList::Error* const first() const
	{
		return next();
	}
	
	
	ErrorList::Error* const next() const
	{
		ErrorList::Error* ret = 0;
		
		if(mCurr < mCount)
			ret = mErrList[mCurr].err;
			
		mCurr++;
		
		return ret;
	}
	
protected:

private:
	
	int mCount;
	mutable int mCurr;
	ErrorList::ErrList* mErrList;
};



#endif

