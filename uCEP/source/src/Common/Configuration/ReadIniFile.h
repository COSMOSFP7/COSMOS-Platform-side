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


#ifndef READINIFILE_H
#define	READINIFILE_H

///#include <string>
#include "IniFileSection.h"
#include <fstream>


///using namespace std;

class ReadIniFile {

public:
    
    ReadIniFile(std::string logFile);
    
    ReadIniFile(const ReadIniFile& orig);
    
    virtual ~ReadIniFile();
    
    
    std::string logFileName="./confFile.ini";
    
    IniFileSection readIniFileUDPSection();
    IniFileSection readIniFileMQTTSection();    
    IniFileSection readFile();

private:
    
    std::string trim(const std::string & s);
    std::string makelower(const std::string & s);
    std::string value_for_key(const std::string & s, const std::string & k);
    bool getini(const std::string & inifile, const std::string & section, const std::string & key, std::string & value);

};

#endif	/* READINIFILE_H */

