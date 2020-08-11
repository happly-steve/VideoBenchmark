#ifndef MYDATA_H
#define MYDATA_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QRunnable>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libswscale/swscale.h>
}

class MyData : public QRunnable
{

public:
    explicit MyData();
    char *data;
    void run();

};

#endif // MYDATA_H
