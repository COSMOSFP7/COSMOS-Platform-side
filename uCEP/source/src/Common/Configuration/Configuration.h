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
    Conventions for file<path | dir | name>:
            dir = directory, EXCLUDING trailing file separator. Example: /var/log
            name = name WITHOUT dir. Example: cep.log
            path = [ dir + file separator ] + name. Examples: /var/log/cep.log, cep.log


    solcep [rootpath] 

    Configurable items:
    These must be done at startup. This file contains the master config settings. Cannot be edited.

            ConfigFileLocation
            administration interface port
            location of the log file
            location of the dolce file
            name of the dolce file	
*/

#pragma once

///#include <string>
#include "ConfigTypes.h"

namespace solcep {

class Configuration
{
public:		
	//! Root path where SOL/CEP executes.
	std::string serverRoot;
	
	Config::Coordinator coordinator; 
	Config::ComplexEventDetector complexEventDetector;
	Config::EventCollector eventCollector;
        Config::ComplexEventPublisher complexEventPublisher;

	// App Helpers
	Config::ComplexEventDetector* findComplexEventDetector(std::string id) const;
	
protected:

	//@{
	//! Internal ports (ZMQ). 
	static const int INT_CEP_PORT = 5555;	// The Complex Event Processor listens here.
	//@}
};

}


