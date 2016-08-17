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



#ifndef _SOL_CEP_TYPES_POS_LITERAL_H_
#define _SOL_CEP_TYPES_POS_LITERAL_H_




struct TPosLiteral
{
	float lat;   // a.k.a y-axis, +90.0 (north) / -90.0 (south)
	float lon;	 // a.k.a. x-axis, -180.0 (west) / +180.0 (east)
	
	bool operator==(const TPosLiteral& rhs) 
	{
		return (lat == rhs.lat) 
			&&	(lon == rhs.lon);
	}
	
	
	bool operator!=(const TPosLiteral& rhs) 
	{
		return !(*this == rhs);
	}

};

#endif

