#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "tree.h"
#include "circular_buffer.h"
#include "logger.h"

void tree_dtor(tree_t** tree) {
    free((*tree)->edges);
    (*tree)->edges = nullptr;
    free(*tree);
    *tree = nullptr;
}

void print_tree(tree_t* tree) {
    printf("Starting node of spanning tree is %lu\n", tree->starting_node);
    for (size_t i = 0; i < tree->edges_amount; i++) {
        printf("%lu - %lu\n", tree->edges[i].parent, tree->edges[i].child);
    }
}

tree_t* find_spanning_tree(graph_t* graph, size_t start) {
    bool* is_nod_visited = (bool*) calloc(graph->nodes_amount, sizeof(char));
    if (is_nod_visited == nullptr) {
        LOG(ERROR, __POS__, "MEMORY WASN'T ALLOCATED" STRERROR(errno));
        return nullptr;
    }
    for (size_t i = 0; i < graph->nodes_amount; i++) {
        is_nod_visited[i] = false;
    }

    ssize_t* parent = (ssize_t*) calloc(graph->nodes_amount, sizeof(ssize_t));
    if (parent == nullptr) {
        LOG(ERROR, __POS__, "MEMORY WASN'T ALLOCATED" STRERROR(errno));
        return nullptr;
    }
    for (size_t i = 0; i < graph->nodes_amount; i++) {
        parent[i] = -1;
    }

    circ_buffer_t queue = {};
    cb_ctor(&queue, graph->nodes_amount, sizeof(size_t));

    size_t start_elm = start;
    cb_push(&queue, &start_elm);

    is_nod_visited[start] = true;

    size_t edges_amount = 0;
    while (queue.head > queue.tail) {
        size_t current_node = 0;
        cb_pop(&queue, &current_node);

        for (size_t i = 0; i < graph->nodes_amount; i++) {
            if (graph->adj_matrix[current_node][i] && !is_nod_visited[i]) {
                is_nod_visited[i] = true;
                edges_amount++;
                parent[i] = (ssize_t) current_node;
                cb_push(&queue, &i);
            }
        }
    }

    tree_t* tree = new_tree(parent, edges_amount, start, graph->nodes_amount);

    free(is_nod_visited);
    is_nod_visited = nullptr;

    free(parent);
    parent = nullptr;

    cb_dtor(&queue);
    return tree;
}

tree_t* new_tree(ssize_t* parent, size_t edges_amount, size_t start, size_t nodes_amount) {
    tree_t* tree = (tree_t*) calloc(sizeof(tree_t), sizeof(char));
    tree->edges_amount = edges_amount;
    tree->starting_node = start;
    tree->edges = (edge_t*) calloc(edges_amount, sizeof(edge_t));

    for (size_t i = 0, j = 0; i < nodes_amount; i++) {
        if (parent[i] != -1) {
            tree->edges[j].parent = (size_t) parent[i];
            tree->edges[j].child = i;
            j++;
        }
    }
    return tree;
}
