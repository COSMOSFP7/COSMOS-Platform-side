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
	See the "SOL/CEP Plugin Developers Guide" (SOL-CEP-0009) and
	the "SOL/CEP Event Wire Protocol" (SOL-CEP-0007) for more information.
*/

#ifndef _ATOS_SOLCEP_PUB_DECODER_PLUGIN_H_
#define _ATOS_SOLCEP_PUB_DECODER_PLUGIN_H_

#include "CEPPlugin.h"
#include <string>

class DecoderPlugin : public CEPPlugin
{
public:

	DecoderPlugin() {}
	
	virtual ~DecoderPlugin() {}
	

	/*!
		\brief  Must be implemented by plugin
                        Called by SOL/CEP when it wants to decode something. 
			
		\param message	Message to be decoded, provided by SOL/CEP.
		\return decoded message.
	*/
	virtual std::string decode(std::string message) = 0;


protected:

	DecoderPlugin(const DecoderPlugin& rhs)	{ }
	
	DecoderPlugin& operator= (const DecoderPlugin& rhs)	{ return* this; }		

private:


};





#endif


