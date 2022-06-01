#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "graph.h"

/*
void manel(){
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

    cout << "\n Max capacidade multiple solutions:" << ld.graph.max_capacity_multiple_solutions(1,s);
    vetor =  ld.graph.get_path_multiple_solutions(1,s);

    for(auto& sol: vetor){
        cout << "\nPath: ";
        for(auto& nodo: sol){
            cout << nodo << " ";
        }
    }

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






}
*/
enum numberSelection {SIZE, INCREMENT};

int number_selection_menu(numberSelection choice) {
    int input;

    switch(choice) {
        case SIZE:
            cout << "Input a group size: ";
            break;
        case INCREMENT:
            cout << "Input the increase in group size: ";
            break;
    }

    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return input;
}

Graph graph_selection_menu(vector<Graph> graphs) {
    int input;

    cout << "Choose which graph to use (1-10): ";

    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return graphs[input-1];
}

void task1_menu(Graph graph) {
    char input;

    cout << setfill('-') << setw(20) << "" << "TASK 1" << setw(20) << "" << endl;
    cout << "1. Maximize group size" << endl;
    cout << "2. Maximize group size and minimize stop overs" << endl;
    cout << "Choose which sub-task to run (0 to return): ";

    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (input) {
    case '0':
        return;
    case '1':
        break;
    case '2':
        break;
    default:
        cout << "Invalid input" << endl;
        break;
    }

    return;
}

void task2_menu(Graph graph) {
    char input;

    cout << setfill('-') << setw(20) << "" << "TASK 2" << setw(20) << "" << endl;
    cout << "1. Determine path for a group of size 'n'" << endl;
    cout << "2. Change path for a group of size 'n' to increase to a size 'm'" << endl;
    cout << "3. Determine maximum possible group size and their path" << endl;
    cout << "4. Calculate when group meets at destination" << endl;
    cout << "5. Determine maximum wait times between the group" << endl;
    cout << "Choose which sub-task to run (0 to return): ";

    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (input) {
        case '0':
            return;
        case '1':
            graph.calculatePathForGroup(number_selection_menu(SIZE));
            graph.printOutput();
            break;
        case '2':
            graph.calculatePathsForGroupIncrease(number_selection_menu(INCREMENT), number_selection_menu(SIZE));
            break;
        case '3':
            graph.getMaxFlow();
            break;
        case '4':
            break;
        case '5':
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        return;
    }
}

int main() {
    vector<Graph> graphs;

    for(int i = 1; i <= 10; i++) {
        ostringstream filename;
        filename << setfill('0') << setw(2) << i;
        graphs.push_back(createGraphFromFile("../Tests_B/in" + filename.str() + "_b.txt"));
    }
    graphs.push_back(createGraphFromFile("../Tests_B/intSlide3.txt"));
    char input;
    do {
        cout << "Choose which task to run (1 or 2, 0 to exit): ";

        cin >> input;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (input) {
        case '0':
            return 0;
            break;
        case '1':
            task1_menu(graph_selection_menu(graphs));
            break;
        case '2':
            task2_menu(graph_selection_menu(graphs));
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    } while (true);
    return 0;
}
