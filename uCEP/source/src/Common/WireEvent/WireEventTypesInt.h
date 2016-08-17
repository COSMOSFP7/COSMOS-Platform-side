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
		\brief Atos Reserved (internal) Wire Format Event Types
		
		Not for publication to anyone.
		
*/

#ifndef _ATOS_SOLCEP_COMMON_WIRE_EVENT_TYPES_INTERNAL_H_
#define _ATOS_SOLCEP_COMMON_WIRE_EVENT_TYPES_INTERNAL_H_

struct WireEventTypesInt
{
	
	//@{
	//! \brief Reserved Event Types. The "public" event types are in public/PluginDev
	static const unsigned char EVT_TYPE_CS = 0x81;	// Atos Reserved
	static const unsigned char EVT_TYPE_TICK = 0x80; // Atos Reserved
	static const unsigned char EVT_TYPE_SHUTDOWN = 0x99; //Atos Reserved
//RP: 04022015 USED TO CHANGE THE VALUE OF A EXTERNAL VARIABLE
        static const unsigned char EVT_TYPE_CHANGE_EXTERNALVAR = 0x82; //Atos Reserved
	//@}
	
};

#endif 