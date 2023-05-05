#include <algorithm>
#include <climits>
#include <functional>
#include <map>
#include <queue>
#include <stack>
#include <vector>

template <typename T>
class graph {  // Class of unweighted undirected graph
   public:
    int number_of_edges = 0;          // number of edges stores the total edges in the graph
    std::map<T, std::vector<T>> adj;  // adj is the adjacency list of the graph

    // This function adds an isolated node in the graph
    void add_node(T u) {
        adj[u];
    }

    // This function adds an edge between given two vertices.
    void add_edge(T u, T v) {
        number_of_edges++;    // updating the number of edges
        adj[u].push_back(v);  // updating the adjacency list of v
        adj[v].push_back(u);  // updating the adjacency list of u
    }

    // It returns the total vertices present in the graph.
    int number_of_nodes() {
        return adj.size();
    }

    // This function removes a given vertex from the graph.
    void remove_node(T u) {
        if (adj.find(u) != adj.end()) {
            number_of_edges -= adj[u].size();  // removing all the edges connected to the given vertex
            for (auto i : adj[u]) {            // removing the given vertex from the adjacency list of its neighbours
                adj[i].erase(find(adj[i].begin(), adj[i].end(), u));
            }
            adj.erase(u);  // Finally removing the given vertex
        }
    }

    // This function removes a given edge between two vertices.
    void remove_edge(T u, T v) {
        if (adj.find(u) != adj.end()) {  // if vertex u is present in the graph
            auto it = find(adj[u].begin(), adj[u].end(), v);
            if (it != adj[u].end()) {                                 // if vertex v is also present in the graph
                adj[u].erase(it);                                     // then, removing v from adjacency list of u
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));  // and removing u from adjacency list of v
                number_of_edges--;                                    // finally updating the number of edges.
            }
        }
    }

    // It just returns the degree of a given vertex.
    int degree(T u) {
        // return adj[u].size();
        return adj.find(u) != adj.end() ? adj[u].size() : -1;
    }

    // It clears the entire graph i.e. it removes all vertices.
    void clear() {
        number_of_edges = 0;
        adj.clear();
    }

    // It performs Breadth First Search traversal on given graph starting from given source vertex s
    std::vector<T> bfs(T s) {
        std::vector<T> bfs;     // It stores the BFS traversal of the given graph
        std::map<T, bool> vis;  // vis map marks visited vertices as true
        vis[s] = true;          // marking source vertex s as visited
        std::queue<T> q;        // q is the exploration queue
        q.push(s);              // pushing the source vertex s in the queue
        while (!q.empty()) {
            T v = q.front();
            q.pop();                 // pop the front vertex of the queue
            bfs.push_back(v);        // and pushes it in the BFS traversal
            for (auto u : adj[v]) {  // pushing all the non-visited neighbours of the popped vertex in the queue
                if (!vis[u]) {
                    q.push(u);
                    vis[u] = true;  // and marking them as visited
                }
            }
        }
        return bfs;  // finally return the BFS traversal
    }

    // It performs Depth First Search traversal on given graph starting from given source vertex u
    std::vector<T> dfs(T u) {
        std::map<T, bool> vis;  // vis map marks visited vertices as true
        std::vector<T> dfs;     // It stores the DFS traversal of the given graph
        vis[u] = true;          // marking source vertex u as visited
        std::stack<T> s;        // s is the exploration stack
        s.push(u);              // pushing the source vertex u in the stack
        while (!s.empty()) {
            T v = s.top();
            dfs.push_back(v);        // and pushes it in the DFS traversal
            s.pop();                 // pop the top vertex of the stack
            for (auto u : adj[v]) {  // pushing all the non-visited neighbours of the popped vertex in the stack
                if (!vis[u]) {
                    s.push(u);
                    vis[u] = true;  // and marking them as visited
                }
            }
        }
        return dfs;  // finally return the DFS traversal
    }

    // This function returns the number of connected components in the graph using dfs traversal.
    int number_of_connected_components() {
        int n(0);                                             // n stores the number of connected components in the graph
        std::map<T, bool> vis;                                // vis map marks visited vertices as true
        std::stack<T> s;                                      // s is the exploration stack
        for (auto it = adj.begin(); it != adj.end(); it++) {  // traversing over all the vertices
            if (!vis[it->first]) {
                vis[it->first] = true;  // if current vertex in not visited, then mark it as visited and start dfs from this vertex as source
                n++;
                s.push(it->first);
                while (!s.empty()) {
                    T v = s.top();
                    s.pop();
                    for (auto u : adj[v]) {
                        if (!vis[u]) {
                            s.push(u);
                            vis[u] = true;
                        }
                    }
                }
            }
        }
        return n;  // finally return the number of connected components
    }

    // This function returns true if the graph is cyclic
    bool cyclic() {
        std::map<T, bool> vis;
        std::map<T, T> p;

        // Performs DFS returns true if it encounters a node that has already been visited
        std::function<bool(T, T)> dfs = [&](T v, T _p) {
            vis[v] = true;
            for (auto i : adj[v]) {
                if (i == _p) {
                    continue;
                }
                if (vis[i]) {
                    return true;
                }
                p[i] = v;
                return dfs(i, v);
            }
            return false;
        };

        // Perform DFS on all unvisited nodes and return true if a cycle is found
        for (auto i : adj) {
            if (!vis[i.first] && dfs(i.first, p[i.first])) {
                return true;
            }
        }
        return false;
    }

    // Uses BFS and two-colourable property of bipartite graph
    bool is_bipartite() {
        // Flag variable stores the final result
        bool flag = true;
        std::map<T, int> side;
        for (auto i : adj) {
            side[i.first] = -1;
        }
        std::queue<T> q;

        // For all vertices if not visited yet perform BFS
        for (auto i : adj) {
            if (side[i.first] == -1) {
                q.push(i.first);
                side[i.first] = 0;
                while (!q.empty()) {
                    T v = q.front();
                    q.pop();
                    for (auto u : adj[v]) {
                        // Assign the opposite colours to all unvisited neighbours
                        if (side[u] == -1) {
                            side[u] = side[v] ^ 1;
                            q.push(u);
                        } else {
                            // If the neighbour is already visited check whether it has the opposite colour or not
                            flag &= side[u] != side[v];
                        }
                    }
                }
            }
        }
        // Finally return flag
        return flag;
    }
};

