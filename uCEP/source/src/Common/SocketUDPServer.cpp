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

#include "SocketUDPServer.h"
///#include <netinet/in.h>
///#include <arpa/inet.h>
#include "Tracer.h"
#include "Configuration/IniFileSection.h"
///#include <stdlib.h>
#include <string.h>
///#include <unistd.h>
#include <poll.h>


namespace solcep {

    int mSocket;
    int mAddressLength, mAddrEmiterLenght;
    struct sockaddr_in mServerAddress;
    struct sockaddr_in clientAddr;
    int mEmitterSocket;
    struct sockaddr_in mEmitterServerAddress;
    
///    SocketUDPServer::SocketUDPServer() {
    SocketUDPServer::SocketUDPServer(IniFileSection _iniFileSec) {
    //init the socket;
                
        mListeningPort= _iniFileSec.portUDPCollect;
        mEmitterPort= _iniFileSec.portUDPPublish;
        
        mPubSocket = createSocket();
        if (mPubSocket == -1)
            ERROR() << "Unable to create the UDP Socket!!" << std::endl;
        else  {
            std::ostringstream sckt; 
            sckt << mListeningPort;
            INFO() << "Listening at UDP Socket port: "<< sckt.str() << std::endl;

        }
        
        bzero(&(mServerAddress.sin_zero), sizeof(mServerAddress.sin_zero));
        mServerAddress.sin_family = AF_INET;
        mServerAddress.sin_port = htons(mListeningPort);
        mServerAddress.sin_addr.s_addr = INADDR_ANY;
    
        mAddressLength = sizeof(mServerAddress);

        int resBind = bind(mPubSocket, (struct sockaddr *)&mServerAddress, mAddressLength);
        if (resBind == -1) {
            ERROR() << "Unable to bind the Collector UDP Socket!!" << std::endl;            
        }


    };
    
    SocketUDPServer::~SocketUDPServer() { 
    
    mSocket = 0;
    mAddressLength = 0;
    mServerAddress = {};
    clientAddr = {};
    
    shutdown(mPubSocket, 2);
    shutdown(mEmitterSocket, 2);
    }

    
    int SocketUDPServer::createSocket() {
            
      if((mSocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
            return -1;
        }

      return mSocket;
     
    }

    int SocketUDPServer::bindSocket(const char* connString) {
     
      	if(bind(mSocket, (struct sockaddr*)&mServerAddress, mAddressLength) == -1)
	{
		return -1;
	}

        return 0;
    }

/*
///    std::string SocketUDPServer::readEventFromSocketUDP() {
        char* SocketUDPServer::readEventFromSocketUDP() {
        
        int bytesRead = 0;
///        lineRead.clear();
        mPacket = (char*)malloc(mMaxPacketSize + 1);

      struct pollfd fds[1];             
///      struct pollfd* fds = (struct pollfd*)malloc(sizeof(struct pollfd));
      
      int timeout= 10;                   
      
      fds[0].fd = mPubSocket;
      fds[0].events = 0;
      fds[0].events |= POLLIN;
      bzero(mPacket, mMaxPacketSize);
          
      if ( poll(fds, 1, timeout) != 0 ) {   ///era == 0 
///         printf("Select has timed out...\n");
///       }

///          bzero(mPacket, mMaxPacketSize);
            
//            while (1) {
                bytesRead = recvfrom(mPubSocket, mPacket, mMaxPacketSize, 
                                    0,
                                    (struct sockaddr*)&mEmitterServerAddress,    //used in the client socket
                                    (socklen_t*)&mAddressLength);

///                        if(bytesRead > 0)
///                        {
///                            std::string msg(mPacket, mPacket + bytesRead);
///                            lineRead = msg;
///                        }
                
///                }
//            }
      }
///      delete fds;
///      free(mPacket);
      
///      return lineRead;
      return mPacket;

    }
*/    


///is socket client of external application
   
///     int SocketUDPServer::sendData(const char* data, int len) {
         int SocketUDPServer::sendData(char* data, int len) {
     
///     int mEmitterPort=50000;

     if (mEmitterSocket < 1)
        mEmitterSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if(mEmitterSocket == -1)
    {
	return 0;
    }
     
    bzero(&(mEmitterServerAddress.sin_zero), sizeof(mEmitterServerAddress.sin_zero));
             
    mEmitterServerAddress.sin_family = AF_INET;
    mEmitterServerAddress.sin_port = htons(mEmitterPort);

    if (len < 1)
         return -1;

     int res = sendto(mEmitterSocket,
                        data, 
			len,
			0,
			(struct sockaddr *)&mEmitterServerAddress,
			sizeof(mEmitterServerAddress));
     
     	if(res <= 0)
		return -1;
     
        return 0;
        
 }
 
    
}
