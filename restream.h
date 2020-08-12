#ifndef RESTREAM_H
#define RESTREAM_H

#include <QRunnable>
#include <chrono>
#include <thread>
#include <tchar.h>
#include <Windows.h>

extern "C"
{
    #include <libavcodec\avcodec.h>
    #include <libavformat\avformat.h>
    #include <libavformat\avio.h>
    #include <libswscale\swscale.h>
    #include <libavutil\time.h>
}

//#pragma comment(lib,"libavformat/libavformat.a")
//#pragma comment(lib,"libavcodec/libavcodec.a")
//#pragma comment(lib,"libavutil/libavutil.a")
//#pragma comment(lib,"libswscale/libswscale.a")
//#pragma comment(lib,"x264.lib")
//#pragma comment(lib,"libswresample/libswresample.a")

class ReStream : public QRunnable
{
public:
    ReStream();
    void run() override;
};

#endif // RESTREAM_H
