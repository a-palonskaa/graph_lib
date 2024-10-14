#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "tree.h"

int main() {
    graph_t* graph = new_graph(5);
    add_undirected_edge(graph, 0, 1);
    add_undirected_edge(graph, 1, 2);
    add_undirected_edge(graph, 1, 3);

    size_t connected_components_amount = count_connected_components(graph);
    tree_t* tree = find_spanning_tree(graph, 0);
    print_tree(tree);
    tree_dtor(&tree);
    graph_dtor(graph);
}
