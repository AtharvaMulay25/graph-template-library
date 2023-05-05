#include <iostream>

#include "../graph.h"

using namespace std;

int main() {
    graph<int> g;
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(0, 4);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 1);

    cout << "The Adjacency List is: "
         << "\n";

    for (auto it : g.adj) {
        cout << it.first << ": ";
        for (auto i : it.second) {
            cout << i << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    if (g.is_bipartite()) {
        cout << "The Graph is Bipartite"
             << "\n";
    } else {
        cout << "The Graph is not Bipartite"
             << "\n";
    }

    g.remove_edge(4, 1);

    cout << "The Adjacency List after removing edge between 4 and 1 is: "
         << "\n";

    for (auto it : g.adj) {
        cout << it.first << ": ";
        for (auto i : it.second) {
            cout << i << " ";
        }
        cout << "\n";
    }

    g.remove_node(4);
    cout << "\n";
    cout << "The Adjacency List after removing node 4 is: "
         << "\n";

    for (auto it : g.adj) {
        cout << it.first << ": ";
        for (auto i : it.second) {
            cout << i << " ";
        }
        cout << "\n";
    }

    if (g.is_bipartite()) {
        cout << "The Graph is Bipartite"
             << "\n";
    } else {
        cout << "The Graph is not Bipartite"
             << "\n";
    }
    return 0;
}