#include <iostream>

#include "../graph.h"

using namespace std;

int main() {
    digraph<int> g;
    g.add_edge(0, 4);
    g.add_edge(1, 3);
    g.add_edge(2, 0);
    g.add_edge(3, 2);
    g.add_edge(4, 1);
    g.add_edge(4, 2);
    g.add_edge(5, 6);
    g.add_edge(6, 8);
    g.add_edge(7, 5);
    g.add_edge(7, 6);
    g.add_edge(8, 7);

    cout << "The number of strongly connected component is " << g.number_of_SCCs() << "\n";
    cout << "The Strongly Connected components are: "
         << "\n";
    vector<vector<int>> V1 = g.SCCs();
    for (auto i : V1) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << "\n";
    }
    return 0;
}