/**
 * @file graph.c
 *
 * @brief This file implements a graph data structure using a table of lists.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "graph.h"
#include "../stack/stack.h"
#include "../queue/queue.h"
#include "../list/list.h"

/**
 * @brief Computes the Euclidean distance between two points.
 *
 * @param x1 x coordinate of the first point
 * @param y1 y coordinate of the first point.
 * @param x2 x coordinate of the second point.
 * @param y2 y coordinate of the second point.
 * @return The Euclidean distance between the input points
 */
double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

/**
 * @brief Function to add an oriented edge in a graph.
 *
 * @param origin Origin vertex  of the edge.
 * @param destination Destination vrtex of the edge.
 * @param graph The graph in which the edge is added.
 *
 * Only the array of adjacency lists is updated.
 */
void addEdgeInGraph(Graph graph, int origin, int destination)
{
    // ça ajoute un element en tete de liste, et on a pas besion de key donc on met "", et value c'est le sommet de destination
    graph.array[origin] = addKeyValueInList(graph.array[origin], "", destination);
}

/**
 * @brief Function to create a random graph with a specified number of vertices and parameter sigma.
 *
 * @param numVertices The number of vertices in the graph.
 * @param sigma Parameter of the procedure to generate a random graph.
 * @param directedt The graph is undirected if directed==0, directed otherwise
 *
 * @return A pointer to the new graph.
 *
 * The elements of the array parents are set to -1.
 * The array of adjacency lists must be updated.
 * If the graph is a directed one, then there exist an edge from P1(x1,y1)
 * to P2(x2,y2) if and only if the euclidean distance between P1 and P2 is
 * less than sigma and y1<y2.
 * If the graph is a undirected one, then there exist an edge between P1(x1,y1)
 * and P2(x2,y2) if and only if the euclidean distance between P1 and P2 is
 * less than sigma.
 */
Graph createGraph(int directed, int numVertices, double sigma)
{
    Graph graph;

    // init les variables
    graph.numberVertices = numVertices;
    graph.sigma = sigma;

    // on reserve la memoire pour numVertices elements
    graph.array = (List *)malloc(numVertices * sizeof(List));
    graph.xCoordinates = (double *)malloc(numVertices * sizeof(double));
    graph.yCoordinates = (double *)malloc(numVertices * sizeof(double));
    graph.parents = (int *)malloc(numVertices * sizeof(int));
    graph.topological_ordering = (int *)malloc(numVertices * sizeof(int));
    graph.earliest_start = (double *)malloc(numVertices * sizeof(double));
    graph.latest_start = (double *)malloc(numVertices * sizeof(double));

    // on remplis les tableaux
    for (int i = 0; i < numVertices; i++)
    {
        graph.xCoordinates[i] = (double)rand() / RAND_MAX;
        graph.yCoordinates[i] = (double)rand() / RAND_MAX; // pour faire des nombres random entre 0.0 et 1.0

        graph.array[i] = NULL; // pour avoir la liste vide au debut
        graph.parents[i] = -1;
        graph.topological_ordering[i] = -1;
        graph.earliest_start[i] = -1.0;
        graph.latest_start[i] = -1.0;
    }

    // on fait les arretes avec les distances et l'orientation
    for (int i = 0; i < numVertices; i++)
    {
        // on prend tous les autres sommets
        for (int j = i + 1; j < numVertices; j++)
        { // i+1 pour pas avoir de doublon

            // on calcule la distance
            double dist = distance(graph.xCoordinates[i], graph.yCoordinates[i], graph.xCoordinates[j], graph.yCoordinates[j]);

            if (dist < sigma)
            {
                if (directed == 0)
                { // non orienté donc on met double arrete
                    addEdgeInGraph(graph, i, j);
                    addEdgeInGraph(graph, j, i);
                }
                else
                { // orienté donc arrete du plus petit y vers le plus grand y
                    if (graph.yCoordinates[i] < graph.yCoordinates[j])
                    {
                        addEdgeInGraph(graph, i, j);
                    }
                    else if (graph.yCoordinates[j] < graph.yCoordinates[i])
                    {
                        addEdgeInGraph(graph, j, i);
                    }
                }
            }
        }
    }
    return graph;
}

