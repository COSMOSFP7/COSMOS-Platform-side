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
	Time 
*/
#ifndef _SOL_CEP_TYPES_TIME_LITERAL_H_
#define _SOL_CEP_TYPES_TIME_LITERAL_H_

#include <time.h>
///#include <assert.h>

#include "TDurationLiteral.h"

struct TTimeLiteral
{
	/* future:
	char mustRepeat; - Y if no YYYY-MM-DD specified 

	char yy;
	char mm;
	char dd;
	*/
	
	char hh;
	char mm;
	char ss;
	

	TTimeLiteral operator+=(const int& rhs) 
	{
		addTime((time_t)rhs);
		return *this;
	}
	
	
	TTimeLiteral operator+=(const TDurationLiteral& rhs) 
	{
		addTime(rhs);
		return *this;
	}

	TTimeLiteral operator-=(const int& rhs) 
	{
		addTime((time_t)-rhs);
		return *this;
	}
	
	TTimeLiteral operator-=(const TDurationLiteral& rhs) 
	{
		addTime(-rhs);
		return *this;
	}
	
	
	bool operator==(const TTimeLiteral& rhs) 
	{
		return (hh == rhs.hh) 
			&&	(mm == rhs.mm)
			&&	(ss == rhs.ss);
	}
	
	
	bool operator!=(const TTimeLiteral& rhs) 
	{
		return !(*this == rhs);
	}


	void addTime(const time_t _seconds)
	{
		time_t t = toSeconds();
		
		t += _seconds;		

		t %= 86400; // 24h rollover
		
		fromSeconds(t);
	}

	
	time_t toSeconds()
	{
		return hh*(time_t)3600 + mm*(time_t)60 + ss;	
	}
	
	
	void fromSeconds(const time_t _seconds)
	{
		time_t t = _seconds;
		
		hh = t / (time_t)3600;
		t -= (hh*(time_t)3600);
	
		mm = t / (time_t)60;
		t -= (mm*(time_t)60);
	
		ss = t;
	}
};



#endif

