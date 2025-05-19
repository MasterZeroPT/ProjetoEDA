/**
 * @file grafos.h
 * @author Pedro Andrade (a31497@alunos.ipca.pt)
 * @brief This header file contains the definitions and declarations for graph data structures and algorithms.
 * @version 0.1
 * @date 2025-05-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once
#include "funcao.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para representar um nó do grafo
typedef struct NoGrafo {
    Coordenada localizacao;
    struct NoGrafo* proximo;         // Próximo nó na lista principal
    struct NoGrafo* adjacentes;      // Lista de adjacentes
} NoGrafo;


// Estrutura para representar um grafo de antenas
typedef struct GrafoAntenas {
    char frequencia;         // Frequência das antenas
    NoGrafo* listaAdjacencia; // Lista de adjacência
    struct GrafoAntenas* proximo; // Próximo grafo (para diferentes frequências)
} GrafoAntenas;

// Função para criar o grafo das antenas com a mesma frequência
GrafoAntenas* CriarGrafoAntenas(CelulaMatriz* matriz);

// Função para criar uma lista de adjacências para as antenas com a mesma frequência
int CriarListaAdjacencias(GrafoAntenas* grafos);

// DFS (Procurar em Profundidade) a partir de uma antena específica, retorna true se encontrou a origem
bool DFS_Antena(GrafoAntenas* grafos, char frequencia, Coordenada origem);

// BFS (Procurar em Largura) a partir de uma antena específica, retorna true se encontrou a origem
bool BFS_Antena(GrafoAntenas* grafos, char frequencia, Coordenada origem);

// Lista todos os caminhos entre duas antenas, retorna o número de caminhos encontrados
int ListarTodosCaminhos(GrafoAntenas* grafos, char frequencia, Coordenada origem, Coordenada destino);

// Lista todas as interseções de arestas entre antenas de frequências diferentes, retorna o número de interseções encontradas
int ListarInterseccoesArestas(GrafoAntenas* grafos);





