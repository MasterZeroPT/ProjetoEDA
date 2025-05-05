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

int main() {
    // LerInput devolve a matriz e antenas juntas
    MatrizAntenas resultado = LerInput("./src/input.txt");
    CelulaMatriz* matriz = resultado.matriz;
    Antena* listaAntenas = resultado.antenas;

    // InserirAntena devolve a nova lista
    //listaAntenas = InserirAntena(listaAntenas, 'A', 0, 0);
    //matriz = AdicionarCelula(matriz, 0, 0, 'A');  // Atualiza a matriz separadamente

    //listaAntenas = InserirAntena(listaAntenas, 'B', 1, 2);
    //matriz = AdicionarCelula(matriz, 1, 2, 'B');

    //listaAntenas = InserirAntena(listaAntenas, 'C', 2, 4);
    //matriz = AdicionarCelula(matriz, 2, 4, 'C');

    // RemoverAntena devolve a lista e matriz atualizadas
    ResultadoRemocao res = RemoverAntena(listaAntenas, matriz, 0, 0);
    listaAntenas = res.lista;
    matriz = res.matriz;

    matriz = InserirEfeitoNefasto(matriz);
    listaAntenas = AtualizarListaAntenas(matriz);

    ImprimirMatriz(matriz);

    // Liberta a memória alocada para a matriz
    while (matriz) {
        CelulaMatriz* temp = matriz;
        matriz = matriz->prox;
        free(temp);
    }

    // Liberta a memória alocada para a lista de antenas
    while (listaAntenas) {
        Antena* temp = listaAntenas;
        listaAntenas = listaAntenas->proximo;
        free(temp);
    }

    return 0;
}