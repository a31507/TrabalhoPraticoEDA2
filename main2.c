#include <stdio.h>
#include "estruturas2.h"

int main() {
    Grafo *g = CriarGrafo();

    // Criar antenas com mesma frequência para serem interligadas
    Antena *a1 = CriarAntena('A', 0, 0);
    Antena *a2 = CriarAntena('A', 1, 0);
    Antena *a3 = CriarAntena('A', 2, 0);
    Antena *a4 = CriarAntena('A', 1, 1);

    // Inserir antenas no grafo
    InsereAntena(g, a1);
    InsereAntena(g, a2);
    InsereAntena(g, a3);
    InsereAntena(g, a4);

    // Interligar antenas com mesma frequência
    InterligarAntenas(g);

    // Preparar array para coordenadas visitadas
    int coords[100][2];

    // Testar DFS
    printf("\n===== DFS (profundidade) a partir de (1,0) =====\n");
    int n_dfs = DFS(g, 1, 0, coords);
    for (int i = 0; i < n_dfs; i++) {
        printf("Antena visitada: (%d, %d)\n", coords[i][0], coords[i][1]);
    }

    // Testar BFS
    printf("\n===== BFS (largura) a partir de (1,0) =====\n");
    int n_bfs = BFS(g, 1, 0, coords);
    for (int i = 0; i < n_bfs; i++) {
        printf("Antena visitada: (%d, %d)\n", coords[i][0], coords[i][1]);
    }

    return 0;
}
