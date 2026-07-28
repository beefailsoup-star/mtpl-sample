#include "graph_adjacency.h"
#include <iostream>

int main() {
    Graph<int> g;
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    std::cout << "Vertices: " << g.vertex_count() << ", Edges: " << g.edge_count() << "\n";

    auto bfs_order = g.bfs(0);
    std::cout << "BFS: ";
    for (int v : bfs_order) std::cout << v << " ";

    auto dfs_order = g.dfs(0);
    std::cout << "\nDFS: ";
    for (int v : dfs_order) std::cout << v << " ";

    std::cout << "\nHas edge 0->1: " << (g.has_edge(0, 1) ? "yes" : "no");
    std::cout << "\nHas vertex 4: " << (g.has_vertex(4) ? "yes" : "no") << "\n";
    return 0;
}