/**
 * @brief Function to print the graph in the console.
 *
 * @param graph The graph to print.
 */
void printConsoleGraph(Graph graph)
{
    printf("---------------\n");
    printf("Print graph:\n");

    for (int i = 0; i < graph.numberVertices; i++)
    {
        printf("Vertex %d: (%f,%f)\n", i, graph.xCoordinates[i], graph.yCoordinates[i]);
    }

    for (int i = 0; i < graph.numberVertices; i++)
    {
        printf("Vertex %d: ", i);
        // pour le sommet i on prend le premier de la liste de ses liaisons
        Cell *current = graph.array[i];

        while (current != NULL)
        { // jusqu'à NULL parce que c'est la fin
            printf("%d -> ", current->value);
            current = current->nextCell;
        }
        printf("NULL\n");
    }

    printf("parents: ");
    for (int i = 0; i < graph.numberVertices; i++)
    {
        printf("%d ", graph.parents[i]);
    }
    printf("\n");

    printf("Topological ordering:\n[");
    for (int i = 0; i < graph.numberVertices; i++)
    {
        printf("%d ", graph.topological_ordering[i]);
    }
    printf("]\n");

    printf("Print start dates:\n");
    for (int i = 0; i < graph.numberVertices; i++)
    {
        printf("vertex %d : [earliest start date=%.2f, latest start date=%.2f ]\n", i, graph.earliest_start[i], graph.latest_start[i]); // %.2f c'est pour les 2 chiffres apres la virgule
    }
    printf("---------------\n");
}

/**
 * @brief Function to draw the graph in a svg file.
 *
 * @param graph The graph to print.
 * @param filename Name of the svg file.
 * @param type if 0, draws only the graph, if 1 draws the covering tree, if 2 draws both graph and spanning tree, if 3 draws the graph with topological order and dates
 * @param directed If directed==0, the graph is undirected and lines are drawn. Otherwise, arrows are drawn.
 */

