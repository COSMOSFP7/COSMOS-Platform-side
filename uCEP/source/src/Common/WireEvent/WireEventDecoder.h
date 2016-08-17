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

struct SEvent;

namespace solcep{
/*!
    \brief Decodes a flat, binary version of SEvent into an SEvent.
 */
class WireEventDecoder
{
public:
    
    WireEventDecoder();
    virtual ~WireEventDecoder();
    /*!
            \brief Creates a new event, discarding any
            other event being built
            \param _data The wire event data, i.e. the internal SOL/CEP event
            \param _dataLen The size of the wire event data
            \returns A reference to the decoded event. 
                    The memory is owned by WireEventDecoder.
     */
    SEvent* create(const unsigned char* _data, const int _dataLen);
///        SEvent* create(char* _data, const int _dataLen);
    
///RP to manage memory leak    
    void externalDestroy(int discard);
        
protected:

    void reset();
    bool getVersion();
    bool getType();
    bool getByteOrder();
    bool getEventId();

    bool getNVPairCount(int& nvPairCount_);

    /*!
        \brief Gets and identifier, which is either an ID or a string
        \param id_ The id
        \param s_ Name. 0 if it's an ID, a pointer to a new allocated string 
                otherwise. The caller must be clean up this string
     */
    bool getIdentifier(unsigned long& id_, char*& s_);

private:

    const unsigned char* mData;
///    unsigned char* mData;
    unsigned int mDataLen;
    unsigned long mOffset;
    SEvent* mEvent;
};

}