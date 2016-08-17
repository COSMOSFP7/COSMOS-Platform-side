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

#include "SimpleDecoderPlugin.h"
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include "../../Types/TPosLiteral.h"
///#include <sys/socket.h>
///#include <arpa/inet.h>
///#include <stdio.h>
///#include <unistd.h>
///#include <string.h>
///#include <stdlib.h>


using namespace std;

const int SimpleDecoderPlugin::MAX_BUF_SIZE = 1024;

int SimpleDecoderPlugin::load() 
{
	mWB = new solcep::WireEventBuilder();
	mBuf = (char*)malloc(MAX_BUF_SIZE);

	return 0; 
}

void SimpleDecoderPlugin::unload() 
{
	free(mBuf);
	delete mWB;
        
        delete mSz;
///        delete mSzSave;
        
}	

string SimpleDecoderPlugin::decode(string message)
{
    initTokenizer(reinterpret_cast<const unsigned char*>(message.c_str()), message.length());

///    char tok1[256];
      char tok1[128];
///    char tok2[256];
      char tok2[128];
///    char tok2[256];
      char tok3[128];

    // type
    if(!nextToken(tok1)) 
        throw runtime_error("Decoder: nextToken failed!");

    // name
    if(!nextToken(tok2)) 
        throw runtime_error("Decoder: nextToken failed!");

    // Setup the Wire Event
    mWB->create(atoi(tok1), tok2);

    // nv-pairs
    int nvPairCount = 0;
    while(nextToken(tok1))
    {
        // --name
        if(!nextToken(tok2))
            throw runtime_error("Decoder: nextToken failed!");

        // --value
        if(!nextToken(tok3))
            throw runtime_error("Decoder: nextToken failed!");
            
        if(!strcmp(tok1, "int")) 
                mWB->add(tok2, atoi(tok3));
        else if(!strcmp(tok1, "float"))
                mWB->add(tok2, (float)atof(tok3));
        else if(!strcmp(tok1, "string")) {
                completeStrToken(tok3);
                mWB->add(tok2, tok3);
        }
        else if(!strcmp(tok1, "char"))
                mWB->add(tok2, (char)tok3[0]);
        else if(!strcmp(tok1, "pos"))
                mWB->addTPL(tok2, tok3);
        else if(!strcmp(tok1, "area"))
                mWB->addArea(tok2, tok3);
        else if(!strcmp(tok1, "time"))
                mWB->addTime(tok2, tok3);

        //throw runtime_error("Decoder: unsupported type");
        
        nvPairCount++;
    }

    mWB->addNVPairCount(nvPairCount);	
///RP 16122014
    std::cout << "\n";
    return mWB->finalize();
}

void SimpleDecoderPlugin::initTokenizer(const unsigned char* _data, const int _size)
{
    mSz = mBuf;
    mSzSave = 0;
    int sz = (_size > MAX_BUF_SIZE) ? MAX_BUF_SIZE : _size;
    bzero(mSz,MAX_BUF_SIZE);
    strncpy(mSz, (char*)_data, sz);
	///RP: 15122014 
	///    for(int i = 0; i < sz + 10; i++)
	///	std::cout << " " << static_cast<unsigned>(mSz[i]) << "-"<< mSz[i];
    
//    delete _data;
}

bool SimpleDecoderPlugin::nextToken(char* token_) {
//    int cnt;	
///    bzero(token_, 256);
    bzero(token_, 128);
    char* t = strtok_r(mSz, " \n\r\t", &mSzSave);
    mSz = 0;
    if(t && strlen(t))
    {
    ///        strncpy(token_, t, 256);
        strncpy(token_, t, 128);
        std::cout << "TOKEN='" << token_ << "' len=" << strlen(token_) << "\t";
        return true;
    }

    return false;
}

///RP:
bool SimpleDecoderPlugin::completeStrToken(char* token_) {
        
    if (token_[0] == '"') {
        if (strlen(token_) > 1 && token_[strlen(token_)-1] == '"') {
            int c=1, cc=0;
            char *tt = (char*)malloc(strlen(token_));
            while (token_[c] != '"') {
                    tt[cc] = token_[c];
                    cc++; c++;
            }
            tt[cc]='\0';
            strcpy(token_, tt);
            free(tt);
        }
        else {
            char *t;
            if (mSzSave[0] == '"') {
                t=(char*)"";
                mSzSave++;
            }
            else
                t = strtok_r(mSz, "\\\"", &mSzSave);
            
            strcat(token_, " ");
            strcat(token_, t);
            int cc=0;
            char *tt = (char*)malloc(strlen(token_));
            for (unsigned c = 0; c < strlen(token_); c++) {
                if (token_[c] != '"') {
                    tt[cc] = token_[c];
                    cc++;
                }
            }
            tt[cc]='\0';
            strcpy(token_, tt);
            free(tt);
        }
    }
    else {
        char *t;
        char *aBackStep= (char*)malloc(strlen(mSzSave));
        strcpy(aBackStep, mSzSave);
        t = strtok_r(mSz, " \n\r\t", &mSzSave);    
        mSz = 0;

        while (t && strlen(t) && !isTypeAccepted(t)) {
            strcat(token_, " ");
            strcat(token_, t);
            strcpy(aBackStep, mSzSave);
            t = strtok_r(mSz, " \n\r\t", &mSzSave);
    ///        mSz = 0;        
        }
        
        strcpy(mSzSave, aBackStep);
        free(aBackStep);
    }
    
    return true;
}

///RP: plesae make consistent with the dolce specification
bool SimpleDecoderPlugin::isTypeAccepted(char* token_) {
    
    if (strcmp(token_, "int") && strcmp(token_, "float") && strcmp(token_, "string") && strcmp(token_, "char") && strcmp(token_, "pos") &&
        strcmp(token_, "area") && strcmp(token_, "time"))
            return false;
    
    return true;
    
}
    

///RP: bool SimpleDecoderPlugin::nextToken(char* token_)
/*bool SimpleDecoderPlugin::nextTokenString(char* token_)
{
//    int cnt;	
///    bzero(token_, 256);
    bzero(token_, 128);
    
    char *ft = mSz, *ftSave;
    char* t = strtok_r(ft, " \n\r\t", &ftSave);
    
    if (t && strlen(t)) {
        while (t && strlen(t) && !(strcmp(t, "int") || strcmp(t, "float") || strcmp(t, "string"))) {
            t = strtok_r(mSz, " \n\r\t", &mSzSave);
            mSz = 0;
            if (t && strlen(t)) {
    ///                strncpy(token_, t, strlen(t));
                strcat(token_,t);

            }           
            t = strtok_r(ft, " \n\r\t", &ftSave);                    
        }
        std::cout << "TOKEN='" << token_ << "' len=" << strlen(token_) << "\t";        
        return true;
    }

    return false;
}
*/

extern "C" CEPPlugin* cep_plugin_create()
{
	return new SimpleDecoderPlugin();
}

extern "C" void cep_plugin_destroy(CEPPlugin* _plugin)
{
	delete _plugin;
}



