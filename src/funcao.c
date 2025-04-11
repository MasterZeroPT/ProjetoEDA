/**
 * @file funcao.c
 * @author Pedro Andrade (a31497@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-03-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "funcao.h"


// Adiciona uma célula à matriz ligada
CelulaMatriz* AdicionarCelula(CelulaMatriz* matriz, int linha, int coluna, char valor) {
    CelulaMatriz* nova = malloc(sizeof(CelulaMatriz));
    if (!nova) return NULL;
    nova->pos.linha = linha;
    nova->pos.coluna = coluna;
    nova->valor = valor;
    nova->prox = matriz;
    return nova;
}

// Lê um ficheiro de texto e cria a matriz ligada e a lista de antenas
MatrizAntenas LerInput(char* nomeFicheiro) {
    FILE* fp = fopen(nomeFicheiro, "r");
    MatrizAntenas resultado = {NULL, NULL};  // Inicializa vazio

    if (!fp) return resultado;

    char c;
    int linha = 0, coluna = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') { linha++; coluna = 0; continue; }
        if (c == ' ') continue;

        resultado.matriz = AdicionarCelula(resultado.matriz, linha, coluna, c);

        if (c != '.' && c != '#') {
            Antena* nova = malloc(sizeof(Antena));
            nova->frequencia = c;
            nova->localizacao.linha = linha;
            nova->localizacao.coluna = coluna;
            nova->proximo = resultado.antenas;
            resultado.antenas = nova;
        }
        coluna++;
    }
    fclose(fp);
    return resultado;
}


// Insere uma nova antena na lista e na matriz
Antena* InserirAntena(Antena* lista, char freq, int linha, int coluna) {
    // Verifica se já existe uma antena nessa posição
    for (Antena* a = lista; a; a = a->proximo) {
        if (a->localizacao.linha == linha && a->localizacao.coluna == coluna) {
            return lista;  // Não faz nada se já existir
        }
    }

    Antena* nova = malloc(sizeof(Antena));
    nova->frequencia = freq;
    nova->localizacao.linha = linha;
    nova->localizacao.coluna = coluna;
    nova->proximo = lista;
    return nova;  // Retorna a nova lista
}

// Remove a antena da lista e da matriz
ResultadoRemocao RemoverAntena(Antena* lista, CelulaMatriz* matriz, int linha, int coluna) {
    ResultadoRemocao res = {lista, matriz};

    // Remove da lista de antenas
    Antena *anterior = NULL, *atual = lista;
    while (atual) {
        if (atual->localizacao.linha == linha && atual->localizacao.coluna == coluna) {
            if (anterior) anterior->proximo = atual->proximo;
            else res.lista = atual->proximo;
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    // Remove da matriz
    CelulaMatriz *prev = NULL, *cur = matriz;
    while (cur) {
        if (cur->pos.linha == linha && cur->pos.coluna == coluna) {
            if (prev) prev->prox = cur->prox;
            else res.matriz = cur->prox;
            free(cur);
            break;
        }
        prev = cur;
        cur = cur->prox;
    }

    return res;
}

// Atualiza a lista de antenas com base na matriz
Antena* AtualizarListaAntenas(CelulaMatriz* matriz) {
    Antena* lista = NULL;
    while (matriz) {
        if (matriz->valor != '.' && matriz->valor != '#') {
            Antena* nova = malloc(sizeof(Antena));
            if (!nova) return NULL;
            nova->frequencia = matriz->valor;
            nova->localizacao = matriz->pos;
            nova->proximo = lista;
            lista = nova;
        }
        matriz = matriz->prox;
    }
    return lista;
}

// Aplica os efeitos nefastos na matriz 
CelulaMatriz* InserirEfeitoNefasto(CelulaMatriz* matriz) {
    CelulaMatriz* cursor1 = matriz;
    // Percorre todas as células da matriz
    while (cursor1) {
        // Ignora as células que não são antenas ('.' ou '#')
        if (cursor1->valor == '.' || cursor1->valor == '#') {
            cursor1 = cursor1->prox;
            continue;
        }
        CelulaMatriz* cursor2 = cursor1->prox; 
        // Compara a célula atual com todas as células seguintes
        while (cursor2) {
            // Verifica se as células têm a mesma frequência
            if (cursor1->valor == cursor2->valor) { 
                // Calcula a posição do primeiro ponto nefasto
                int x1 = 2 * cursor1->pos.linha - cursor2->pos.linha;
                int y1 = 2 * cursor1->pos.coluna - cursor2->pos.coluna;

                // Calcula a posição do segundo ponto nefasto
                int x2 = 2 * cursor2->pos.linha - cursor1->pos.linha;
                int y2 = 2 * cursor2->pos.coluna - cursor1->pos.coluna;

                // Verifica se o primeiro ponto nefasto está dentro dos limites
                if (x1 >= 0 && y1 >= 0) {
                    bool existe1 = false;
                    CelulaMatriz* m1 = matriz;
                    // Verifica se já existe uma célula na posição calculada
                    while (m1) {
                        if (m1->pos.linha == x1 && m1->pos.coluna == y1) {
                            // Se for uma célula vazia ('.'), transforma-a em '#'
                            if (m1->valor == '.') m1->valor = '#';
                            existe1 = true;
                            break;
                        }
                        m1 = m1->prox;
                    }
                    // Se não existir, adiciona uma nova célula com valor '#'
                    if (!existe1)
                        matriz = AdicionarCelula(matriz, x1, y1, '#');
                }

                // Verifica se o segundo ponto nefasto está dentro dos limites
                if (x2 >= 0 && y2 >= 0) {
                    bool existe2 = false;
                    CelulaMatriz* m2 = matriz;
                    // Verifica se já existe uma célula na posição calculada
                    while (m2) {
                        if (m2->pos.linha == x2 && m2->pos.coluna == y2) {
                            // Se for uma célula vazia ('.'), transforma-a em '#'
                            if (m2->valor == '.') m2->valor = '#';
                            existe2 = true;
                            break;
                        }
                        m2 = m2->prox;
                    }
                    // Se não existir, adiciona uma nova célula com valor '#'
                    if (!existe2)
                        matriz = AdicionarCelula(matriz, x2, y2, '#');
                }
            }
            cursor2 = cursor2->prox;
        }
        cursor1 = cursor1->prox;
    }
    return matriz;
}
    
// Imprime a matriz na consola (ordenada por linha e coluna)
void ImprimirMatriz(CelulaMatriz* matriz) {
    int maxLinha = 0, maxColuna = 0;
    CelulaMatriz* cursor = matriz;
    while (cursor) {
        if (cursor->pos.linha > maxLinha) maxLinha = cursor->pos.linha;
        if (cursor->pos.coluna > maxColuna) maxColuna = cursor->pos.coluna;
        cursor = cursor->prox;
    }

    for (int l = 0; l <= maxLinha; l++) {
        for (int c = 0; c <= maxColuna; c++) {
            char encontrado = '.';
            cursor = matriz;
            while (cursor) {
                if (cursor->pos.linha == l && cursor->pos.coluna == c) {
                    encontrado = cursor->valor;
                    break;
                }
                cursor = cursor->prox;
            }
            printf("%c ", encontrado);
        }
        printf("\n");
    }
}





