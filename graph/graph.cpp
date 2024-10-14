#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "circular_buffer.h"
#include "graph.h"
#include "logger.h"

graph_t* new_graph(size_t nodes_amount) {
    graph_t* graph = (graph_t*) calloc(sizeof(graph_t), sizeof(char));
    if (graph == nullptr) {
        LOG(ERROR, __POS__, "MEMORY WASN'T ALLOCATED" STRERROR(errno));
        return nullptr;
    }

    graph->nodes_amount = nodes_amount;

    graph->adj_matrix = (bool**) calloc(nodes_amount, sizeof(bool*));
    if (graph->adj_matrix == nullptr) {
        LOG(ERROR, __POS__, "MEMORY WASN'T ALLOCATED" STRERROR(errno));
        return nullptr;
    }

    for (size_t i = 0; i < nodes_amount; i++) {
        graph->adj_matrix[i] = (bool*) calloc(nodes_amount, sizeof(bool));
        if (graph->adj_matrix[i] == nullptr) {
            LOG(ERROR, __POS__, "MEMORY WASN'T ALLOCATED" STRERROR(errno));
            return nullptr;
        }

        for (size_t j = 0; j < nodes_amount; j++) {
            graph->adj_matrix[i][j] = false;
        }
    }

    return graph;
}

void graph_dtor(graph_t* graph) {
    for (size_t i = 0; i < graph->nodes_amount; i++) {
        free(graph->adj_matrix[i]);
        graph->adj_matrix[i] = nullptr;
    }

    free(graph->adj_matrix);
    graph->adj_matrix = nullptr;

    free(graph);
    graph = nullptr;
}

void add_undirected_edge(graph_t* graph, size_t src, size_t dst) {
    graph->adj_matrix[src][dst] = true;
    graph->adj_matrix[dst][src] = true;
}

