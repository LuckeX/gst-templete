#include "wrapper.h"
#include "Server.h"
#include <iostream>
#include <queue>


using namespace std;

void* call_instance(){
    return new Server_Client(5,false);
}

void call_listento(void* instance,int minPort,int maxPort){
    Server_Client* sc = static_cast<Server_Client*>(instance);
    sc->listento(minPort,maxPort);
}

unsigned short call_getListeningPort(void* instance){
    Server_Client* sc = static_cast<Server_Client*>(instance);
    return sc->getListeningPort();
}

void *call_getBuffer(){
    if(!Server_Client::m_receiveQueue.empty()){
        boost::lock_guard<boost::mutex>lock(Server_Client::m_receiveQueueMutex);
        void *p = Server_Client::m_receiveQueue.front().buffer.get();
        Server_Client::m_receiveQueue.pop();
        return p;
    }
    return NULL;
}

void call_connect(void* instance, char* ip,int port){
   Server_Client *sc = static_cast<Server_Client*>(instance);
   sc->connect(ip,port);
}

void call_sendData(void* instance, void *buf, int len){
    Server_Client *sc = static_cast<Server_Client*>(instance);
    sc->sendData((char*)buf,len);
}