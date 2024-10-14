#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "tree.h"
#include "path.h"

int main() {
    graph_t* graph = new_graph(5);
    add_undirected_edge(graph, 0, 1);
    add_undirected_edge(graph, 0, 2);
    path_t* path = find_shortest_path(graph, 1, 0);

    printf("%zu \n", path->path_len);
    free(path->nodes);
    path->nodes = nullptr;
    free(path);
    path = nullptr;


    size_t connected_components_amount = (size_t) count_connected_components(graph);
    (void) connected_components_amount;
    tree_t* tree = find_spanning_tree(graph, 0);
    print_tree(tree);
    tree_dtor(&tree);
    graph_dtor(graph);
}
