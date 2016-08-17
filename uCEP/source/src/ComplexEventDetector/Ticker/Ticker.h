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

///#include <string>
///#include <thread>
///#include <mutex>



namespace solcep
{

/*!
	\brief Sends periodic ticks to the Engine
	
*/
class Ticker
{
public:
	Ticker(const int _interval = 1);
	virtual ~Ticker();
        bool canExecute();
        void publishData(std::string message);       
        void sleepMs(int mSec) 
        {
///            std::this_thread::sleep_for(std::chrono::milliseconds(mSec));
        }
        
        

protected:
	
	int mInterval; //seconds
	virtual void processPublishedMessage(std::string message);
	void work();
        
        
private:
    bool mCanExecute;
///    std::mutex mMutex;
///    std::unique_ptr<std::thread> mThread;

        
};

}


