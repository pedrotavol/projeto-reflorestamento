#ifndef _PROJETO_H
#define _PROJETO_H

//Esta biblioteca define o TAD Projeto (de Reflorestamento) e implementa as funções de manipulação
//de lista duplamente encadeada de projetos (com nó descritor).

#include "arvore.h" //(Depende da biblioteca arvore.h)

typedef struct projeto{
    char nomeProjeto[60], descricao[100], dataDeInicio[12]; //dia/mes/ano (00/00/0000)
    ListaArvores arvores;
} Projeto;

typedef struct noProjeto{
    struct noProjeto *prox, *ant;
    Projeto info;
} NoProjeto;

typedef struct descritorProjeto{
    NoProjeto *inicio, *fim;
    int quantDeProjetos;
} DescritorProjeto;

typedef DescritorProjeto* ListaProjetos;

ListaProjetos criarListaProjetos(); //Remove projeto da lista de projetos
int adicionarProjetoOrdenado(ListaProjetos lista, Projeto projeto); //Adiciona projeto na lista em ordem alfabetica
int removerProjeto(ListaProjetos lista, Projeto projeto); //Remove projeto da lista de projetos
int buscarProjetoPorNome(char *nomeDoProjeto, ListaProjetos lista, Projeto *projetoDest); //Busca projeto pelo nome e salva as informações em projetoDest
void imprimirProjetos(NoProjeto *inicio); //Imprime nome dos projetos recursivamente
int contarArvoresProjetos(NoProjeto *inicio); //Calcula o total de árvores plantadas de uma lista de projetos recursivamente
void liberarListaProjetos(ListaProjetos lista); //Libera a memoria alocada pela lista de projetos

#endif // _PROJETO_H

