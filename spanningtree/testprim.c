#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../graph/graph.h"
#include "prim.h"

void test_Prim_unit() {
    printf("Tests Unitaires de Prim\n");

    // Graphe complet sigma = 2.0
    Graph g1 = createGraph(0, 5, 2.0);
    for(int i = 0; i < g1.numberVertices; i++) {
        g1.parents[i] = -1; // init tableau parents
    }
    Prim(g1, 0);
    
    int rootCount1 = 0;
    for (int i = 0; i < g1.numberVertices; i++) {
        if (g1.parents[i] == -1) rootCount1++;
    }
    if (rootCount1 == 1) {
        printf("Graphe connexe : 1 seule racine trouvee\n");
    } else {
        printf("Graphe connexe : %d racines trouvees au lieu d'une seule\n", rootCount1);
    }

    // Graphe deconnecte sigma = 0.0
    Graph g2 = createGraph(0, 5, 0.0);
    for(int i = 0; i < g2.numberVertices; i++) {
        g2.parents[i] = -1;
    }
    Prim(g2, 0); // on lance depuis 0 et c'est le seul qui sera exploré
    
    int rootCount2 = 0;
    for (int i = 0; i < g2.numberVertices; i++) {
        if (g2.parents[i] == -1) rootCount2++;
    }
    if (rootCount2 == 5) {
        printf("Graphe deconnecte : tous les sommets restent isoles\n");
    } else {
        printf("Graphe deconnecte : %d racines trouvees -> impossible\n", rootCount2);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    test_Prim_unit(); // tests unitaires

    //test visuel
    printf("Test Visuel\n");
    int n = 500;
    double sigma = 0.05;
    Graph graph = createGraph(0, n, sigma);

    // init tableau parents
    for(int i = 0; i < n; i++) {
        graph.parents[i] = -1;
    }

    Prim(graph, 0);

    // dessin graphe et arbre couvrant
    drawGraph(graph, "prim-graph-tree.svg", 2, 0);
    drawGraph(graph, "prim-tree.svg", 1, 0);

    printf("[OK] Fichiers 'prim-graph-tree.svg' et 'prim-tree.svg' generes avec succes.\n");

    return 0;
}