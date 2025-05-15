/**
 * @file main2.c
 * @author goncalo rodrigues (a31507@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "estruturas2.h"

#define MAXCAMINHOS 100
#define MAXPASSOS 100

int main() {
    Grafo *g = CarregarGrafo("mapafase2.txt");
    if (!g) {
        printf("Erro ao carregar o grafo.\n");
        return 1;
    }

    // === 3.a: DFS ===
    int dfs_coords[100][2];
    int totalDFS = DFS(g, 5, 6, dfs_coords);

    printf("Resultado da DFS a partir de (5,6):\n");
    for (int i = 0; i < totalDFS; i++) {
        printf("(%d, %d)\n", dfs_coords[i][0], dfs_coords[i][1]);
    }
    printf("\n");

    // === 3.b: BFS ===
    int bfs_coords[100][2];
    int totalBFS = BFS(g, 5, 6, bfs_coords);

    printf("Resultado da BFS a partir de (5,6):\n");
    for (int i = 0; i < totalBFS; i++) {
        printf("(%d, %d)\n", bfs_coords[i][0], bfs_coords[i][1]);
    }
    printf("\n");

    // === 3.c: Caminhos possíveis entre duas antenas ===
    int caminhos[MAXCAMINHOS][MAXPASSOS][2];
    int caminhoTemp[MAXPASSOS][2];

    // Inicializar caminhos com -1
    for (int i = 0; i < MAXCAMINHOS; i++)
        for (int j = 0; j < MAXPASSOS; j++)
            caminhos[i][j][0] = caminhos[i][j][1] = -1;

    // Reset visitas
    for (Antena *a = g->inicio; a; a = a->prox)
        a->visitado = 0;

    Antena *origem = NULL, *destino = NULL;
    for (Antena *a = g->inicio; a; a = a->prox) {
        if (a->x == 5 && a->y == 6) origem = a;
        if (a->x == 9 && a->y == 8) destino = a;
    }

    if (origem && destino) {
        int totalCaminhos = GuardarCaminhos(origem, destino, caminhoTemp, 0, caminhos, 0);

        printf("Caminhos entre (5,6) e (9,8):\n");
        for (int i = 0; i < totalCaminhos; i++) {
            printf("Caminho %d: ", i + 1);
            for (int j = 0; j < MAXPASSOS; j++) {
                if (caminhos[i][j][0] == -1) break;
                printf("(%d,%d)", caminhos[i][j][0], caminhos[i][j][1]);
                if (j < MAXPASSOS - 1 && caminhos[i][j + 1][0] != -1) printf(" -> ");
            }
            printf("\n");
        }
    } else {
        printf("Origem ou destino não encontrados.\n");
    }

    // === 3.d: Verificar intersecção entre frequências ===
    int ix, iy;
    bool intersecao = HaIntersecaoEntreFrequencias(g, 5, 6, 9, 8, &ix, &iy);
    if (intersecao) {
        printf("\nInterseção entre frequências detetada em (%d, %d)\n", ix, iy);
    } else {
        printf("\nNenhuma interseção entre frequências foi detetada.\n");
    }

    return 0;
}
