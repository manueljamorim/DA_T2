#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "Graph.h"

void max_capacity(Graph graph){
    int s = graph.getN();
    cout << "\n1.1 Max capacidade: " << graph.max_capacity(1,s);
    vector<int> lista = graph.get_path(1,s);
    cout << "\nPath: ";
    for(int i=0; i<lista.size() ;i++){
        cout << lista[i];
        if(i!=lista.size()-1){
            cout << "-->";
        }
    }
    cout << "\n\n";
}
void max_capacity_min_transbordo(Graph graph){
    int s = graph.getN();

    cout << "\n1.2 Max capacidade & min transbordos solution: ";
    set<vector<int>> sol_set = graph.multi_objective_solutions(1,s);
    for(auto& sol: sol_set){
        cout << "\nPath: ";

        int cap = graph.calc_capacity(sol);
        int trans = sol.size()-1;

        for(int i=0; i<sol.size() ;i++){
            cout << sol[i];
            if(i!=sol.size()-1){
                cout << "-->";
            }
        }

        cout << "\t\t Cap: " << cap << "  Trans: " << trans;
    }
    cout << "\n\n";
}

/*
void teste(Graph graph){
    int s = graph.getN();


    cout << "\n Min transbordos:" << graph.min_transbordos_multiple_solutions(1,s);
    vector<vector<int>> vetor = graph.get_path_multiple_solutions(1,s);

    for(auto& sol: vetor){
        cout << "\nPath: ";
        for(auto& nodo: sol){
            cout << nodo << " ";
        }
    }

    cout << "\n Max capacidade multiple solutions:" << graph.max_capacity_multiple_solutions(1,s);
    vetor =  graph.get_path_multiple_solutions(1,s);

    for(auto& sol: vetor){
        cout << "\nPath: ";
        for(auto& nodo: sol){
            cout << nodo << " ";
        }
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
        max_capacity(graph);
        break;
    case '2':
        max_capacity_min_transbordo(graph);
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

    for (int i = 1; i <= 10; i++) {
        ostringstream filename;
        filename << setfill('0') << setw(2) << i;
        graphs.push_back(createGraphFromFile("../Tests_B/in" + filename.str() + "_b.txt"));
    }
    graphs.push_back(createGraphFromFile("../Tests_B/intSlide3.txt"));

    max_capacity_min_transbordo(graphs[9-1]);
}
/*
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
*/