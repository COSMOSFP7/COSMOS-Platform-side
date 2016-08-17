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


#ifndef _SOL_CEP_S_EVENT_H_
#define _SOL_CEP_S_EVENT_H_

#include "TValue.h"
#include "../ComplexEventDetector/Engine/Types/EComplexEvent.h"
#include "../ComplexEventDetector/Engine/Types/EPayloadAttribute.h"

struct SNVPairs
{
    SNVPairs() : name(0), prev(0) {}
    ~SNVPairs() 
    { 
        if(name)
            free(name);
    }

    unsigned long id;
    char* name; // if 0, id is used

    TValue val;	

    SNVPairs* prev;
};

/*!
    \brief Incoming event from the outside, to be presented to the Framework
*/
struct SEvent
{
    SEvent() : type(0),	id(0), name(0), nvPairs(0) {}
    ~SEvent() {	
        
        SNVPairs *toDlt, *snvP = nvPairs;      

        while (snvP) {
            toDlt= snvP;
            snvP = snvP->prev;
            if (toDlt->val.t == t_string && strlen(toDlt->val.v.stringVal))
                free(toDlt->val.v.stringVal);
                        
            toDlt->val=0;
            
            delete toDlt;
        }

        free(name);            
        
    } //FIXME-TODO cleanup any allocated memory  
	
    unsigned char type;
	
    unsigned long id;
    char* name;	// if 0, id is used.
	
    SNVPairs* nvPairs;
///RP: used to injected events
    EComplexEvent *refComplex;
    long oid;
    EPayloadAttribute *payloadAttrs;
    
};





#endif

