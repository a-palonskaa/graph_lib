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
    return components_amount;
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

// typedef struct {
//     size_t parent;
//     size_t child;
// } edge_t;
//
// typedef struct {
//     edge_t* edges;
//     size_t edges_amount;
//     size_t starting_node;
// } tree_t;

// void bfs_shortest_path(graph_t* graph, size_t start, size_t target) {
//     size_t* distance = (size_t*)malloc(graph->nodes_amount * sizeof(size_t));
//     size_t* parent = (size_t*)malloc(graph->nodes_amount * sizeof(size_t));
//     bool* visited = (bool*)calloc(graph->nodes_amount, sizeof(bool));
//     Queue* queue = createQueue(graph->nodes_amount);
//
//     for (size_t i = 0; i < graph->nodes_amount; i++) {
//         distance[i] = SIZE_MAX; // или бесконечность
//         parent[i] = SIZE_MAX;   // или невалидное значение
//     }
//
//     visited[start] = true;
//     distance[start] = 0;
//     push(queue, start);
//
//     while (!isEmpty(queue)) {
//         size_t current = pop(queue);
//
//         for (size_t i = 0; i < graph->nodes_amount; i++) {
//             if (graph->adj_matrix[current][i] && !visited[i]) {
//                 visited[i] = true;
//                 distance[i] = distance[current] + 1;
//                 parent[i] = current;
//                 push(queue, i);
//
//                 if (i == target) {
//                     break; // нашли целевой узел, можем прервать
//                 }
//             }
//         }
//     }
//
//     // Построение пути
//     if (distance[target] != SIZE_MAX) {
//         printf("Кратчайший путь: ");
//         size_t current = target;
//         while (current != SIZE_MAX) {
//             printf("%zu ", current);
//             current = parent[current];
//         }
//         printf("\n");
//     } else {
//         printf("Нет пути до целевого узла.\n");
//     }
//
//     free(distance);
//     free(parent);
//     free(visited);
//     freeQueue(queue);
// }

