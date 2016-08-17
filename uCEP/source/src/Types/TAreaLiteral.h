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



#ifndef _SOL_CEP_TYPES_AREA_LITERAL_H_
#define _SOL_CEP_TYPES_AREA_LITERAL_H_

///#include <stdio.h>
///#include <string.h>
///#include <stdlib.h>
///#include <time.h>
#include <math.h>
///#include <assert.h>

#include "../Common/GeoHelper.h"


struct TAreaLiteral
{
	char type; // 0-circular, 1-area
	
	float lat;
	float lon;
	float lat2;
	
	union 
	{
		float lon2;	//type 1
		float radius;	// type 0 (circular)
	};
	
	enum 
	{
		KAreaCircular = 0,
		KAreaRectangular = 1
	};
	
	bool operator==(const TAreaLiteral& rhs) 
	{
		if((type != rhs.type)
		|| (lat != rhs.lat)
		|| (lon != rhs.lon)
		|| (lon2 != rhs.lon2))
			return false;
			
		return (type == KAreaRectangular) ? 
			(lat2 == rhs.lat2) : true;
	}

	TAreaLiteral operator+=(const float& rhs) 
	{
		if(type == KAreaCircular)
			radius += rhs;
		else
		{
			// Really, the spec should have been made 'easier' by
			// specifying that the top-left and bottom-right corners
			// will be moved N/2 meters north-west and south-east, respectively
			// just like TPosLiteral +/- float.
			//
			// Instead, we follow the spec, by moving the top-left north by N/2
			// meters, them west by N/2 meters. The same procedure for 
			// bottom-left (first south, then east, by N/2 meters)
			//
			// (Same comment applies top operator-)
			//
			float dist = rhs / 2.0;
			
			GeoHelper::AddDistance(lat, lon, dist, 0.0);		//North
			GeoHelper::AddDistance(lat, lon, dist, 270.0); 	//West
			GeoHelper::AddDistance(lat2, lon2, dist, 180.0);	//South
			GeoHelper::AddDistance(lat2, lon2, dist, 90.0);	//East
		}
			
		sanityCheck();
		
		return *this;
		
	}
	
	TAreaLiteral operator-=(const float& rhs) 
	{
		if(type == KAreaCircular)
			radius -= rhs;
		else
		{
			float dist = rhs / 2.0;
			
			GeoHelper::AddDistance(lat, lon, dist, 180.0);	//South
			GeoHelper::AddDistance(lat, lon, dist, 90.0);	//East
			GeoHelper::AddDistance(lat2, lon2, dist, 0.0);		//North
			GeoHelper::AddDistance(lat2, lon2, dist, 270.0); 	//West
			
		}
			
		sanityCheck();
		
		return *this;
	}
	
	
	void sanityCheck()
	{
		if(type == KAreaCircular)
		{
			if(radius < 0.0)
				radius = 0.0;
		}
		else
		{
			if(lat < -90.0) lat = -90.0;
			if(lat > +90.0) lat = +90.0;
			if(lon < -180.0) lon = -180.0;
			if(lon > +180.0) lon = +180.0;
			//FIXME: geo sanity check. 
		}
	}
	
};


#endif

