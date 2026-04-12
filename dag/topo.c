/**
 * @file topo.c
 *
 * @brief This file implements based on the topological ordering.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../graph/graph.h"
#include "../stack/stack.h"


/**
 * @brief Function to perform a topological sort of a graph. Update the field topological_ordering of the graph.
 *
 * @param graph The graph to be sorted.
 */
void topologicalSort(Graph graph){
    // Vérifie si la structure est correcte avande passer au tri
    if (graph.numberVertices <= 0 || graph.array == NULL || graph.topological_ordering == NULL) {
        printf("\033[1;31mError: invalid graph structure.\033[0m\n");
        return;
    }

    // Initialisation des variables utilisées
    int numberVertices = graph.numberVertices;
    int *enteringVertices = (int *)calloc(numberVertices, sizeof(int)); // nombre de prédecéssers
    int *queue = (int *)malloc(numberVertices * sizeof(int)); // file de sommets à traiter

    // Calcul du nombre de prédecesseurs pour chaque sommet
    for (int vertex = 0; vertex < numberVertices; vertex++) {
        Cell *current = graph.array[vertex];
        while (current != NULL) {
            enteringVertices[current->value]++;
            current = current->nextCell;
        }
    }

    // Initialisation de la file avec les sommets sans prédecesseurs
    int queueStart = 0;
    int queueEnd = 0;
    for (int vertex = 0; vertex < numberVertices; vertex++) {
        if (enteringVertices[vertex] == 0) {
            queue[queueEnd++] = vertex;
        }
        graph.topological_ordering[vertex] = -1;
    }

    // Traitement de la file pour construire l'ordre topologique
    int orderingIndex = 0;
    while (queueStart < queueEnd) {
        int currentVertex = queue[queueStart++];
        graph.topological_ordering[orderingIndex++] = currentVertex;

        Cell *current = graph.array[currentVertex];
        while (current != NULL) {
            int neighbor = current->value;
            enteringVertices[neighbor]--;
            if (enteringVertices[neighbor] == 0) {
                queue[queueEnd++] = neighbor;
            }
            current = current->nextCell;
        }
    }

    // Tests pour vérifier si le tri topologique a réussi
    if (orderingIndex != numberVertices) {
        for (int i = 0; i < numberVertices; i++) {
            graph.topological_ordering[i] = -1;
        }
        printf("\033[1;31mError: the graph contains a cycle, topological sort is impossible.\033[0m\n");
        free(enteringVertices);
        free(queue);
        return;
    }

    // Affichage de l'ordre topologique
    printf("Topological ordering: [");
    for (int i = 0; i < orderingIndex; i++) {
        printf("%d", graph.topological_ordering[i]);
        if (i < orderingIndex - 1) {
            printf(" ");
        }
    }
    printf("]\n");

    // Libération des variables
    free(enteringVertices);
    free(queue);
}


/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */

void computeEarliestStartDates(Graph graph) {
    // Vérifie si la structure est correcte avantde passer au calcul
    if (graph.numberVertices <= 0 || graph.array == NULL || graph.topological_ordering == NULL ||
        graph.earliest_start == NULL || graph.xCoordinates == NULL || graph.yCoordinates == NULL) {
        printf("\033[1;31mError: invalid graph structure for earliest start dates.\033[0m\n");
        return;
    }

    int n = graph.numberVertices;

    // Vérifie que l'ordre topologique est valide avant de calculer les dates
    if (graph.topological_ordering[0] < 0 || graph.topological_ordering[0] >= n) {
        topologicalSort(graph);
    }

    // Vérifie que l'ordre topologique est valide après le tri
    if (graph.topological_ordering[0] < 0 || graph.topological_ordering[0] >= n) {
        printf("\033[1;31mError: cannot compute earliest dates without a valid topological ordering.\033[0m\n");
        return;
    }

    // Initialisation des dates au plus tôt à 0
    for (int i = 0; i < n; i++) {
        graph.earliest_start[i] = 0.0;
    }

    // Calcul des dates au plus tôt en suivant l'ordre topologique
    for (int i = 0; i < n; i++) {
        int vertex = graph.topological_ordering[i];
        if (vertex < 0 || vertex >= n) {
            printf("\033[1;31mError: invalid topological ordering entry.\033[0m\n");
            return;
        }

        Cell *current = graph.array[vertex];
        while (current != NULL) {
            int neighbor = current->value;
            double weight = distance(
                graph.xCoordinates[vertex], graph.yCoordinates[vertex],
                graph.xCoordinates[neighbor], graph.yCoordinates[neighbor]
            );

            double candidateDate = graph.earliest_start[vertex] + weight;
            if (candidateDate > graph.earliest_start[neighbor]) {
                graph.earliest_start[neighbor] = candidateDate;
            }

            current = current->nextCell;
        }
    }
}


/**
 * @brief Function to compute the latest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the latest start dates.
 * Updates the array containing the latest start date of each vertex in the graph structure.
 */
void computeLatestStartDates(Graph graph) {
    return;
}

