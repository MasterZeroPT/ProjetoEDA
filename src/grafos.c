/**
 * @file grafos.c
 * @author Pedro Andrade (a31497@alunos.ipca.pt)
 * @brief Implementação das funções para manipulação de grafos de antenas
 * @version 0.1
 * @date 2025-05-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "grafos.h"
#include "struct.h"
#include <math.h> // Para calcular as distâncias
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar para adicionar um nó (vértice) à lista de adjacência
NoGrafo* AdicionarNo(NoGrafo* lista, Coordenada localizacao) {
    NoGrafo* novo = malloc(sizeof(NoGrafo)); // Aloca memória para o novo nó
    if (!novo) return NULL;
    novo->localizacao = localizacao;
    novo->proximo = lista;
    return novo;
}

// Função para criar o grafo das antenas com a mesma frequência
GrafoAntenas* CriarGrafoAntenas(CelulaMatriz* matriz) {
    GrafoAntenas* grafos = NULL; // Inicializa o grafo

    // Percorre a matriz para encontrar antenas
    for (CelulaMatriz* cursor1 = matriz; cursor1; cursor1 = cursor1->prox) { // ";cursor1;" = cursor1 != NULL
        if (cursor1->valor == '.' || cursor1->valor == '#') continue; //Ignora células vazias ou com efeito nefasto

        // Verifica se já existe um grafo para a frequência
        GrafoAntenas* grafoAtual = grafos;
        while (grafoAtual && grafoAtual->frequencia != cursor1->valor) { // grafoAtual != NULL && grafoAtual->frequencia != cursor1->valor
            grafoAtual = grafoAtual->proximo;
        }

        // Se não existir, cria um novo grafo para a frequência
        if (!grafoAtual) {
            GrafoAntenas* novoGrafo = malloc(sizeof(GrafoAntenas));
            if (!novoGrafo) return NULL; // !novografo = malloc falhou
            novoGrafo->frequencia = cursor1->valor;
            novoGrafo->listaAdjacencia = NULL;
            novoGrafo->proximo = grafos;
            grafos = novoGrafo;
            grafoAtual = novoGrafo;
        }

        // Adiciona a antena à lista de adjacência do grafo
        grafoAtual->listaAdjacencia = AdicionarNo(grafoAtual->listaAdjacencia, cursor1->pos);
    }

    return grafos;
}

// Função para calcular a distância entre duas coordenadas
double CalcularDistancia(Coordenada a, Coordenada b) {
    return sqrt(pow(a.linha - b.linha, 2) + pow(a.coluna - b.coluna, 2)); // Calcula através da fórmula: √((x2-x1)² + (y2-y1)²)
}

// Função para criar uma lista de adjacências para as antenas com a mesma frequência
int CriarListaAdjacencias(GrafoAntenas* grafos) {
    if (!grafos) return -1;
    for (GrafoAntenas* grafoAtual = grafos; grafoAtual; grafoAtual = grafoAtual->proximo) {
        for (NoGrafo* no1 = grafoAtual->listaAdjacencia; no1; no1 = no1->proximo) { // no1 significa "nó nº1" 
            no1->adjacentes = NULL; // Limpa a lista de adjacentes antes de preencher
            for (NoGrafo* no2 = grafoAtual->listaAdjacencia; no2; no2 = no2->proximo) {
                if (no1 != no2) {
                    double distancia = CalcularDistancia(no1->localizacao, no2->localizacao);
                    if (distancia <= 50.0) { //Altere aqui o valor do limite de distância
                        NoGrafo* novoAdj = malloc(sizeof(NoGrafo)); 
                        if (!novoAdj) continue;
                        novoAdj->localizacao = no2->localizacao;
                        novoAdj->proximo = no1->adjacentes;
                        novoAdj->adjacentes = NULL; // Não precisa de adjacentes para adjacentes
                        no1->adjacentes = novoAdj;
                    }
                }
            }
        }
    }
    return 0;
}

// Função auxiliar para marcar visitados
bool jaVisitado(Coordenada* visitados, int n, Coordenada c) {
    for (int i = 0; i < n; i++)
        if (visitados[i].linha == c.linha && visitados[i].coluna == c.coluna)
            return true;
    return false;
}

// DFS recursivo
void DFS_Rec(NoGrafo* no, Coordenada* visitados, int* nVisitados) { // nVisitados é um ponteiro para o número de visitados
    if (!no || jaVisitado(visitados, *nVisitados, no->localizacao)) return; // Se o nó é nulo ou já foi visitado, retorna
    visitados[*nVisitados] = no->localizacao; // Marca como visitado
    (*nVisitados)++;
    printf("Antena alcançada (DFS) em (%d, %d)\n", no->localizacao.linha, no->localizacao.coluna);
    for (NoGrafo* adj = no->adjacentes; adj; adj = adj->proximo) {
        DFS_Rec(adj, visitados, nVisitados); 
    }
}

// Função principal de DFS a partir de uma antena específica
bool DFS_Antena(GrafoAntenas* grafos, char frequencia, Coordenada origem) {
    // Encontra o grafo da frequência
    GrafoAntenas* g = grafos;
    while (g && g->frequencia != frequencia) g = g->proximo; 
    if (!g) { // Frequência não encontrada
        return false;
    }
    // Encontra o nó de origem
    NoGrafo* no = g->listaAdjacencia;
    while (no && !(no->localizacao.linha == origem.linha && no->localizacao.coluna == origem.coluna))
        no = no->proximo;
    if (!no) { // Antena de origem não encontrada
        return false;
    }
    // Array para marcar visitados (tamanho máximo ajustável se necessário)
    Coordenada visitados[30];
    int nVisitados = 0;
    DFS_Rec(no, visitados, &nVisitados); 

    return true;
}

// Função principal de BFS a partir de uma antena específica
// Retorna true se a BFS foi realizada com sucesso, false caso contrário
bool BFS_Antena(GrafoAntenas* grafos, char frequencia, Coordenada origem) {
    // Encontra o grafo da frequência
    GrafoAntenas* g = grafos;
    while (g && g->frequencia != frequencia) g = g->proximo; 
    if (!g) { // Frequência não encontrada
        return false;
    }
    // Encontra o nó de origem
    NoGrafo* no = g->listaAdjacencia;
    while (no && !(no->localizacao.linha == origem.linha && no->localizacao.coluna == origem.coluna))
        no = no->proximo;
    if (!no) { // Antena de origem não encontrada
        return false;
    }

    // Inicializa a fila para BFS
    NoGrafo* fila[100]; // Tamanho máximo da fila
    int inicio = 0, fim = 0; // Índices para o início e fim da fila
    Coordenada visitados[100];
    int nVisitados = 0;

    fila[fim++] = no; // Adiciona o nó de origem à fila
    visitados[nVisitados++] = no->localizacao; 

    while (inicio < fim) {
        NoGrafo* atual = fila[inicio++];
        printf("Antena alcançada (BFS) em (%d, %d)\n", atual->localizacao.linha, atual->localizacao.coluna);

        for (NoGrafo* adj = atual->adjacentes; adj; adj = adj->proximo) {
            // Verifica se já foi visitado
            bool ja_vis = false;
            for (int i = 0; i < nVisitados; i++) {
                if (visitados[i].linha == adj->localizacao.linha && visitados[i].coluna == adj->localizacao.coluna) {
                    ja_vis = true;
                    break;
                }
            }
            if (!ja_vis) {
                fila[fim++] = adj;
                visitados[nVisitados++] = adj->localizacao;
            }
        }
    }
    return true;
}

// Função auxiliar recursiva para listar todos os caminhos
// Retorna o número de caminhos encontrados
int ListarCaminhosRec(NoGrafo* atual, Coordenada destino, Coordenada* caminho, int profundidade, bool* visitados, NoGrafo* lista, int* encontrou) {
    if (!atual) return 0;

    int total = 0;

    // Marca como visitado
    caminho[profundidade] = atual->localizacao;
    profundidade++;

    // Se chegou ao destino, imprime o caminho
    if (atual->localizacao.linha == destino.linha && atual->localizacao.coluna == destino.coluna) {
        *encontrou = 1;
        printf("Caminho: ");
        for (int i = 0; i < profundidade; i++) {
            printf("(%d,%d)%s", caminho[i].linha, caminho[i].coluna, (i == profundidade-1) ? "" : " -> "); 
        }
        printf("\n");
        return 1;
    }

    // Marca o nó como visitado
    int idx = 0;
    for (NoGrafo* n = lista; n; n = n->proximo, idx++) {
        if (n->localizacao.linha == atual->localizacao.linha && n->localizacao.coluna == atual->localizacao.coluna) {
            visitados[idx] = true;
            break;
        }
    }

    // Percorre adjacentes
    for (NoGrafo* adj = atual->adjacentes; adj; adj = adj->proximo) {
        // Só visita se não foi visitado ainda neste caminho
        int adj_idx = 0;
        for (NoGrafo* n = lista; n; n = n->proximo, adj_idx++) {
            if (n->localizacao.linha == adj->localizacao.linha && n->localizacao.coluna == adj->localizacao.coluna) {
                if (!visitados[adj_idx]) {
                    total += ListarCaminhosRec(adj, destino, caminho, profundidade, visitados, lista, encontrou);
                }
                break;
            }
        }
    }

    // Desmarca o nó ao voltar (backtracking)
    idx = 0;
    for (NoGrafo* n = lista; n; n = n->proximo, idx++) {
        if (n->localizacao.linha == atual->localizacao.linha && n->localizacao.coluna == atual->localizacao.coluna) {
            visitados[idx] = false;
            break;
        }
    }

    return total;
}

// Função principal para listar todos os caminhos entre duas antenas
// Agora retorna o número de caminhos encontrados entre origem e destino
int ListarTodosCaminhos(GrafoAntenas* grafos, char frequencia, Coordenada origem, Coordenada destino) {
    // Encontra o grafo da frequência
    GrafoAntenas* g = grafos;
    while (g && g->frequencia != frequencia) g = g->proximo;
    if (!g) { // Frequência não encontrada
        return 0;
    }
    // Encontra o nó de origem
    NoGrafo* noOrigem = g->listaAdjacencia;
    while (noOrigem && !(noOrigem->localizacao.linha == origem.linha && noOrigem->localizacao.coluna == origem.coluna))
        noOrigem = noOrigem->proximo;
    if (!noOrigem) { // Antena de origem não encontrada
        return 0;
    }
    // Prepara arrays auxiliares
    Coordenada caminho[100];
    bool visitados[100] = {false};
    int encontrou = 0;
    int total = ListarCaminhosRec(noOrigem, destino, caminho, 0, visitados, g->listaAdjacencia, &encontrou);
    if (!encontrou) {
        printf("Nenhum caminho encontrado entre (%d,%d) e (%d,%d).\n", origem.linha, origem.coluna, destino.linha, destino.coluna);
    }
    return total;
}

// A função retorna o número de pares de antenas listados
int ListarInterseccoesAntenas(GrafoAntenas* grafos) { // Provavelmente devia ser chamado ListarParesAntenas
    int total = 0;
    for (GrafoAntenas* g1 = grafos; g1; g1 = g1->proximo) {
        for (GrafoAntenas* g2 = grafos; g2; g2 = g2->proximo) {
            if (g1 == g2) continue; // Frequências iguais, ignora
            // Para evitar pares repetidos, só considera se a frequência de g1 < g2
            if (g1->frequencia >= g2->frequencia) continue;
            for (NoGrafo* n1 = g1->listaAdjacencia; n1; n1 = n1->proximo) {
                for (NoGrafo* n2 = g2->listaAdjacencia; n2; n2 = n2->proximo) {
                    printf("Par de antenas: [%c](%d,%d) <-> [%c](%d,%d)\n",
                        g1->frequencia, n1->localizacao.linha, n1->localizacao.coluna,
                        g2->frequencia, n2->localizacao.linha, n2->localizacao.coluna
                    );
                    total++;
                }
            }
        }
    }
    return total;
}

// Função auxiliar para determinar se dois segmentos se cruzam
bool SegsIntersetam(Coordenada a1, Coordenada a2, Coordenada b1, Coordenada b2, Coordenada* intersec) {
    // Usando determinantes para segmentos em 2D
    int d = (a2.linha - a1.linha) * (b2.coluna - b1.coluna) - (a2.coluna - a1.coluna) * (b2.linha - b1.linha);
    if (d == 0) return false; // Paralelos

    double t = ((b1.linha - a1.linha) * (b2.coluna - b1.coluna) - (b1.coluna - a1.coluna) * (b2.linha - b1.linha)) / (double)d; // Esta fórmula calcula o ponto de interseção
    double u = ((b1.linha - a1.linha) * (a2.coluna - a1.coluna) - (b1.coluna - a1.coluna) * (a2.linha - a1.linha)) / (double)d;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        // Interseção dentro dos segmentos
        if (intersec) {
            intersec->linha = a1.linha + t * (a2.linha - a1.linha);
            intersec->coluna = a1.coluna + t * (a2.coluna - a1.coluna);
        }
        return true;
    }
    return false;
}

// A função retorna o número de interseções encontradas entre pares de antenas
int ListarInterseccoesArestas(GrafoAntenas* grafos) {
    int total = 0;
    for (GrafoAntenas* g1 = grafos; g1; g1 = g1->proximo) {
        for (NoGrafo* n1 = g1->listaAdjacencia; n1; n1 = n1->proximo) {
            for (NoGrafo* adj1 = n1->adjacentes; adj1; adj1 = adj1->proximo) {
                Coordenada a1 = n1->localizacao;
                Coordenada a2 = adj1->localizacao;
                for (GrafoAntenas* g2 = g1->proximo; g2; g2 = g2->proximo) { // Só pares diferentes
                    for (NoGrafo* n2 = g2->listaAdjacencia; n2; n2 = n2->proximo) {
                        for (NoGrafo* adj2 = n2->adjacentes; adj2; adj2 = adj2->proximo) {
                            Coordenada b1 = n2->localizacao;
                            Coordenada b2 = adj2->localizacao;
                            Coordenada intersec;
                            if (SegsIntersetam(a1, a2, b1, b2, &intersec)) {
                                printf("Interseção entre [%c](%d,%d)<->(%d,%d) e [%c](%d,%d)<->(%d,%d) em (%.1f,%.1f)\n",
                                    g1->frequencia, a1.linha, a1.coluna, a2.linha, a2.coluna,
                                    g2->frequencia, b1.linha, b1.coluna, b2.linha, b2.coluna,
                                    (float)intersec.linha, (float)intersec.coluna
                                );
                                total++;
                            }
                        }
                    }
                }
            }
        }
    }
    return total;
}

