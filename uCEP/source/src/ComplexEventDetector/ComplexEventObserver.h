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
	Abstract interface that observes the generation of complex events.
	
*/
#ifndef _SOL_CEP_COMPLEX_EVENT_OBSERVER_H_
#define _SOL_CEP_COMPLEX_EVENT_OBSERVER_H_

struct EComplexEvent;
struct ECapturedEvent;

class ComplexEventObserver
{
public:
	
	/*!
		\brief Called by the observed object when there is a complex
			event
		\param _complexEvent The Complex Event that is raised.
		\param _origEvent The event that originated the complex event.
			If 0, the complex event was caused by time expiry
	*/
	virtual void raise(EComplexEvent* _complexEvent, ECapturedEvent* _origEvent = 0) = 0;

	
protected:
	
	ComplexEventObserver() {}
					
	virtual ~ComplexEventObserver() {}


private:

	ComplexEventObserver(const ComplexEventObserver& rhs) 
	{ }
	
	ComplexEventObserver& operator= (const ComplexEventObserver& rhs)	{ return *this; }


};



#endif


