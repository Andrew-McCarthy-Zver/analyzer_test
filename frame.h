#ifndef FRAME_H
#define FRAME_H

#include <QString>

class Frame
{
public:
    Frame();

    int number;
    int size;
    int more_fragments;
    int seqnum;
    int fragnum;
    double offset;
    QString ta;
    QString ra;
    QString ssid;
    QString type;


};

#endif // FRAME_H
