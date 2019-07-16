#ifndef WRAPPER_H_
#define WRAPPER_H_
// #include <gst/gst.h>

#ifdef __cplusplus 
extern "C" { 
#endif 

	void call_LocalStream_Create(char* url,char* from,char* to,int width,int height,int fps);
	void call_Store_Buf(void * buf,int size);

#ifdef __cplusplus
 } 
#endif

#endif //WRAPPER_H_
