#ifndef DA_T2_GRAPH_H
#define DA_T2_GRAPH_H

using namespace std;
#include <list>
#include <vector>
#include <set>

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


    vector<int> get_path(int a, int b);
    int max_capacity(int a, int b);
    int min_transbordos_multiple_solutions(int a, int b);
    int max_capacity_multiple_solutions(int a, int b);

    //apenas para graficos aciclicos
    vector<vector<int>> get_path_multiple_solutions(int a, int b);
    void recursive(int a, int b, vector<int> path, vector<vector<int>> &result);
    set<vector<int>> multi_objective_solutions(int a, int b);

    int calc_capacity(vector<int> a);
    bool compare_capacity(const vector<int> &a, const vector<int> &b);
};


#endif //DA_T2_GRAPH_H
