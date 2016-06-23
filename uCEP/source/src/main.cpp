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

#include "Common/BCEPManager.h"


//using namespace solcep;
//using namespace std;



/*
 * 
 */
int main(int argc, char** argv) {
    
    
#ifdef MQTT
    printf("MQTT enabled \n");
#endif
#ifndef MQTT
    printf("UDP enabled \n");
#endif
    
    
    BCEPManager* bCEPManager = new BCEPManager();
    bCEPManager->BCEPStart(argc, argv);

///    exit(2);
    return 0;
}

