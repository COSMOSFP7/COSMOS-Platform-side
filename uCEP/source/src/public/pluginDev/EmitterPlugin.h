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

#ifndef _ATOS_SOLCEP_PUB_EVENT_EMITTER_PLUGIN_H_
#define _ATOS_SOLCEP_PUB_EVENT_EMITTER_PLUGIN_H_

#include "CEPPlugin.h"

class EmitterPlugin : public CEPPlugin
{
public:

	EmitterPlugin() {}
	
	virtual ~EmitterPlugin() {}
	
															
	/*!
		\brief Emits an event.
			To be implemented by the plugin provider.
			
		\param data The event data
		\param size The event size
			
		\returns PLUGIN_OK if emitted succesfully.
	*/
	virtual int emit(	const unsigned char* _data, 
						const unsigned int _size) = 0;

protected:

	EmitterPlugin(const EmitterPlugin& rhs)	{ }
	
	EmitterPlugin& operator= (const EmitterPlugin& rhs)	{ return* this; }		

private:


};





#endif


