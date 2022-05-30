//
// Created by Manuel Amorim on 27/05/2022.
//

#include "Graph.h"
#include "minHeap.h"
#include "maxHeap.h"


// a) Distância entre dois nós
/*
int Graph::dijkstra_distance(int a, int b) {
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
            if(heap.hasKey(edge.dest) && nodes[min].dist+ edge.weight<nodes[edge.dest].dist){
                nodes[edge.dest].pred = min;
                nodes[edge.dest].dist = nodes[min].dist + edge.weight;
                heap.decreaseKey(edge.dest,nodes[min].dist + edge.weight);
            }
        }
    }

    if(nodes[b].dist==INT32_MAX) return -1;
    return nodes[b].dist;
}
*/

//1.1
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





