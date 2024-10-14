#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    size_t nodes_amount;
    bool** adj_matrix;
} graph_t;

graph_t* new_graph(size_t nodes_amount);
void graph_dtor(graph_t* graph);

void add_undirected_edge(graph_t* graph, size_t src, size_t dst);
ssize_t count_connected_components(graph_t* graph);
void breadth_first_search(graph_t* graph, size_t start, bool* is_nod_visited);


#endif /* GRAPH_H */

