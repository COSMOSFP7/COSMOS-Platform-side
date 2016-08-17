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
#include <sstream>
#include "../../Types/TValue.h"

namespace solcep {

/*!
        \brief Builds a flat, binary representation of SEvent, so it can
        be sent over the wire, between threads and/or processes.
	
        Supports version 1.
	
        \note IDs (non-string identifiers) are NOT supported
	
 */
class WireEventBuilder
{
public:
    
    WireEventBuilder();
    virtual ~WireEventBuilder();

    /*!
            \brief Creates a new event, discarding any
            other event being built
     */
    void create(const int _type, std::string _name = "");

    //! Adds number of NV-pairs
    void addNVPairCount(unsigned short count)
    {
        //Hack need to re-write!
        std::string temp = mStream.str();
        temp.replace(mPairPos, sizeof(count), (char*)&count, sizeof(count));
        reset();
        mStream << temp;
    }
    
    ///RP: 17122014
    void updatePairsCount();

    /*!
        Finalizes the event building.
        The reference to the internal event is kept in memory
        by the builder and is overwritten on create()

        \returns A reference to the built event.
     */
    std::string finalize();
    static const unsigned int ID_MASK = 0x80000000UL;
    void add(std::string name);
    void add(std::string name, const int value);
    void add(std::string name, const float value);
    void add(std::string name, const char* value);
    void add(std::string name, const char value);       ///RP
    void addTPL(std::string name, const char* value);
    void addArea(std::string name, const char* value);
    void addTime(std::string name, const char* value);

    void add(std::string name, const TPosLiteral value);
    void add(std::string name, const TAreaLiteral value);
    void add(std::string name, const TTimeLiteral value);
    void serializeVar(TValue& value);
    void reset();
    
protected:

    void add(unsigned char byte);
///    void reset();
    void checkSize(const int _addedDataSize);

private:
    int mPairPos = 0;
    std::ostringstream mStream;
};

}


