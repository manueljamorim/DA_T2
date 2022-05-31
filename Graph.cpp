#include <queue>
#include <climits>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "minHeap.h"
#include "maxHeap.h"


// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : s(1), t(num), n(num), hasDir(dir), nodes(num+1) {}

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

    int src, dest, cap, flow, dur;
    for(int i = 0; i < n_edges; i++) {
        getline(file, line);
        istringstream(line) >> src >> dest >> cap >> dur;
        graph.addEdge(src, dest, cap, dur);
        //graph.addEdge(dest, src, 0, dur); Residual edge
    }


    file.close();

    return graph;
}

Graph createGraphFromOutput() {
    string line;

    ifstream file("../Tests_B/output.txt");

    if(!file.is_open()) {
        cerr << "Unable to open file" << endl;
    }
    
    int n_nodes, n_edges;
    getline(file, line);
    istringstream(line) >> n_nodes >> n_edges;
    Graph graph = Graph(n_nodes, true);

    while(!file.eof()) {
        int src, dest, flow, dur;
        for(int i = 0; i < n_edges; i++) {
            getline(file, line);
            istringstream(line) >> src >> dest >> flow >> dur;
            graph.addEdge(src, dest, 0, dur, flow, true);
        }

        getline(file, line);
        istringstream(line) >> n_nodes >> n_edges;
    }
    file.close();

    return graph;
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int capacity, int duration, int flow, bool fromOutput) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    if(fromOutput) {
        for(Edge& edge : this->nodes[src].adj) {
            if(edge.src == src && edge.dest == dest) {
                edge.flow = flow;
                return;
            }
        } 
    } 

    this->nodes[src].adj.push_back({src, dest, capacity, duration, flow});
    if (!hasDir) this->nodes[dest].adj.push_back({dest, src, capacity, duration, flow});


}

// ----------------- Task 1 Functions -------------------
int Graph::max_capacity(int a, int b){
    MaxHeap<int,int> heap(nodes.size(),-1);

    for(int i =1;i<nodes.size();i++){
        if(i==a){
            nodes[a].cap = INT32_MAX;
        }else{
            nodes[i].cap = 0;
        }
        nodes[i].pred = -1;

        heap.insert(i,nodes[i].cap);
    }

    while(heap.getSize()!=0){
        int max = heap.removeMax();
        for(auto edge : nodes[max].adj){
            if(heap.hasKey(edge.dest) && min(nodes[max].cap,edge.capacity)>nodes[edge.dest].cap){
                nodes[edge.dest].pred = max;
                nodes[edge.dest].cap = min(nodes[max].cap,edge.capacity);
                heap.increaseKey(edge.dest,nodes[edge.dest].cap);
            }
        }
    }

    if(nodes[b].cap==INT32_MAX) return -1;
    return nodes[b].cap;

}


vector<int> Graph::get_path(int a, int b) {
    vector<int> path;

    int predessor = b;
    path.insert(path.begin(),b);
    while(predessor!=a){
        predessor = nodes[predessor].pred;
        path.insert(path.begin(),predessor);
    }
    return path;
}

//1.2
int Graph::min_transbordos_multiple_solutions(int a, int b){

    MinHeap<int,int> heap(nodes.size(),-1);

    for(int i =1;i<nodes.size();i++){
        if(i==a){
            nodes[a].dist = 0;
        }else{
            nodes[i].dist = INT32_MAX;
        }
        nodes[i].pred = -1;
        nodes[i].pred_v.clear();
        heap.insert(i,nodes[i].dist);
    }

    while(heap.getSize()!=0){
        int min = heap.removeMin();
        for(auto edge : nodes[min].adj){
            if(nodes[min].dist+ 1==nodes[edge.dest].dist){
                nodes[edge.dest].pred_v.push_back(min);
            }else if(nodes[min].dist+ 1<nodes[edge.dest].dist){
                nodes[edge.dest].pred_v.clear();
                nodes[edge.dest].pred_v.push_back(min);
                nodes[edge.dest].dist = nodes[min].dist + 1;
                heap.decreaseKey(edge.dest,nodes[min].dist + 1);
            }

        }
    }

    if(nodes[b].dist==INT32_MAX) return -1;
    return nodes[b].dist;

}

