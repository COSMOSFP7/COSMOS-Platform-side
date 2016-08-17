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


/*!
		\brief Public Wire Format Event Types
		
*/

#ifndef _ATOS_SOLCEP_PUB_WIRE_EVENT_TYPES_H_
#define _ATOS_SOLCEP_PUB_WIRE_EVENT_TYPES_H_

struct WireEventTypes
{

	//@{
	//! \brief Public Event Types
	static const unsigned char EVT_TYPE_NORMAL = 0x00;
	static const unsigned char EVT_TYPE_EXT = 0x01;
	static const unsigned char EVT_TYPE_COMPLEX = 0x02;
        static const unsigned char EVT_TYPE_INJECTED_EVENT = 0x03;
	//@}
	
	//! Maximum id of public event.
	static const unsigned char EVT_TYPE_MAX = 0x7F;
};

#endif 