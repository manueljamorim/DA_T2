#ifndef DA_T2_LOADDATA_H
#define DA_T2_LOADDATA_H


#include "Graph.h"
#include <fstream>
#include <iostream>

class LoadData {
public:
    Graph graph;
    vector<string> split(const string &s,const string &del);

    void load();
};


#endif //DA_T2_LOADDATA_H
