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



//FIXME-REFACTOR: move to 'lang/Types' ?

/*
	TValue - This is the main type used throughout the CEP 
*/
#ifndef _SOL_CEP_TYPES_TTYPE_H_
#define _SOL_CEP_TYPES_TTYPE_H_



enum TType
{
	//IMPORTANT - THESE VALUES MUST CORRESPOND TO THE OFFICIAL WIRE EVENT PROTOCOL SPEC.
	t_char = 		0,
	t_string =		1,
	t_int =			2,
	t_float =		3,
	t_pos =			4,
	t_area =		5,
	t_duration =	6,
	t_time =		7,
	t_ersatz = 		99,	//! 'wild card' used in InstructionEvaluator
	t_invalid =		100
};


#endif

