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
	Types for the Execution Framework
	
*/
#ifndef _SOL_CEP_ENGINE_TYPES_EVENT_PERIOD_H_
#define _SOL_CEP_ENGINE_TYPES_EVENT_PERIOD_H_



struct EEventList;	


struct EEventPeriod
{
	EEventPeriod() : duration(0)
					, events(0)
	{}

	time_t duration;
	
	EEventList* events;
};


#endif
