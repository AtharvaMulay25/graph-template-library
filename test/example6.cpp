#include <iostream>

#include "../graph.h"

using namespace std;

int main() {
    wdigraph<int> g;
    g.add_edge(0, 1, -5);
    g.add_edge(0, 3, 3);
    g.add_edge(0, 2, 2);
    g.add_edge(2, 3, 1);
    g.add_edge(1, 2, 4);

    cout << "By Bellman Ford Algorithm ..."
         << "\n";

    vector<vector<int>> V = g.bellman_ford();
    cout << "Shortest distance from all nodes to all other nodes: "
         << "\n";

    for (auto i : g.adj) {
        cout << i.first << " ";
    }
    cout << "\n";

    auto it = g.adj.begin();
    for (auto i : V) {
        cout << it->first << " ";
        for (auto j : i) {
            if (j == INT_MAX) {
                cout << "∞ ";
            } else {
                cout << j << " ";
            }
        }
        cout << "\n";
        it++;
    }
    return 0;
}