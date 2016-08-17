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
	Core Execution Framework
	
	Frameworks are built by FrameworkBuilder and 
	executed by the ComplexEventDetector Engine.
	
*/
#ifndef _SOL_CEP_ENGINE_TYPES_E_FRAMEWORK_H_
#define _SOL_CEP_ENGINE_TYPES_E_FRAMEWORK_H_

#include "EEvent.h"
#include "EEventAttribute.h"

#include "EEventAttributeValue.h"

#include "ECapturedEvent.h"
#include "ECapturedEventPool.h"
#include "EComplexEvent.h"
#include "EComplexEventFunction.h"
#include "EDetectionTree.h"
#include "EEventPeriod.h"
#include "EExternal.h"
//#include "EPayloadAttribute.h"
#include "EPayloadAttribute.h"
#include "EProgram.h"
#include "../../../DolceParser/ScriptCompiler/SymbolTable.h"
#include "../../../Common/BCEPManager.h"


class BCEPManager;

struct EFramework
{
	EFramework() : complexEvents(0)
			, complexEventFunctions(0)
			, events(0)
			, externals(0)
	{}


	EComplexEvent* complexEvents;
	EComplexEventFunction* complexEventFunctions;
	EEvent* events;
	EExternal* externals;
        SymbolTable* mSymTab;
///RP: to restart
        BCEPManager* bcepMngr;
        
};


#endif
