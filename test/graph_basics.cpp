#include <iostream>

#include "../graph.h"

using namespace std;

int main() {
    wdigraph<int> g;

    g.add_edge(1, 0, 5);
    g.add_edge(1, 2, 3);
    g.add_edge(2, 3, 8);
    g.add_edge(3, 1, 2);
    g.add_edge(3, 0, 3);
    g.add_edge(0, 3);

    cout << "The in degree of 3 is " << g.in_degree(3) << "\n";
    cout << "The out degree of 3 is " << g.out_degree(3) << "\n";
    cout << "The number of edges in g are " << g.number_of_edges << "\n";
    cout << "The number of nodes in g are " << g.number_of_nodes() << "\n\n";

    g.remove_edge(1, 2);

    cout << "The in degree of 3 is " << g.in_degree(3) << "\n";
    cout << "The out degree of 3 is " << g.out_degree(3) << "\n";
    cout << "The number of edges in g are " << g.number_of_edges << "\n";
    cout << "The number of nodes in g are " << g.number_of_nodes() << "\n\n";

    g.remove_node(3);

    cout << "The in degree of 3 is " << g.in_degree(3) << "\n";
    cout << "The out degree of 3 is " << g.out_degree(3) << "\n";
    cout << "The number of edges in g are " << g.number_of_edges << "\n";
    cout << "The number of nodes in g are " << g.number_of_nodes() << "\n\n";

    g.clear();

    cout << "The in degree of 3 is " << g.in_degree(3) << "\n";
    cout << "The out degree of 3 is " << g.out_degree(3) << "\n";
    cout << "The number of edges in g are " << g.number_of_edges << "\n";
    cout << "The number of nodes in g are " << g.number_of_nodes() << "\n";
    return 0;
}