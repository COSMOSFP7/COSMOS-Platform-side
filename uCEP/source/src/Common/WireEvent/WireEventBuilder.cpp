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


#include "WireEventBuilder.h"
#include "../../Types/TPosLiteral.h"

namespace solcep
{
using namespace std;

WireEventBuilder::WireEventBuilder() { }

WireEventBuilder::~WireEventBuilder() {
    
    reset();
    
}

void WireEventBuilder::create(const int _type, string _name)
{
    reset();

    add(0x01);	// version 1
    add(_type);
    add(0x00);	// little endian (TODO: relialbly detect this info!!)

    if(_name.length() > 0)
        add(_name);
        
    string tmp = mStream.str();
    mPairPos = mStream.str().length();
    unsigned short pairs = 0;
    mStream.write(reinterpret_cast<const char*>(&pairs), sizeof(pairs));
///is used by the decode too
}
	
string WireEventBuilder::finalize()
{
    return mStream.str();
}

void WireEventBuilder::reset()
{
    mStream.str("");
    mStream.clear();
}

void WireEventBuilder::add(string name)
{
    auto length = static_cast<unsigned int>(name.length() | ID_MASK);
    mStream.write(reinterpret_cast<const char*>(&length), sizeof(length));
    mStream << name;
}
	
void WireEventBuilder::add(unsigned char byte)
{
    mStream << byte;
}

void WireEventBuilder::add(string name, const int value)
{
    add(name);	
    TValue v((int)value);
    serializeVar(v);
    
///    updatePairsCount();
    
///RP is neccesary for the count used in the Pairs
/*  moved to a new method
    std::string temp = mStream.str();
    short count=0;
    
    char* cPair = new char(2);
    temp.copy(cPair, sizeof(count), mPairPos);
    count= static_cast<short>(*cPair);
    
    count++;
    delete cPair;
    
    temp.replace(mPairPos, sizeof(count), (char*)&count, sizeof(count));
    reset();
    mStream << temp;
*/
    
}

void WireEventBuilder::add(string name, const float value)
{
    add(name);
    TValue v((float)value);
    serializeVar(v);
///	updatePairsCount();    
}

void WireEventBuilder::add(string name, const char* value)
{
    add(name);
    TValue v(value);
    serializeVar(v);
}

///RP
void WireEventBuilder::add(string name, const char value)
{
    add(name);
    TValue v(value);
    serializeVar(v);
}

///RP
void WireEventBuilder::add(string name, const TPosLiteral value)
{
    add(name);
    TValue v(value);
    serializeVar(v);
}

///RP
void WireEventBuilder::add(string name, const TAreaLiteral value)
{
    add(name);
    TValue v(value);
    serializeVar(v);
}
//Works with time data type (not is a timestamp) used to encode
void WireEventBuilder::add(string name, const TTimeLiteral value)
{
    add(name);
    TValue v(value);
    serializeVar(v);

}


///RP
void WireEventBuilder::addTPL(string name, const char* value)
{
    add(name);
    char *sep;
    sep= strtok((char*)value, "\\\\");    
    TPosLiteral tpl;
    tpl.lat = (float)atof(sep);
    sep= strtok(NULL, "\\\\");
    tpl.lon = (float)atof(sep);
            
    TValue v(tpl);
    serializeVar(v);    
}

void WireEventBuilder::addArea(string name, const char* value)
{
    add(name);
    char *sep;
    sep= strtok((char*)value, "\\\\");    
    
    TAreaLiteral area;
    area.lat = (float)atof(sep);
    
    sep= strtok(NULL, "\\\\");
    area.lon = (float)atof(sep);

    sep= strtok(NULL, "\\\\");    
    area.radius = (float)atof(sep);
    area.type = 0;
    
    sep= strtok(NULL, "\\\\");
    if (sep != NULL) {
        area.lat2 = area.radius;
        area.lon2 = (float)atof(sep);
        area.type = 1;
    }
    
    TValue v(area);
    serializeVar(v);
}

//Works with time data type (not is a timestamp) used to decode
void WireEventBuilder::addTime(string name, const char* value)
{
    add(name);
    TTimeLiteral v_time;
    struct tm tm;
    if (strchr(value,'@') && strlen(value)>8)
        strptime(value, "%Y-%m-%d@%H:%M:%S", &tm);  //%Y-%m-%d %H:%M:%S
    else
        strptime(value, "%H:%M:%S", &tm);
    
    v_time.hh = tm.tm_hour;
    v_time.mm = tm.tm_min;
    v_time.ss = tm.tm_sec;
    
//    time_t var_time = mktime(&tm);  // t is now
    TValue v(v_time);
    serializeVar(v);
    
}


void WireEventBuilder::serializeVar(TValue& value)
{
    size_t count;	
    value.serialize(0, &count);
    auto buff = (unsigned char*)malloc(count);
    value.serialize(buff);
    mStream << string(reinterpret_cast<const char*>(buff), count);
    free(buff);
}

///RP: To update the count of Pairs in the Wire Event; could use the addNVPairCount(unsigned short count) method!!
void WireEventBuilder::updatePairsCount() {
    
    std::string temp = mStream.str();
    short count=0;
    
    char* cPair = new char(2);
    temp.copy(cPair, sizeof(count), mPairPos);
    count= static_cast<short>(*cPair);
    
    count++;
    delete cPair;
    
    temp.replace(mPairPos, sizeof(count), (char*)&count, sizeof(count));
    reset();
    mStream << temp;

    
}

}