int Graph::max_capacity_multiple_solutions(int a, int b) {
    MaxHeap<int,int> heap(nodes.size(),-1);

    for(int i =1;i<nodes.size();i++){
        if(i==a){
            nodes[a].cap = INT32_MAX;
        }else{
            nodes[i].cap = 0;
        }
        nodes[i].pred = -1;
        nodes[i].pred_v.clear();

        heap.insert(i,nodes[i].cap);
    }

    while(heap.getSize()!=0){
        int max = heap.removeMax();
        for(auto edge : nodes[max].adj){

            if(min(nodes[max].cap,edge.capacity)==nodes[edge.dest].cap){
                nodes[edge.dest].pred_v.push_back(max);
            }else if(min(nodes[max].cap,edge.capacity)>nodes[edge.dest].cap){
                nodes[edge.dest].pred_v.clear();
                nodes[edge.dest].pred_v.push_back(max);
                nodes[edge.dest].cap = min(nodes[max].cap,edge.capacity);
                heap.increaseKey(edge.dest,nodes[edge.dest].cap);
            }

        }
    }

    if(nodes[b].cap==INT32_MAX) return -1;
    return nodes[b].cap;

}

void Graph::recursive(int a, int b, vector<int> path, vector<vector<int>>& result){
    if(b==a){
        path.insert(path.begin(),b);
        result.push_back(path);
        return;
    }else{
        path.insert(path.begin(),b);
        for(int prev: nodes[b].pred_v){
            recursive(a, prev,path, result);
        }
        return;
    }
}
vector<vector<int>> Graph::get_path_multiple_solutions(int a, int b) {
    vector<vector<int>> paths;
    vector<int> path;

    recursive(a, b, path, paths);

    return paths;
}


int Graph::calc_capacity(vector<int> a){
    int c = INT32_MAX;

    for(int i =0; i<a.size()-1;i++){
        int origin = a[i];
        int destiny = a[i+1];

        int cap = 0;
        for(auto& edge: nodes[origin].adj){
            if(edge.dest==destiny && edge.capacity>cap){
                cap= edge.capacity; // if there is more than one edge from a to b then chooses the one with bigger capacity
            }
        }
        if(cap<c){
            c = cap;
        }
    }
    return c;
}

set<vector<int>> Graph::multi_objective_solutions(int a, int b){
    min_transbordos_multiple_solutions(a,b);
    vector<vector<int>> sol_transbordo = get_path_multiple_solutions(a,b);

    max_capacity_multiple_solutions(a,b);
    vector<vector<int>> sol_capacity = get_path_multiple_solutions(a,b);

    //Solucoes de maxima capacidade com menos transbordos
    sort(sol_capacity.begin(),sol_capacity.end(),[] (const vector<int>& a, const vector<int>& b) {
        return a.size() < b.size();
    });
    if(!sol_capacity.empty()){
        while(sol_capacity.back().size()>sol_capacity[0].size()){
            sol_capacity.pop_back();
        }
    }

    //Solucoes de  transbordos minimos com maior capacidade
    sort(sol_transbordo.begin(),sol_transbordo.end(),[this] (const vector<int>& a, const vector<int>& b) {
        return this->calc_capacity(a)>this->calc_capacity(b);
    });
    if(!sol_transbordo.empty()){
        while(calc_capacity(sol_transbordo.back())<calc_capacity(sol_transbordo[0])){
            sol_transbordo.pop_back();
        }
    }

    set<vector<int>> solutions;
    for(auto& sol: sol_capacity){
        solutions.insert(sol);
    }
    for(auto& sol: sol_transbordo){
        solutions.insert(sol);
    }

    return solutions;

}
// ------------------------------------------------------


// ----------------- Task 2 Functions -------------------
bool Graph::calculatePathForGroup(int size) {
    bool result = solve(size);
    if(!result)
        cout << "There's no possible path for a group of size " << size << endl;

    return result;

}

void Graph::calculatePathsForGroupIncrease(int increment, int startSize) {
    bool result = calculatePathForGroup(startSize);
    if(!result)
        return;
    printOutput();
    Graph resultGraph1 = createGraphFromOutput();

    this->maxFlow = 0;
    for(int v = 1; v <= n; v++) {
        for(Edge& e : nodes[v].adj)
        e.flow = 0;
    }
    
    result = calculatePathForGroup(startSize + increment);
    if(!result)
        return;
    printOutput();
    Graph resultGraph2 = createGraphFromOutput();

    printChanges(resultGraph1, resultGraph2);
}

int Graph::getMaxFlow() {
    solve();
    cout << "Maximum group size is: " << maxFlow << endl;
    printOutput();
    return maxFlow;
}

