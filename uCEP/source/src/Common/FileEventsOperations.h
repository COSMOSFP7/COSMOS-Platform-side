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


///RP: not used: now  we use udp sockets
/*

#include <string>

#ifndef FILEEVENTSOPERATIONS_H
#define	FILEEVENTSOPERATIONS_H

namespace solcep {
    
    class FileEventsOperations
    {
        public:
            
            FileEventsOperations();
            
            virtual ~FileEventsOperations();
            
            bool existsEventInFile();
            
            std::string readEventFromFile();
            
            void writeCEventToFile(std::string);

            const char* getFileName();

///RP 0k:
    //        const char* fNameIn = (const char*)"/home/adminuser/projects/bcep/incoming/event.txt";
    //        const char* fNameOut = (const char*)"/home/adminuser/projects/bcep/outgoing/"; // to write the file with triggered event.
///RP 0k:
            
            const int LENMAXPATH = 128;
            char* fNameIn = new char[LENMAXPATH];
            char* fNameOut = new char[LENMAXPATH];
            
    protected:
            
        
    };
}

#endif	/* FILEEVENTSOPERATIONS_H */

*/