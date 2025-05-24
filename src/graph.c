#include "graph.h"

#include "stdlib.h"
#include "stdio.h"

int addNode(struct Graph *graph, int node_id)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    printf("Adding node: %d\n", node_id);
}

int removeNode(struct Graph *graph, int node_id)
{
    printf("Removing node: %d\n", node_id);
}

int addEdge(struct Graph *graph, int onode_id, int dnode_id)
{
    printf("Adding edge: %d-%d\n", onode_id, dnode_id);
}

int removeEdge(struct Graph *graph, int onode_id, int dnode_id)
{
    printf("Removing edge: %d-%d\n", onode_id, dnode_id);
}