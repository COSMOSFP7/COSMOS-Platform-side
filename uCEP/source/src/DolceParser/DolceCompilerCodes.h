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


/************************

	NOTE: The codes descbibed should adhere to document SOL-CEP-0004,
		"SOL/CEP DOLCE COMPILER CODES".

*************************/

/* 
	Errors and warning messages related to Dolce.
	These errors are generated during compiling, parsing, and runtime
	engine construction.

*/
#ifndef _SOL_CEP_DOLCE_MSG_H_
#define _SOL_CEP_DOLCE_MSG_H_


//---- Compiler

// Generic compiler error. In the future, must extract more
// precise info from yacc.
static const int DMSG_SYNTAX_ERROR = 100;



// ----Analyzer

// "Variable not declared"
static const int DMSG_AL_UNDECLARED_VAR = 1000;

// "'detect' statement missing. Identifier x must be associated to
//  an event in the 'detect' statement.
static const int DMSG_AL_MISSING_DETECT_STMT = 1001;

// "Undeclared event"
static const int DMSG_AL_EVENT_NOT_DECLARED = 1002;

// "Tuple scope specifier must refer to an event or complex event"
static const int DMSG_AL_TUPLE_SCOPE_SPEC_NOT_E_OR_CE = 1003;

// "Variable is not defined for event x, and is not an external variable"
static const int DMSG_AL_VAR_NOT_FOR_EVT_NOR_EXT = 1004;

// "Variable is ambiguous for event or complex event"
static const int DMSG_AL_AMBIGUOUS_VAR_FOR_E_OR_CE = 1005;

// "Undeclared external variable"
static const int DMSG_AL_EXT_VAR_NOT_DECLARED = 1006;

// "Undeclared attribute for event"
static const int DMSG_AL_ATTR_NOT_DECLARED_FOR_EVT = 1007;


// Runtime engine construction

// "Time window identifier must be declared as an external variable"
static const int DMSG_RT_TIME_WIN_ID_NOT_EXT = 2000;

// "Time window is of invalid type. Must be 'integer' or 'duration'"
static const int DMSG_RT_TIME_WIN_INVALID_TYPE = 2001;

// "Identifier is of an unexpected type"
static const int DMSG_RT_ID_UNEXPECTED_TYPE = 2002;

#endif
