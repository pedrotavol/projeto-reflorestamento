#include "arvore.h"

ListaArvores criarListaArvores(){ //Cria e inicializa uma lista de árvores
    ListaArvores lista = (ListaArvores)malloc(sizeof(*lista));
    if(lista == NULL){ //Se a alocação deu errado
        return NULL;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantEspecies = 0;

    return lista; //Retorna o descritor da lista alocada
}

int adicionarArvoreOrdenada(ListaArvores lista, Arvore arvore, int quantidade){ //Adiciona árvore alfabeticamente e incrementa quantidade de arvores na lista
    NoArvore *novaArvore = (NoArvore*)malloc(sizeof(NoArvore));
    if(novaArvore == NULL){ //Se a alocação deu errado
        return 0;
    }

    novaArvore->quantDaEspecie = quantidade;
    novaArvore->info = arvore;
    novaArvore->ant = NULL;
    novaArvore->prox = NULL;

    NoArvore *atual = lista->inicio;

    //Percorre a lista até encontrar a posição alfabeta correta da nova árvore ou até que a lista acabe
    while(atual != NULL && strcmp(novaArvore->info.nomeCientifico, atual->info.nomeCientifico) > 0)
        atual = atual->prox;


    if(atual == lista->inicio){ //Se a posição correta for no início
        novaArvore->prox = lista->inicio; //O proximo de novo vira o atual inicio

        if(lista->quantEspecies > 0) //Se a lista não está vazia
            lista->inicio->ant = novaArvore; //Novo vira o anterior do atual inicio
        else //Se a lista está vazia
            lista->fim = novaArvore; //O fim coincide com o inicio

        lista->inicio = novaArvore; //Novo vira o novo inicio da lista
    }
    else if(atual == NULL){ //Se a posição correta for no final
        novaArvore->ant = lista->fim; //O anterior de novo vira o atual fim
        lista->fim->prox = novaArvore; //Novo vira o proximo do fim atual
        lista->fim = novaArvore; //Novo vira o novo fim
    }
    else{ //Se a posição está no meio, coloca novo entre o anterior do atual e atual
        novaArvore->prox = atual;
        novaArvore->ant = atual->ant;

        atual->ant->prox = novaArvore;
        atual->ant = novaArvore;
    }

    lista->quantEspecies++;

    return 1;
}

int removerArvores(ListaArvores lista, Arvore arvore){ //Remove árvore da lista de árvores
    if(lista->quantEspecies == 0) //Se a lista estiver vazia
        return 0;

    NoArvore *atual = lista->inicio;

    while(atual != NULL){ //Enquanto houver elementos na lista
        if(strcmp(atual->info.nomeCientifico, arvore.nomeCientifico) == 0) //Encontre aquele com o mesmo nome
            break;

        atual = atual->prox; //Percorre a lista
    }

    if(atual == NULL) //Se a arvore não foi encontrada
        return 0;

    if(atual == lista->inicio){ //Se o elemento removido for o inicio da lista
        if(lista->quantEspecies == 1){ //Se o elemento removido for o unico da lista
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

    lista->quantEspecies--;

    free(atual); //Libera memoria alocada pelo no

    return 1;
}

int buscarArvorePorNome(char *nomeDaArvore, ListaArvores lista, Arvore *arvoreDest){ //Busca arvore pelo nome e salva as informações em arvoreDest
    NoArvore *atual = lista->inicio;

    while(atual != NULL){ //Enquanto ainda houver elementos na lista
        if(strcmp(atual->info.nomeCientifico, nomeDaArvore) == 0){ //Se o elemento foi encontrado
            *arvoreDest = atual->info; //Armazena as ifnormações da arvore encontrada na arvoreDest
            return 1;
        }
        atual = atual->prox; //Percorre a lista
    }

    return 0;
}

void imprimirArvoresSimples(NoArvore *inicio){ //Imprime nome das árvores recursivamente
    if(inicio == NULL) //Se chegamos no ultimo nó
        return;

    printf("%s\n", inicio->info.nomeCientifico);

    imprimirArvoresSimples(inicio->prox);
}

void imprimirArvoresCompleto(NoArvore *inicio){ //Imprime todas as informações das árvores recursivamente
    if(inicio == NULL) //Se chegamos no ultimo nó
        return;

    printf("\nEspecie: %s\n", inicio->info.nomeCientifico);
    printf("Origem: %s\n", (inicio->info.origem == 1) ? "Nativa" : "Exotica"); //Verdadeiro : Falso
    printf("Quantidade: %d\n", inicio->quantDaEspecie);

    imprimirArvoresCompleto(inicio->prox);
}

int contarArvores(NoArvore *inicio){ //Calcula recursivamente o total de arvores de uma lista de árvores
    if(inicio == NULL)
        return 0;

    return inicio->quantDaEspecie + contarArvores(inicio->prox);
}

void liberarListaArvores(ListaArvores lista){ //Libera a memória alocada pela lista de árvores
    NoArvore *copia;

    while(lista->inicio != NULL){
        copia = lista->inicio;
        lista->inicio = lista->inicio->prox;

        free(copia); //Liberando memória alocada por cada nó
    }
    free(lista); //Liberando memória alocada pelo descritor
}

