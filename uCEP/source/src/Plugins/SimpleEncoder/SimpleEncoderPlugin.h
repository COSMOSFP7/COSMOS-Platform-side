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
	Encodes to the Simple Event Format
*/
	
#ifndef _SOL_CEP_PLUGIN_SIMPLE_ENCODER_
#define _SOL_CEP_PLUGIN_SIMPLE_ENCODER_

#include "../../public/pluginDev/EncoderPlugin.h"
#include "../../Common/WireEvent/WireEventDecoder.h"
///#include <string>

class SimpleEncoderPlugin : public EncoderPlugin
{
public:
	virtual ~SimpleEncoderPlugin() {};
	
	virtual int load();
	
	virtual void unload();
	
	virtual std::string encode(std::string message);

	static const int ERR_ENCODER = 100;	

private:

    solcep::WireEventDecoder* mWD;
};



#endif


