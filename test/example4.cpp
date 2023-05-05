#include <iostream>

#include "../graph.h"

using namespace std;

int main() {
    digraph<int> g;
    g.add_edge(1, 3);
    g.add_edge(2, 0);
    g.add_edge(3, 2);
    g.add_edge(4, 0);
    g.add_edge(4, 1);
    g.add_edge(4, 2);

    vector<int> V = g.topological_sort();
    cout << "The Topological sort is: ";
    for (auto it : V) {
        cout << it << " ";
    }
    cout << "\n";
    return 0;
}