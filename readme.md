# Trabalho Prático de EDA

Este repositório contém o trabalho prático da disciplina de Estruturas de Dados e Algoritmos (EDA). O objetivo deste projeto é implementar um sistema de mapa de antenas e os vários efeitos nefastos utilizando a linguagem C.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
TrabalhoPratico/
├── src/
│   ├── funcao.c       # Implementação das funções
│   ├── funcao.h       # Cabeçalho das funções
│   ├── main.c         # Arquivo principal
├── build/             # Diretório para arquivos compilados
├── prog               # Executável gerado
├── makefile           # Arquivo de automação de compilação
├── doxygen            # Documentação Doxygen
└── readme.md          # Documentação do projeto
```

## Requisitos

- GCC (GNU Compiler Collection)
- Make

## Como Compilar e Executar

1. Certifique-se de que o `make` está instalado no seu sistema.
2. Navegue até o diretório do projeto.
3. Execute o comando `make` para compilar o projeto.
4. O executável será gerado com o nome `prog`.
5. Para executar o programa, utilize o comando:
    ```
    ./prog
    ```

## Limpeza

Para remover os arquivos compilados e o executável, execute:
```
make clean
```

## Funcionalidades

- **funcao.c**: Contém a implementação das funções principais do projeto.
- **main.c**: Arquivo principal que utiliza as funções implementadas em `funcao.c`.

## Autor

Pedro Andrade - 31497 1º Ano LESI