bool Graph::solve(int maxSize) {
    int flow;
    ofstream output("../Tests_B/output.txt");

    do {
        for(int v = 1; v <= n; v++) {
            nodes[v].visited = false;
            nodes[v].parent = INT_MAX;
        }
        flow = bfs(output, maxSize);
        maxFlow += flow;
    } while(flow != 0 && maxSize > 0);

    output.close();

    if(maxSize > 0)
        return false;

    return true;
}

int Graph::remainingCapacity(Edge e) {
    return e.capacity - e.flow;
}

bool Graph::isResidual(Edge e) {
    return e.capacity == 0;
}

void Graph::augmentEdge(Edge& e, int limit) {
    e.flow += limit;
}

int Graph::bfs(ofstream& output, int& maxSize) {
    queue<int> q;
    q.push(s);
    nodes[s].visited = true;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(u == t) break;
        for(Edge& e : nodes[u].adj) {
            int w = e.dest;
            if(remainingCapacity(e) > 0 && !nodes[w].visited) {
                nodes[w].visited = true;
                nodes[w].parent = u;
                q.push(w);
            }
        }
    }

    if(!nodes[t].visited) return 0;

    // Retrieve path nodes and edges traversed and write to output file
    vector<Edge> edge_path;
    int num_nodes = 1;
    for(int i = t; i != s; i = nodes[i].parent) {
        num_nodes++;
    }

    for(int i = t; i != s; i = nodes[i].parent) {
        for(Edge e : nodes[nodes[i].parent].adj) {
            if(e.dest == i) {
                edge_path.push_back(e);
            }
        }
    }

    int limit = INT_MAX / 2;
    for(Edge edge : edge_path) {
        limit = min(limit, remainingCapacity(edge));
    }

    if(maxSize != INT_MAX) {
        if(limit >= maxSize)
            limit = maxSize;

        maxSize -= limit;
        if(maxSize < 0)
            maxSize = 0;
    }

    for(Edge edge : edge_path) {
        augmentEdge(edge, limit);
        for(int i = 0; i < nodes[edge.src].adj.size(); i++) {
            if(nodes[edge.src].adj[i].src == edge.src && nodes[edge.src].adj[i].dest == edge.dest)
                nodes[edge.src].adj[i] = edge;
        }
    }

    
    output << t << " " << num_nodes - 1 << endl;
    for(int i = t; i != s; i = nodes[i].parent) {
        for(Edge e : nodes[nodes[i].parent].adj) {
            if(e.dest == i) {
                output << e.src << " " << e.dest << " " << e.flow << " " << e.duration << endl;
            }
        }
    }

    return limit;
}

void Graph::printOutput() {
    Graph graph = createGraphFromOutput();

    for(int v = 1; v <= graph.n; v++) graph.nodes[v].visited = false;

    queue<int> q;
    q.push(graph.s);
    nodes[graph.s].visited = true;

    cout << "Starting from node 1 with a group of " << maxFlow << endl;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(Edge& e : graph.nodes[u].adj) {
            int w = e.dest;
            if(!graph.nodes[w].visited) {
                graph.nodes[w].visited = true;
                q.push(w);
            }
            cout << "\tA group of "<< e.flow << " move from node " << e.src << " to node " << e.dest << endl;
        }
    }
    cout << "Finishing in node " << graph.t << " with a group of " << maxFlow << endl;
}

void Graph::printChanges(Graph graph1, Graph graph2) {
    queue<int> q;
    q.push(graph2.s);
    nodes[graph2.s].visited = true;

    bool matched = false;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(Edge& e2 : graph2.nodes[u].adj) {
            for(Edge& e1 : graph1.nodes[u].adj) {
                if(e1.src == e2.src && e1.dest == e2.dest) {
                    matched = true;
                    if(e1.flow == e2.flow) {
                        cout << "Unchanged  -- " << "Node " << e1.src << " to " << e1.dest << " group size " << e1.flow << endl;
                    }
                    else {
                        cout << "Changed    -- " << "Node " << e1.src << " to " << e1.dest << " group size changed from " << e1.flow << " to " << e2.flow << endl;
                    }
                }
            }
            if(!matched)
                cout << "Added      -- " << "Node " << e2.src << " to " << e2.dest << " group size " << e2.flow << endl;
            matched = false;

            int w = e2.dest;
            if(!graph2.nodes[w].visited) {
                graph2.nodes[w].visited = true;
                q.push(w);
            }
        }
    }
}
// ------------------------------------------------------

