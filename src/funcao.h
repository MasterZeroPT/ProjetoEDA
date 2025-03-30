/**
 * @file funcao.h
 * @author Pedro Andrade (a31497@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-03-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include "struct.h"

bool LerInput(char* nomeficheiro, Antena** listaAntenas, char*** matrizOut, int* linhasOut, int* colunasOut);
bool InserirAntena(Antena** listaAntenas, char frequencia, int linha, int coluna);
void ImprimirAntenas(Antena* listaAntenas);
bool RemoverAntena(Antena** listaAntenas, char frequencia, int linha, int coluna);
void InserirEfeitoNefasto(char** matriz, int linhas, int colunas);
void ImprimirMatriz(char** matriz, int linhas, int colunas);
void AtualizarListaLigada(Antena** listaAntenas, char** matriz, int linhas, int colunas);