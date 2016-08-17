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

#include "../../ComplexEventDetector/Engine/Types/EProgram.h"
#include "../../Types/TValue.h"
#include "../../Types/TAddress.h"
#include "../ScriptCompiler/ASTree.h"

/* 
    builds programs for the Expression Evaluator	
*/
class ProgramBuilder 
{

public:

	ProgramBuilder();
	~ProgramBuilder();

	/*
		Recursively builds a program starting from an expression node
	*/
	int build(ASTree* const _node, const bool _new = true);
	
	
	/*
		Finalizes the program and returns a pointer to the instructions.
		The caller is responsible for releasing the returned memory
	*/
	EProgram* finalize();
        
#ifdef CEP_DEBUG
	void print(const EProgram* _code, const int _indent = 0, const bool _raw = false);
	const char* indent(const int _indent);
	static const char* opcodeAsString(const unsigned char _opcode);
	char mIndent[64];
#endif


protected:

	int emitInstruction(const unsigned char _opcode,
						const unsigned char _operandLength = 0,
						const unsigned char* _operand = 0);
						
	int emitInstruction(const unsigned char _opcode,
						const TAddress& _addr);
						
	int emitInstruction(const unsigned char _opcode,
						const TValue* _val);
						
						
	void createProgram();

	TAddress getComplexEventFuncAddrFromNode(ASTree* const _node) const;
	
private:

	unsigned long mAllocProgramSize; // block-allocated size
	int mPC;
	
	EProgram* mProgram;
	
	static const unsigned long BLOCK_SIZE = 64UL;
	
	
	// returns oid
	long addConstant(const TValue* _val);

	long mNextOid;      
};
