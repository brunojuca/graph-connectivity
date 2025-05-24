#include "graph.h"

#include "stdlib.h"
#include "stdio.h"

void printGraph(struct Graph *graph)
{
    struct Node *p;

    printf("Grafo:\n");
    printf("Número de nós: %d\n", graph->num_nodes);
    p = graph->nodes;
    while (p)
    {
        printf("%d-> ", p->value);

        struct Node *neighbor = p->neighbors;
        while (neighbor)
        {
            printf("%d ", neighbor->value);
            neighbor = neighbor->next;
        }
        p = p->next;
        printf("\n");
    }
}

int addNode(struct Graph *graph, int node_id)
{
    printf("Adicionando vértice: %d\n", node_id);
    struct Node *p, *new_node;

    p = graph->nodes;
    while (p && p->value != node_id)
        p = p->next;

    if (p)
    {
        printf("O vértice %d já existe.\n", node_id);
        return 1;
    }

    new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->value = node_id;
    new_node->next = graph->nodes;
    new_node->neighbors = NULL;

    graph->nodes = new_node;
    graph->num_nodes++;
    printf("Vértice %d adicionado com sucesso.\n", node_id);
    return 1;
}

int removeNode(struct Graph *graph, int node_id)
{
    printf("Removendo vértice: %d\n", node_id);
    struct Node *p, *prev;
    p = graph->nodes;
    prev = NULL;
    while (p && p->value != node_id)
    {
        prev = p;
        p = p->next;
    }
    if (!p)
    {
        printf("O vértice %d não existe.\n", node_id);
        return 0;
    }
    if (prev)
        prev->next = p->next;
    else
        graph->nodes = p->next;

    struct Node *neighbor = p->neighbors;
    while (neighbor)
    {
        struct Node *temp = neighbor;
        neighbor = neighbor->next;
        free(temp);
    }
    free(p);
    graph->num_nodes--;
    printf("Vértice %d removido com sucesso.\n", node_id);
    return 1;
}

int addEdge(struct Graph *graph, int onode_id, int dnode_id)
{
    printf("Adicionando aresta: %d-%d\n", onode_id, dnode_id);
    struct Node *onode = graph->nodes;
    struct Node *dnode = graph->nodes;
    while (onode && onode->value != onode_id)
        onode = onode->next;
    while (dnode && dnode->value != dnode_id)
        dnode = dnode->next;
    if (!onode || !dnode)
    {
        printf("Um dos vértices não existe.\n");
        return 1;
    }
    struct Node *neighbor = onode->neighbors;
    while (neighbor && neighbor->value != dnode_id)
        neighbor = neighbor->next;
    if (neighbor)
    {
        printf("A aresta já existe.\n");
        return 1;
    }
    neighbor = (struct Node *)malloc(sizeof(struct Node));
    neighbor->value = dnode_id;
    neighbor->next = onode->neighbors;
    onode->neighbors = neighbor;
    printf("Aresta %d-%d adicionada com sucesso.\n", onode_id, dnode_id);
    return 1;
}

int removeEdge(struct Graph *graph, int onode_id, int dnode_id)
{
    printf("Removendo aresta: %d-%d\n", onode_id, dnode_id);
    struct Node *onode = graph->nodes;
    struct Node *prev = NULL;
    while (onode && onode->value != onode_id)
        onode = onode->next;
    if (!onode)
    {
        printf("O vértice de origem não existe.\n");
        return 1;
    }
    struct Node *neighbor = onode->neighbors;
    while (neighbor && neighbor->value != dnode_id)
    {
        prev = neighbor;
        neighbor = neighbor->next;
    }
    if (!neighbor)
    {
        printf("A aresta não existe.\n");
        return 1;
    }
    if (prev)
        prev->next = neighbor->next;
    else
        onode->neighbors = neighbor->next;
    free(neighbor);
    printf("Aresta %d-%d removida com sucesso.\n", onode_id, dnode_id);
    return 1;
}

/**
 * @brief O algoritmo de busca do trabalho de grafos,
você vai fazer o algoritmo guloso.
Como funciona o algoritmo guloso que o professor quer?
O professor vai, você quer, você vai ter que dizer um nó
de onde ele vai começar a sua busca, certo?
Então, isso também o usuário, ele precisa dizer.
Então, você vai lá colocar uma opção.
Quando a pessoa escolher para realizar a busca,
você vai colocar uma opção de qual nó ela quer começar.
Aí, depois que você escolhe o nó, você vai buscar, você vai olhar para esse nó e vai ver os vizinhos desse nó.
E aí você vai olhar qual é o maior valor dos vizinhos.
Então, você vai entrar no vizinho com o maior valor.
E assim por diante.
Lembrando que sempre você tem que olhar para todos os maiores valores dos vizinhos já visitados.
Ou seja, se você visitou A e visitou B, você vai ter que ver qual é o maior valor dos vizinhos de A e os vizinhos de B para você ir para o próximo.

 */
int greedySearch(struct Graph *graph, int start_node_id)
{
    /* printf("Iniciando busca gulosa a partir do nó: %d\n", start_node_id);
    struct Node *start_node = graph->nodes;
    while (start_node && start_node->value != start_node_id)
        start_node = start_node->next;

    if (!start_node)
    {
        printf("O nó inicial não existe.\n");
        return 0;
    }

    struct Node *cadidates = start_node->neighbors
        
    

    printf("Busca gulosa concluída.\n");
    return 1; // Retornar 1 se a busca foi bem-sucedida */
}
