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
	Interface for Config File Handlers.
	Config File Handlers know how to read an write Configuration files.
	
*/
#pragma once
#include "Configuration.h"

namespace solcep {

class IConfigFileHandler
{
public:

	virtual ~IConfigFileHandler() {}

	virtual void read(Configuration& conf) = 0;
	virtual void write(Configuration& conf) = 0;
};

}


