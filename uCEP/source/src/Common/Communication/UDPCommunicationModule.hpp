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


#ifndef UDPCOMMUNICATIONMODULE_HPP
#define	UDPCOMMUNICATIONMODULE_HPP


#include "../Configuration/ReadIniFile.h"
#include <netinet/in.h>
#include <poll.h>



namespace solcep {

    class UDPCommunicationModule : public CommunicationModule {
    public:
        UDPCommunicationModule(IniFileSection iniFileSection);
        ~UDPCommunicationModule();
        virtual char * receiveData();
        virtual void sendData(const char * message);
    protected:
        static int createSocket();
        static int bindSocket(const char*);

        unsigned short int mListeningPort; //= 29654;
        unsigned short int mEmitterPort; //= 50000;
        static const int mMaxPacketSize = 1024;

        char* mPacket;
        int mPubSocket;





    };

    int tsocket;
    int taddressLength, taddrEmiterLenght;
    struct sockaddr_in tServerAddress;
    struct sockaddr_in tclientAddr;
    int tEmitterSocket;
    struct sockaddr_in tEmitterServerAddress;

    UDPCommunicationModule::UDPCommunicationModule(IniFileSection iniFileSection) {
        
        IniFileSection _iniFileSec = iniFileSection;

        mListeningPort = _iniFileSec.portUDPCollect;
        mEmitterPort = _iniFileSec.portUDPPublish;

        mPubSocket = createSocket();
        if (mPubSocket == -1)
            ERROR() << "Unable to create the UDP Socket!!" << std::endl;
        else {
            std::ostringstream sckt;
            sckt << mListeningPort;
            INFO() << "Listening at UDP Socket port: " << sckt.str() << std::endl;

        }

        bzero(&(tServerAddress.sin_zero), sizeof (tServerAddress.sin_zero));
        tServerAddress.sin_family = AF_INET;
        tServerAddress.sin_port = htons(mListeningPort);
        tServerAddress.sin_addr.s_addr = INADDR_ANY;

        taddressLength = sizeof (tServerAddress);

        int resBind = bind(mPubSocket, (struct sockaddr *) &tServerAddress, taddressLength);
        if (resBind == -1) {
            ERROR() << "Unable to bind the Collector UDP Socket!!" << std::endl;
        }
    }
    UDPCommunicationModule::~UDPCommunicationModule(){
        tsocket = 0;
        taddressLength = 0;
        tServerAddress = {};
        tclientAddr = {};

        shutdown(mPubSocket, 2);
        shutdown(tEmitterSocket, 2);
        
    }
    
    int UDPCommunicationModule::createSocket() {
            
      if((tsocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
            return -1;
        }

      return tsocket;
     
    }

    int bindSocket(const char* connString) {
     
      	if(bind(tsocket, (struct sockaddr*)&tServerAddress, taddressLength) == -1)
	{
		return -1;
	}

        return 0;
    }

    
///    std::string SocketUDPServer::readEventFromSocketUDP() {
        char* UDPCommunicationModule::receiveData() {
        
        //int bytesRead = 0;
///        lineRead.clear();
        mPacket = (char*)malloc(mMaxPacketSize + 1);

      struct pollfd fds[1];             /* fd's used by poll */
///      struct pollfd* fds = (struct pollfd*)malloc(sizeof(struct pollfd));
      
      int timeout= 0;                   /* Time value for time out 0/1000 de segundo */
      
      fds[0].fd = mPubSocket;                    /* Poll socket s */
      fds[0].events = 0;
      fds[0].events |= POLLIN;          /* Poll on read readiness */
      bzero(mPacket, mMaxPacketSize);
          
      if ( poll(fds, 1, timeout) != 0 ) {   ///era == 0 
///         printf("Select has timed out...\n");
///       }

///          bzero(mPacket, mMaxPacketSize);
            
//            while (1) {
                recvfrom(mPubSocket, mPacket, mMaxPacketSize, 
                                    0,
                                    (struct sockaddr*)&tEmitterServerAddress,    //used in the client socket
                                    (socklen_t*)&taddressLength);

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
    

///is socket client of external application
   
///     int SocketUDPServer::sendData(const char* data, int len) {
         void UDPCommunicationModule::sendData(const char* data) {
             
             int len = strlen(data) + 1;
     
///     int mEmitterPort=50000;

     if (tEmitterSocket < 1)
        tEmitterSocket = socket(AF_INET, SOCK_DGRAM, 0);
             
    /*
    if(mEmitterSocket == -1)
    {
	return 0;
    }*/
     
    bzero(&(tEmitterServerAddress.sin_zero), sizeof(tEmitterServerAddress.sin_zero));
             
    tEmitterServerAddress.sin_family = AF_INET;
    tEmitterServerAddress.sin_port = htons(mEmitterPort);
    
    
    //if (len < 1)
         //return -1;

     sendto(tEmitterSocket,
                        data, 
			len,
			0,
			(struct sockaddr *)&tEmitterServerAddress,
			sizeof(tEmitterServerAddress));
     /*
     	if(res <= 0)
		return -1;
     
        return 0;
      */
      
      
        
 }
    

#endif	/* UDPCOMMUNICATIONMODULE_HPP */
}



