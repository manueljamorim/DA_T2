#include <iostream>
#include "LoadData.h"
#include "maxHeap.h"


int main() {
    LoadData ld;
    ld.load();

    int s = ld.graph.nodes.size()-1;

    cout << "\n1.1 Max capacidade:" << ld.graph.max_capacity(1,s);
    vector<int> lista = ld.graph.get_path(1,s);
    cout << "\nPath: ";
    for(int value: lista){
        cout << value << " ";
    }

    cout << "\n Min transbordos:" << ld.graph.min_transbordos_multiple_solutions(1,s);
    vector<vector<int>> vetor = ld.graph.get_path_multiple_solutions(1,s);

    for(auto& sol: vetor){
        cout << "\nPath: ";
        for(auto& nodo: sol){
            cout << nodo << " ";
        }
    }

    /*
    cout << "\n Max capacidade multiple solutions:" << ld.graph.max_capacity_multiple_solutions(1,s);
    vetor =  ld.graph.get_path_multiple_solutions(1,s);

    for(auto& sol: vetor){
        cout << "\nPath: ";
        for(auto& nodo: sol){
            cout << nodo << " ";
        }
    }
     */

    cout << "\n1.2 Max capacidade & min transbordos solution:";
    set<vector<int>> sol_set = ld.graph.multi_objective_solutions(1,s);
    for(auto& sol: sol_set){
        cout << "\nPath: ";

        int cap = ld.graph.calc_capacity(sol);
        int trans = sol.size()-1;

        for(auto& nodo: sol){
            cout << nodo << " ";
        }

        cout << "\t Cap: " << cap << "  Trans: " << trans;
    }

    return 0;
}