template <typename T>
class digraph {  // Class of directed graph
    // Standard dfs function used for getting the finishing time of all the vertices a
    void dfs(T node, std::stack<T> &st, std::map<T, bool> &vis, std::map<T, std::vector<T>> &adj) {
        vis[node] = true;  // marking current vertex as visited
        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfs(it, st, vis, adj);
            }
        }
        st.push(node);  // and storing their time in the stack
    }

    // Standard dfs function applied on the transpose graph of the original graph for getting the SCCs of the graph
    void revDfs(int node, std::map<T, bool> &vis, std::map<T, std::vector<T>> &transpose, std::vector<T> &SCC) {
        SCC.push_back(node);
        vis[node] = true;
        for (auto it : transpose[node]) {
            if (!vis[it]) {
                revDfs(it, vis, transpose, SCC);
            }
        }
    }

   public:
    int number_of_edges = 0;          // number of edges stores the total edges in the directed graph
    std::map<T, std::vector<T>> adj;  // adj is the adjacency list of the directed graph
    std::map<T, int> _in_degree;      // _in_degree stores the indegree of a given vertex

    // This function adds an isolated node in the directed graph
    void add_node(T u) {
        adj[u];
    }

    // This function adds a directed edge from vertex u to vertex v.
    void add_edge(T u, T v) {
        number_of_edges++;    // updating the number of edges
        adj[u].push_back(v);  // updating the adjacency list of u
        adj[v];               // forming empty adjacency list for v
        _in_degree[v]++;      // updating indegree of v
    }

    // It returns the total vertices present in the directed graph.
    int number_of_nodes() {
        return adj.size();
    }

    // out_degree stores the outdegree of a given vertex
    int out_degree(T u) {
        // return adj[u].size();
        return adj.find(u) != adj.end() ? adj[u].size() : -1;
    }

    int in_degree(T u) {
        return adj.find(u) != adj.end() ? _in_degree[u] : -1;
    }

    // This function removes a given vertex from the graph.
    void remove_node(T u) {
        if (adj.find(u) != adj.end()) {
            for (auto &i : adj) {
                if (i.first == u) {
                    number_of_edges -= i.second.size();  // removing all the edges connected to the given vertex
                    for (auto j : i.second) {
                        _in_degree[j]--;  // updating the indegree of its neighbours
                    }
                    continue;
                }

                auto it = find(i.second.begin(), i.second.end(), u);
                if (it != i.second.end()) {
                    i.second.erase(it);  // removing the given vertex from the adjacency list of its neighbours
                    number_of_edges--;   // again updating the number of edges
                }
            }
            adj.erase(u);         // removing the given vertex from the adjacency list
            _in_degree.erase(u);  // and then updating ther indegree of the removed vertex
        }
    }

    // This function removes a given edge between two vertices.
    void remove_edge(T u, T v) {
        if (adj.find(u) != adj.end()) {  // if vertex u is present in the graph
            auto it = find(adj[u].begin(), adj[u].end(), v);
            if (it != adj[u].end()) {  // if vertex v is also present in the graph
                adj[u].erase(it);      // then, removing v from adjacency list of u
                _in_degree[v]--;       // updating the indegree of v
                number_of_edges--;     // finally updating the number of edges.
            }
        }
    }

    // It clears the entire directed graph i.e. it removes all vertices.
    void clear() {
        number_of_edges = 0;
        _in_degree.clear();
        adj.clear();
    }

    // It performs Breadth First Search traversal on given graph starting from given source vertex s
    std::vector<T> bfs(T s) {
        std::vector<T> bfs;     // It stores the BFS traversal of the given graph
        std::map<T, bool> vis;  // vis map marks visited vertices as true
        vis[s] = true;          // marking source vertex s as visited
        std::queue<T> q;        // q is the exploration queue
        q.push(s);              // pushing the source vertex s in the queue
        while (!q.empty()) {
            T v = q.front();
            q.pop();                 // pop the front vertex of the queue
            bfs.push_back(v);        // and pushes it in the BFS traversal
            for (auto u : adj[v]) {  // pushing all the non-visited neighbours of the popped vertex in the queue
                if (!vis[u]) {
                    q.push(u);
                    vis[u] = true;  // and marking them as visited
                }
            }
        }
        return bfs;  // finally return the BFS traversal
    }

    // It performs Depth First Search traversal on given graph starting from given source vertex u
    std::vector<T> dfs(T u) {
        std::vector<T> dfs;     // It stores the DFS traversal of the given graph
        std::map<T, bool> vis;  // vis map marks visited vertices as true
        vis[u] = true;          // marking source vertex u as visited
        std::stack<T> s;        // s is the exploration stack
        s.push(u);              // pushing the source vertex u in the stack
        while (!s.empty()) {
            T v = s.top();
            s.pop();                 // pop the top vertex of the stack
            dfs.push_back(v);        // and pushes it in the DFS traversal
            for (auto u : adj[v]) {  // pushing all the non-visited neighbours of the popped vertex in the stack
                if (!vis[u]) {
                    s.push(u);
                    vis[u] = true;  // and marking them as visited
                }
            }
        }
        return dfs;  // finally return the DFS traversal
    }

    // This function returns true if the graph is cyclic
    // It uses topological_sort to check for cycles
    bool cyclic() {
        return topological_sort().size() != adj.size();
    }

    // It uses Kahn's algorithm to find a topological sort
    // If the graph is not a DAG it return an empty list
    std::vector<T> topological_sort() {
        std::vector<T> ans;
        std::map<T, int> inDegree = _in_degree;
        std::queue<T> q;
        for (auto i : adj) {
            if (inDegree[i.first] == 0) {
                q.push(i.first);
            }
        }

        while (!q.empty()) {
            T v = q.front();
            q.pop();
            ans.push_back(v);
            for (auto i : adj[v]) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    q.push(i);
                }
            }
        }

        if (ans.size() == adj.size()) {
            return ans;
        }
        return {};
    }

    // This function prints all the SCCs in the given directed graph using Kosaraju's Algorithm
    std::vector<std::vector<T>> SCCs() {
        std::vector<std::vector<T>> SCCsOfGraph;  // this vector stores all SCC vectors
        std::stack<int> st;                       // Fills Stack with vertices (in increasing order of finishing times)
        std::map<T, bool> vis;                    // vis map marks visited vertices as true
        for (auto it : adj) {                     // Calling dfs on first key in adj
            if (!vis[it.first]) {
                dfs(it.first, st, vis, adj);  // which fills the stack according to finishing time
            }
        }

        std::map<T, std::vector<T>> transpose;  // stores the transpose of the original graph
        // Filling the adj list of the transpose graph in transpose
        for (auto it : adj) {
            vis[it.first] = false;
            for (auto itr : adj[it.first]) {
                transpose[itr].push_back(it.first);
            }
        }

        while (!st.empty()) {  // Popping the vertex from top one by one
            int node = st.top();
            st.pop();
            if (!vis[node]) {  // and then calling dfs on the transpose graph
                std::vector<T> SCC;
                revDfs(node, vis, transpose, SCC);  // which in turn will stores all the SCCs in the SCCsOfGraph
                SCCsOfGraph.push_back(SCC);
            }
        }
        return SCCsOfGraph;  // finally return the SCCsOfGraph vector
    }

    // It returns the total number of strongly connected components (SCCs) present in the directed graph.
    int number_of_SCCs() {
        std::vector<std::vector<T>> SCCs = this->SCCs();
        return SCCs.size();
    }
};

