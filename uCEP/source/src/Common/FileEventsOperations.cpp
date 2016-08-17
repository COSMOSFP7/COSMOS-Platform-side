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


///RP: not used: now  we use udp sockets
/*
#include "FileEventsOperations.h"
#include <sys/stat.h>
#include <fstream>
#include "Tracer.h"
#include <ctime>
#include <string.h>
//#include <chrono>
#include <unistd.h>
#include <iostream>

namespace solcep {

    //        sprintf(fNTemp, "/proc/%d/exe", pid);
    FileEventsOperations::FileEventsOperations() {
//        char* fNTemp = new char[LENMAXPATH];
        char* fNTemp = (char*)"/proc/self/cwd";
        if (readlink(fNTemp, fNameIn, LENMAXPATH) == -1) {
            perror("readlink");
            ERROR() << "Impossible build the path for file events." << std::endl;
        }
        else {
            strcpy(fNameOut, fNameIn);
            strcat(fNameIn, "/incoming/event.txt");
            strcat(fNameOut, "/outgoing/");
            
            INFO() << "Looking file of events at: " << fNameIn << std::endl;
            INFO() << "Folder to put triggered events: " << fNameOut << std::endl;

        }
        
//        delete fNTemp;
    }

    FileEventsOperations::~FileEventsOperations() { 
    
        delete fNameIn;
        delete fNameOut;
    }
    
//verify if an event has arrived    
    bool FileEventsOperations::existsEventInFile() {
        
        struct stat buffer;

        return (stat(fNameIn, &buffer) == 0);
        
    }
    
    
    std::string FileEventsOperations::readEventFromFile() {
        std::string aLine;
        
///        std::ifstream input("/home/adminuser/projects/bcep/incoming/events.txt");        0k
        std::ifstream input(fNameIn);
        
        
        std::getline( input, aLine );
           
        input.close();
        
        if( remove(fNameIn) != 0 )
            ERROR() << "Unable to work with the events file!!" << std::endl;

        
        return aLine;
        
    }
    
    
    void FileEventsOperations::writeCEventToFile(std::string msg) {
        
        const char* ffName = getFileName();

        std::ofstream output(ffName);
        
        if (output.good()) {
            output.write(msg.c_str(), msg.size());
            output.flush();
        }
        else INFO() << "Output folder path is missing: " << fNameOut << std::endl;
        
        output.close();
        delete ffName;
        
    }
    
///RP: generate the file name to cEvent; based on timestamp.
    const char* FileEventsOperations::getFileName() {
        
        char* buffer = new char[16];

        struct timespec timeNow;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timeNow);  //  CLOCK_REALTIME
///        long int nanoS = timeNow.tv_nsec;           0k
        
        std::sprintf(buffer, "%lu", timeNow.tv_nsec);
               
        char* fName=  (char*)malloc(128); //malloc(strlen(fNameOut) + strlen(buffer) + 1);

        strcpy(fName, fNameOut);
        strcat(fName, buffer);
        strcat(fName, ".txt");
        INFO() << "File name generated: " << fName << std::endl;
        
       const char* fullName = (const char *)fName;
        
        delete buffer;
 
        return fullName;
    }
    
}

*/