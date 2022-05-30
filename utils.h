#include <fstream>
#include <sstream>
#include <string>

#include "graph.h"

Graph createGraphFromFile(string filename) {
    string line;

    ifstream file(filename);

    if(!file.is_open()) {
        cerr << "Unable to open file" << endl;
    }

    int n_nodes, n_edges;
    getline(file, line);
    istringstream(line) >> n_nodes >> n_edges;

    Graph graph = Graph(n_nodes, true);

    int src, dest, cap, dur;
    for(int i = 0; i < n_edges; i++) {
        getline(file, line);
        istringstream(line) >> src >> dest >> cap >> dur;
        graph.addEdge(src, dest, cap, dur);
        //graph.addEdge(dest, src, 0, dur); Residual edge
    }

    file.close();
    return graph;
}