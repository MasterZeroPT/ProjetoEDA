/**
 * @file main.c
 * @author Pedro Andrade (a31497@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "funcao.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

Antena* listaAntenas = NULL; // Declare listaAntenas before calling LerInput
char** matriz = NULL;
int linhas = 0, colunas = 0;
LerInput("./src/exemplo.txt", &listaAntenas, &matriz, &linhas, &colunas);

// Inserir algumas antenas manualmente
//InserirAntena(&listaAntenas, 'A', 0, 0);
//InserirAntena(&listaAntenas, 'B', 1, 2);
//InserirAntena(&listaAntenas, 'C', 2, 4);
printf("\n");

// Imprimir a lista de antenas
//ImprimirAntenas(listaAntenas);
printf("\n");

// Remover uma antena
RemoverAntena(&listaAntenas, 'A', 0, 0);
printf("\n");

//ImprimirAntenas(listaAntenas);
printf("\n");

// Aplicar o efeito nefasto na matriz
InserirEfeitoNefasto(matriz, linhas, colunas);

// Atualizar a lista ligada com base na matriz da função InserirEfeitoNefasto
AtualizarListaLigada(&listaAntenas, matriz, linhas, colunas);

// Imprimir a matriz final
ImprimirMatriz(matriz, 12, 12);
printf("\n");

// Liberar memória da lista de antenas
while (listaAntenas) {
    Antena* temp = listaAntenas;
    listaAntenas = listaAntenas->proximo;
    free(temp);
}

// Liberar memória da lista de efeitos nefastos
EfeitoNefasto* listaEfeitos = NULL; // Declare and initialize the list of effects
while (listaEfeitos) {
    EfeitoNefasto* temp = listaEfeitos;
    listaEfeitos = listaEfeitos->proximo;
    free(temp);
}

// Liberar memória da matriz
if (matriz) {
    for (int i = 0; i < linhas; i++) { 
        free(matriz[i]);
    }
    free(matriz);
}

}