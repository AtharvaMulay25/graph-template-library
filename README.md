# Graph-Template-Library

Defines container template classes to study graphs in C++

# Summary

- Graph template library to study graphs in C++

- Generic graph library

- Defines several container template classes

- Data structures for graphs, digraphs and weighted graphs

- Many standard graph algorithms

- Nodes can be arbitrary objects

# Example

Finds number of connected components in an undirected graph

```cpp
#include <iostream>
#include "graph.h"

int main() {
    graph<char> g;
    g.add_edge('a', 'b');
    g.add_edge('c', 'd');
    g.add_edge('d', 'e');
    g.add_edge('f', 'g');

    std::cout << "Number of connected components in g are " << g.number_of_connected_components() << "\n";
    return 0;
}
```

Output

```
Number of connected components in g are 3
```