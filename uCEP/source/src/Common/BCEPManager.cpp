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


#include "BCEPManager.h"
#include "../DolceParser/ScriptCompiler/Compiler.h"
#include "../ComplexEventDetector/Engine/Types/EFramework.h"
#include "../DolceParser/ScriptCompiler/ErrorList.h"
#include "../DolceParser/FrameworkBuilder/FrameworkBuilder.h"
#include "../ComplexEventDetector/ComplexEventDetector.h"
#include "SocketUDPServer.h"
#include "../Plugins/SimpleDecoder/SimpleDecoderPlugin.h"
#include "Tracer.h"
#include "Configuration/ReadIniFile.h"


#ifdef MQTT
#include "Communication/MQTTCommunicationModule.hpp"
#endif

#include "Communication/UDPCommunicationModule.hpp"

#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

using namespace solcep;
using namespace std;

int atom = 1;
EFramework* framework;
ComplexEventDetector *ced;

///FileEventsOperations* mFeo;
//SocketUDPServer* mSockUDPS;
CommunicationModule *cm;
SimpleDecoderPlugin* sdp;

IniFileSection BCEPManager::checkInputParams(int argc, char *argv[]){
    
    IniFileSection iniFileSec;
    for (int i=1; i<argc; i++){
        string argument = argv[i];
        if (argument.compare("-h") == 0){
            std::cout << "bcep usage:" << "\n";
            std::cout << "  -h   help" << "\n";
            std::cout << "  -mi  mptt input topic (10 characters max)" << "\n";
            std::cout << "  -mo  mqtt output topic (10 characters max)" << "\n";
            std::cout << "  -n   client name for mqtt subscription (10 characters max)" << "\n";
            std::cout << "  -d   dolce specification file (30 characters max)" << "\n";
            std::cout << "  -f   configuration file" << "\n";
            std::cout << "\n" << "example:" << "\n";
            std::cout << "            -n trafficCep_1 bcep -mi speedCollector -mo incidencePublisher -d incidentRules.dolce";
            
            exit (0);
        }
        else if (argument.compare("-mi") == 0){
            i++;
            iniFileSec.topicMQTTCollect = argv[i];
        }
        else if (argument.compare("-mo") == 0){
            i++;
            iniFileSec.topicMQTTPublish = argv[i];
        }
        else if (argument.compare("-d") == 0){
            i++;
            iniFileSec.dolceSpec = argv[i];
        }
        else if (argument.compare("-c") == 0){
            i++;
            iniFileSec.confFile = argv[i];
        }
        else if (argument.compare("-n") == 0){
            i++;
            iniFileSec.cepName = argv[i];
        }
    }
    return iniFileSec;
}



void *checkQueue(void *arg);

struct argsToThread {
    ComplexEventDetector *mced;
    Queue *mqueue;
    SimpleDecoderPlugin *msdp;
} *mArgsToThread;

BCEPManager::BCEPManager() {
    
        mQueue = new Queue();

}

BCEPManager:: ~BCEPManager(){
    
    delete framework;
    delete mQueue;
}

void shutdown(int sig) {
    std::cout << "Unexpected ending!!";
    
    delete framework;
    
    sdp->unload();
    
    delete ced;
    //delete mSockUDPS;
    delete cm;
    delete sdp;
    
    free(mArgsToThread);
    
    atom = 0;
}


