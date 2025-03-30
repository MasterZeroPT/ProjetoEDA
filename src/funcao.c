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

/**
 * @brief Lê a entrada de um ficheiro, processa-a numa matriz e cria uma lista ligada de antenas.
 * 
 * Esta função lê um ficheiro especificado pelo parâmetro `nomeficheiro`, processa o seu conteúdo
 * numa matriz 2D (ignorando espaços) e cria uma lista ligada de antenas com base nos dados da matriz.
 * Cada antena é representada por um caractere na matriz que não seja um '.' (ponto).
 * 
 * @param nomeficheiro O nome do ficheiro a ser lido.
 * @param listaAntenas Um ponteiro para a cabeça da lista ligada de antenas. Será atualizado com a lista criada.
 * @param matrizOut Um ponteiro para a matriz 2D que será criada e preenchida com os dados do ficheiro.
 * @param linhasOut Um ponteiro para um inteiro que armazenará o número de linhas da matriz.
 * @param colunasOut Um ponteiro para um inteiro que armazenará o número de colunas da matriz.
 * 
 * @return `true` se o ficheiro foi lido e processado com sucesso, `false` caso contrário.
 * 
 * @note O chamador é responsável por liberar a memória alocada para a matriz e a lista ligada de antenas.
 * 
 * @warning Certifique-se de que o ficheiro existe e está acessível. Falhas na alocação de memória resultarão
 *          em uma mensagem de erro e a função retornará `false`.
 */
bool LerInput(char* nomeficheiro, Antena** listaAntenas, char*** matrizOut, int* linhasOut, int* colunasOut) {
    FILE* fp = fopen(nomeficheiro, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro %s", nomeficheiro);
        return false;
    }
    int linhas = 0, capacidadeLinhas = 50;
    int colunas = 0;
    char** matriz = malloc(capacidadeLinhas * sizeof(char*)); // aloca um array de apontadores
    if (!matriz) { //verificar se o malloc da matriz funcionou
        printf("Erro ao alocar memória para a matriz.\n");
        fclose(fp);
        return false;
    }

    *listaAntenas = NULL; //inicializar a lista ligada
    char* linha = malloc(256 * sizeof(char)); // buffer para temporariamente armazenar cada linha do ficheiro
    if (!linha) {
        printf("Erro ao alocar memória para o buffer da linha.\n");
        fclose(fp);
        free(matriz);
        return false;
    }

    while (fgets(linha, 256, fp)) { // Lê uma linha do ficheiro apontado por 'fp' e armazena no buffer 'linha'.
        if (linhas >= capacidadeLinhas) { // verifica se a memória alocada é suficiente e realoca para uma memória maior se não for.
            capacidadeLinhas *= 2; // duplica o tamanho da capacidade de linhas
            matriz = realloc(matriz, capacidadeLinhas * sizeof(char*));
            if (!matriz) {
                printf("Erro ao realocar memória.\n");
                free(linha);
                fclose(fp);
                return false;
            }
        }

        // Conta o número de colunas ignorando os espaços
        for (int i = 0; linha[i] != '\0'; i++) {
            if (linha[i] != ' ' && linha[i] != '\n') {
                colunas++;
            }
        }

        // Aloca memória para a linha atual
        matriz[linhas] = malloc((colunas + 1) * sizeof(char)); // "+1" para garantir espaço para o "\0" na memória
        if (!matriz[linhas]) {
            printf("Erro ao alocar memória para a linha %d.\n", linhas);
            free(linha);
            fclose(fp);
            return false;
        }

        // Preenche a linha da matriz ignorando os espaços
        int colunaAtual = 0;
        for (int i = 0; linha[i] != '\0'; i++) {
            if (linha[i] != ' ' && linha[i] != '\n') {
                matriz[linhas][colunaAtual++] = linha[i]; // Constroi a matriz de forma organizada sem espaços
            }
        }
        matriz[linhas][colunaAtual] = '\0'; // Adiciona o fim da string

        // Processa os caracteres da linha para criar a lista ligada de antenas
        for (int coluna = 0; coluna < colunas; coluna++) {
            if (matriz[linhas][coluna] != '.') {
                Antena* novaAntena = malloc(sizeof(Antena)); // Verifica se a posição especificada na matriz não está vazia ('.'). Se a posição estiver ocupada, aloca memória para uma nova estrutura Antena.
                if (!novaAntena) {
                    printf("Erro ao alocar memória para a antena.\n");
                    free(linha);
                    fclose(fp);
                    return false;
                }
                novaAntena->frequencia = matriz[linhas][coluna];
                novaAntena->localizacao.linha = linhas;
                novaAntena->localizacao.coluna = coluna;
                novaAntena->proximo = *listaAntenas;
                *listaAntenas = novaAntena;
            }
        }

        linhas++;
    }
    free(linha); // Liberta o buffer da linha
    fclose(fp);

    // Retorna os resultados 
    *matrizOut = matriz;
    *linhasOut = linhas;
    *colunasOut = colunas;

    return true;
}

