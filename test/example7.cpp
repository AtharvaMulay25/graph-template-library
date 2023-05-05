#include <iostream>

#include "../graph.h"

using namespace std;

int main() {
    wgraph<char> g;
    g.add_edge('A', 'B', 4);
    g.add_edge('B', 'D', 9);
    g.add_edge('D', 'F', 2);
    g.add_edge('F', 'E', 6);
    g.add_edge('E', 'C', 3);
    g.add_edge('C', 'A', 5);
    g.add_edge('B', 'C', 11);
    g.add_edge('E', 'D', 13);
    g.add_edge('E', 'B', 7);

    cout << "By Dijkshtra's Algorithm ..."
         << "\n";

    map<char, int> V = g.dijkstra('A');
    cout << "Shortest distance from vertex 'A' to all other nodes: "
         << "\n";
    for (auto it : V) {
        cout << it.first << ": " << it.second << "\n";
    }

    vector<char> V1 = g.path('A', 'F');
    cout << "Shortest path from 'A' to 'F' is: ";
    for (auto it : V1) {
        cout << it << " ";
    }
    cout << "\n";
    return 0;
}