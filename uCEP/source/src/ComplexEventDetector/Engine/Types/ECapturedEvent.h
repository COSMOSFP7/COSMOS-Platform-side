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


/*!
	\brief Types for the Execution Framework

*/
#ifndef _SOL_CEP_ENGINE_TYPES_ECAPTURED_EVENT_H_
#define _SOL_CEP_ENGINE_TYPES_ECAPTURED_EVENT_H_

///#include <time.h>

#include "EProgram.h"

struct EEventPeriod;

struct ECapturedEvent
{
	ECapturedEvent() : oid(-1L)
					, values(0)
					, prev(0)
					, next(0)
					
	{}
	
	
	time_t timeStamp;
	
	long oid;
        unsigned char type;

	EEventAttributeValue* values;
	
#ifdef CEP_DEBUG
	char name[33];
#endif	

	// Double-LL
	ECapturedEvent* prev;
	ECapturedEvent* next;	
};


#endif
