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



#ifndef MQTTCOMMUNICATIONMODULE_HPP
#define	MQTTCOMMUNICATIONMODULE_HPP

#include "CommunicationModule.hpp"
#include <stdio.h>
#include "mosquitto.h"
#include "../Queue.h"
#include "../Configuration/ReadIniFile.h"

namespace solcep {

class MQTTCommunicationModule : public CommunicationModule {
public:
    struct mosquitto *mosq = NULL;
    static Queue mosqQueue;

    MQTTCommunicationModule(IniFileSection iniFileSection);
    ~MQTTCommunicationModule();
    virtual char * receiveData();
    virtual void sendData(const char* message);



private:

    static char * topicCollect;
    static char * topicPublish;
    static void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str);
    static void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    static void my_connect_callback(struct mosquitto *mosq, void *userdata, int result);
    static void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos);
    static void addMessage(void * message);
    static string format(void * vmessage);
    static char * stringToCharArr(std::string cad);

};


Queue MQTTCommunicationModule::mosqQueue;
char * MQTTCommunicationModule::topicCollect = NULL;
char * MQTTCommunicationModule::topicPublish = NULL;

MQTTCommunicationModule::MQTTCommunicationModule(IniFileSection iniFileSection) {
    //mosqQueue = new Queue();
    IniFileSection fileSection= iniFileSection;
    
    const char * host = fileSection.hostMQTT.c_str();
    int port = fileSection.portMQTT;
    topicCollect = stringToCharArr(fileSection.topicMQTTCollect);
    topicPublish = stringToCharArr(fileSection.topicMQTTPublish);
    
    mosquitto_lib_init();
    int keepAlive = 60;
    char id[11];
    strncpy(id, iniFileSection.cepName.c_str(),sizeof(id));
    bool clean_session = true;

    mosq = mosquitto_new(id, clean_session, NULL);
    if ((fileSection.userMQTT!=NULL) || (fileSection.passwordMQTT!=NULL)){
            mosquitto_username_pw_set(mosq,fileSection.userMQTT,fileSection.passwordMQTT);
    }

    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
    }
    if (mosquitto_connect(mosq, host, port, keepAlive)) {
        fprintf(stderr, "Unable to connect.\n");
    }
    mosquitto_log_callback_set(mosq, my_log_callback);
    mosquitto_connect_callback_set(mosq, my_connect_callback);
    mosquitto_message_callback_set(mosq, my_message_callback);
    mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
    
    mosquitto_loop_start(mosq);

}

MQTTCommunicationModule::~MQTTCommunicationModule() {
    mosquitto_loop_stop(mosq,true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    delete topicCollect;
    delete topicPublish;
}

char * MQTTCommunicationModule::receiveData() {
    return  stringToCharArr(mosqQueue.pop());
}

void MQTTCommunicationModule::sendData(const char* message){
    mosquitto_publish(mosq,NULL,topicPublish,strlen(message),message,1,false);    
}

void MQTTCommunicationModule::my_log_callback(mosquitto* mosq, void* userdata, int level, const char* str) {
    printf("%s\n", str);
}

void MQTTCommunicationModule::my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    if (message->payloadlen) {
        printf("%s %s\n", message->topic, (char *) message->payload);
        addMessage(message->payload);
    } else {
        printf("%s (null)\n", message->topic);
    }
    //fflush(stdout);
}

void MQTTCommunicationModule::my_connect_callback(struct mosquitto *mosq, void *userdata, int result) {
    if (!result) {
        // Subscribe to broker information topics on successful connect
        //mosquitto_subscribe(mosq, NULL, "$SYS/#", 2);
        mosquitto_subscribe(mosq, NULL, topicCollect, 2);
    } else {
        fprintf(stderr, "Connect failed\n");
    }
}

void MQTTCommunicationModule::my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos) {
    int i;

    printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
    for (i = 1; i < qos_count; i++) {
        printf(", %d", granted_qos[i]);
    }
    printf("\n");
}

void MQTTCommunicationModule::addMessage(void * message) {
    mosqQueue.push(format(message));
}

std::string MQTTCommunicationModule::format(void* vmessage){
    return std::string((char *)vmessage);
}

char * MQTTCommunicationModule::stringToCharArr(std::string cad){
    char * cop = new char[cad.length() + 1];
    strcpy(cop, cad.c_str());
    return cop;
    
}



#endif	/* MQTTCOMMUNICATIONMODULE_HPP */

}

/* for testing
int main(int argc, char** argv) {
    
    CommunicationModule * cm = new MQTTCommunicationModule();

    while (true){
       string scad = cm->receiveData();
       if (scad.size()>0){
           const char * cad = scad.c_str();
            printf("received data \n");           
            printf(cad);
            printf("...............\n");
            cm->sendData("mandado datito");
       }

    }

    
    
    return 0;

}

*/
