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
  
 */#include "EventBuilder.h"

///#include <stdio.h>
///#include <string.h>
///#include <stdlib.h>
///#include <assert.h>

#include "../../Common/Err.h"


#include "../../ComplexEventDetector/Engine/Types/EEvent.h"
#include "../../ComplexEventDetector/Engine/Types/EEventAttribute.h"
#include "../../ComplexEventDetector/Engine/Types/EComplexEvent.h"

#include "FrameworkBuilder.h"
#include "ProgramBuilder.h"


EventBuilder::EventBuilder(FrameworkBuilder* const _fb,
							EEvent* _event_)
	: mEvent(_event_)
	, mFrameworkBuilder(_fb)

{
	assert(_event_);
}



EventBuilder::EventBuilder(FrameworkBuilder* const _fb)
	: mEvent(0)
	, mFrameworkBuilder(_fb)

{

}

EventBuilder::~EventBuilder()
{

}


void EventBuilder::init()
{
}


void EventBuilder::deinit()
{
}


int EventBuilder::build(ASTree* const _node)
{
#ifdef CEP_DEBUG
	printf("EventBuilder::build | node = [0x%p]\n", _node);
#endif

	ASTreeItr itr(_node);
	
	ASTree* node;
	ProgramBuilder* pb = mFrameworkBuilder->getProgramBuilder();

	//--- Create
	//
	node = itr.firstChild();
	assert(node);
	
	mEvent = new EEvent();
	node->getSymbol()->engineObj = (void*)mEvent;
	
	char* name = node->getSymbolName();
	char* c = (char*)malloc(strlen(name) + 1);
	strcpy(c, name);
	
	mEvent->name = c;
        
	mEvent->oid = mFrameworkBuilder->getNextOid();
	
	//--- Attributes ("use")
	//
	node = _node->descendant(ASTree::PUse);
	if(node)
	{
		buildEventAttributes(node);
		
	}
	
	//--- Accept-Condition ("accept")
	//
	node = _node->descendant(ASTree::PAccept);
	
	if(node)
	{
		pb->build(node);
		mEvent->accept = pb->finalize();
		
	}
	
	//--- Period ("lasts")
	//
	node = _node->descendant(ASTree::PLasts);
	if(node)
	{
		//FIXME
	}

	return OK;
}



int EventBuilder::addComplexEventRef(EComplexEvent* const _complex)
{
	EComplexEvent* ce = mEvent->refComplexEvents;
	
	// Do not add if it already exists
	while(ce)
	{
		if(ce->oid == _complex->oid)
			return OK;
			
		ce = ce->prev;
	}
	
	_complex->prev = mEvent->refComplexEvents;
	mEvent->refComplexEvents = _complex;
                
	return OK;
}



EEvent* EventBuilder::finalize()
{
	return mEvent;
}


//FIXME: string-constants --> data page + back-ref



int EventBuilder::buildEventAttributes(ASTree* const _node)
{
	ASTreeItr itr(_node->descendant(ASTree::PEventAttributeList));
	
	ASTree* attr = itr.firstChild();
	ASTree* id;
	mFrameworkBuilder->getSymbolTable();
	
	SymbolTable::Symbol* sym;
	
	while(attr)
	{
		id = attr->descendant(ASTree::PIdentifier);
		assert(id);
		sym = id->getSymbol();
		assert(sym);
		
		EEventAttribute* ea = new EEventAttribute();
///RP: to fix   (char*)malloc(strlen(name) + 1)
                ea->name = (char*)malloc(strlen(sym->name) + 1);
		strcpy(ea->name, sym->name); //FIXME dynamic alloc!
		
		ea->type = sym->dataType;
		ea->oid = mFrameworkBuilder->getNextOid();

#ifdef CEP_DEBUG
		printf("[EventBuilder::buildEventAttributes] setting type for attr '%s' to '%s'\n", ea->name, symTab->dataTypeAsString(ea->type));
#endif
		// make sure we can find the attribute reference from other parts of the engine
		sym->engineObj = (void*)ea;
		
		// add to list
		ea->prev = mEvent->attributes;
		mEvent->attributes = ea;
		
		attr = itr.nextChild();
	}

	return 0;
}




#ifdef CEP_DEBUG

void EventBuilder::printEventAttributes()
{
	//mFrameworkBuilder->printEventAttributes(mEvent);
}



#endif


