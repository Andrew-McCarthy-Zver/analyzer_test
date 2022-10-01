#include "graph.h"

Graph::Graph()
{

}

void Graph:: Form()
{
    size = vertexes.size();
    matrix = new int*[size];
    for(int k = 0; k < size; k++)
    {
        matrix[k] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[k][j] = 0;
            foreach (Frame fr, edges)
            {
                if (fr.ta == vertexes[k].address && fr.ra == vertexes[j].address) matrix[k][j]++;
            }
        }
    }
}