template <typename T>
class wgraph {  // Class of weighted undirected graph
   public:
    std::map<T, std::vector<std::pair<T, int>>> adj;  // adj is the adjacency list of the graph
    int number_of_edges = 0;                          // number of edges stores the total edges in the graph

    void add_edge(T v, T w, int k = 1) {  // This function adds an edge between given two vertices of given weight assuming default edge weight as 1.
        adj[v].push_back({w, k});         // updating the adjacency list of w
        adj[w].push_back({v, k});
        number_of_edges++;  // updating the adjacency list of v
    }

    // This function adds an isolated node in the graph
    void add_node(T u) {
        adj[u];
    }

    // It returns the total vertices present in the graph.
    int number_of_nodes() {
        return adj.size();
    }

    // This function removes a given vertex from the graph.
    void remove_node(T u) {
        number_of_edges -= adj[u].size();  // removing all the edges connected to the given vertex
        for (auto i : adj[u]) {
            int p = 0;
            for (auto it : adj[i.first]) {
                if (it.first == u) {
                    adj[i.first].erase(adj[i.first].begin() + p);  // removing the given vertex from the adjacency list of its neighbours
                }
                p++;
            }
        }
        adj.erase(u);  // Finally removing the given vertex
    }

    // This function removes a given edge between two vertices.
    void remove_edge(T u, T v) {
        std::vector<std::pair<T, int>> V1 = adj[u];
        std::vector<std::pair<T, int>> V2 = adj[v];
        int p = 0;
        for (auto it : V1) {  // searching for vertex v
            if (it.first == v) {
                adj[u].erase(adj[u].begin() + p);  // and then removing vertex v from adjacency list of u
            }
            p++;
        }

        p = 0;
        for (auto it : V2) {  // searching for vertex u
            if (it.first == u) {
                adj[v].erase(adj[v].begin() + p);  // removing vertex v from adjacency list of v
            }
            p++;
        }
        number_of_edges--;  // updating the number of edges
    }

