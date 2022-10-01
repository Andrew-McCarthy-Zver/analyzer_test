#ifndef VERTEX_H
#define VERTEX_H

#include <QString>

class Vertex
{
public:
    Vertex(int number, QString add, QString id,  QString tp, bool tochka );
    int num;
    QString address;
    QString ssid;
    QString type;
    bool t_d;
};

#endif // VERTEX_H
