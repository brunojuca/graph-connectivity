#include "graph.h"

#include "stdlib.h"
#include "stdio.h"

void printGraph(struct Graph *graph)
{
    if (!graph)
        return;

    printf("Grafo:\n");
    printf("Número de nós: %d\n", graph->num_nodes);

    struct Node *p = graph->first_node;

    while (p)
    {
        printf("%d -> ", p->value);

        struct Edge *edge = p->first_edge;
        while (edge)
        {
            printf("%d ", edge->destination->value);
            edge = edge->next;
        }
        printf("\n");
        p = p->next;
    }
}

int addNode(struct Graph *graph, int node_id)
{
    if (!graph)
        return 1;

    printf("Adicionando vértice: %d\n", node_id);

    struct Node *p = graph->first_node;
    while (p)
    {
        if (p->value == node_id)
        {
            printf("O vértice %d já existe.\n", node_id);
            return 1;
        }
        p = p->next;
    }

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->value = node_id;
    new_node->first_edge = NULL;
    new_node->next = graph->first_node;
    graph->first_node = new_node;

    graph->num_nodes++;

    printf("Vértice %d adicionado com sucesso.\n", node_id);
    return 1;
}

int removeNode(struct Graph *graph, int node_id)
{
    if (!graph)
        return 1;

    printf("Removendo vértice: %d\n", node_id);

    struct Node *p = graph->first_node;
    struct Node *prev = NULL;

    while (p && p->value != node_id)
    {
        prev = p;
        p = p->next;
    }

    if (!p)
    {
        printf("O vértice %d não existe.\n", node_id);
        return 1;
    }

    struct Node *q = graph->first_node;
    while (q)
    {
        if (q != p)
            removeEdge(graph, q->value, node_id);
        q = q->next;
    }

    struct Edge *e = p->first_edge;
    while (e)
    {
        struct Edge *temp = e;
        e = e->next;
        free(temp);
    }

    if (prev)
        prev->next = p->next;
    else
        graph->first_node = p->next;

    free(p);
    graph->num_nodes--;

    printf("Vértice %d removido com sucesso.\n", node_id);
    return 1;
}

struct Node *findNode(struct Graph *graph, int node_id)
{
    struct Node *p = graph->first_node;
    while (p)
    {
        if (p->value == node_id)
            return p;
        p = p->next;
    }
    return NULL;
}

int addEdge(struct Graph *graph, int onode_id, int dnode_id)
{
    if (!graph)
        return 1;

    printf("Adicionando aresta: %d-%d\n", onode_id, dnode_id);

    struct Node *onode = findNode(graph, onode_id);
    struct Node *dnode = findNode(graph, dnode_id);

    if (!onode || !dnode)
    {
        printf("Um dos vértices não existe.\n");
        return 1;
    }

    struct Edge *e = onode->first_edge;
    while (e)
    {
        if (e->destination == dnode)
        {
            printf("A aresta já existe.\n");
            return 1;
        }
        e = e->next;
    }

    struct Edge *new_edge = (struct Edge *)malloc(sizeof(struct Edge));
    new_edge->destination = dnode;
    new_edge->next = onode->first_edge;
    onode->first_edge = new_edge;

    printf("Aresta %d-%d adicionada com sucesso.\n", onode_id, dnode_id);
    return 1;
}

int removeEdge(struct Graph *graph, int onode_id, int dnode_id)
{
    if (!graph)
        return 0;

    printf("Removendo aresta: %d-%d\n", onode_id, dnode_id);

    struct Node *onode = findNode(graph, onode_id);
    struct Node *dnode = findNode(graph, dnode_id);

    if (!onode || !dnode)
    {
        printf("Um dos vértices não existe.\n");
        return 0;
    }

    struct Edge *e = onode->first_edge;
    struct Edge *prev = NULL;

    while (e)
    {
        if (e->destination == dnode)
        {
            if (prev)
                prev->next = e->next;
            else
                onode->first_edge = e->next;

            free(e);
            printf("Aresta %d-%d removida com sucesso.\n", onode_id, dnode_id);
            return 1;
        }
        prev = e;
        e = e->next;
    }

    printf("A aresta não existe.\n");
    return 1;
}

void destroyGraph(struct Graph *graph)
{
    if (!graph)
        return;

    struct Node *p = graph->first_node;

    while (p)
    {
        struct Edge *e = p->first_edge;

        while (e)
        {
            struct Edge *temp_edge = e;
            e = e->next;
            free(temp_edge);
        }

        struct Node *temp_node = p;
        p = p->next;
        free(temp_node);
    }

    graph->first_node = NULL;
    graph->num_nodes = 0;

    printf("Grafo destruído com sucesso.\n");
}

int isVisited(struct Node **visited, int visited_count, struct Node *node)
{
    int i;
    for (i = 0; i < visited_count; i++)
    {
        if (visited[i] == node)
            return 1;
    }
    return 0;
}

int greedySearch(struct Graph *graph, int start_value)
{
    if (!graph)
        return 1;

    struct Node *start_node = findNode(graph, start_value);
    if (!start_node)
    {
        printf("Nó de início %d não encontrado.\n", start_value);
        return 1;
    }

    struct Node **visited = (struct Node **)malloc(sizeof(struct Node *) * graph->num_nodes);
    int visited_count = 0;

    visited[visited_count++] = start_node;
    printf("Caminho de visitação: %d ", start_node->value);

    while (1)
    {
        struct Node *next_node = NULL;
        int max_value = -2147483648;
        int i = 0;

        for (i = 0; i < visited_count; i++)
        {
            struct Edge *e = visited[i]->first_edge;
            while (e)
            {
                if (!isVisited(visited, visited_count, e->destination))
                {
                    if (e->destination->value > max_value)
                    {
                        max_value = e->destination->value;
                        next_node = e->destination;
                    }
                }
                e = e->next;
            }
        }

        if (next_node)
        {
            visited[visited_count++] = next_node;
            printf("-> %d ", next_node->value);
        }
        else
        {
            break;
        }
    }

    printf("\n");

    if (visited_count == graph->num_nodes)
        printf("O grafo é conexo.\n");
    else
        printf("O grafo NÃO é conexo.\n");
    free(visited);
    return 1;
}