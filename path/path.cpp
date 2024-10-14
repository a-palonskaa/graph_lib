#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "circular_buffer.h"
#include "path.h"
#include "graph.h"
#include "logger.h"

const size_t POISON_VALUE = 666;

path_t* find_shortest_path(graph_t* graph, size_t start, size_t target) {
    size_t* distance = (size_t*) calloc(graph->nodes_amount, sizeof(size_t));
    size_t* parent = (size_t*) calloc(graph->nodes_amount, sizeof(size_t));
    bool* visited = (bool*) calloc(graph->nodes_amount, sizeof(bool));
    circ_buffer_t queue = {};
    cb_ctor(&queue, graph->nodes_amount, sizeof(size_t));

    for (size_t i = 0; i < graph->nodes_amount; i++) {
        distance[i] = POISON_VALUE;
        parent[i] = POISON_VALUE;
    }

    visited[start] = true;
    distance[start] = 0;
    size_t start_elm = start;
    cb_push(&queue, &start_elm);

    while (queue.tail < queue.head) {
        size_t current_node = 0;
        cb_pop(&queue, &current_node);

        for (size_t i = 0; i < graph->nodes_amount; i++) {
            if (graph->adj_matrix[current_node][i] && !visited[i]) {
                visited[i] = true;
                distance[i] = distance[current_node] + 1;
                parent[i] = current_node;
                cb_push(&queue, &i);

                if (i == target) {
                    break;
                }
            }
        }
    }

    path_t* path = (path_t*) calloc(sizeof(path_t), sizeof(char));
    path->starting_node = start;
    path->destination_node = target;

    if (distance[target] == POISON_VALUE) {
        path->path_len = 0;
    } else {
        path->path_len = distance[target];
        path->nodes = (size_t*) calloc(distance[target], sizeof(size_t));

        size_t current_node = target;
        size_t j = 0;
        while (current_node != POISON_VALUE) {
            path->nodes[j++] = current_node;
            current_node = parent[current_node];
        }
    }

    free(distance);
    distance = nullptr;

    free(parent);
    parent = nullptr;

    free(visited);
    visited = nullptr;

    cb_dtor(&queue);
    return path;
}


ssize_t count_connected_components(graph_t* graph) {
    assert(graph);

    bool* is_nod_visited = (bool*) calloc(graph->nodes_amount, sizeof(char));
    if (is_nod_visited == nullptr) {
        LOG(ERROR, __POS__, "MEMORY WASN'T ALLOCATED" STRERROR(errno));
        return -1;
    }

    for (size_t i = 0; i < graph->nodes_amount; i++) {
        is_nod_visited[i] = false;
    }

    size_t components_amount = 0;
    for (size_t i = 0; i < graph->nodes_amount; i++) {
        if (!is_nod_visited[i]) {
            components_amount++;
            breadth_first_search(graph, i, is_nod_visited);
        }
    }

    free(is_nod_visited);
    is_nod_visited = nullptr;
    return (ssize_t) components_amount;
}

void breadth_first_search(graph_t* graph, size_t start, bool* is_nod_visited) {
    circ_buffer_t queue = {};
    cb_ctor(&queue, graph->nodes_amount, sizeof(size_t));

    size_t start_elm = start;
    cb_push(&queue, &start_elm);

    is_nod_visited[start] = true;

    while (queue.head != queue.tail) {
        size_t current_node = 0;
        cb_pop(&queue, &current_node);

        for (size_t i = 0; i < graph->nodes_amount; i++) {
            if (graph->adj_matrix[current_node][i] && !is_nod_visited[i]) {
                is_nod_visited[i] = true;
                cb_push(&queue, &i);
            }
        }
    }

    cb_dtor(&queue);
}



