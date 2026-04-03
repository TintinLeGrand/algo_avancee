/**
 * @file graph.c
 *
 * @brief This file implements a graph data structure using a table of lists.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../graph/graph.h"
#include "../heap/heap.h"

/**
 * @brief Function that computes a minimum spanning tree of graph g of the connex component of the vertex s
 *
 * @param graph The graph
 * @param s Index of the initial vertex of the Prim procedure.
 *
 * The array parents is updated so that it contains the spanning tree
 * computed by the Prim algorithm.
 * Note that the array parents must be initialized before calling the function.
 */
void Prim(Graph g, int s){
    Heap* heap = createHeap(g.numberVertices); // on cree le tas

    // on init les distances
    for (int i = 0; i < g.numberVertices; i++) {
        if (i == s) {
            insertHeap(heap, i, 0.0); // sommet debut distance 0 pour etre pris en premier
        } else {
            insertHeap(heap, i, 1000.0); // les autres disntance 1000 pour infini
        }
    }

    while (heap->nbElements > 0) {
        int u = removeElement(heap); // sommet le plus proche
                
        // on parcourt tous ses voisins
        Cell* current = g.array[u];
        while (current != NULL) {
            int v = current->value;
            
            if (heap->position[v] != -1) { // si v encore dans le tas

                double weight = distance(g.xCoordinates[u], g.yCoordinates[u], g.xCoordinates[v], g.yCoordinates[v]);
                
                if (weight < heap->priority[v]) { // si chemin meilleur
                    g.parents[v] = u; // u devient parent de v
                    modifyPriorityHeap(heap, v, weight); // priorité = nouveau poid
                }
            }
            current = current->nextCell;
        }
    }
    free(heap->heap);
    free(heap->position);
    free(heap->priority);
    free(heap);
}

