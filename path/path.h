#ifndef PATH_H
#define PATH_H

#include "graph.h"

typedef struct {
    size_t starting_node;
    size_t destination_node;
    size_t* nodes;
    size_t path_len;
} path_t;

path_t* find_shortest_path(graph_t* graph, size_t start, size_t target);
ssize_t count_connected_components(graph_t* graph);
void breadth_first_search(graph_t* graph, size_t start, bool* is_nod_visited);

#endif /* PATH_H */
