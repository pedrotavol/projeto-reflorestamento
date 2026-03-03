#ifndef _ARVORE_H
#define _ARVORE_H

//Esta biblioteca define o TAD Árvore e implementa as funções de manipulação
//de uma lista duplamente encadeada de árvores (com nó descritor).

#include "ferramentas.h" //(Depende das funções auxiliares da biblioteca ferramentas)

typedef struct arvore{
    char nomeCientifico[60];
    int origem; //Nativa (1) ou Exótica (2)
} Arvore;

typedef struct noArvore{
    struct noArvore *prox, *ant;
    int quantDaEspecie;
    Arvore info;
} NoArvore;

typedef struct descritorArvore{
    NoArvore *inicio, *fim;
    int quantEspecies;
} DescritorArvore;

typedef DescritorArvore* ListaArvores;

ListaArvores criarListaArvores(); //Cria e inicializa uma lista de árvores
int adicionarArvoreOrdenada(ListaArvores lista, Arvore arvore, int quantidade); //Adiciona árvore à lista em ordem alfabética
int removerArvore(ListaArvores lista, Arvore arvore); //Remove árvore da lista de árvores
int buscarArvorePorNome(char *nomeDaArvore, ListaArvores lista, Arvore *arvoreDest); //Busca arvore pelo nome e salva as informações em arvoreDest
void imprimirArvoresSimples(NoArvore *inicio); //Imprime nome das árvores recursivamente
void imprimirArvoresCompleto(NoArvore *inicio); //Imprime todas as informações das árvores recursivamente
int contarArvores(NoArvore *inicio); //Calcula recursivamente o total de arvores de uma lista de árvores
void liberarListaArvores(ListaArvores lista); //Libera a memória alocada pela lista de árvores

#endif // _ARVORE_H
