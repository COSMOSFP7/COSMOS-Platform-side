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


#pragma once

//#include <pthread.h>
#include "ComplexEventObserver.h"
#include "Engine/Types/EFramework.h"
#include "Engine/Engine.h"
///#include <string>
#include "../Common/Trace.h"
#include "../Common/Tracer.h"
//#include "../Common/FileEventsOperations.h"
#include "../Common/SocketUDPServer.h"
#include "../Common/WireEvent/WireEventDecoder.h"
#include "../Common/WireEvent/WireEventBuilder.h"
#include "../Common/Communication/CommunicationModule.hpp"

namespace solcep {

/*!
    \brief Detects complex events.
 */
class ComplexEventDetector : public ComplexEventObserver
{
public:
    ComplexEventDetector(EFramework * const framework);

    virtual ~ComplexEventDetector();

    //! Implemented from ComplexEventObserver base class.
    virtual void raise(EComplexEvent* _complexEvent, ECapturedEvent* _origEvent = 0);

    void publishData(std::string message);
    void publishExceptionalData(std::string message);
    void preparePublishToAbsent(EComplexEvent* _complexEvent, ECapturedEvent* _origEvent);
    
    Engine* mEngine;
///    FileEventsOperations* mFileEventOper;
    //SocketUDPServer* mSocketUDPServer;
///    WireEventDecoder *wed;
    
    CommunicationModule* cm;
    
    //! CEPWorker Callback
    void processPublishedMessage(std::string message);
    
private:
///    bool belongToPayload(std::string, EComplexEvent*);
    
///RP:    
    bool complexEventIsPrintable(EComplexEvent* _complexEvent);
///    long appearInSomeDetectionTree(EComplexEvent* _complexEvent);
    //RP:
    EComplexEvent* appearInSomeDetectionTree(EComplexEvent* _complexEvent);
    void createInjectedEvent(EComplexEvent* _complexEvent, ECapturedEvent* _origEvent);
    WireEventBuilder* addAttributesToPublish(EComplexEvent* _complexEvent, ECapturedEvent* _origEvent);
    void putQuotationMarks(char *_tmpStr, TValue _tv);
    
};

}
