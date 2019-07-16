#include "wrapper.h"
#include "p2psocketsignalingchannel.h"
#include "owt/base/deviceutils.h"
#include "owt/base/localcamerastreamparameters.h"
#include "owt/base/stream.h"
#include "owt/p2p/p2pclient.h"

#include <memory>
#include <iostream>


// void *call_Person_Create() { 
// return new Person("Aland", 18); // 构造 
// } 
// void call_Person_Destroy(void *p) { 
// delete static_cast<Person *>(p); // 释放
//  } 
//  int call_Person_GetAge(void *p) { 
//  	return static_cast<Person *>(p)->GetAge(); 
//  } 
//  const char *call_Person_GetName(void *p) { 
//  	return static_cast<Person *>(p)->GetName(); 
//  }


// void *call_Signaling_Create(){
// 	return new SignalingChannel();
// }
// void call_Signaling_Destroy(void *s){
// 	delete static_cast<SignalingChannel *>(s);
// }
// void call_Signaling_Connect(void *s,char *host,char *token){
// 	static_cast<SignalingChannel *>(s)->Connect(host,token);
// }

using namespace owt::base;
using namespace owt::p2p;
using namespace std;
void call_LocalStream_Create(char* url,char* from,char* to)
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

//    cout << "Press Enter to connect peerserver." << endl;
//    cin.ignore();
    pc->Connect(url, from, nullptr, nullptr);
    pc->AddAllowedRemoteId(to);

    int error_code = 0;
    std::shared_ptr<owt::base::LocalCameraStreamParameters> lcsp;
    lcsp.reset(new LocalCameraStreamParameters(true, true));
    lcsp->Resolution(640, 480);
    std::vector<std::string> devices = DeviceUtils::VideoCapturerIds();
    if (!devices.empty()) {
        std::string id = devices.at(0);
        lcsp->CameraId(id);
    }
    std::shared_ptr<LocalStream> shared_stream = LocalStream::Create(*lcsp, error_code);

//    cout << "Press Enter to publish stream to remote user " << to << endl;
//    cin.ignore();
    pc->Publish(to, shared_stream, nullptr, nullptr);
    cout << "Press Enter to exit." << endl;
    cin.ignore();
}