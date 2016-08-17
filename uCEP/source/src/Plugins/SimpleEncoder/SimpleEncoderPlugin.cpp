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

#include "SimpleEncoderPlugin.h"

///#include <string>
///RP: #include <cstring>
#include <stdexcept>
#include "../../Types/SEvent.h"

using namespace std;

int SimpleEncoderPlugin::load() 
{ 
	mWD = new solcep::WireEventDecoder();
	return 0;
}

void SimpleEncoderPlugin::unload()
{
    mWD->externalDestroy(1);
    delete mWD;
}

string SimpleEncoderPlugin::encode(string message)
{
	SEvent* e = mWD->create((unsigned char*)message.c_str(), message.length());

	if(!e)
            throw runtime_error("Unable to encode message!");

        char buff[256];
///        sprintf(buff, "%s", e->name);
        sprintf(buff, "%d %s", e->type, e->name); 
	
        string str = buff;
        
	SNVPairs* attr = e->nvPairs;
	
	while(attr)
	{
		if(attr->val.t == t_int)
			str += " int";
		else if(attr->val.t == t_float)
			str += " float";
		else if(attr->val.t == t_string)
			str += " string";
        	else if(attr->val.t == t_char)
			str += " char";
                else if(attr->val.t == t_pos)
			str += " pos";
                else if(attr->val.t == t_area)
			str += " area";
		else if(attr->val.t == t_time)
			str += " time";
		else
                    str += " [UNSUPPORTED-TYPE]";

		
                sprintf(buff, " %s %s", attr->name, attr->val.asStringRaw());
///RP::28102015                                sprintf(buff, " %s %s ", attr->name, attr->val.asString());
		str += buff;

		attr = attr->prev;
	}
	
	
	str += "\n";
        
        return str;
}