/**
 * @param listaAntenas Ponteiro para a lista de antenas onde a nova antena será inserida.
 * @param frequencia   Caracter que representa a frequência da antena a ser inserida.
 * @param linha        Inteiro que indica a linha onde a antena será posicionada.
 * @param coluna       Inteiro que indica a coluna onde a antena será posicionada.
 */
bool InserirAntena(Antena** listaAntenas, char frequencia, int linha, int coluna) {
    // Verifica se já existe uma antena na mesma coordenada
    for (Antena* atual = *listaAntenas; atual; atual = atual->proximo) { // "; atual;" o loop continua enquanto a variável não for nula (NULL)
        if (atual->localizacao.linha == linha && atual->localizacao.coluna == coluna) {
            //printf("Já existe uma antena na posição (%d, %d).\n", linha, coluna); //está com bugs
            return false;
        }
    }

    // Cria uma nova antena
    Antena* novaAntena = malloc(sizeof(Antena));
    if (!novaAntena) {
        printf("Erro ao alocar memória para a nova antena.\n");
        return false;
    }

    novaAntena->frequencia = frequencia;
    novaAntena->localizacao.linha = linha;
    novaAntena->localizacao.coluna = coluna;
    novaAntena->proximo = *listaAntenas;
    *listaAntenas = novaAntena;

    // Libera a memória da antena criada, caso necessário


    return true;
}

/**
 * @brief Imprime a lista de antenas na consola.
 * 
 * Esta função percorre uma lista ligada de antenas e imprime as informações
 * de cada antena, incluindo a frequência e a sua localização (linha e coluna).
 * Caso a lista esteja vazia, uma mensagem informativa será exibida.
 * 
 * @param listaAntenas Ponteiro para o início da lista ligada de antenas.
 */
void ImprimirAntenas(Antena* listaAntenas) {
    if (!listaAntenas) {
        printf("A lista de antenas está vazia.\n");
        return;
    }

    printf("Lista de Antenas:\n");
    for (Antena* atual = listaAntenas; atual; atual = atual->proximo) {
        printf("Antena: %c na posição (%d, %d)\n", 
               atual->frequencia, 
               atual->localizacao.linha, 
               atual->localizacao.coluna);
    }
}

/**
 * @brief Remove uma antena da lista de antenas com base na frequência e localização fornecidas.
 * 
 * @param listaAntenas Ponteiro para o ponteiro da lista de antenas.
 * @param frequencia Caracter que representa a frequência da antena a ser removida.
 * @param linha Inteiro que representa a linha da localização da antena.
 * @param coluna Inteiro que representa a coluna da localização da antena.
 * @return true Se a antena foi encontrada e removida com sucesso.
 * @return false Se a antena não foi encontrada ou a lista de antenas está vazia.
 * 
 * @note A função libera a memória alocada para a antena removida.
 * @note Caso a lista esteja vazia, uma mensagem será exibida no console.
 * @note Caso a antena não seja encontrada, uma mensagem será exibida no console.
 */
