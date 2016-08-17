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


#include "../../Common/WireEvent/WireEventBuilder.h"
#include "../../Common/WireEvent/WireEventTypesInt.h"
#include "../../Common/Trace.h"

#include "Ticker.h"

namespace solcep
{

using namespace std;

Ticker::Ticker(const int _interval)
	: mInterval(_interval)
{ }

Ticker::~Ticker() { }

void Ticker::work()
{
    WireEventBuilder wb;
    wb.create(WireEventTypesInt::EVT_TYPE_TICK);
    string msg = wb.finalize();
    
    int poll = 0;
    while(this->canExecute())
    {
        if(++poll > 100)
        {
            poll = 0;
            publishData(msg);
        }
        sleepMs(100);
    }
}

void Ticker::processPublishedMessage(string message) { }


bool Ticker::canExecute() 
{
    bool res;
///    mMutex.lock();
    res = mCanExecute;
///    mMutex.unlock();
    return res;
}

void Ticker::publishData(string message) 
{
    INFO() << "Publish: " << message << endl;
    //mPubSocket->send((void*) message.c_str(), message.length(), ZMQ_DONTWAIT);
}


}