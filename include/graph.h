#ifndef GRAPH_H
#define GRAPH_H

struct Node
{
    int value;
    struct Node *neighbors;
    struct Node *next;
};

struct Graph
{
    struct Node *nodes;
};

/**
 * @brief Adds node.
 *
 * @return struct Node*
 */
int addNode(struct Graph *graph, int node_id);

/**
 * @brief Returns 1 if node was removed and 0 otherwise.
 *
 * @return int
 */
int removeNode(struct Graph *graph, int node_id);

/**
 * @brief Adds edge to graph.
 *
 * @return struct Node*
 */
int addEdge(struct Graph *graph, int onode_id, int dnode_id);

/**
 * @brief Returns 1 if edge was removed and 0 otherwise.
 *
 * @return int
 */
int removeEdge(struct Graph *graph, int onode_id, int dnode_id);

#endif
