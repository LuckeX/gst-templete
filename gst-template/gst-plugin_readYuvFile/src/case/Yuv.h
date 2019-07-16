//
// Created by xyk on 19-4-29.
//

#ifndef OWT_P2P_SAMPLE_YUV_H
#define OWT_P2P_SAMPLE_YUV_H

#pragma once
#include <stdio.h>
#include <pthread.h>
#include "owt/base/framegeneratorinterface.h"
#include <string>
#include <queue>
#include <memory>


using namespace std;
using namespace owt::base;

struct Buffer{
    shared_ptr<uint8_t> buf;
    int len;
    Buffer(int l){
        len = l;
        buf.reset(new uint8_t[len+10]);
    }
};



class YuvVideo : public VideoFrameGeneratorInterface{
public:
    YuvVideo(int width,int height,int fps);
    ~YuvVideo();
    uint32_t GetNextFrameSize(); //1382400
    uint32_t GenerateNextFrame(uint8_t* frame_buffer, const uint32_t capacity);
    int GetHeight();
    int GetWidth();
    int GetFps();
    VideoFrameGeneratorInterface::VideoFrameCodec GetType();
    static void StoreBuf(void* buf,int size);
    static pthread_mutex_t mutex;        
    static queue<Buffer> Buf;

private:
    int m_width;
    int m_height;
    int m_fps;
    uint32_t m_frame_data_size;
    VideoFrameGeneratorInterface::VideoFrameCodec m_type;
};


#endif //OWT_P2P_SAMPLE_YUV_H