    // It just returns the degree of a given vertex.
    int degree(T u) {
        // return adj[u].size();
        return adj.find(u) != adj.end() ? adj[u].size() : -1;
    }

    // It clears the entire graph i.e. it removes all vertices.
    void clear() {
        number_of_edges = 0;
        adj.clear();
    }

    // This function finds shortest distances from src to all other vertices, it also detects negative weight cycle
    std::vector<std::vector<int>> bellman_ford() {
        std::vector<std::vector<int>> distance;  // it stores the shortest distances from source vertex to all other vertices
        for (auto it2 : adj) {
            std::map<T, int> dist;

            // Initialize distances from src to all other vertices as INFINITE
            for (auto it1 : adj) {
                dist[it1.first] = INT_MAX;
            }

            // Relax all edges |V| - 1 times. A simple shortest path from src to any other vertex can have at-most |V| - 1 edges
            dist[it2.first] = 0;
            for (int i = 0; i < adj.size() - 1; i++) {
                for (auto it : adj) {
                    for (auto it1 = it.second.begin(); it1 != it.second.end(); it1++) {
                        T u = it.first;
                        T v = it1->first;
                        int wt = it1->second;
                        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                            dist[v] = dist[u] + wt;
                        }
                    }
                }
            }

            std::vector<int> dist_;
            for (auto it : dist) {
                dist_.push_back(it.second);
            }

            // check for negative-weight cycles.  The above step guarantees shortest distances if graph doesn't contain negative weight cycle.  If we get a shorter path, then there is a cycle.
            for (auto it : adj) {
                for (auto it1 = it.second.begin(); it1 != it.second.end(); it1++) {
                    T u = it.first;
                    T v = it1->first;
                    int wt = it1->second;
                    if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                        return {{-1}};  // If negative cycle is detected, simply return {{-1}}
                    }
                }
            }
            distance.push_back(dist_);  // finally return the distance vector
        }
        return distance;
    }

    std::map<T, int> dijkstra(T s) {
        // Initialize the map of distances with infinity (INT_MAX).
        // ans then set distance of the starting vertex s from itself as 0.
        d.clear();
        p.clear();
        for (auto i : adj) {
            d[i.first] = INT_MAX;
            p[i.first] = T{};
        }

        // Create a min priority queue q of pairs in which the first attribute is distance from s
        // and the second attribute is a graph node. Initialize it with {0, s}.
        d[s] = 0;
        std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> q;
        q.push({0, s});

        // Extract the v and d_v (distance of v from s)  from the top of the min priority queue q. If the queue is empty, halt and return
        while (!q.empty()) {
            T v = q.top().second;
            int d_v = q.top().first;
            q.pop();
            if (d_v != d[v]) {
                continue;
            }

            // For all neighbours e of v, if d[v] + weight of edge {v, e} / (v, e) (for wdigraph) is less than distance of e from s
            // then update the distance fo e from s. Push the pair of distance of e from s and e in the priority queue q. Update predecessor of e to v.
            for (auto e : adj[v]) {
                T to = e.first;
                int len = e.second;

                if (d[v] + len < d[to]) {
                    d[to] = d[v] + len;
                    p[to] = v;
                    q.push({d[to], to});
                }
            }
        }
        // Finally, return d.
        return d;
    }

    // It uses Dijakstra algorithm to calculate shortest path from starting vertex to destination vertex using predecessor map
    std::vector<T> path(T from, T to) {
        dijkstra(from);
        d.clear();
        std::vector<T> path1;
        for (T v = to; v != from; v = p[v]) {
            path1.push_back(v);
        }
        path1.push_back(from);
        reverse(path1.begin(), path1.end());
        return path1;
    }

   private:
    std::map<T, int> d;  // map of distances.
    std::map<T, T> p;    // map of predecessors.
};

