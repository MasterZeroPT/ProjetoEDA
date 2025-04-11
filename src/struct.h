/**
 * @file struct.h
 * @author Pedro Andrade (a31497@alunos.ipca.pt)
 * @brief Header com os structs
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
// Estrutura para representar as coordenadas
typedef struct Coordenada {
    int linha;
    int coluna;
} Coordenada;

// Estrutura para representar uma antena
typedef struct Antena {
    char frequencia;
    Coordenada localizacao;
    struct Antena* proximo;
} Antena;

// Estrutura para representar uma localização com efeito nefasto
typedef struct EfeitoNefasto {
    Coordenada localizacao;
    struct EfeitoNefasto* proximo;
} EfeitoNefasto;

// Célula da matriz
typedef struct CelulaMatriz {
    Coordenada pos;
    char valor;
    struct CelulaMatriz* prox;
} CelulaMatriz;

typedef struct {
    CelulaMatriz* matriz;
    Antena* antenas;
} MatrizAntenas;  // Para devolver a matriz e antenas juntas

typedef struct {
    Antena* lista;
    CelulaMatriz* matriz;
} ResultadoRemocao;  // Para devolver a lista e a matriz após a remoção
