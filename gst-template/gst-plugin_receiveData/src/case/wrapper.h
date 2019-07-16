#ifndef PIPELINE_WRAPPER_H
#define PIPELINE_WRAPPER_H


#ifdef __cplusplus
extern "C" {
#endif

void* call_Instance();
void call_listento(void* instance,int minPort,int maxPort);
unsigned short call_getListeningPort(void* instance);
void call_connect(char* ip,int port);

void *call_getBuffer();

#ifdef __cplusplus
}
#endif



#endif //PIPELINE_WRAPPER_H