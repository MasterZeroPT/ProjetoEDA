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

MatrizAntenas LerInput(char* nomeFicheiro);  
Antena* InserirAntena(Antena* lista, char freq, int linha, int coluna);  
ResultadoRemocao RemoverAntena(Antena* lista, CelulaMatriz* matriz, int linha, int coluna);  
Antena* AtualizarListaAntenas(CelulaMatriz* matriz);
void ImprimirMatriz(CelulaMatriz* matriz);
CelulaMatriz* AdicionarCelula(CelulaMatriz* matriz, int linha, int coluna, char valor);
CelulaMatriz* InserirEfeitoNefasto(CelulaMatriz* matriz);