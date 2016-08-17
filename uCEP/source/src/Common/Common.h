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

struct TPosLiteral;

/* 
    Common functions	
 */
class Common
{
public:

    virtual ~Common() {}

    /*!
        \brief Builds a path from a dir and a name, adding
                a path separator
        \param _dir The directory part. Must NOT end with path separator
        \param _name The file name
        \param _sep The path separator
        \returns A pointer to the full path. The caller is responsible for free()-ing the
                memory occupied by the path.
     */
///    static char* BuildPath(const char* _dir, const char* _name, const char _sep = '/');

///    static char* CopyStr(const char* _str);
///    static void ReleaseStr(const char* _str);
};


