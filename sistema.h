#ifndef _SISTEMA_H
#define _SISTEMA_H

//Biblioteca responsável pelas funções principais do sistema,
//incluindo leitura e impressão de dados e a manipulação de listas
//duplamente encadeadas de projetos e árvores (com nó descritor)

#include "projeto.h" //(Depende da biblioteca projeto.h)

int menu();

//Criação
Arvore criarArvore();
Projeto criarProjeto();

//Operações com Árvores
int cadastrarArvores(ListaArvores lista);

int cadastrarArvoreEmProjeto(ListaProjetos lista);
void listarArvoreDeProjeto(ListaProjetos lista);

int contarArvoreProjetoNome(ListaProjetos lista);
int contarTotalArvores(ListaProjetos lista);

//Operações com Projetos
int cadastrarProjetos(ListaProjetos lista);
void listarProjetos(ListaProjetos lista);

int removerProjetoPorNome(ListaProjetos lista);
int lerProjetoPorNome(ListaProjetos lista, Projeto *infoProjeto);
int pesquisarProjetosPorNome(ListaProjetos lista);

//Arquivos
int lerProjetosArquivo(ListaProjetos lista);
int gerarRelatorioProjetos(ListaProjetos lista);

#endif // _SISTEMA_H
