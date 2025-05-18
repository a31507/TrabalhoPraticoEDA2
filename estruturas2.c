/**
 * @file estruturas2.c
 * @author goncalo rodrigues (a31507@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <stdbool.h>
 #include "estruturas2.h"

#define MAXCAMINHOS 100
#define MAXPASSOS 100

Grafo* CriarGrafo() {
    Grafo* g = malloc(sizeof(Grafo));
    if (g == NULL) return NULL;

    g->inicio = NULL;
    g->numantenas = 0;

    return g;
}

Antena* CriarAntena(char freq, int x, int y) {
    Antena *a = malloc(sizeof(Antena));                                       // alocado espaço para a nova antena
    if (a == NULL) return NULL;                                               // se não for possível alocar memória, retorna NULL

    a->frequencia = freq;                                                     // atribuída a frequência recebida
    a->x = x;                                                                  // atribuída a coordenada x
    a->y = y;                                                                  // atribuída a coordenada y
    a->adj = NULL;                                                             // inicializada a lista de adjacências a NULL
    a->prox = NULL;                                                            // próxima antena também a NULL

    return a;                                                                  // retorna a antena criada
}


Antena* InsereAntena(Grafo *g, Antena *nova) {
    if (g == NULL || nova == NULL) return NULL;                               // caso o grafo ou a antena a inserir seja nula, retorna NULL

    Antena *atual = g->inicio;                                                // ponteiro que percorre a lista ligada de antenas
    Antena *anterior = NULL;                                                  // ponteiro para guardar a antena anterior

    while (atual != NULL) {                                                                     // ciclo para encontrar a posição correta
        if (nova->frequencia < atual->frequencia) break;                                        // compara as frequências, insere antes se for menor
        if (nova->frequencia == atual->frequencia && nova->y < atual->y) break;                    // se frequências iguais, compara coordenadas y
        if (nova->frequencia == atual->frequencia && nova->y == atual->y && nova->x < atual->x) break; // se y iguais, compara x

        anterior = atual;                                                     // avança os ponteiros
        atual = atual->prox;
    }

    if (anterior == NULL) {                                                   // se for inserida no início da lista
        nova->prox = g->inicio;                                               // a nova antena aponta para a primeira atual
        g->inicio = nova;                                                     // a nova antena passa a ser a primeira
    } else {
        nova->prox = anterior->prox;                                          // a nova antena aponta para a próxima da anterior
        anterior->prox = nova;                                                // a anterior aponta agora para a nova
    }

    g->numantenas++;                                                          // incrementa o número de antenas no grafo

    return nova;                                                              // retorna a antena inserida
}


Adjacencias* InserirAdjacencia(Antena *origem, Antena *destino)  {                  // função auxiliar que tambem nunca ira ser chamada no main pois e parte da funcao de interligar antenas
    if (!origem || !destino) 
    return NULL;

    int dx = destino->x - origem->x;                                               // inicialmente calculamos a distancia entre as duas antenas
    int dy = destino->y - origem->y;                                               // como o mapa e de coordenadas precisamos de obter quanto vale cada cateto
    float distancia = sqrtf((float)dx*dx + (float)dy*dy);                          // para de seguida calcular a hipotenusa, tendo assim a distancia sem desvios

    Adjacencias *adj = malloc(sizeof(Adjacencias));                                // alocado o espaco de memoria 
    if (!adj)
    return NULL;
    adj->antenadestino = destino;                                                  // atribuidos os parametros da adjacencia
    adj->distancia = distancia;

    adj->prox = origem->adj;                                                       // a adjacencia e inserida na lista ligada de adjacencias
    origem->adj = adj;

    return adj;
}

bool RemoverAntena(Grafo *g, int x, int y) {
    if (!g || !g->inicio) 
    return 0;

    Antena *anterior = NULL;
    Antena *atual = g->inicio;

    while (atual != NULL) {                                             //percorre a lista ligada das antenas
        if (atual->x == x && atual->y == y) {                           // ate encontrar a antena pretendida
        
            Antena *a = g->inicio;
            while (a != NULL) {                                         // enquanto houver antenas na lista ligada
                if (a != atual) {                                       // e se a antena pretendida a ser removida for diferente da que esta a correr no ciclo
                    RemoverAdjacencia(a, atual);                        // e chamada a funcao para remover as suas adjacencias
                }
                a = a->prox;
            }

            Adjacencias *adj = atual->adj;                              // libertar o espaco de memoria das adjacencias
            while (adj != NULL) {
                Adjacencias *temp = adj;
                adj = adj->prox;
                free(temp);
            }

            if (anterior == NULL) {                                    // se a antena a ser removida se encontra no inicio da lista ligada de antenas
                g->inicio = atual->prox;                               // a proxima passa a ser a primeira antena
            } else {                                                   // caso nao esteja no inicio da lista
                anterior->prox = atual->prox;                          // a antena anterior passa a estar ligada a antena a seguir a atual
            }

            free(atual);                                               // a antena atual e removida
            g->numantenas--;                                           // a antena e removida com sucesso e retirada da contagem de antenas
            return 1;
        }

        anterior = atual;                                              
        atual = atual->prox;
    }

    return 0;
}

bool RemoverAdjacencia(Antena *origem, Antena *destino) {               // funcao auxiliar para a remover antena, nunca sera chamada no ficheiro main
    if (!origem || !destino)                                            // caso origem ou destino seja NULL
    return 0;

    Adjacencias *anterior = NULL;
    Adjacencias *atual = origem->adj;

    while (atual != NULL) {                                             // enquanto existir adjacencias na lista de adjacencias da antena
        if (atual->antenadestino == destino) {                          // se for a adjacencia pretendida para ser removida
            if (anterior == NULL) {                                     // se a adjacencia a ser removida se encontra no inicio da lista ligada de adjacencias
                origem->adj = atual->prox;                              // a adjacencia e eliminada e o primeira adjacencia passa a ser a segunda
            } else {                                                    // quando a adjacencia a remover nao esta no inicio
                anterior->prox = atual->prox;                           // o atual é eliminado e o anterior passa a estar ligada ao a seguir ao atual
            }
            free(atual);                                                // libertado o atual
            return 1;
        }
        anterior = atual;                                               // segue para a proxima
        atual = atual->prox;
    }

    return 0;
}

bool AlterarAntena(Grafo *g, int x, int y, char novaFreq, int novoX, int novoY) {
    if (!g) 
    return 0;

    Antena *a = g->inicio;

    while (a) {                                                                 
        if (a->x == x && a->y == y) {                                           // toma a antena pretendida para ser alterada
            
            for (Antena *atual = g->inicio; atual; atual = atual->prox) {       // inicia um ciclo que percorre a lista das antenas
                if (atual != a) {                                               // caso a antena pretendida para alterar nao seja a mesma que a que esta no ciclo atualmente
                    RemoverAdjacencia(atual, a);
                    RemoverAdjacencia(a, atual);                                // a funcao para remover adjacencia e chamada (mesmo que nao exista adjacencia entre as antenas)
                }
            }

            
            Adjacencias *adj = a->adj;                                          // libertar o espaco de memoria das adjacencias
            while (adj) {
                Adjacencias *temp = adj;
                adj = adj->prox;
                free(temp);
            }
            a->adj = NULL;

            
            a->frequencia = novaFreq;                                   // os novos valores sao atribuidos a antena
            a->x = novoX;
            a->y = novoY;

            for (Antena *atual = g->inicio; atual; atual = atual->prox){
            if(atual != a && atual->frequencia == a->frequencia){
            
            InserirAdjacencia(atual, a);                                   // e chamada a funcao inserir adjacencias para serem atribuidas a antenas as novas adjacencias
            InserirAdjacencia(a, atual);

            }

        }
            return 1;
        }
        a = a->prox;
    }

    return 0;
}

int InterligarAntenas(Grafo *g) {
    if (g == NULL) 
    return 0;

    int total = 0;                                                      // contagem para as antenas que seram ligada
    Antena *a1 = g->inicio;

    while (a1 != NULL) {                                                // ciclo que percorre a lista ligada de antenas, a partir da primeira passado por todas e repetindo o processo seguindo para as proximas antenas
        Antena *a2 = a1->prox;                                          //...
        while (a2 != NULL) {                                            //...
            if (a1->frequencia == a2->frequencia) {                     // caso as antenas tenham a mesma frequencia (requisito para se interligarem)
               
                InserirAdjacencia(a1,a2);
                InserirAdjacencia(a2,a1);
                    total += 2;
                }
            }
            a2 = a2->prox;
        }
        a1 = a1->prox;
    

    return total;
}

bool GravarGrafoBinario(Grafo *g, const char *filename) {
    if (g == NULL || filename == NULL) 
    return 0;

    FILE *file = fopen(filename, "wb");                                 // o ficheiro e aberto em modo escrita binario
    if (file == NULL) 
    return 0;

    fwrite(&g->numantenas, sizeof(int), 1, file);                       // escreve o numero de antenas existentes

    Antena *a = g->inicio;                                              // e chamada a lista ligada de antenas
    while (a != NULL) {             
    
        fwrite(&a->frequencia, sizeof(char), 1, file);                  // sao escritos os dados de cada antena
        fwrite(&a->x, sizeof(int), 1, file);
        fwrite(&a->y, sizeof(int), 1, file);

        int numAdj = 0;
        Adjacencias *adj = a->adj;                                      //...
        while (adj != NULL) {                                               
            numAdj++;
            adj = adj->prox;
        }                                                               // conta tambem e escreve o numero de adjacencias de cada antena

        // Escreve o número de adjacências
        fwrite(&numAdj, sizeof(int), 1, file);                          //...

    
        adj = a->adj;                                                  // e chamada a lista das adjacencias
        while (adj != NULL) {                                           
            int dx = adj->antenadestino->x;
            int dy = adj->antenadestino->y;
            fwrite(&dx, sizeof(int), 1, file);                          // sao escritos os dados de cada adjacencia
            fwrite(&dy, sizeof(int), 1, file);
            fwrite(&adj->distancia, sizeof(float), 1, file);
            adj = adj->prox;
        }

        a = a->prox;
    }

    fclose(file);
    return 1;
}

Grafo* CarregarGrafo(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) 
    return NULL;

    Grafo* g = CriarGrafo();                                                // e criado o grafo
        if (!g) {
            
            fclose(file);
            return NULL;
        }

    char linha[256];                                                      // definido um n de caracteres por linha
    int y = 0;

    while (fgets(linha, sizeof(linha), file)) {                         
        for (int x = 0; linha[x] && linha[x] != '\n'; x++) {               // ciclo para percorrer os caracteres de cada linha
            char c = linha[x];
            if (c != '.') {
                Antena* nova = CriarAntena(c, x, y);
                InsereAntena(g, nova);  
            }
        }
        y++;
    }
    fclose(file);

    InterligarAntenas(g);                                                 // e chamada a funcao InterligarAntenas para ligar as antenas com a mesma frequencia
            
    return g;

}

int DFSaux(Antena *atual, int coords[][2], int i) {                          // funcao auxiliar que percorre o grafo e guarda as coordenadas das antenas atingidas
    if (!atual || atual->visitado)                                               // caso a antena ja tenha sido visitada
     return i;

    atual->visitado = 1;                                                     // a antena e marcada como visitada
    coords[i][0] = atual->x;                                                 // as suas coordenadas sao guardadas
    coords[i][1] = atual->y;
    i++;

    for (Adjacencias *adj = atual->adj; adj; adj = adj->prox)                // a lista das antenas adjacente a atual e percorrida
        i = DFSaux(adj->antenadestino, coords, i);

    return i;
}

int DFS(Grafo *g, int x, int y, int coords[][2]) {                          // funcao que reinicializa o grafo e procura a antena da qual queremos partir
    if (!g) 
    return 0;

    for (Antena *a = g->inicio; a; a = a->prox)                             // marca todas as antenas como nao visitadas (reinicializa o grafo)
        a->visitado = 0;

    Antena *inicio = g->inicio;
    while (inicio) {                                                       // ciclo para percorrer a lista ligada das antena
        if (inicio->x == x && inicio->y == y)                              // se a antena for a pretendida
            break;                                                         // para o ciclo
        inicio = inicio->prox;
    }

    if (!inicio)                                                           
    return 0;

    return DFSaux(inicio, coords, 0);
}

int BFS(Grafo *g, int x, int y, int coords[][2]) {                           // funcao principal de procura em largura a partir de uma antena nas coordenadas dadas
    if (!g) 
        return 0;

    for (Antena *a = g->inicio; a; a = a->prox)                              // reinicializa o estado de visitado de todas as antenas
        a->visitado = 0;

    Antena *inicio = g->inicio;
    while (inicio) {                                                         // procura a antena de partida com as coordenadas dadas
        if (inicio->x == x && inicio->y == y)
            break;
        inicio = inicio->prox;
    }
    if (!inicio)
        return 0;

    NoFila *inicioFila = NULL, *fimFila = NULL;

    NoFila *novo = malloc(sizeof(NoFila));                                          // aloca o primeiro nó da fila com a antena de partida
    novo->antena = inicio;
    novo->prox = NULL;
    inicioFila = fimFila = novo;
    inicio->visitado = 1;

    int i = 0;

    while (inicioFila) {                                                            // enquanto houver antenas na fila
        Antena *a = inicioFila->antena;

        coords[i][0] = a->x;                                                        // guarda as coordenadas da antena atual
        coords[i][1] = a->y;
        i++;

        for (Adjacencias *adj = a->adj; adj; adj = adj->prox) {                      // percorre as adjacencias da antena atual
            Antena *vizinho = adj->antenadestino;
            if (!vizinho->visitado) {
                vizinho->visitado = 1;

                NoFila *novo = malloc(sizeof(NoFila));                              // adiciona o vizinho à fila
                novo->antena = vizinho;
                novo->prox = NULL;
                fimFila->prox = novo;
                fimFila = novo;
            }
        }

        NoFila *temp = inicioFila;                                                  // remove o nó atual da fila
        inicioFila = inicioFila->prox;
        free(temp);
    }

    return i;                                                                       // retorna o número total de antenas visitadas
}

int GuardarCaminhos(Antena *origem, Antena *destino, int caminho[][2], int i, int caminhos[MAXCAMINHOS][MAXPASSOS][2], int total) {
    if (!origem || origem->visitado)                                                // caso a antena seja nula ou ja tenha sido visitada, nao prossegue
        return total;

    origem->visitado = 1;                                                           // marca a antena como visitada
    caminho[i][0] = origem->x;                                                      // guarda as suas coordenadas
    caminho[i][1] = origem->y;
    i++;

    if (origem == destino) {                                                        // se a antena atual for a de destino
        for (int j = 0; j < i; j++) {                                               // copia o caminho atual para a lista de caminhos encontrados
            caminhos[total][j][0] = caminho[j][0];
            caminhos[total][j][1] = caminho[j][1];
        }
        total++;                                                                    // aumenta o total de caminhos encontrados
    } else {
        for (Adjacencias *adj = origem->adj; adj; adj = adj->prox) {                // percorre as adjacencias e chama recursivamente para cada vizinho
            total = GuardarCaminhos(adj->antenadestino, destino, caminho, i, caminhos, total);
        }
    }

    origem->visitado = 0;                                                           // ao sair da chamada recursiva, desmarca a antena como visitada
    return total;                                                                   // retorna o total de caminhos encontrados
}

bool VerificarIntersecao(Antena *a, Antena *destino, char freq, int *ix, int *iy) {
    if (!a || a->visitado)                                                           // se a antena e nula ou ja visitada
        return 0;

    if (a->frequencia != freq) {                                                     // se a frequencia da antena for diferente da original
        *ix = a->x;                                                                  // guarda as coordenadas da intersecao
        *iy = a->y;
        return 1;                                                                    // intersecao encontrada
    }

    if (a == destino) 
    return 0;                                                                        // se chegou ao destino sem intersecao, retorna false

    a->visitado = 1;                                                                 // marca como visitada

    for (Adjacencias *adj = a->adj; adj; adj = adj->prox) {                          // percorre adjacencias
        if (!adj->antenadestino->visitado) {
            if (VerificarIntersecao(adj->antenadestino, destino, freq, ix, iy)) {
                a->visitado = 0;                                                     // desmarca antes de retornar
                return 1;
            }
        }
    }

    a->visitado = 0;                                                                // desmarca apos a recursao
    return 0;                                                                       // nao foi encontrada intersecao
}

bool HaIntersecaoEntreFrequencias(Grafo *g, int x1, int y1, int x2, int y2, int *ix, int *iy) {
    if (!g) 
    return 0;

    for (Antena *a = g->inicio; a; a = a->prox)                                     // reinicializa todos os visitados
        a->visitado = 0;

    Antena *origem = NULL, *destino = NULL;

    for (Antena *a = g->inicio; a; a = a->prox) {                                   // encontra as antenas com as coordenadas dadas
        if (a->x == x1 && a->y == y1) origem = a;
        if (a->x == x2 && a->y == y2) destino = a;
    }

    if (!origem || !destino)
     return 0;                                                                      // se alguma nao for encontrada, retorna falso

    return VerificarIntersecao(origem, destino, origem->frequencia, ix, iy);        // chama funcao auxiliar para completar a verificacao
}