void drawGraph(Graph graph, char *filename, int type, int directed)
{

    FILE *fptr;
    fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(-1);
    }
    fprintf(fptr, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
    fprintf(fptr, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
    fprintf(fptr, "  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
    fprintf(fptr, "<svg width=\"800\" height=\"800\"\n");
    fprintf(fptr, "     xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    fprintf(fptr, "<rect x=\"0\" y=\"0\" width=\"100%%\" height=\"100%%\" fill=\"white\" />\n");

    fprintf(fptr, "<defs>\n");
    fprintf(fptr, "<marker id=\"arrow\" markerWidth=\"10\" markerHeight=\"10\" refX=\"10\" refY=\"3\" orient=\"auto\">\n");
    fprintf(fptr, "<path d=\"M0,0 L0,6 L9,3 z\"/>\n");
    fprintf(fptr, "</marker>\n");
    fprintf(fptr, "</defs>\n");

    for (int i = 0; i < graph.numberVertices; i++)
    {
        int x1 = (int)(600 * graph.xCoordinates[i]) + 100;
        int y1 = (int)(600 * graph.yCoordinates[i]) + 100;
        fprintf(fptr, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"blue\" />\n", x1, y1, 3);
    }

    for (int i = 0; i < graph.numberVertices; i++)
    {
        int x1 = (int)(600 * graph.xCoordinates[i]) + 100;
        int y1 = (int)(600 * graph.yCoordinates[i]) + 100;
        fprintf(fptr, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"blue\" />\n", x1, y1, 3);
        for (int j = i + 1; j < graph.numberVertices; j++)
            if (distance(graph.xCoordinates[i], graph.yCoordinates[i],
                         graph.xCoordinates[j], graph.yCoordinates[j]) <= graph.sigma)
            {
                int x2 = (int)(600 * graph.xCoordinates[j]) + 100;
                int y2 = (int)(600 * graph.yCoordinates[j]) + 100;
                int xorigin, yorigin, xdestination, ydestination;
                if (graph.yCoordinates[i] < graph.yCoordinates[j])
                {
                    xorigin = x1;
                    yorigin = y1;
                    xdestination = x2;
                    ydestination = y2;
                }
                else
                {
                    xorigin = x2;
                    yorigin = y2;
                    xdestination = x1;
                    ydestination = y1;
                }
                char arrow[30];
                if (directed == 1)
                    strcpy(arrow, "marker-end=\"url(#arrow)\"");
                else
                    strcpy(arrow, " ");

                switch (type)
                {
                case 0:
                case 3:
                    fprintf(fptr, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"\n",
                            xorigin, yorigin, xdestination, ydestination);
                    fprintf(fptr, "      style=\"stroke: darkgray;\" %s />\n", arrow);
                    break;
                case 1:
                    if (graph.parents[i] == j || graph.parents[j] == i)
                    {
                        fprintf(fptr, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"\n",
                                xorigin, yorigin, xdestination, ydestination);
                        fprintf(fptr, "      style=\"stroke: red;\" %s />\n", arrow);
                    }
                    break;
                case 2:
                    fprintf(fptr, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"\n",
                            xorigin, yorigin, xdestination, ydestination);
                    if (graph.parents[i] == j || graph.parents[j] == i)
                        fprintf(fptr, "      style=\"stroke: red;\" %s />\n", arrow);
                    else
                        fprintf(fptr, "      style=\"stroke: darkgray;\" %s />\n", arrow);
                    break;
                }
            }
    }
    if (type == 3)
    {
        for (int i = 0; i < graph.numberVertices; i++)
        {
            int vertex = graph.topological_ordering[i];
            int x1 = (int)(600 * graph.xCoordinates[vertex]) + 100;
            int y1 = (int)(600 * graph.yCoordinates[vertex]) + 100;
            fprintf(fptr, "<text x=\"%d\" y=\"%d\" font-family=\"Verdana\" font-size=\"10\"> P%d:[%d,%.3lf,%.3lf]  </text>", x1 + 10, y1, vertex, i, graph.earliest_start[vertex], graph.latest_start[vertex]);
        }
    }
    fprintf(fptr, "</svg>\n");
    fclose(fptr);
}

/**
 * @brief Function that performs a depth first search from a vertex.
 *
 * @param graph The graph on which the depth first search is done.
 * @param vertex The origin of depth first search.
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the depth first search.
 * Note that the array parents is not initialized in the function and
 * must be initialized before calling the function.
 */

void graphDFS(Graph graph, int vertex)
{
    // TODO: Test graph
    if ((vertex < 0) || (vertex >= graph.numberVertices))
    {
        printf("\033[1;31mVertex out of range in DFS search\033[0m\n");
        return;
    }

    int *visited = calloc(graph.numberVertices, sizeof(int));
    Stack *stack = createStack();

    visited[vertex] = 1;
    push(stack, vertex);

    while (!isStackEmpty(*stack))
    {
        int current = pop(stack);

        Cell *cell = graph.array[current];
        while (cell != NULL)
        {
            int neighbor = cell->value;
            if (!visited[neighbor])
            {
                visited[neighbor] = 1;
                graph.parents[neighbor] = current;
                push(stack, neighbor);
            }
            cell = cell->nextCell;
        }
    }

    free(stack);
    free(visited);

    return;
}

/**
 * @brief Function that performs a breadth first search from a vertex.
 *
 * @param graph The graph on which the breadth first search is done.
 * @param vertex The origin of breadth first search.
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the breadth first search.
 * Note that the array parents is not initialized in the function and
 * must be initialized before calling the function.
 */
void graphBFS(Graph graph, int vertex)
{
    return;
}

/**
 * @brief Function that counts te number of connex components in a graph and that computes a covering forest (one tree by components)
 *
 * @param graph The graph
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the breadth first search.
 * Note that the array parents is initialized in the function.
 */
int numberOfComponents(Graph graph)
{
    int componentsCount = 0;

    // on met tous les sommets en non visités
    for (int i = 0; i < graph.numberVertices; i++) {
        graph.parents[i] = -1;
    }

    // pour chaque sommet
    for (int i = 0; i < graph.numberVertices; i++) {
        if (graph.parents[i] == -1) { // si c'est -1 c'est pas visité donc c'est une nouvelle composante
            componentsCount++;
            graphDFS(graph, i); // parcour en profondeur pour visiter toute la composante
        }
    }
    return componentsCount;
}
