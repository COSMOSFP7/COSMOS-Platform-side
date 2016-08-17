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

/* 
	Engine
	
*/
#ifndef _SOL_CEP_ENGINE_BUILDER_H_
#define _SOL_CEP_ENGINE_BUILDER_H_


///#include <stdio.h>


#include "../../ComplexEventDetector/Engine/Types/EComplexEvent.h"
#include "../../ComplexEventDetector/Engine/Types/EComplexEventFunction.h"
#include "../ScriptCompiler/ASTree.h"


struct Engine;
struct EEvent;
struct EFramework;
struct EComplexEvent;
struct EEventAttribute;
struct EDetectionTree;
struct EEventPeriod;
struct EPayloadAttribute;
struct EExternal;




class Compiler;
class SymbolTable;
class ProgramBuilder;
class ErrorList;


class FrameworkBuilder
{
public:
	FrameworkBuilder(	Compiler* const _c, 
					ErrorList* const _el);
					
	~FrameworkBuilder();
	
	/*!
		\brief Builds a new Execution Framework
		\param res_ The result, which is OK on success or another
			code if there's an error.
		\returns An instance of the execution framework or 0 in case
			of an error. Caller must delete the instance when done.
	*/
	EFramework* build(int& res_);

	EEvent* newEvent(const char* _name);
	EComplexEvent* newComplexEvent(const char* _name);
	
	int newAttributeForEvent(const char* _eventName,
							 EEventAttribute* const _attr);
	
							
	int build(ASTree* const _node, const int _pass);
	

	ProgramBuilder* const getProgramBuilder() const { return mProgramBuilder; }
	SymbolTable* const getSymbolTable() const { return mSymTab; }
	ErrorList* const getErrorList() const { return mErrorList; }
	EExternal* getExternalIdReference(ASTree* const _node, const TType _expectedType);
	
	long getOidFromIdNode(ASTree* const _idNode);
	
	long getNextOid() { return ++mOid; }
	
//FIXME: move to Engine 
long findEvent(const char* _name);
void resolveWindowValues(EComplexEvent* const _complex);

/*FIXmE: REMOVE
time_t durationLiteralAsTime(const TDurationLiteral& _dl) const;
time_t durationUnitAsSeconds(const TDurationUnit& _durationUnit) const;
*/


protected:
	
	FrameworkBuilder();
	
	FrameworkBuilder(const FrameworkBuilder& rhs) : mCompiler(0), mSymTab(0), mErrorList(0)	{}
	
	FrameworkBuilder& operator= (const FrameworkBuilder& rhs)	{ return *this; }

// Structs that end with "s" are a collection
//
	void init();
	void deinit();

	
	int buildExternals(EFramework*& _framework_);
	int buildEvents(EFramework*& _framework_);
	int buildComplexEvents(EFramework*& _framework_);

	EExternal* createExternal(ASTree* const _node);
	
private:

	Compiler* const mCompiler;
	SymbolTable* mSymTab;
	ErrorList* const mErrorList;
	
	ProgramBuilder* mProgramBuilder;
	
	long mOid;

	

#ifdef CEP_DEBUG

		
	void print(EFramework*& _framework_);
	void printExternals(EFramework*& _framework_);
	void printEvents(EFramework*& _framework_);
	void printComplexEvents(EFramework*& _framework_);
	void printComplexEventFunctions(EFramework*& _framework_);
	void printEventAttributes(EEvent* _e, const int _indent = 0);
	void printPayload(EComplexEvent* _ce, const int _indent = 0);
	const char* indent(const int _indent);

	char* windowInfo(EComplexEvent* const _complex);
	const char* windowTypeAsString(const EComplexEvent::TWindowType _winType);
	const char* complexEventFunctionAsString(const EComplexEventFunction::Function _func);
	
	char mIndent[64];

#endif

};



#endif


