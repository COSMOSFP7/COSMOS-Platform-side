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
	Engine
	
*/
#ifndef _SOL_CEP_EVENT_BUILDER_H_
#define _SOL_CEP_EVENT_BUILDER_H_


///#include <stdio.h>

#include "../ScriptCompiler/ASTree.h"


class FrameworkBuilder;
struct EEvent;
struct EComplexEvent;
struct EEventAttribute;
struct ProgramBuilder;

class EventBuilder
{
public:
	EventBuilder(	FrameworkBuilder* const _eb,
					EEvent* _event_);
					
	EventBuilder(	FrameworkBuilder* const _eb);

	~EventBuilder();
	
							
	int build(ASTree* const _node);
	

	/*!
		\brief Relates a complex event to the event, only if it's 
			not already related.
		\param _complex The complex event to add
		\returns OK
	*/
	int addComplexEventRef(EComplexEvent* const _complex);
	
	/*!
		Returns a built event structure.
		Caller is responsible for releasing memory
	*/
	EEvent* finalize();
	
protected:
	
	EventBuilder();
	
	EventBuilder(const EventBuilder& rhs) : mEvent(0), mFrameworkBuilder(0)	{ }
	
	EventBuilder& operator= (const EventBuilder& rhs)	{ return *this; }


	void init();
	void deinit();

	int buildEventAttributes(ASTree* const _node);
	
private:

	EEvent* mEvent;
	FrameworkBuilder* const mFrameworkBuilder;
	
#ifdef CEP_DEBUG

	void printEventAttributes();

#endif

};



#endif


