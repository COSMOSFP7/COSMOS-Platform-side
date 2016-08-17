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

	

#ifndef _SOL_CEP_INSTRUCTION_EVALUATOR_H_
#define _SOL_CEP_INSTRUCTION_EVALUATOR_H_


struct EProgram;
struct ECapturedEventPool;

class Stack;
class Engine;

#include "../../Types/TValue.h"
#include "Stack.h"

/*!
	\brief Executes code generated with ProgramBuilder.
	
	Implemented as a simple stack machine that grinds through the code
	and updates the stack accordingly
*/
class InstructionEvaluator
{
public:
	InstructionEvaluator(Engine* const _engine);
					
	~InstructionEvaluator();
	
	
	/*!
		\brief Executes an instruction
		\param _operandLen Length of operand
		\param _operand the operand data
		\returns ERR_IE_ABORT if the engine for some reason cannot continue, OK otherwise
	*/
	typedef int (InstructionEvaluator::*TInstructionFunc)(int _operandLen, unsigned char* _operand);
	
	//! Maps opcodes to implementations
	struct TInstructionMap
	{
		unsigned char opcode;
		TInstructionFunc func;
	};
	
	//!@{
	//! Must be sized according to the set of opcodes (see below)
	static const int KMaxInstruction = 30;
	TInstructionMap mInstructions[KMaxInstruction]; 
	//!@}
	
	
	/*!
		\brief Runs a program
		\param _program The program to run
		\param _pool The captured events against which to operate
		\return OK on success
	*/
	int run(EProgram* _program, ECapturedEventPool* _pool);
        
        ///RP:20150211
        int runWithoutComplexFunctions(	EProgram* _program,ECapturedEventPool* _pool);
	
	TValue* const getTopOfStack() const;
        
///RP:        
        bool popStack(TValue* val_) const;
	
	//! Change this when instruction set changes.
	static const unsigned long SOLCEP_PROGRAM_VERSION = 0x00010000;

	//!@{ 
	//! Instruction set constants
	static const unsigned char HAS_OPERAND_LENGTH = 0x80;
	static const int OPCODE_SIZE = sizeof(unsigned char);
	static const int OPERAND_LENGTH_SIZE = sizeof(unsigned char); //! instruction data size - size
	//!@}

	//!@{
	//! opcodes
	static const unsigned char PUSH = 0x80;
	static const unsigned char PUSHX = 0x81;
	static const unsigned char PUSHA = 0x82;
	static const unsigned char POP = 0x03;
	static const unsigned char ADD = 0x10;
	static const unsigned char SUB = 0x11;
	static const unsigned char MUL = 0x12;
	static const unsigned char DIV = 0x13;
	static const unsigned char EVAL = 0x14;
	static const unsigned char CEQ = 0x20;
	static const unsigned char CNE = 0x21;
	static const unsigned char CGE = 0x22;
	static const unsigned char CGT = 0x23;
	static const unsigned char CLE = 0x24;
	static const unsigned char CLT = 0x25;
	static const unsigned char ANDL = 0x30;
	static const unsigned char ORL = 0x31;
	static const unsigned char IAREA = 0x40;
	static const unsigned char DIFF = 0xC1;
	static const unsigned char DIFFX = 0x42;
	static const unsigned char CNT = 0xC3;
	static const unsigned char SUM = 0xC4;
	static const unsigned char AVG = 0xC5;
	static const unsigned char RESET = 0x70;
	static const unsigned char TRAP = 0x76;
	static const unsigned char NOP = 0x77;	
	//!@}
	
protected:

	void reset();

	void initInstructions();
	void initInstruction(	const int _index, 
							const unsigned char _opcode,
							TInstructionFunc func);
							
							
	int doInstruction(	const unsigned char _opcode,
						const int _operandLen,
						const unsigned char* _operand);
	
	//!@{
	//! Instruction implementations
	int f_push	(int _operandLen, unsigned char* _operand);
	int f_pushx	(int _operandLen, unsigned char* _operand);
	int f_pusha	(int _operandLen, unsigned char* _operand);
	int f_pop	(int _operandLen, unsigned char* _operand);
	int f_add	(int _operandLen, unsigned char* _operand);
	int f_sub	(int _operandLen, unsigned char* _operand);
	int f_mul	(int _operandLen, unsigned char* _operand);
	int f_div	(int _operandLen, unsigned char* _operand);
	int f_eval	(int _operandLen, unsigned char* _operand);
	int f_ceq	(int _operandLen, unsigned char* _operand);
	int f_cne	(int _operandLen, unsigned char* _operand);
	int f_cge	(int _operandLen, unsigned char* _operand);
	int f_cgt	(int _operandLen, unsigned char* _operand);
	int f_cle	(int _operandLen, unsigned char* _operand);
	int f_clt	(int _operandLen, unsigned char* _operand);
	int f_andl	(int _operandLen, unsigned char* _operand);
	int f_orl	(int _operandLen, unsigned char* _operand);
	int f_iarea	(int _operandLen, unsigned char* _operand);
	int f_diff	(int _operandLen, unsigned char* _operand);
	int f_diffx	(int _operandLen, unsigned char* _operand);
	int f_cnt	(int _operandLen, unsigned char* _operand);
	int f_sum	(int _operandLen, unsigned char* _operand);
	int f_avg	(int _operandLen, unsigned char* _operand);
	int f_reset	(int _operandLen, unsigned char* _operand);
	int f_trap	(int _operandLen, unsigned char* _operand);
	int f_nop	(int _operandLen, unsigned char* _operand);
	//!@}
	
	
	unsigned long mPC;	//! Program counter
	
	Stack* mStack; //! Stack
	Engine* const mEngine; 
	ECapturedEventPool* mPool;
	
	TValue mLatestStackValue;

	bool isInArea(const TAreaLiteral& _area, const TPosLiteral& _pos);

#ifdef CEP_DEBUG
	TAreaLiteral makeArea(
						const float _lat, 
						const float _lon, 
						const float _lat2, 
						const float _lon2);

	TAreaLiteral makeArea(
						const float _lat, 
						const float _lon,
						const float _radius);
						
	TPosLiteral makePos(const float _lat, 
						const float _lon);						
#endif


private:

	void unittest();
        
        //RP: 20150211
        bool isComplexFunction (unsigned char _opcode);        
        TValue getAttributeToGroup(long _oid);
        
};





#endif


