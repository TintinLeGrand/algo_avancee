# TP - Parcours dans les graphes

_Ce TP a été réalisé par Léni SOREL et Ethan LE NEINDRE, dans le cadre du cours d'algorithhmie avancée de Loïc LHÔTE, à l'ENSICAEN._

## Makefiles

Chaque dossier contient un Makefile pour compiler les composants du projet. Le Makefile principal contient une commande `make all` qui permet de tout compiler, `make clean-all` pour tout nettoyer, et une commande `make zip` qui permet de zipper les fichiers sans inclure les binaires et fichiers inutiles (utilisé pour le rendu).

## Crédits

Pour les tests unitaires, la partie suivante a été faite à partir d'une conversation sur StackOverflow :

```c
#define ASSERT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            printf("    [FAIL] %s\n", message); \
            return 0; \
        } \
    } while (0)

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
```

Le reste du code est strictement écrit par Léni SOREL et Ethan LE NEINDRE, d'après le squelette de projet de Loïc LHÔTE. Ce TP n'a pas été fait avec usage d'IA générationnelle dans le code qui est écrit.