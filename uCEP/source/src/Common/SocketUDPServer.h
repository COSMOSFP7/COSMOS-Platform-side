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


///#include <string>
#include <netinet/in.h>
#include "Configuration/IniFileSection.h"

#ifndef SOCKETUDPSERVER_H
#define	SOCKETUDPSERVER_H

namespace solcep {
    
  class SocketUDPServer
    {
        public:
            
            SocketUDPServer();
            SocketUDPServer(IniFileSection);
            virtual ~SocketUDPServer();
            
///            std::string readEventFromSocketUDP();
            char* readEventFromSocketUDP();
///            int sendData(const char*, int);
              int sendData(char*, int);
            
        protected:
            static int createSocket();
            static int bindSocket(const char*);
            
            unsigned short int mListeningPort;//= 29654;
            unsigned short int mEmitterPort;//= 50000;
            static const int mMaxPacketSize=1024;

            char* mPacket;
            int mPubSocket;
            
///            std::string lineRead;
    
    };
  
  }
  
#endif	/* SOCKETUDPSERVER_H */

