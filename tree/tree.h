#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include "graph.h"

typedef struct {
    size_t parent;
    size_t child;
} edge_t;

typedef struct {
    edge_t* edges;
    size_t edges_amount;
    size_t starting_node;
} tree_t;

tree_t* find_spanning_tree(graph_t* graph, size_t start);
tree_t* new_tree(ssize_t* parent, size_t edges_amount, size_t start, size_t nodes_amount);
void tree_dtor(tree_t** tree);
void print_tree(tree_t* tree);

#endif /* TREE_H */
