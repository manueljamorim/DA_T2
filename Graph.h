#ifndef DA_T2_GRAPH_H
#define DA_T2_GRAPH_H

using namespace std;
#include <list>
#include <vector>

class Graph {
public:
    struct Edge {
        int dest;   // Destination node
        int capacity;
        int duration;
    };
    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)

        bool visited;   // Has the node been visited on a search?
        int pred;
        int dist;
        int cap;

        vector<int> pred_v;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    vector<Node> nodes;


    list<int> get_path(int a, int b);
    int max_capacity(int a, int b);
    int min_transbordos(int a, int b);

    int max_capacity_multiple_solutions(int a, int b);
    list<list<int>> get_path_multiple_solutions(int a, int b);

    int recursive(int a, int current);
};


#endif //DA_T2_GRAPH_H
