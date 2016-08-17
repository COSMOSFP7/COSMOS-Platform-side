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


///#include <stdio.h>
///#include <stdlib.h>
///#include <string.h>
///#include <math.h>
///#include <assert.h>

#include "Common.h"

/*
char* Common::BuildPath(const char* _dir, const char* _name, const char _sep)
{
	assert(_dir);
	assert(_name);
	
///	char* path = (char*)malloc(strlen(_dir) + strlen(_name) + 2);
	
///	sprintf(path, "%s%c%s", _dir, _sep, _name);
	
	return path;
}
*/

/*
char* Common::CopyStr(const char* _str)
{
    if(_str)
    {
///        char* newStr = (char*)malloc(strlen(_str) + 1);

        strcpy(newStr, _str);

        return newStr;
    }

    return 0;
}
*/


///void Common::ReleaseStr(const char* _str)
///{
///    if(_str)
///        free((void*)_str);
///}

static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
static const double EARTH_RADIUS_KM = 6371.0;