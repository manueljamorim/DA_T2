#include <queue>
#include <climits>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "minHeap.h"
#include "maxHeap.h"
#include <stack>



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

list<int> Graph::get_path(int a, int b) {
    list<int> path;

    int predessor = b;
    path.push_front(b);
    while(predessor!=a){
        predessor = nodes[predessor].pred;
        path.push_front(predessor);
    }
    return path;
}

int Graph::min_transbordos(int a, int b){
    MinHeap<int,int> heap(nodes.size(),-1);

    for(int i =1;i<nodes.size();i++){
        if(i==a){
            nodes[a].dist = 0;
        }else{
            nodes[i].dist = INT32_MAX;
        }
        nodes[i].pred = -1;
        heap.insert(i,nodes[i].dist);
    }

    while(heap.getSize()!=0){
        int min = heap.removeMin();
        for(auto edge : nodes[min].adj){
            if(heap.hasKey(edge.dest) && nodes[min].dist+ 1<nodes[edge.dest].dist){
                nodes[edge.dest].pred = min;
                nodes[edge.dest].dist = nodes[min].dist + 1;
                heap.decreaseKey(edge.dest,nodes[min].dist + 1);
            }
        }
    }

    if(nodes[b].dist==INT32_MAX) return -1;
    return nodes[b].dist - 1;

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

        heap.insert(i,nodes[i].cap);
    }

    while(heap.getSize()!=0){
        int max = heap.removeMax();
        for(auto edge : nodes[max].adj){
            if(heap.hasKey(edge.dest)){
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
    }

    if(nodes[b].cap==INT32_MAX) return -1;
    return nodes[b].cap;

}


int Graph::recursive(int a, int current){
    return 0;
}

list<list<int>> Graph::get_path_multiple_solutions(int a, int b) {
    list<list<int>> paths;

    for(int i =1;i<nodes.size();i++){
        nodes[i].visited = 0;
    }

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
// ----------------- Task 3 Functions -------------------

double Graph::task2_4solver(){ //


    double DurMin;

    solve(); // gera ficheiro com os encaminhamentos

    Graph aux_g = createGraphFromOutput(); // cria grafo a partir de um ficheiro

    stack<int> S;

    for(int i = 1 ; i <= aux_g.n; i++){ // iniciar EarliestStart e GrauE a 0 e dá reset aos pais
        aux_g.nodes[i].es = 0;
        aux_g.nodes[i].parent = -1;
        aux_g.nodes[i].grauE = 0;
    }



    for(int i = 1 ; i <= aux_g.n; i++) {
        for (int k = 0; k < aux_g.nodes[i].adj.size(); k++) {
            aux_g.nodes[nodes[i].adj[k].dest].grauE = aux_g.nodes[nodes[i].adj[k].dest].grauE + 1;

        }
    }

    for(int i=1; i <= aux_g.n ; i++){
        if(aux_g.nodes[i].grauE == 0){
            S.push(i);
        }
    }



    DurMin = -1;
    int vf = -1; //null
    int v;


    while(!S.empty()){
        v = S.top();

        S.pop();

            if( DurMin < aux_g.nodes[v].es){
                DurMin = aux_g.nodes[v].es;
                vf = v;
            }

        for(Edge& e : aux_g.nodes[v].adj) {
            int w = e.dest;


            if(aux_g.nodes[w].es < (aux_g.nodes[v].es + e.duration)){
                aux_g.nodes[w].es = aux_g.nodes[v].es + e.duration;
                aux_g.nodes[w].parent = v;
            }


                aux_g.nodes[w].grauE = aux_g.nodes[w].grauE - 1;
                if(aux_g.nodes[w].grauE == 0){
                    S.push(w);
                }
        }
    }


    return  DurMin;
}

void Graph::task2_5solver() {

    double DurMin;

    solve(); // gera ficheiro com os encaminhamentos

    Graph aux_g = createGraphFromOutput(); // cria grafo a partir de um ficheiro

    stack<int> S;

    for(int i = 1 ; i <= aux_g.n; i++){ // iniciar EarliestStart e GrauE a 0 e dá reset aos pais
        aux_g.nodes[i].es = 0;
        aux_g.nodes[i].parent = -1;
        aux_g.nodes[i].grauE = 0;
    }



    for(int i = 1 ; i <= aux_g.n; i++) {
        for (int k = 0; k < aux_g.nodes[i].adj.size(); k++) {
            aux_g.nodes[nodes[i].adj[k].dest].grauE = aux_g.nodes[nodes[i].adj[k].dest].grauE + 1;

        }
    }

    for(int i=1; i <= aux_g.n ; i++){
        if(aux_g.nodes[i].grauE == 0){
            S.push(i);
        }
    }



    DurMin = -1;
    int vf = -1; //null
    int v;


    while(!S.empty()){
        v = S.top();

        S.pop();

        if( DurMin < aux_g.nodes[v].es){
            DurMin = aux_g.nodes[v].es;
            vf = v;
        }

        for(Edge& e : aux_g.nodes[v].adj) {
            int w = e.dest;


            if(aux_g.nodes[w].es < (aux_g.nodes[v].es + e.duration)){
                aux_g.nodes[w].es = aux_g.nodes[v].es + e.duration;
                aux_g.nodes[w].parent = v;
            }


            aux_g.nodes[w].grauE = aux_g.nodes[w].grauE - 1;
            if(aux_g.nodes[w].grauE == 0){
                S.push(w);
            }
        }
    }

    int aux = INT_MAX;



   for(int i=1; i <= aux_g.n ;i++ ){
       for(int k=0; k < aux_g.nodes[i].adj.size();k++){

           aux_g.nodes[i].adj[k].fl = aux_g.nodes[aux_g.nodes[i].adj[k].dest].es - (aux_g.nodes[i].es + aux_g.nodes[i].adj[k].duration) ;

       }
   }


    for(int i=1; i <= aux_g.n ;i++ ){
        for(int k=0; k < aux_g.nodes[i].adj.size();k++){
            cout << "Folga livre: " << aux_g.nodes[i].adj[k].fl << "\n";
        }
    }

    for(size_t i=1; i <= aux_g.n; i++){

        for(Edge e : aux_g.nodes[i].adj){
            if(e.fl <= aux){
                aux = e.fl;
            }

        }

        if(aux > 0 && aux != INT_MAX){
            cout << "No: " << i << " com FL " << aux << '\n' ;
        }

        aux = INT_MAX;
    }

}





























// ------------------------------------------------------