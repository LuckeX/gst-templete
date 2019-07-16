#ifndef WRAPPER_H_
#define WRAPPER_H_


#ifdef __cplusplus 
extern "C" { 
#endif 
	// void *call_Person_Create(); 
	// void call_Person_Destroy(void *); 
	// int call_Person_GetAge(void *); 
	// const char *call_Person_GetName(void *);

	// void *call_Signaling_Create();
	// void call_Signaling_Destroy(void *);
	// void call_Signaling_Connect(void *,char *,char *);

	void call_LocalStream_Create(char* url,char* from,char* to);

#ifdef __cplusplus
 } 
#endif

#endif //WRAPPER_H_