void BCEPManager::BCEPStart(int argc, char *argv[]) {
    
    signal(SIGINT, &shutdown);
    Trace::LogLevel= 4;
    Trace::SetTracer(make_unique<StdOutTracer>());
    
    IniFileSection  iniFileParams = checkInputParams (argc, argv);

    ReadIniFile* iniFile = new ReadIniFile(iniFileParams.confFile);
    IniFileSection iniFileSec = iniFile->readFile();
    
    iniFileSec.confFile = iniFileParams.confFile;
    iniFileSec.topicMQTTCollect = iniFileParams.topicMQTTCollect;
    iniFileSec.topicMQTTPublish = iniFileParams.topicMQTTPublish;
    iniFileSec.dolceSpec = iniFileParams.dolceSpec;
    delete iniFile;
    
    string fileName = iniFileSec.dolceSpec;
    int res;
    
    framework = createFramework(fileName.c_str(), res);

    if(!framework)
        throw runtime_error("Unable to create EFramework");
    
    INFO() << "Main framework created " << std::endl;
    
    ced = new ComplexEventDetector(framework);
    
    INFO() << "Complex Event Detector created " << std::endl;    

    sdp = new SimpleDecoderPlugin();
    sdp->load();
    INFO() << "Decoder utility loaded " << std::endl;
    
    
    
   
    
#ifndef MQTT
    cm = new UDPCommunicationModule(iniFileSec);
#endif
    
#ifdef MQTT
    cm = new MQTTCommunicationModule(iniFileSec);
#endif
    
    //mSockUDPS = new SocketUDPServer(iniFileSecUDP);
    
    //ced->mSocketUDPServer = mSockUDPS;
    ced->cm = cm;
    
////RP: threads!!!    
    pthread_t threadDetector;
    mArgsToThread = (argsToThread*)malloc(sizeof(argsToThread));
    mArgsToThread->mced = ced;
    mArgsToThread->mqueue = mQueue;
    mArgsToThread->msdp = sdp;
    pthread_create(&threadDetector, NULL, checkQueue, (void*) mArgsToThread);
    
    std::string lineToRead;
    char *charsRead;

///   int eventosPermitidos = 0;
    
    while (atom  /* eventosPermitidos < 100000 */) {
///RP        if (sentinel == 25) {      //to tuning the listening
                    charsRead = cm->receiveData();
                    lineToRead.assign(charsRead);
                    free(charsRead);
                 
                    if (lineToRead.size()>0) {
                        mQueue->push(lineToRead);
                        INFO() << "Entry: " << lineToRead <<std::endl;
                    }

                
////                lineToRead = mSockUDPS->readEventFromSocketUDP();
////              if (lineToRead.size()>0) {
////                    INFO() << "Entry: " << lineToRead <<std::endl;
////                    ced->processPublishedMessage(sdp->decode(lineToRead));
///                    eventosPermitidos++;
////                }
            
    }
}

///RP: method that is executed when the thread threadDetector is pick up by some processor
void *checkQueue(void *arg) {
    
    argsToThread *_mArgsToThread= (argsToThread*) arg;
    int sntnl=0;
    time_t bgn = time(NULL);
    while (1) {
        
        if (_mArgsToThread->mqueue->front()) {
            _mArgsToThread->mced->processPublishedMessage(_mArgsToThread->msdp->decode(_mArgsToThread->mqueue->pop()));
            sntnl+=2;
        }
        else {
            usleep(10); // 10 microseconds
            sntnl++;
        }
        if (sntnl >= 10000) {
            if ((time(NULL) - bgn) >= 10) {
                INFO() << "Publish: " << std::endl;
                _mArgsToThread->mced->processPublishedMessage("\001\200");  //to renew the trees
                sntnl=0;
                bgn = time(NULL);
            }
        }
    }
    
    return 0;
}


//RP: To restart with a new Dolce file
bool BCEPManager::BCEPRestart(int flag) {
    
    if (flag == 1) {  ///Now only 1; 1-->reload
        string fileName = "./detect.dolce";
        int res;
        framework = createFramework(fileName.c_str(), res);

        if(!framework && !res)   ///RP: in this point maybe!! to achieve that not die when the dolce is not 0k
            throw runtime_error("Unable to update Framework");
    
        INFO() << "Main framework updated " << std::endl;
    
        delete ced;
        ced = new ComplexEventDetector(framework);
        
        return 1;
    }
    
    return 0;    
}


void BCEPManager::compileSource(const char* fileName, Compiler* const compiler)
{
    FILE* f = 0;

    if(fileName)
    {
        f = fopen(fileName,"r");
        if(f == NULL)
        {
            throw std::runtime_error("Unable to open file for compilation.");
        }
    }
    else
    {
        f = stdin;
    }

    compiler->compile(f);
    if(fileName)
        fclose(f);
}


EFramework* BCEPManager::createFramework(const char* sourceFile, int& res_)
{
    ErrorList* errList = new ErrorList();
    Compiler* compiler = new Compiler(errList);

    compileSource(sourceFile, compiler);
	
    if(!errList->hasError())
    {
	FrameworkBuilder fb(compiler, errList);
	framework = fb.build(res_);
///RP:
        framework->bcepMngr = this;
    }
    else
    {
        delete compiler->mSymbolTable;  ///RP:
        delete compiler;
        
        INFO()<<"FATAL: Errors found in Dolce script. Engine not built! : "<<std::endl;
        throw std::runtime_error(/*"FATAL: Errors found in Dolce script. Engine not built! : " + */ errList->mHead->s);
                
        delete errList->mHead;    
        delete errList;
        delete sourceFile;
    }
    
//RP:

//rolando    compiler->mTree->startCompletDestroy();    

    delete compiler->mTree;
    delete compiler->mSymbolTable;
    delete compiler;
    delete errList->mHead;
    delete errList;
///    delete sourceFile;
    
    return framework;
}

