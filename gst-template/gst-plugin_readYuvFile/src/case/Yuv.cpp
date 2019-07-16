//
// Created by xyk on 19-4-29.
//

#include "Yuv.h"


#include <iostream>
#include <string.h>

using namespace std;

pthread_mutex_t YuvVideo::mutex;


queue<Buffer> YuvVideo::Buf;

void YuvVideo::StoreBuf(void *buf,int size) {
    Buffer t(size);
    
    memcpy(t.buf.get(),buf,t.len); 

    pthread_mutex_lock(&mutex);
    
    Buf.push(t);
    pthread_mutex_unlock(&mutex);
}


YuvVideo::YuvVideo(int width, int height, int fps){
    m_width = width;
    m_height = height;
    m_type = VideoFrameGeneratorInterface::I420;
    m_fps = fps;
    int size = m_width * m_height;
    int qsize = size / 4;
    m_frame_data_size = size + 2 * qsize;
    //m_frame_data_size = size*1.5;

    pthread_mutex_init(&mutex,NULL);
}

YuvVideo::~YuvVideo(){
//    if(m_fd){
//        cout<<"m_fd is not null"<<endl;
//        fclose(m_fd);
//    }
}

uint32_t YuvVideo::GetNextFrameSize() {
    return m_frame_data_size;
}



int YuvVideo::GetHeight() { return m_height; }
int YuvVideo::GetWidth() { return m_width; }
int YuvVideo::GetFps() { return m_fps; }
VideoFrameGeneratorInterface::VideoFrameCodec YuvVideo::GetType() { return m_type; }

uint32_t YuvVideo::GenerateNextFrame(uint8_t* frame_buffer, const uint32_t capacity) {
    if (frame_buffer == nullptr) {
//        LOG_DEBUG("Invaild buffer for frame generator.");
        return 0;
    }
    if (capacity < m_frame_data_size) {
        return 0;
    }

    pthread_mutex_lock(&mutex);
    if(!Buf.empty()){
        Buffer temp=Buf.front();
        Buf.pop(); 
        memcpy(frame_buffer,temp.buf.get(),temp.len); 
    }
    pthread_mutex_unlock(&mutex);

    return m_frame_data_size;
}