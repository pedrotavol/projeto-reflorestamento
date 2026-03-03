#include "projeto.h"

ListaProjetos criarListaProjetos(){ //Cria e inicializa uma lista de projetos
    ListaProjetos lista = (ListaProjetos)malloc(sizeof(*lista));

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantDeProjetos = 0;

    return lista; //Retorna descritor da lista alocada
}

int adicionarProjetoOrdenado(ListaProjetos lista, Projeto projeto){ //Adiciona projeto na lista em ordem alfabetica
    NoProjeto *novoProjeto = (NoProjeto*)malloc(sizeof(NoProjeto));
    if(novoProjeto == NULL){ //Se a alocação deu errado
        return 0;
    }

    novoProjeto->info = projeto;
    novoProjeto->ant = NULL;
    novoProjeto->prox = NULL;

    NoProjeto *atual = lista->inicio;

    //Percorre a lista até encontrar a posição alfabeta correta do novo projeto ou até que a lista acabe
    while(atual != NULL && strcmp(novoProjeto->info.nomeProjeto, atual->info.nomeProjeto) > 0)
        atual = atual->prox;

    if(atual == lista->inicio){ //Se a posição correta for no início
        novoProjeto->prox = lista->inicio; //O proximo de novo vira o atual inicio

        if(lista->quantDeProjetos > 0) //Se a lista não está vazia
            lista->inicio->ant = novoProjeto; //Novo vira o anterior do atual inicio
        else //Se a lista está vazia
            lista->fim = novoProjeto; //O fim coincide com o inicio

        lista->inicio = novoProjeto; //Novo vira o novo inicio da lista
    }
    else if(atual == NULL){ //Se a posição correta for no final
        novoProjeto->ant = lista->fim; //O anterior de novo vira o atual fim
        lista->fim->prox = novoProjeto; //Novo vira o proximo do fim atual
        lista->fim = novoProjeto; //Novo vira o novo fim
    }
    else{ //Se a posição está no meio, coloca novo entre o anterior do atual e atual
        novoProjeto->prox = atual;
        novoProjeto->ant = atual->ant;

        atual->ant->prox = novoProjeto;
        atual->ant = novoProjeto;
    }

    lista->quantDeProjetos++;

    return 1;
}

int removerProjeto(ListaProjetos lista, Projeto projeto){ //Remove projeto da lista de projetos
    if(lista->quantDeProjetos == 0){ //Se a lista estiver vazia
        return 0;
    }
    NoProjeto *atual = lista->inicio;

    while(atual != NULL){
        if(strcmp(atual->info.nomeProjeto, projeto.nomeProjeto) == 0)
            break;

        atual = atual->prox;
    }

    if(atual == NULL) //Se o projeto não foi encontrado
        return 0;

    if(atual == lista->inicio){ //Se o elemento removido for o inicio da lista
        if(lista->quantDeProjetos == 1){ //Se o elemento removido for o unico da lista
            lista->inicio = NULL;
            lista->fim = NULL;
        }
        else{
            lista->inicio = atual->prox; //O inicio vira o proximo elemento
            atual->prox->ant = NULL; //Atualiza o anterior do novo inicio
        }
    }
    else if(atual == lista->fim){ //Se o elemento removido for o fim da lista
        lista->fim = atual->ant; //O fim vira o elemento anterior
        atual->ant->prox = NULL; //Atualiza o proximo do novo fim
    }
    else{ //Se o elemento removido estiver no meio da lista
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }

    lista->quantDeProjetos--;

    liberarListaArvores(atual->info.arvores); //Liberando memória alocada pela lista de árvores do projeto
    free(atual); //Liberando memoria alocada pelo nó do projeto

    return 1;
}

int buscarProjetoPorNome(char *nomeDoProjeto, ListaProjetos lista, Projeto *projetoDest){ //Busca projeto pelo nome e salva as informações em projetoDest
    NoProjeto *atual = lista->inicio;

    while(atual != NULL){
        if(strcmp(atual->info.nomeProjeto, nomeDoProjeto) == 0){
            *projetoDest = atual->info;
            return 1;
        }
        atual = atual->prox;
    }

    return 0;
}

void imprimirProjetos(NoProjeto *inicio){ //Imprime nome dos projetos recursivamente
    if(inicio == NULL)
        return;

    printf("%s\n", inicio->info.nomeProjeto);

    imprimirProjetos(inicio->prox);
}

int contarArvoresProjetos(NoProjeto *inicio){ //Calcula o total de árvores de uma lista de projetos recursivamente
    if(inicio == NULL)
        return 0;

    return contarArvores(inicio->info.arvores->inicio) + contarArvoresProjetos(inicio->prox);
}

void liberarListaProjetos(ListaProjetos lista){ //Libera a memoria alocada pela lista de projetos
    NoProjeto *copia;

    while(lista->inicio != NULL){
        copia = lista->inicio;
        lista->inicio = lista->inicio->prox;

        liberarListaArvores(copia->info.arvores); //Liberando memória alocada da lista de arvores de cada projeto
        free(copia); //Liberando memoria de cada no da lista de projetos
    }
    free(lista); //Liberando descritor
}
