/**
 * @file estruturas2.h
 * @author goncalo rodrigues (a31507@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#define MAXCAMINHOS 100
#define MAXPASSOS 100

/**
 * @brief estrutura da antena que contem a frequência, as coordenadas, lista de adjacências, ponteiro para a próxima antena e flag de visitado
 */
typedef struct Antena {
    char frequencia;
    int x, y;
    struct Antena *prox;
    struct Adjacencias *adj;
    bool visitado;
} Antena;

/**
 * @brief estrutura que representa uma adjacência entre antenas (ligação entre duas antenas com a mesma frequência)
 */
typedef struct Adjacencias {
    float distancia;
    Antena *antenadestino;
    struct Adjacencias *prox;
} Adjacencias;

/**
 * @brief estrutura principal do grafo que guarda o número total de antenas e o início da lista ligada de antenas
 */
typedef struct Grafo {
    int numantenas;
    Antena *inicio;
} Grafo;

/**
 * @brief estrutura auxiliar para implementar fila ligada (usada no bfs)
 */
typedef struct NoFila {
    Antena *antena;
    struct NoFila *prox;
} NoFila;

/**
 * @brief cria e inicializa um grafo vazio
 * @return Grafo* ponteiro para o grafo criado
 */
Grafo* CriarGrafo();

/**
 * @brief cria uma antena com a frequência e coordenadas fornecidas
 * @param freq letra da frequência da antena
 * @param x coordenada x
 * @param y coordenada y
 * @return Antena* ponteiro para a antena criada
 */
Antena* CriarAntena(char freq, int x, int y);

/**
 * @brief insere uma nova antena no grafo
 * @param g ponteiro para o grafo
 * @param a ponteiro para a nova antena
 * @return Antena* ponteiro para a antena inserida
 */
Antena* InsereAntena(Grafo *g, Antena *a);

/**
 * @brief remove uma antena do grafo com base nas coordenadas
 * @param g ponteiro para o grafo
 * @param x coordenada x da antena a remover
 * @param y coordenada y da antena a remover
 * @return true se a antena foi removida com sucesso
 * @return false caso contrário
 */
bool RemoverAntena(Grafo *g, int x, int y);

/**
 * @brief cria uma adjacência entre duas antenas
 * @param origem antena de origem
 * @param destino antena de destino
 * @return Adjacencias* ponteiro para a adjacência criada
 */
Adjacencias* InserirAdjacencia(Antena *origem, Antena *destino);

/**
 * @brief remove uma adjacência entre duas antenas
 * @param origem antena de origem
 * @param destino antena de destino
 * @return true se a adjacência foi removida
 * @return false caso contrário
 */
bool RemoverAdjacencia(Antena *origem, Antena *destino);

/**
 * @brief altera os dados de uma antena existente
 * @param g ponteiro para o grafo
 * @param x coordenada x da antena a alterar
 * @param y coordenada y da antena a alterar
 * @param novaFreq nova frequência a atribuir
 * @param novoX nova coordenada x
 * @param novoY nova coordenada y
 * @return true se a antena foi alterada
 * @return false caso contrário
 */
bool AlterarAntena(Grafo *g, int x, int y, char novaFreq, int novoX, int novoY);

/**
 * @brief cria ligações entre antenas com a mesma frequência
 * @param g ponteiro para o grafo
 * @return int número total de ligações criadas
 */
int InterligarAntenas(Grafo *g);

/**
 * @brief guarda o grafo num ficheiro binário
 * @param g ponteiro para o grafo
 * @param filename nome do ficheiro binário
 * @return true se o grafo foi guardado com sucesso
 * @return false caso contrário
 */
bool GravarGrafoBinario(Grafo *g, const char *filename);

/**
 * @brief carrega o grafo a partir de um ficheiro de texto
 * @param filename nome do ficheiro de texto
 * @return Grafo* ponteiro para o grafo carregado
 */
Grafo* CarregarGrafo(const char *filename);

/**
 * @brief função auxiliar da dfs que percorre recursivamente o grafo
 * @param atual antena atual
 * @param coords array onde serão guardadas as coordenadas das antenas visitadas
 * @param i índice atual
 * @return int número de antenas visitadas
 */
int DFSaux(Antena *atual, int coords[][2], int i);

/**
 * @brief executa uma pesquisa em profundidade a partir de uma antena
 * @param g ponteiro para o grafo
 * @param x coordenada x da antena inicial
 * @param y coordenada y da antena inicial
 * @param coords array onde serão guardadas as coordenadas das antenas visitadas
 * @return int número de antenas visitadas
 */
int DFS(Grafo *g, int x, int y, int coords[][2]);

/**
 * @brief executa uma pesquisa em largura (bfs) a partir de uma antena
 * @param g ponteiro para o grafo
 * @param x coordenada x da antena inicial
 * @param y coordenada y da antena inicial
 * @param coords array onde serão guardadas as coordenadas das antenas visitadas
 * @return int número de antenas visitadas
 */
int BFS(Grafo *g, int x, int y, int coords[][2]);

/**
 * @brief guarda todos os caminhos possíveis entre duas antenas
 * @param origem antena de origem
 * @param destino antena de destino
 * @param caminho caminho temporário atual
 * @param i índice atual no caminho
 * @param caminhos array com todos os caminhos encontrados
 * @param total total de caminhos encontrados até agora
 * @return int total de caminhos encontrados
 */
int GuardarCaminhos(Antena *origem, Antena *destino, int caminho[][2], int i, int caminhos[MAXCAMINHOS][MAXPASSOS][2], int total);

/**
 * @brief verifica se existe uma interseção de frequências no caminho entre duas antenas
 * @param a antena atual
 * @param destino antena de destino
 * @param freq frequência da antena de origem
 * @param ix ponteiro para guardar a coordenada x da interseção (caso exista)
 * @param iy ponteiro para guardar a coordenada y da interseção (caso exista)
 * @return true se existir interseção
 * @return false caso contrário
 */
bool VerificarIntersecao(Antena *a, Antena *destino, char freq, int *ix, int *iy);

/**
 * @brief função principal que verifica se existe interseção de frequências entre duas antenas
 * @param g ponteiro para o grafo
 * @param x1 coordenada x da antena de origem
 * @param y1 coordenada y da antena de origem
 * @param x2 coordenada x da antena de destino
 * @param y2 coordenada y da antena de destino
 * @param ix ponteiro para guardar a coordenada x da interseção (caso exista)
 * @param iy ponteiro para guardar a coordenada y da interseção (caso exista)
 * @return true se existir interseção
 * @return false caso contrário
 */
bool HaIntersecaoEntreFrequencias(Grafo *g, int x1, int y1, int x2, int y2, int *ix, int *iy);

