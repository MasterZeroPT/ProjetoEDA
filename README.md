# Projeto EDA

Este repositório contém o projeto desenvolvido para a disciplina de Estruturas de Dados e Algoritmos (EDA) no IPCA. Implementa um sistema com uma mapa de antenas e os seus efeitos nefastos utilizando a linguagem C.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
ProjetoEDA/
├── src/
│   ├── funcao.c
│   ├── funcao.h
│   ├── struct.h
│   ├── main.c
├── build/
│   ├── funcao.o
│   ├── main.o
│   ├── libfuncao.a
├── makefile
├── doxygen/
└── README.md
```

### Arquivos principais

- **src/funcao.c**: Implementação das funções principais do projeto.
- **src/funcao.h**: Cabeçalho com as definições das funções.
- **src/struct.h**: Definição das estruturas de dados utilizadas no projeto.
- **src/main.c**: Arquivo principal que contém a função `main`.
- **makefile**: Arquivo para automação da compilação e construção do projeto.

## Como Compilar

Para compilar o projeto, certifique-se de que você possui o GCC instalado. Em seguida, execute o comando:

```bash
make
```

Isso irá gerar o executável `prog` na raiz do projeto.

## Como Executar

Após a compilação, o programa pode ser executado com o comando:

```bash
./prog
```

## Limpeza

Para limpar os arquivos gerados durante a compilação, execute:

```bash
make clean
```

## Dependências

- GCC (GNU Compiler Collection)
- Sistema operacional compatível com `make`

## Autor

Pedro Andrade - 31497 1º Ano LESI
