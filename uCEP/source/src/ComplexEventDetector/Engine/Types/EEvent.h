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
#ifndef _SOL_CEP_ENGINE_TYPES_EEVENT_H_
#define _SOL_CEP_ENGINE_TYPES_EEVENT_H_

#include "EProgram.h"
#include "EEventAttribute.h"

#include <stdlib.h>
#include <stdio.h>

struct EEventPeriod;
struct EProgram;
struct EComplexEvent;
///struct EEventAttribute;

struct EEvent
{
	EEvent() : oid(-1L)
			, id(0)
			, name(0) 
			, accept(0)
			, attributes(0)
			, refComplexEvents(0)
			, period(0)
			, prev(0)
	{}

	long oid;			//! engine object id (internal)
	
	//!@{
	/*!
		\brief Events can be identified either by id or by name
		The initial Dolce spec included a 'map' keyword to map names
		to internal ids, for performance reasons.
		Currently, just the name is used. Id has been left in the structs,
		should the 'map' keyword or similar be implemented in the future.
	*/
	unsigned long id;	//! Not used.
	char* name;
	//!@}
	
	EProgram* accept; //! Stack-program for expression evaluation.
	EEventAttribute* attributes;
	EComplexEvent* refComplexEvents; //! Complex events that reference this event.
	EEventPeriod* period;
	
	EEvent* prev; //  Used for LL
        
        ~EEvent() {
            
            EEventAttribute *toDlt, *eEAttr = attributes;
        
            while (eEAttr) {
                toDlt= eEAttr;
                eEAttr = eEAttr->prev;
                free(toDlt->name);
                delete toDlt;
            }
            free(name);
        }

};


#endif
