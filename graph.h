#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include "vertex.h"
#include "frame.h"
#include <QList>

class Graph
{
public:
    Graph();
    void Form();
     QList<Vertex> vertexes;
     QList<Frame> edges;
     int size;
     int **matrix;
};

#endif // GRAPH_H
