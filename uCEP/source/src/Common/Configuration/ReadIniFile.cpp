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


#include <string.h>

#include "ReadIniFile.h"
#include "../Tracer.h"

ReadIniFile::ReadIniFile(std::string logFile) {
    
    if (logFile.length()>4){
        logFileName=logFile;
    }
    
    IniFileSection readIniFileUDPSection();
    IniFileSection readIniFileMQTTSection();    
    IniFileSection readFile();

}
/*
ReadIniFile::ReadIniFile(const ReadIniFile& orig) {
}
*/ 
ReadIniFile::~ReadIniFile() {
    
}

std::string ReadIniFile::trim(const std::string & s)
{
    size_t l = s.length();
    if (l == 0)
        return s;
    size_t b = s.find_first_not_of(" \t\r\n\0");
    if (b == std::string::npos)
        b = 0;
    size_t e = s.find_last_not_of(" \t\r\n\0");
    if (e == std::string::npos)
        return s.substr(b);
    return s.substr(b, e-b+1);
}


std::string ReadIniFile::makelower(const std::string & s)
{
    std::string str = s;
    for( std::string::iterator i = str.begin(); i != str.end(); ++i)
        if (tolower(*i) != (int)*i)
            *i = (char)tolower(*i);
    return str;
}

std::string ReadIniFile::value_for_key(const std::string & s, const std::string & k)
{
    size_t p = s.find('=');
    if (p == std::string::npos || trim(makelower(s.substr(0,p))) != k)
        return "";
    p = s.find_first_not_of(" \t\n\r\0", p+1);
    // check for empty value and return space char
    if (p == std::string::npos)
        return " ";

    return s.substr(p);
}


bool ReadIniFile::getini(const std::string & inifile, const std::string & section, const std::string & key, std::string & value)
{
    std::string s, k;
    std::string sec = std::string("[") + makelower(section) + "]";
    std::ifstream file(inifile.c_str());
    if (!file) {
       INFO()<<"Configuration file could not be opened; the default sockets will be used!"<<std::endl;
       return 0;
    }
    k = trim(makelower(key));
    bool found_section  = 0;
    while (std::getline(file, s))
    {
       if (! found_section)
       {
          if (trim(makelower(s)) == sec)
              found_section = 1;
          continue;
       }
       // check for next section
       s = trim(s);
       int l;
       if ((l = s.length()) > 1 && s[0] == '[' && s[l-1] == ']')
           // break loop if next section begins
           break;
       value = value_for_key(trim(s), k);
       if (value.length())
       {
           // close file before return
           file.close();
           return 1;
       }
    }
    
    file.close();
    
    if (found_section) {
        INFO()<<"Key not found: "<<key;
        return 0;
    }
    else {
        INFO()<<"Section not found: "<<section;
        return 0;
    }
    return 1;
                
}



IniFileSection ReadIniFile::readIniFileUDPSection() {
    
    IniFileSection structIniFile;
    std::string updSection= "UPDPorts", aKey= "portUDPCollect", aValue;
    std::string dolceSection= "DOLCE";
    
    if (getini(logFileName, updSection, aKey, aValue)) {
        std::stringstream(aValue) >> structIniFile.portUDPCollect;
        aKey = "portUDPPublish";
        if (getini(logFileName, updSection, aKey, aValue))
            std::stringstream(aValue) >> structIniFile.portUDPPublish;
        
        aKey = "dolceSpec";
        if (getini(logFileName, dolceSection, aKey, aValue))
            std::stringstream(aValue) >> structIniFile.dolceSpec;
    }
    
    return structIniFile;
}

IniFileSection ReadIniFile::readIniFileMQTTSection() {
    
    IniFileSection structIniFile;
    std::string section= "MQTT", aKey= "portMQTT", aValue;
    std::string dolceSection= "DOLCE";
    
    if (getini(logFileName, section, aKey, aValue)) {
        std::stringstream(aValue) >> structIniFile.portMQTT;
        
        aKey = "hostMQTT";
        if (getini(logFileName, section, aKey, aValue))
            std::stringstream(aValue) >> structIniFile.hostMQTT;
        
        aKey = "topicMQTTCollect";
        if (getini(logFileName, section, aKey, aValue))
            std::stringstream(aValue) >> structIniFile.topicMQTTCollect; 
        
        aKey = "topicMQTTPublish";
        if (getini(logFileName, section, aKey, aValue))
            std::stringstream(aValue) >> structIniFile.topicMQTTPublish;
        
        aKey = "cepName";
        if (getini(logFileName, section, aKey, aValue))
            std::stringstream(aValue) >> structIniFile.cepName;
        
        aKey = "dolceSpec";
        if (getini(logFileName, dolceSection, aKey, aValue))
            std::stringstream(aValue) >> structIniFile.dolceSpec;        
        
        aKey = "userMQTT";
        if (getini(logFileName, section, aKey, aValue))
            structIniFile.userMQTT = aValue.c_str();
        
        aKey = "passwordMQTT";
        if (getini(logFileName, section, aKey, aValue))
            structIniFile.passwordMQTT = aValue.c_str();

    }
    return structIniFile;
}

IniFileSection ReadIniFile::readFile(){
    IniFileSection structIniFile;
#ifndef MQTT
    structIniFile = readIniFileUDPSection();
#endif

#ifdef MQTT
    structIniFile = readIniFileMQTTSection();
#endif
    
    return structIniFile;
}