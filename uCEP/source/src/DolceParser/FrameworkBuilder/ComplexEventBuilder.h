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
#ifndef _SOL_CEP_COMPLEX_EVENT_BUILDER_H_
#define _SOL_CEP_COMPLEX_EVENT_BUILDER_H_


///#include <stdio.h>

#include "../ScriptCompiler/ASTree.h"
#include "../../ComplexEventDetector/Engine/Types/EComplexEventFunction.h"

class ProgramBuilder;
class FrameworkBuilder;
struct EComplexEvent;
struct EPayloadAttribute;
struct EEventAttribute;
struct EDetectionTree;
struct EFramework;

class ComplexEventBuilder
{
public:
	ComplexEventBuilder(FrameworkBuilder* const _fb,
						EComplexEvent* _complex);

	ComplexEventBuilder(FrameworkBuilder* const _fb);

	~ComplexEventBuilder();
	
	int build(	EFramework*& _framework_,
				ASTree* const _node);
	
	/*
		Returns a built complex event structure.
		Caller is responsible for releasing memory
	*/
	EComplexEvent* finalize();
	

protected:
	
	ComplexEventBuilder();
	
	ComplexEventBuilder(const ComplexEventBuilder& rhs) : mFrameworkBuilder(0) {}
	
	ComplexEventBuilder& operator= (const ComplexEventBuilder& rhs)	{ return *this; }


	int buildPayloadAttributes(ASTree* const _node);
	
	int buildComplexEventFunctions(	EFramework*& _framework_,
									ASTree* const _node);
									
	int buildPrograms(ASTree* const _node);
	
	int resolveWindow(ASTree* const _node);

	int resolveGroupAttribute(ASTree* const _node);
	
	TValue* resolveIdValue(ASTree* const _node, const TType _expectedType);
	
	EDetectionTree* buildDetectionTree(ASTree* const _node);
	EDetectionTree* buildDetectionTreeNode(ASTree* const _node);

	int resolveDuration(ASTree* const _node);
	int resolveRecurringTime(ASTree* const _node);
	int resolveTupleCount(ASTree* const _node);
	
private:

	FrameworkBuilder* const mFrameworkBuilder;
	EComplexEvent* mComplex;
	
	ProgramBuilder* mProgramBuilder;
	
	EComplexEventFunction::Function nodeAsFunction(ASTree* const _node);


#ifdef CEP_DEBUG
	void dumpPayloadAttributes(EComplexEvent* const _complex);
#endif

};



#endif


