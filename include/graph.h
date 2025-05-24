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
    int num_nodes;
};

/**
 * @brief Prints the graph structure. 
 * 
 * @param graph 
 * @param node_id 
 */
void printGraph(struct Graph *graph);

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


/**
 * @brief Faz uma busca gulosa no grafo a partir de um nó inicial. Retorna se o grafo é conexo ou não. Imprime o caminho encontrado.
 * 
 * @param graph 
 * @param start_node_id 
 * @return int 
 */
int greedySearch(struct Graph *graph, int start_node_id);

#endif
