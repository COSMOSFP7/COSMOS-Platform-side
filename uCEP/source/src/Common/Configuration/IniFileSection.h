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


#ifndef INIFILESECTION_H
#define	INIFILESECTION_H

#include <string>


struct IniFileSection
{
    std::string confFile = "./confFile.ini";
            
    int portUDPCollect = 29201;
    int portUDPPublish = 50000;
    
    int portMQTT = 1883;
    std::string hostMQTT = "localhost";
    std::string topicMQTTCollect = "topicInputDefault";
    std::string topicMQTTPublish = "topicOutputDefault";
    std::string dolceSpec = "detect.dolce";
    std::string cepName = "bcep";
    const char * userMQTT = NULL;
    const char * passwordMQTT = NULL;


    
};

#endif	/* INIFILESECTION_H */

