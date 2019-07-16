#include "wrapper.h"
#include "p2psocketsignalingchannel.h"
#include "owt/base/deviceutils.h"
#include "owt/base/localcamerastreamparameters.h"
#include "owt/base/stream.h"
#include "owt/p2p/p2pclient.h"
#include "Yuv.h"
#include <zconf.h>

#include <memory>
#include <iostream>


using namespace owt::base;
using namespace owt::p2p;
using namespace std;

void call_Store_Buf(void * buf,int size){
   YuvVideo::StoreBuf(buf,size); 
}

void call_LocalStream_Create(char* url,char* from,char* to,int width,int height,int fps)
{
    P2PClientConfiguration configuration;
    AudioCodecParameters audio_param;
    audio_param.name = AudioCodec::kOpus;
    AudioEncodingParameters audio_encoding_param(audio_param, 0);
    configuration.audio_encodings.push_back(audio_encoding_param);

    VideoCodecParameters video_param;
    video_param.name = VideoCodec::kH264;
    VideoEncodingParameters video_encoding_param(video_param, 0, false);
    configuration.video_encodings.push_back(video_encoding_param);

    std::shared_ptr<P2PSignalingChannelInterface> signaling_channel(new P2PSocketSignalingChannel());
    std::shared_ptr<P2PClient> pc(new P2PClient(configuration, signaling_channel));

    // Get the input parameters for signaling
   // sleep(2);
   // cout << "Press Enter to connect peerserver." << endl;
   // cin.ignore();
    pc->Connect(url, from, nullptr, nullptr);
    pc->AddAllowedRemoteId(to);

    // int error_code = 0;
    // std::shared_ptr<owt::base::LocalCameraStreamParameters> lcsp;
    // lcsp.reset(new LocalCameraStreamParameters(true, true));
    // lcsp->Resolution(640, 480);
    // std::vector<std::string> devices = DeviceUtils::VideoCapturerIds();
    // if (!devices.empty()) {
    //     std::string id = devices.at(0);
    //     lcsp->CameraId(id);
    // }

    // int width=1280,height=720,fps=60;
    // string path="/home/xyk/Documents/CLionProjects/OMSLinuxSample/1280x720_60_FourPeople.yuv";
    unique_ptr<YuvVideo>framer(new YuvVideo(width,height,fps));

    shared_ptr<LocalCustomizedStreamParameters>lcsp(new LocalCustomizedStreamParameters(true,true));
    shared_ptr<LocalStream> shared_stream = LocalStream::Create(lcsp,std::move(framer));

//    cout << "Press Enter to publish stream to remote user " << to << endl;
//    cin.ignore();
    pc->Publish(to, shared_stream, nullptr, nullptr);
    cout << "Press Enter to exit." << endl;
    cin.ignore();
}

