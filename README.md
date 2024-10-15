# Graph Library

## Overview

This C library provides functionality for creating and manipulating graphs using an adjacency matrix representation. It includes features for adding edges, finding shortest paths, counting connected components, and constructing spanning trees.

## Features

- Create and initialize a new graph.
- Add undirected edges between nodes.
- Find the shortest path between two nodes.
- Count the number of connected components in the graph.
- Find a spanning tree of the graph.
- Cleanly deallocate all allocated memory for graphs and trees.

## Installation

To use this library, include the necessary headers in your C program and link against this library during compilation. Ensure that the `circular_buffer.h` and `logger.h` headers are also included.


## Usage

### Creating a New Graph

```c
#include "graph.h"

graph_t* graph = new_graph(number_of_nodes);
```

### Adding Edges

To add an undirected edge between two nodes, use the following function:

```c
add_undirected_edge(graph, source_node, destination_node);
```

### Finding Shortest Path

To find the shortest path between two nodes in the graph, you can use the `find_shortest_path` function. It takes the starting node and the target node as parameters:

```c
path_t* path = find_shortest_path(graph, start_node, target_node);
```

### Counting Connected Components

To count the number of connected components in the graph, use the `count_connected_components` function:

```c
ssize_t components = count_connected_components(graph);
```

### Finding Spanning Tree

To find the spanning tree starting from a specific node, you can use the `find_spanning_tree` function:
```c
tree_t* tree = find_spanning_tree(graph, start_node);
```

### Memory Management

Remember to free the allocated memory for the graph and any associated structures when they are no longer needed:

```c
graph_dtor(graph);
```

## Example Usage

Here’s a simple example of how to use the library:

```c
#include "graph.h"

int main() {
    graph_t* graph = new_graph(5);

    add_undirected_edge(graph, 0, 1);
    add_undirected_edge(graph, 1, 2);
    add_undirected_edge(graph, 2, 0);

    ssize_t components = count_connected_components(graph);
    printf("Number of connected components: %zd\n", components);

    path_t* path = find_shortest_path(graph, 0, 2);
    // Handle the path...

    tree_t* tree = find_spanning_tree(graph, 0);
    // Handle the tree...

    graph_dtor(graph);
    return 0;
}
```