template <typename T>
class wdigraph {  // Class of weighted directed graph
   public:
    std::map<T, std::vector<std::pair<T, int>>> adj;  // adj is the adjacency list of the weighted directed graph
    int number_of_edges = 0;                          // number of edges stores the total edges in the weighted directed graph
    std::map<T, int> _in_degree;                      // _in_degree stores the indegree of a given vertex

    // This function adds a directed edge from vertex u to vertex v with given weight assuming default edge weight as 1
    void add_edge(T v, T w, int k = 1) {
        adj[v].push_back({w, k});  // updating the adjacency list of v by adding edge of weight k
        adj[w];
        number_of_edges++;
        _in_degree[w]++;  // creating the adjacency list of w
    }

    // This function adds an isolated node in the weighted directed graph
    void add_node(T u) {
        adj[u];
    }

    // It returns the total vertices present in the graph.
    int number_of_nodes() {
        return adj.size();
    }

    // out_degree stores the outdegree of a given vertex
    int out_degree(T u) {
        // return adj[u].size();
        return adj.find(u) != adj.end() ? adj[u].size() : -1;
    }

    int in_degree(T u) {
        return adj.find(u) != adj.end() ? _in_degree[u] : -1;
    }

    // This function removes a given vertex from the graph.
    void remove_node(T u) {
        for (auto &i : adj) {
            if (i.first == u) {
                std::vector<std::pair<T, int>> V = adj[u];
                number_of_edges -= V.size();  // removing all the edges connected to the given vertex
                for (auto j : V) {
                    _in_degree[j.first]--;  // updating the indegree of its neighbours
                }
                continue;
            }

            std::vector<std::pair<T, int>> V = adj[i.first];
            int p = 0;
            for (auto it : V) {
                if (it.first == u) {
                    adj[i.first].erase(adj[i.first].begin() + p);  // removing the given vertex from the adjacency list of its neighbours
                    number_of_edges--;                             // again updating the number of edges
                }
                p++;
            }
        }
        adj.erase(u);         // removing the given vertex from the adjacency list
        _in_degree.erase(u);  // and then updating ther indegree of the removed vertex
    }

