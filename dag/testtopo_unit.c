#include <stdlib.h>
#include <stdio.h>
#include "../graph/graph.h"
#include "topo.h"

// Extrait d'une conversation sur stackoverflow
//
// Permet de fair des tests d'assertions
#define ASSERT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            printf("    [FAIL] %s\n", message); \
            return 0; \
        } \
    } while (0)

// Extrait (et modifié) d'une conversation sur stackoverflow
//
// Exécute un test
static void runTest(const char *name, int (*testFunction)(void), int *tests_run, int *tests_failed) {
    (*tests_run)++;
    int ok = testFunction();
    if (ok) {
        printf("[OK] %s\n", name);
    } else {
        printf("[KO] %s\n", name);
        (*tests_failed)++;
    }
}

// Fonction pour créer un graphe pour les tests
static Graph createGraphTest(int n) {
    Graph g = (Graph){0};
    g.numberVertices = n;
    g.array = (List *)calloc(n, sizeof(List));
    g.topological_ordering = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        g.topological_ordering[i] = -1;
    }

    return g;
}

// Fonction pour libérer la mémoire d'un graphe
static void freeGraphTest(Graph g) {
    for (int i = 0; i < g.numberVertices; i++) {
        freeList(g.array[i]);
    }
    free(g.array);
    free(g.topological_ordering);
}

// Fonction pour valider si l'ordre topologique est correct
static int validateTopologicalOrder(Graph g) {
    // Créer un tableau pour stocker la position de chaque sommet dans l'ordre topologique
    int n = g.numberVertices;
    int *position = (int *)malloc(n * sizeof(int));
    int *seen = (int *)calloc(n, sizeof(int));

    // Initialisation des positions à -1
    for (int i = 0; i < n; i++) {
        position[i] = -1;
    }

    // Vérifier que chaque sommet apparaît une seule fois dans l'ordre topologique
    for (int i = 0; i < n; i++) {
        int vertex = g.topological_ordering[i];
        if (vertex < 0 || vertex >= n) {
            free(position);
            free(seen);
            return 0;
        }
        if (seen[vertex]) {
            free(position);
            free(seen);
            return 0;
        }
        seen[vertex] = 1;
        position[vertex] = i;
    }

    // Vérifier que pour chaque arête de a vers b, position[a] < position[b]
    for (int u = 0; u < n; u++) {
        Cell *current = g.array[u];
        while (current != NULL) {
            int v = current->value;
            if (position[u] >= position[v]) {
                free(position);
                free(seen);
                return 0;
            }
            current = current->nextCell;
        }
    }

    // Libère les variables utilisées
    free(position);
    free(seen);
    return 1;
}

// Fonction pour vérifier que tous les éléments sont à -1 (pour vérifier cycle)
static int allValuesNegative(Graph g) {
    for (int i = 0; i < g.numberVertices; i++) {
        if (g.topological_ordering[i] != -1) {
            return 0;
        }
    }
    return 1;
}

// Tests unitaires pour la fonction topologicalSort
//
static int test_chain(void) {
    Graph g = createGraphTest(4);
    addEdgeInGraph(g, 0, 1);
    addEdgeInGraph(g, 1, 2);
    addEdgeInGraph(g, 2, 3);

    topologicalSort(g);

    ASSERT_TRUE(validateTopologicalOrder(g), "L'ordre topologique n'est pas valide.");

    freeGraphTest(g);
    return 1;
}

static int test_multiple_sources(void) {
    Graph g = createGraphTest(6);
    addEdgeInGraph(g, 0, 3);
    addEdgeInGraph(g, 1, 3);
    addEdgeInGraph(g, 1, 4);
    addEdgeInGraph(g, 2, 4);
    addEdgeInGraph(g, 2, 5);

    topologicalSort(g);

    ASSERT_TRUE(validateTopologicalOrder(g), "L'ordre topologique n'est pas valide.");

    freeGraphTest(g);
    return 1;
}

static int test_disconnected(void) {
    Graph g = createGraphTest(6);
    addEdgeInGraph(g, 0, 1);
    addEdgeInGraph(g, 2, 3);
    addEdgeInGraph(g, 4, 5);

    topologicalSort(g);

    ASSERT_TRUE(validateTopologicalOrder(g), "L'ordre topologique n'est pas valide.");

    freeGraphTest(g);
    return 1;
}

static int test_cycle(void) {
    Graph g = createGraphTest(3);
    addEdgeInGraph(g, 0, 1);
    addEdgeInGraph(g, 1, 2);
    addEdgeInGraph(g, 2, 0);

    topologicalSort(g);

    ASSERT_TRUE(allValuesNegative(g), "Toutes les valeurs doivent être à -1");

    freeGraphTest(g);
    return 1;
}

// Lance des tests grâce à runTest
int main(void) {
    int tests_run = 0;
    int tests_failed = 0;

    runTest("test_chain", test_chain, &tests_run, &tests_failed);
    runTest("test_multiple_sources", test_multiple_sources, &tests_run, &tests_failed);
    runTest("test_disconnected", test_disconnected, &tests_run, &tests_failed);
    runTest("test_cycle", test_cycle, &tests_run, &tests_failed);

    printf("\n%d/%d tests passed\n", tests_run - tests_failed, tests_run);
    if (tests_failed != 0) {
        return 1;
    }
    return 0;
}
