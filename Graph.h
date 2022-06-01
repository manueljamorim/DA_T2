#include <list>
#include <vector>


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
        int es; //earliest start
        int grauE;
        vector<int> pred_v;
    };

    int n; // Graph size (vertices are numbered from 1 to n)
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
    list<int> get_path(int a, int b);

    int max_capacity(int a, int b);

    int min_transbordos(int a, int b);

    int max_capacity_multiple_solutions(int a, int b);

    list<list<int>> get_path_multiple_solutions(int a, int b);

    int recursive(int a, int current);
// ------------------------------------------------------


// ----------------- Task 2 Functions -------------------
    // 2.1
    bool calculatePathForGroup(int size);

    // 2.2
    void calculatePathsForGroupIncrease(int increment, int startSize);
    void printChanges(Graph graph1, Graph graph2);

    // 2.3
    int getMaxFlow(); // grafo para file

    int bfs(ofstream& output, int& maxSize);

    int remainingCapacity(Edge e);
    
    bool isResidual(Edge e);

    void augmentEdge(Edge& e, int limit);

    void execute();

    bool solve(int maxSize = INT_MAX);

    void printOutput();

// ------------------------------------------------------

//-------------Task 2+ Functions--------------------------
//2.4


    double task2_4solver();
};



// Creates a graph from a given input file
Graph createGraphFromFile(string filename);

Graph createGraphFromOutput(); // este

