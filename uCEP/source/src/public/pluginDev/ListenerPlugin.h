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

#ifndef _ATOS_SOLCEP_PUB_EVENT_LISTENER_PLUGIN_H_
#define _ATOS_SOLCEP_PUB_EVENT_LISTENER_PLUGIN_H_

#include "CEPPlugin.h"

class ListenerPlugin : public CEPPlugin
{
public:

	ListenerPlugin() {}
	
	virtual ~ListenerPlugin() {}
	
	/*!
		\brief
		Prototype for callback function. Implemented by SOL/CEP.
		Must be called to present data to SOL/CEP
		
		\param _data The data to send 
		\param _size The size of the data
		\param _reserved MUST be the parameter supplied in _reserved by start().
	*/
	typedef int (ListenerPlugin::*TDataCallbackFunc)(const unsigned char* _data,
														  const unsigned int _size,
														  void* _reserved);
															
	/*!
		\brief 
			Must be implemented by plugin provider.
			
			Called by SOL/CEP when it wants to start listening. 
			It is expected a continuous loop that calls
			send() each time data is received.
			
		\param _dataCallback	Provided by SOL/CEP when invoked.
		\param _reserved 		Provided by SOL/CEP when invoked. 
								Atos reserved.
			
		\return PLUGIN_OK when finished or other error code when
			it cannot be started.
	*/
	virtual int start(	TDataCallbackFunc _dataCallback, 
						void* _reserved) = 0;

	/*!
		\brief 
			Must be implemented by plugin provider
			
			Called by SOL/CEP when it wants to stop	listening. 
			
		\return PLUGIN_OK.
	*/
	virtual int stop() = 0;
	
	
	/*!
		\brief Provided by SOL/CEP
	*/
	int callback(const unsigned char*, unsigned int, void*);

protected:

	ListenerPlugin(const ListenerPlugin& rhs)	{ }
	
	ListenerPlugin& operator= (const ListenerPlugin& rhs)	{ return* this; }		

private:


};





#endif


