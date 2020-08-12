#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QRunnable>
#include <stdio.h>
#include <qslog/QsLog.h>

#define __STDC_CONSTANT_MACROS

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "SDL2/SDL.h"
};
//Refresh Event
#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)

#define SFM_BREAK_EVENT  (SDL_USEREVENT + 2)

class Player : public QRunnable
{

public:
    explicit Player();
    void run();
};

#endif // PLAYER_H
