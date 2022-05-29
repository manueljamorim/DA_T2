#include <iostream>
#include "LoadData.h"
#include "maxHeap.h"


int main() {
    LoadData ld;
    ld.load();

    cout << "\n Max capacidade:" << ld.graph.max_capacity(1,4);
    list<int> lista = ld.graph.get_path(1,4);
    cout << "\nPath:\n";
    for(int value: lista){
        cout << value << endl;
    }

    cout << "\n Min transbordos:" << ld.graph.min_transbordos(1,4);
    lista = ld.graph.get_path(1,4);
    cout << "\nPath:\n";
    for(int value: lista){
        cout << value << endl;
    }

    cout << "\n Max capacidade multiple solutions:" << ld.graph.max_capacity_multiple_solutions(1,4);



    return 0;
}