bool RemoverAntena(Antena** listaAntenas, char frequencia, int linha, int coluna) {
    if (!*listaAntenas) {
        printf("A lista de antenas está vazia.\n");
        return false;
    }

    Antena* atual = *listaAntenas;
    Antena* anterior = NULL;

    while (atual) {
        if (atual->frequencia == frequencia &&
            atual->localizacao.linha == linha &&
            atual->localizacao.coluna == coluna) {
            
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                *listaAntenas = atual->proximo;
            }

            free(atual);
            printf("Antena %c na posição (%d, %d) removida com sucesso.\n", frequencia, linha, coluna);
            return true;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("Antena %c na posição (%d, %d) não encontrada.\n", frequencia, linha, coluna);
    return false;
}

/**
 * @brief Insere efeitos nefastos em uma matriz com base no alinhamento de antenas.
 *
 * Esta função percorre uma matriz bidimensional e verifica o alinhamento entre antenas
 * (representadas por caracteres diferentes de '.' e '#'). Quando duas antenas com a mesma
 * frequência estão alinhadas horizontalmente, verticalmente ou diagonalmente, e a distância
 * entre elas é par, um efeito nefasto (representado por '#') é inserido na extremidade entre
 * as antenas, desde que esse espaço esteja vazio (representado por '.').
 *
 * @param matriz Ponteiro para a matriz bidimensional de caracteres.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 */
void InserirEfeitoNefasto(char** matriz, int linhas, int colunas) {
    // Iterar sobre todas as células da matriz
    for (int linha1 = 0; linha1 < linhas; linha1++) {
        for (int coluna1 = 0; coluna1 < colunas; coluna1++) {
            char antena1 = matriz[linha1][coluna1];
            if (antena1 == '.' || antena1 == '#') continue; // Ignorar espaços livres e efeitos já aplicados

            // Verificar alinhamento com outras antenas
            for (int linha2 = 0; linha2 < linhas; linha2++) {
                for (int coluna2 = 0; coluna2 < colunas; coluna2++) {
                    char antena2 = matriz[linha2][coluna2];
                    if (antena2 == '.' || antena2 == '#' || (linha1 == linha2 && coluna1 == coluna2)) continue;

                    // Verificar se as antenas têm a mesma frequência
                    if (antena1 == antena2) {
                        // Verificar alinhamento horizontal, vertical ou diagonal
                        if (linha1 == linha2 || coluna1 == coluna2 || abs(linha1 - linha2) == abs(coluna1 - coluna2)) {
                            // Calcular incrementos para linha e coluna
                            int incLinha = (linha1 == linha2) ? 0 : (linha2 > linha1 ? 1 : -1);
                            int incColuna = (coluna1 == coluna2) ? 0 : (coluna2 > coluna1 ? 1 : -1);

                            // Calcular a distância total
                            int distancia = (linha1 == linha2) ? abs(coluna2 - coluna1) : abs(linha2 - linha1);

                            // Verificar se a distância é par (para aplicar o efeito nas extremidades)
                            if (distancia % 2 == 0) {
                                // Calcular as extremidades
                                int linhaEfeito1 = linha1 + incLinha;
                                int colunaEfeito1 = coluna1 + incColuna;
                                int linhaEfeito2 = linha2 - incLinha;
                                int colunaEfeito2 = coluna2 - incColuna;

                                // Verificar se as extremidades estão dentro dos limites da matriz e são espaços livres
                                if (linhaEfeito1 >= 0 && linhaEfeito1 < linhas &&
                                    colunaEfeito1 >= 0 && colunaEfeito1 < colunas &&
                                    matriz[linhaEfeito1][colunaEfeito1] == '.') {
                                    matriz[linhaEfeito1][colunaEfeito1] = '#';
                                }
                                if (linhaEfeito2 >= 0 && linhaEfeito2 < linhas &&
                                    colunaEfeito2 >= 0 && colunaEfeito2 < colunas &&
                                    matriz[linhaEfeito2][colunaEfeito2] == '.') {
                                    matriz[linhaEfeito2][colunaEfeito2] = '#';
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
/**
 * @brief Atualiza uma lista ligada de antenas com base em uma matriz de dados.
 * 
 * Esta função limpa a lista ligada existente de antenas e a atualiza com os dados dos efeitos nefastos 
 * fornecidos na matriz da função anterior. 
 * Cada célula da matriz pode representar uma
 * antena ou outro tipo de informação relevante para a lista.
 * 
 * @param listaAntenas Ponteiro para o ponteiro da lista ligada de antenas.
 *                      A lista será limpa e atualizada pela função.
 * @param matriz Matriz de caracteres contendo os dados para atualizar a lista.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 */
void AtualizarListaLigada(Antena** listaAntenas, char** matriz, int linhas, int colunas) {
    // Limpar a lista ligada existente
    while (*listaAntenas) {
        Antena* temp = *listaAntenas;
        *listaAntenas = (*listaAntenas)->proximo;
        free(temp);
    }

    // Criar uma nova lista ligada com base na matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] != '.' && matriz[i][j] != '#') { // Apenas antenas originais
                Antena* novaAntena = malloc(sizeof(Antena));
                if (!novaAntena) {
                    printf("Erro ao alocar memória para a antena.\n");
                    return;
                }
                novaAntena->frequencia = matriz[i][j];
                novaAntena->localizacao.linha = i;
                novaAntena->localizacao.coluna = j;
                novaAntena->proximo = *listaAntenas;
                *listaAntenas = novaAntena;
            }
        }
    }
}

/**
 * @brief Imprime uma matriz de caracteres na consola.
 *
 * Esta função exibe uma matriz bidimensional de caracteres na consola,
 * formatada com os elementos separados por espaços e cada linha numa nova linha.
 *
 * @param matriz Ponteiro para a matriz de caracteres a ser impressa.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 */
void ImprimirMatriz(char** matriz, int linhas, int colunas) {
    printf("\nMatriz atual:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}




