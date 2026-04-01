#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "time.h"

void test_createGraph() {
    printf("Test de createGraph\n");
    int n = 5;
    Graph g = createGraph(0, n, 0.5);
    
    int ok = 1;
    if (g.numberVertices != n) ok = 0;
    if (g.sigma != 0.5) ok = 0;
    if (g.array == NULL || g.parents == NULL) ok = 0;
    
    if (ok) {
        printf("Le graphe a bien ete initialise\n");
    } else {
        printf("Les variables du graphe sont mal initialisees\n");
    }
}

void test_addEdgeInGraph() {
    printf("Test de addEdgeInGraph\n");

    Graph g = createGraph(1, 3, 0.0); 
    addEdgeInGraph(g, 0, 1);
    
    if (g.array[0] != NULL && g.array[0]->value == 1) { // liste non vide et valeur a 1
        printf("L'arete 0 -> 1 a bien ete ajoutee\n");
    } else {
        printf("L'arete n'a pas ete ajoutee\n");
    }
}

void test_numberOfComponents() {
    printf("Test de numberOfComponents\n");
    
    // cas 1 graphe complet
    Graph g1 = createGraph(0, 10, 1.5);
    int nbComp1 = numberOfComponents(g1);
    if (nbComp1 == 1) {
        printf("OK Graphe tres dense (sigma=1.5) : 1 seule composante trouvee\n");
    } else {
        printf("Graphe tres dense : %d composantes trouvees au lieu de 1\n", nbComp1);
    }

    // cas 2 aucun sommet relie
    Graph g2 = createGraph(0, 10, 0.0);
    int nbComp2 = numberOfComponents(g2);
    if (nbComp2 == 10) {
        printf("OK Graphe non connecte (sigma=0.0) : 10 composantes trouvees\n");
    } else {
        printf("Graphe deconnecte : %d composantes trouvees au lieu de 10\n", nbComp2);
    }
}


int main() {
    srand(time(NULL));

    printf("TESTS UNITAIRES\n\n");
    
    test_addEdgeInGraph();
    printf("\n");
    
    test_createGraph();
    printf("\n");
    
    test_numberOfComponents();
    printf("\n");
    
    return 0;
}