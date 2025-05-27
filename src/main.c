#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "graph.h"

char input[BUFF_LINE_SIZE], *endptr;

int applyNodes(FILE *input_stream, struct Graph *graph, int callback(struct Graph *graph, int))
{
    int node_id;
    do
    {
        if (fgets(input, sizeof(char) * BUFF_LINE_SIZE, input_stream) == NULL)
            throwInputError();
        node_id = strtol(input, &endptr, 10);
    } while (input[0] != '#' && (callback(graph, node_id) || throwInputError()));
}

int applyEdges(FILE *input_stream, struct Graph *graph, int callback(struct Graph *graph, int, int))
{
    int onode_id, dnode_id;
    do
    {
        if (fscanf(input_stream, "%s", input) <= 0)
        {
            if (feof(input_stream))
                break;
            throwInputError();
        }
        if (input[0] == '#')
        {
            getc(input_stream);
            break;
        }
        onode_id = strtol(input, &endptr, 10);

        if (fscanf(input_stream, "%s", input) <= 0)
        {
            if (feof(input_stream))
                break;
            throwInputError();
        }
        dnode_id = strtol(input, &endptr, 10);
    } while (input[0] != '\n' && input[0] != '\r' && input[0] != '#' && (callback(graph, onode_id, dnode_id) && callback(graph, dnode_id, onode_id) || throwInputError()));
}

int main(int argc, char const *argv[])
{
    FILE *input_stream;
    const char *filename = argv[1];
    char opt;

    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->first_node = NULL;
    graph->num_nodes = 0;

    if (filename)
    {
        input_stream = fopen(filename, "r");
        applyNodes(input_stream, graph, addNode);
        applyEdges(input_stream, graph, addEdge);
        printf("\nGrafo iniciado com valores do arquivo.\n");
        fclose(input_stream);
        input_stream = stdin;
    }
    else
    {
        input_stream = stdin;
    }

    if (input_stream)
    {
        do
        {
            printf("\nGRAPH CONNECTIVITY\n\n");
            printGraph(graph);
            printf("\n1 - Adicionar vértices\n");
            printf("2 - Remover vértices\n");
            printf("3 - Adicionar arestas\n");
            printf("4 - Remover arestas\n");
            printf("5 - Busca gulosa\n");
            printf("0 - Sair\n");

            if (fscanf(input_stream, "%c", &opt) <= 0)
                throwInputError();
            getc(input_stream);

            switch (opt)
            {
            case '1':
                printf("\nDigite os vértices do grafo como números inteiros, separando-os com ENTER. Digite # para finalizar.\n");
                applyNodes(input_stream, graph, addNode);
                printf("Fim da inserção de vértices.\n");
                break;
            case '2':
                printf("\nDigite os vértices que deseja remover do grafo como números inteiros, separando-os com ENTER. Digite # para finalizar.\n");
                applyNodes(input_stream, graph, removeNode);
                printf("Fim da remoção de vértices.\n");
                break;
            case '3':
                printf("\nDigite as arestas do grafo como pares de números inteiros, separando-os por ESPAÇO. Digite # para finalizar.\n");
                applyEdges(input_stream, graph, addEdge);
                printf("Fim da inserção de arestas.\n");
                break;
            case '4':
                printf("\nDigite as arestas que deseja remover do grafo como pares de números inteiros, separando-os por ESPAÇO. Digite # para finalizar.\n");
                applyEdges(input_stream, graph, removeEdge);
                printf("Fim da remoção de arestas.\n");
                break;
            case '5':
                printf("\nDigite o nó inicial para a busca gulosa: ");
                if (fgets(input, sizeof(char) * BUFF_LINE_SIZE, input_stream) == NULL)
                    throwInputError();
                int start_value = strtol(input, &endptr, 10);
                printf("Iniciando busca gulosa a partir do nó %d...\n", start_value);
                greedySearch(graph, start_value);
                printf("Busca gulosa concluída.\n");
                break;
            case '0':
                return 0;
                break;
            default:
                printf("Opção inválida.");
                break;
            }
        } while (opt != '0');
    }
    else
        throwInputError();
    destroyGraph(graph);
    return 0;
}