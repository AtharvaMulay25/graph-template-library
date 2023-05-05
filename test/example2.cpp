#include <iostream>

#include "../graph.h"

using namespace std;

int main() {
    graph<int> g;
    g.add_edge(0, 1);
    g.add_edge(0, 4);
    g.add_edge(0, 5);
    g.add_edge(1, 2);
    g.add_edge(1, 4);
    g.add_edge(2, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);
    g.add_edge(4, 5);
    g.add_edge(6, 7);
    g.add_edge(6, 8);

    g.add_node(9);

    vector<int> V1 = g.dfs(0);
    vector<int> V2 = g.bfs(0);
    cout << "The DFS Traversal is: ";
    for (auto it : V1) {
        cout << it << " ";
    }
    cout << "\n";

    cout << "The BFS Traversal is: ";
    for (auto it : V2) {
        cout << it << " ";
    }
    cout << "\n";

    if (g.cyclic()) {
        cout << "Graph has atleast one cycle"
             << "\n";
    } else {
        cout << "Graph doesn't have a cycle"
             << "\n";
    }
    return 0;
}