//
// Created by Manuel Amorim on 27/05/2022.
//

#include "Graph.h"
#include "minHeap.h"
#include "maxHeap.h"
#include <queue>

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

//1.2
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

}

list<list<int>> Graph::get_path_multiple_solutions(int a, int b) {
    list<list<int>> paths;

    for(int i =1;i<nodes.size();i++){
        nodes[i].visited = 0;
    }


}



