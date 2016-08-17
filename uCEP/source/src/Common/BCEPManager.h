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


//using namespace solcep;
using namespace std;

#include "../DolceParser/ScriptCompiler/Compiler.h"
#include "../ComplexEventDetector/Engine/Types/EFramework.h"
#include "../ComplexEventDetector/ComplexEventDetector.h"
#include "SocketUDPServer.h"
#include "Queue.h"
#include "../ComplexEventDetector/ComplexEventDetector.h"
#include "./Configuration/IniFileSection.h"
        
#ifndef BCEPMANAGER_H
#define	BCEPMANAGER_H

class EFramework;

class BCEPManager
{
    
    protected:
        Queue *mQueue;
        IniFileSection checkInputParams(int argc, char *argv[]);        
        
    public:
        
        BCEPManager();
        virtual ~BCEPManager();
        void BCEPStart(int argc, char *argv[]);
        bool BCEPRestart(int flag);
        
        
        void compileSource(const char* fileName, Compiler* const compiler);
        EFramework* createFramework(const char* sourceFile, int& res_);

};

#endif	/* BCEPMANAGER_H */