    // This function removes the given directed edge between two vertices.
    void remove_edge(T u, T v) {
        std::vector<std::pair<T, int>> V = adj[u];
        int p = 0;
        for (auto it : V) {
            if (it.first == v) {
                adj[u].erase(adj[u].begin() + p);  // then, removing v from adjacency list of u
                _in_degree[v]--;                   // updating the indegre of v
                number_of_edges--;                 // finally updating the number of edges.
            }
            p++;
        }
    }

    // It clears the entire directed graph i.e. it removes all vertices.
    void clear() {
        number_of_edges = 0;
        _in_degree.clear();
        adj.clear();
    }

    // This function finds shortest distances from src to all other vertices, it also detects negative weight cycle
    std::vector<std::vector<int>> bellman_ford() {
        std::vector<std::vector<int>> distance;  // it stores the shortest distances from source vertex to all other vertices

        for (auto it2 : adj) {
            std::map<T, int> dist;
            // Initialize distances from src to all other vertices as INFINITE
            for (auto it1 : adj) {
                dist[it1.first] = INT_MAX;
            }

            // Relax all edges |V| - 1 times. A simple shortest path from src to any other vertex can have  at-most |V| - 1 edges
            dist[it2.first] = 0;
            for (int i = 0; i < adj.size() - 1; i++) {
                for (auto it : adj) {
                    for (auto it1 = it.second.begin(); it1 != it.second.end(); it1++) {
                        T u = it.first;
                        T v = it1->first;
                        int wt = it1->second;
                        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                            dist[v] = dist[u] + wt;
                        }
                    }
                }
            }

            std::vector<int> dist_;
            for (auto it : dist) {
                dist_.push_back(it.second);
            }
            // check for negative-weight cycles. The above step guarantees shortest distances if graph doesn't contain negative weight cycle. If we get a shorter path, then there is a cycle.
            for (auto it : adj) {
                for (auto it1 = it.second.begin(); it1 != it.second.end(); it1++) {
                    T u = it.first;
                    T v = it1->first;
                    int wt = it1->second;
                    if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                        return {{-1}};  // If negative cycle is detected, simply return {{-1}}
                    }
                }
            }
            distance.push_back(dist_);
        }
        return distance;  // finally return the distance vector
    }

    std::map<T, int> dijkstra(T s) {
        // Initialize the map of distances with infinity (INT_MAX).
        // ans then set distance of the starting vertex s from itself as 0.

        d.clear();
        p.clear();
        for (auto i : adj) {
            d[i.first] = INT_MAX;
            p[i.first] = T{};
        }

        // Create a min priority queue q of pairs in which the first attribute is distance from s
        // and the second attribute is a graph node. Initialize it with {0, s}.
        d[s] = 0;
        std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> q;
        q.push({0, s});

        // Extract the v and d_v (distance of v from s)  from the top of the min priority queue q. If the queue is empty, halt and return
        while (!q.empty()) {
            T v = q.top().second;
            int d_v = q.top().first;
            q.pop();
            if (d_v != d[v]) {
                continue;
            }

            // For all neighbours e of v, if d[v] + weight of edge {v, e} / (v, e) (for wdigraph) is less than distance of e from s
            // then update the distance fo e from s. Push the pair of distance of e from s and e in the priority queue q. Update predecessor of e to v.
            for (auto e : adj[v]) {
                T to = e.first;
                int len = e.second;

                if (d[v] + len < d[to]) {
                    d[to] = d[v] + len;
                    p[to] = v;
                    q.push({d[to], to});
                }
            }
        }
        // Finally, return d.
        return d;
    }

    // It uses Dijakstra algorithm to calculate shortest path from starting vertex to destination vertex using predecessor map
    std::vector<T> path(T from, T to) {
        dijkstra(from);
        d.clear();
        std::vector<T> path1;
        for (T v = to; v != from; v = p[v]) {
            path1.push_back(v);
        }
        path1.push_back(from);
        reverse(path1.begin(), path1.end());
        return path1;
    }

   private:
    std::map<T, int> d;  // map of distances.
    std::map<T, T> p;    // map of predecessors
};