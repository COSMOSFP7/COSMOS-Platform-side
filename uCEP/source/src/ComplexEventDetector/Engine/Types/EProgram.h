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
	Types for the Execution Framework
	
*/
#ifndef _SOL_CEP_ENGINE_TYPES_EPROGRAM_H_
#define _SOL_CEP_ENGINE_TYPES_EPROGRAM_H_

/*!
	\brief P-Code for stack machine.
	
	See ProgramBuilder and InstructionEvaluator.
	
	// *******
	//WARNING: Used in memory operations! Keep this as a POC struct.
	// *******
	
		version - program format version
		size - total image length. Equals the size
			of code segment + data segment
		codeStart - start address of program code
		data - start of data segment + program data.
			Program starts at 'dataSegmentLength'
			
        +----------------+
	    | version        |
	    +----------------+ 
	    | imageSize      |
	    +----------------+ 
	 .--| codeStart      |
	 |  +----------------+ -------.
	 |  | <data segment> |        |
	 |  +----------------+         >--- image (imageSize)
	 '->| <code segment> |        |
	    +----------------+ -------'
*/
struct EProgram
{

	unsigned long version;
	unsigned long imageSize;
	unsigned long codeStart;
	unsigned char* image;	// Contains data segment + code segment
};



#endif
