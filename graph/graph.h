#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    size_t nodes_amount;
    bool** adj_matrix;
} graph_t;

graph_t* new_graph(size_t nodes_amount);
void graph_dtor(graph_t* graph);
void add_undirected_edge(graph_t* graph, size_t src, size_t dst);

#endif /* GRAPH_H */

