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
#include "grafos.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // LerInput devolve a matriz e antenas juntas
    MatrizAntenas resultado = LerInput("./src/input.txt");
    CelulaMatriz* matriz = resultado.matriz;
    Antena* listaAntenas = resultado.antenas;

    // InserirAntena devolve a nova lista
    listaAntenas = InserirAntena(listaAntenas, 'A', 0, 0);
    matriz = AdicionarCelula(matriz, 0, 0, 'A');  // Atualiza a matriz separadamente

    listaAntenas = InserirAntena(listaAntenas, 'B', 1, 2);
    matriz = AdicionarCelula(matriz, 1, 2, 'B');

    listaAntenas = InserirAntena(listaAntenas, 'C', 2, 4);
    matriz = AdicionarCelula(matriz, 2, 4, 'C');

    // RemoverAntena devolve a lista e matriz atualizadas
    ResultadoRemocao res = RemoverAntena(listaAntenas, matriz, 0, 0);
    listaAntenas = res.lista;
    matriz = res.matriz;

    matriz = InserirEfeitoNefasto(matriz);
    listaAntenas = AtualizarListaAntenas(matriz);

    ImprimirMatriz(matriz);


    // Cria o grafo das antenas
    GrafoAntenas* grafos = CriarGrafoAntenas(matriz);

    // Cria a lista de adjacências para as antenas com a mesma frequência
    CriarListaAdjacencias(grafos);

    // Exemplo de iteração sobre o grafo com a lista de adjacências
    for (GrafoAntenas* g = grafos; g; g = g->proximo) {
        printf("Frequência: %c\n", g->frequencia);
        for (NoGrafo* n = g->listaAdjacencia; n; n = n->proximo) {
            printf("  Localização: (%d, %d)\n", n->localizacao.linha, n->localizacao.coluna);
            for (NoGrafo* adj = n->adjacentes; adj; adj = adj->proximo) {
                //printf("    Adjacente: (%d, %d)\n", adj->localizacao.linha, adj->localizacao.coluna);
            }
        }
    }

    // Exemplo: DFS a partir da antena de frequência 'A' na posição (0,0)
    Coordenada origem;
    origem.linha = 1;
    origem.coluna = 6;
    Coordenada destino;
    destino.linha = 11;
    destino.coluna = 10;
    DFS_Antena(grafos, 'A', origem);
    BFS_Antena(grafos, 'A', origem);
    ListarTodosCaminhos(grafos, 'A', origem, destino);
    ListarInterseccoesArestas(grafos);

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

    // Liberação de memória do grafo (implemente uma função para liberar)

    return 0;
}