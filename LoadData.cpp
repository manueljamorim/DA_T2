#include "LoadData.h"

using namespace std;

void LoadData::load(){

    string textLine;

    ifstream MyReadFile("../Tests/in01.txt");

    if(!MyReadFile.is_open()) {
        cout << "ERRO";
        return;
    }

    vector<string> parsed_string;
    int i =0;
    while (getline (MyReadFile, textLine)) {
        string del = " ";
        parsed_string = split(textLine,del);
        if(i==0){
            graph.n= stoi(parsed_string[0]);
            //first line
            for(int j=0;j<=stoi(parsed_string[0]);j++){
                graph.nodes.push_back(Graph::Node());
            }
            i++;
            continue;
        }
        Graph::Edge edge;

        edge.dest = stoi(parsed_string[1]);
        edge.capacity = stoi(parsed_string[2]);
        edge.duration = stoi(parsed_string[3]);

        graph.nodes[stoi(parsed_string[0])].adj.push_back(edge);
    }
    MyReadFile.close();
}

vector<string> LoadData::split(const string &s, const string &del) {
    vector<string> final;

    unsigned int start = 0;
    unsigned int end = s.find(del);
    while (end != -1) {
        final.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    final.push_back(s.substr(start, end - start));

    return final;
}
