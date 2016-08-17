
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

#include <sstream>
#include <memory>
#include <ctime>

#define INFO() solcep::Trace().Info()
#define WARN() solcep::Trace().Warn()
#define ERROR() solcep::Trace().Err()

namespace solcep {

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class ITracer
{
public:
    virtual void Trace(std::string message) = 0;
    virtual ~ITracer() {}
};
    
class Trace {
public:
    
    static int LogLevel;
    
    Trace() {};
    virtual ~Trace()
    {
        if(Trace::mTracer && Trace::LogLevel >= mLogLevel)
            Trace::mTracer->Trace(mStream.str());
    }

    static std::unique_ptr<ITracer> GetTracer()
    {
        return std::move(Trace::mTracer);
    }
    
    static void SetTracer(std::unique_ptr<ITracer> tracer)
    {
        Trace::mTracer = std::move(tracer);
    }
    
    virtual std::ostringstream& Info() 
    {
        mLogLevel = 2;
        mStream << GetCurrentTime() << " <INFO> :";
        return mStream;        
    }
    virtual std::ostringstream& Warn() 
    {
        mLogLevel = 1;
        mStream << GetCurrentTime() << " <WARNING> :";
        return mStream; 
    }
    virtual std::ostringstream& Err() 
    {
        mStream << GetCurrentTime() << " <ERROR> :";
        return mStream; 
    };
    
    void Terminate()
    {
        mStream << "$stop$";
    }

private:
///    int mLogLevel = 0;
        int mLogLevel = 4;
    std::ostringstream mStream;
    static std::unique_ptr<ITracer> mTracer;
    
    std::string GetCurrentTime()
    {
        char buffer[128];
        std::time_t now = std::time(nullptr);
        strftime(buffer, sizeof(buffer), "%a %b %e %X %y", std::localtime(&now));
        return std::string(buffer);
    }
};

} /* namespace solcep */