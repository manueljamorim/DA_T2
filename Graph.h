#include <list>
#include <vector>
#include <set>

using namespace std;

class Graph {
private:
    struct Edge {
        int src; // Source node
        int dest; // Destination node
        int capacity; // Capacity of the vehicle
        int duration; // Duration of the travel
        int flow; // Flow going through the edge
    };

    struct Node {
        int parent; // The parent node
        vector<Edge> adj; // The list of outgoing vehicles (to adjacent places)
        bool visited; // Has the place been visited on a search?
        int pred;
        int dist;
        int cap;
        vector<int> pred_v;
    };

    int n;
public:
    int getN() const;

private:
    // Graph size (vertices are numbered from 1 to n)
    int s, t; // Source node and destination/sink node
    bool hasDir; // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    
    bool solved = false; // Indicate whether the algorithm has ran. The result in successive runs will always be the same
    int maxFlow = 0; // Maximum flow. Calculated by calling the solve method

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int capacity, int duration, int flow = 0, bool fromOutput = false);


// ----------------- Task 1 Functions -------------------
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

// ------------------------------------------------------


// ----------------- Task 2 Functions -------------------
    // 2.1
    bool calculatePathForGroup(int size);

    // 2.2
    void calculatePathsForGroupIncrease(int increment, int startSize);
    void printChanges(Graph graph1, Graph graph2);

    // 2.3
    int getMaxFlow();

    int bfs(ofstream& output, int& maxSize);

    int remainingCapacity(Edge e);
    
    bool isResidual(Edge e);

    void augmentEdge(Edge& e, int limit);

    void execute();

    bool solve(int maxSize = INT_MAX);

    void printOutput();

// ------------------------------------------------------
};

// Creates a graph from a given input file
Graph createGraphFromFile(string filename);

Graph createGraphFromOutput();
