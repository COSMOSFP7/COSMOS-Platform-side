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

//#include "../Trace.h"
#include "Trace.h"
#include <iostream>
///#include <iomanip>

namespace solcep{

/*
 *  Propagates trace messages to standard error output
 */
class StdOutTracer : public ITracer
{   
public:
    void Trace(std::string message) 
    {
        std::cerr << message;
    }
};

/*  
 *  Propagates log messages to remote log writer.
 */

///RP
/*
class SockTracer : public ITracer
{
public:
    SockTracer(EndPoint& endPoint, std::unique_ptr<ITracer> tracer)
        : mTracer(std::move(tracer))
    {
        mSocket = make_unique<zmq::socket_t>(endPoint.getContext(), ZMQ_PUSH);
        std::string conStr = endPoint.getConnStr();
        mSocket->connect(conStr.c_str());
    }
    
    void Trace(std::string message)
    {     
        if(!mSocket->send(message.data(), message.size(), ZMQ_DONTWAIT))
            WARN() << "Socket busy, message was not sent!" << std::endl;
        if(mTracer)
            mTracer->Trace(message);
    }
    
private:
    std::unique_ptr<zmq::socket_t> mSocket;
    std::unique_ptr<ITracer> mTracer;
};
*/


}

