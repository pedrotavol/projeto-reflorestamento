#include "sistema.h"

int menu() {
    int operacao;

    printf("+---------------------------------------+\n");
    printf("|                MENU                   |\n");
    printf("+---------------------------------------+\n");

    printf("\n| PROJETOS\n");
    printf("| [1]  Cadastrar projeto(s)\n");
    printf("| [2]  Remover projeto por nome\n");
    printf("| [3]  Listar projeto(s)\n");
    printf("| [4]  Pesquisar projeto por nome\n");

    printf("\n| ARVORES\n");
    printf("| [5]  Cadastrar arvore em projeto\n");
    printf("| [6]  Remover especie de arvore em projeto\n");
    printf("| [7]  Listar arvores de um projeto\n");
    printf("| [8]  Contar arvores de um projeto\n");
    printf("| [9]  Total de arvores plantadas\n");

    printf("\n| ARQUIVOS E RELATORIOS\n");
    printf("| [10] Ler arquivo de projetos\n");
    printf("| [11] Gerar relatorio dos projetos\n\n");

    printf("| [0]  Sair\n");
    printf("_________________________________________\n\n");

    printf("\nDigite a operacao desejada: ");
    scanf("%d", &operacao);
    printf("\n");

    limparBuffer();

    return operacao;
}

Arvore criarArvore(){ //Cria e retorna árvore com as informações inseridas
    Arvore novaArvore;

    printf("\nInsira o nome cientifico da especie: ");
    lerString(novaArvore.nomeCientifico, sizeof(novaArvore.nomeCientifico)); //Ler nome da nova arvore

    do{ //Enquanto não inserir uma opção válida
        printf("Insira a origem da especie ([1] Nativa ou [2] Exotica): "); //Imprime a mensagem padrão
        scanf("%d", &novaArvore.origem); //Lê a opção
        limparBuffer(); //Limpa o \n

        if(novaArvore.origem != 1 && novaArvore.origem != 2){
            printf("Erro: operacao invalida.\n\n");
        }
    }while(novaArvore.origem != 1 && novaArvore.origem != 2);

    return novaArvore; //Retorna arvore com as novas informações
}

Projeto criarProjeto(){
    Projeto novoProjeto;

    printf("Insira o nome do projeto: ");
    lerString(novoProjeto.nomeProjeto, sizeof(novoProjeto.nomeProjeto)); //Lê nome do projeto

    printf("Insira a data de inicio do projeto (00/00/0000): ");
    lerString(novoProjeto.dataDeInicio, sizeof(novoProjeto.dataDeInicio)); //Lê data de início do projeto

    char op;
    do{ //Enquanto não inserir uma opção válida
        printf("Deseja inserir um descricao? (S ou N): "); //Imprime mensagem padrão
        scanf("%c", &op); //Lê a opção
        limparBuffer(); //Limpa o \n

        if(op == 'S' || op == 's'){ //Se positivo
            printf("Insira a descricao (ate 150 caracteres): ");
            lerString(novoProjeto.descricao, sizeof(novoProjeto.descricao));//Lê a descrição
        }
        else if(op == 'N'|| op == 'n'){ //Se negativo
            strcpy(novoProjeto.descricao, "Sem descricao");
        }
        else{
            printf("Erro: operacao invalida.\n\n");
        }

    }while(op != 'S' && op != 's' && op != 'N' && op != 'n');

    novoProjeto.arvores = criarListaArvores(); //Inicializa lista de árvores do novo projeto
    cadastrarArvores(novoProjeto.arvores); //Cadastra as árvores do projeto (se possível)

    return novoProjeto; //Retorna o novo projeto com as informações
}

int cadastrarArvores(ListaArvores lista){
    Arvore novaArvore;

    int numEspecies;
    lerQuantidade("\nInsira a quantidade de especies que deseja cadastrar: ", &numEspecies); //Lê uma quantidade valida de espécies

    int numRepresentantes; //Número de representantes de cada espécie
    while(numEspecies > 0){
        novaArvore = criarArvore();

        lerQuantidade("Insira a quantidade de representantes da especie no projeto: ", &numRepresentantes);//Lê uma quantidade válida de representantes da espécie

        if(adicionarArvoreOrdenada(lista, novaArvore, numRepresentantes) == 0){
            printf("Erro: arvore \"%s\" nao cadastrada.\n\n", novaArvore.nomeCientifico);
            return 0;
        }

        numEspecies--;
    }

    printf("\n");
    printf("Arvore(s) cadastrada(s)!\n\n");

    return 1;
}

int cadastrarArvoreEmProjeto(ListaProjetos lista){ //Cadastra arvore em um projeto específico
    Projeto infoProjeto;

    if(lerProjetoPorNome(lista, &infoProjeto) == 0) //Lê e procura o projeto pelo nome
        return 0;

    if(cadastrarArvores(infoProjeto.arvores) == 0) //Cadastra arvore no projeto
        return 0;

    return 1;
}

int removerArvoreDeProjeto(ListaProjetos lista){
    Projeto infoProjeto;

    if(lerProjetoPorNome(lista, &infoProjeto) == 0) //Lê e procura o projeto pelo nome
        return 0;

    if(infoProjeto.arvores->quantEspecies == 0){
        printf("Erro: lista vazia.\n\n");
        return 0;
    }

    Arvore arvore;
    printf("Digite o nome da especie de arvore que deseja remover: ");
    lerString(arvore.nomeCientifico, sizeof(arvore.nomeCientifico));

    if(removerArvores(infoProjeto.arvores, arvore) == 0){
        printf("Erro: especie nao encontrada.\n\n");
        return 0;
    }

    printf("Especie removida com sucesso!\n\n");
    return 1;
}

void listarArvoreDeProjeto(ListaProjetos lista){ //Lista árvores de um projeto específico
    Projeto infoProjeto;

    if(lerProjetoPorNome(lista, &infoProjeto) == 0) //Procura projeto pelo nome
        return;

    imprimirArvoresCompleto(infoProjeto.arvores->inicio); //Imprime todas as informacoes de arvores de um projeto
    printf("\n");
}

int contarArvoreProjetoNome(ListaProjetos lista){ //Conta o número de árvores de um projeto pelo nome
    Projeto infoProjeto;

    if(lerProjetoPorNome(lista, &infoProjeto) == 0) //Lê e procura projeto pelo nome
        return 0;

    printf("Esse projeto tem %d arvores plantadas.\n\n", contarArvores(infoProjeto.arvores->inicio));
    return 1;
}

int contarTotalArvores(ListaProjetos lista){ //Conta o número total de árvores de todos os projetos
    if(lista->quantDeProjetos == 0){
        printf("Erro: lista vazia.\n\n");
        return 0;
    }

    printf("Foram plantadas, no total, %d arvores.\n\n", contarArvoresProjetos(lista->inicio));
    return 1;
}

int cadastrarProjetos(ListaProjetos lista){ //Cadastra uma certa quantidade de projetos na lista
    Projeto novoProjeto;

    int numProjetos;
    lerQuantidade("Insira a quantidade de projetos que deseja cadastrar: ", &numProjetos);
    printf("\n");

    while(numProjetos > 0){
        novoProjeto = criarProjeto();

        if(adicionarProjetoOrdenado(lista, novoProjeto) == 0){
            printf("Erro: projeto \"%s\" nao cadastrado\n\n", novoProjeto.nomeProjeto);
            return 0;
        }

        numProjetos--;
    }

    printf("Projeto(s) cadastrado(s)!\n\n");
    return 1;
}

int removerProjetoPorNome(ListaProjetos lista){ //Remover projeto pelo nome
    Projeto infoProjeto;

    if(lerProjetoPorNome(lista, &infoProjeto) == 0) //Lê e procura projeto pelo nome
        return 0;

    if(removerProjeto(lista, infoProjeto) == 1)
        printf("Projeto removido.\n\n");

    return 1;
}

void listarProjetos(ListaProjetos lista){ //Lista projetos de uma lista
    if(lista->quantDeProjetos == 0){
        printf("Nenhum projeto cadastrado.\n\n");
        return;
    }

    imprimirProjetos(lista->inicio);
    printf("\n");
}

int lerProjetoPorNome(ListaProjetos lista, Projeto *infoProjeto){ //Lê e busca projetos por nome
    if(lista->quantDeProjetos == 0){
        printf("Erro: lista vazia.\n\n");
        return 0;
    }

    char nomeDoProjeto[60];

    printf("Insira o nome do projeto: ");
    lerString(nomeDoProjeto, sizeof(nomeDoProjeto)); //Lê nome do projeto

    if(buscarProjetoPorNome(nomeDoProjeto, lista, infoProjeto) == 0){ //Se achou armazena em infoProjeto
        printf("Erro: projeto nao encontrado.\n\n");
        return 0;
    }

    return 1;
}

int pesquisarProjetosPorNome(ListaProjetos lista){ //Imprime todas as informações de um projeto específico
    Projeto infoProjeto;

    if(lerProjetoPorNome(lista, &infoProjeto) == 0) //Lê e procura um projeto por nome
        return 0;

    printf("\n--------------------------------------------------\n");
    printf("Projeto: %s\n", infoProjeto.nomeProjeto);
    printf("Data de Inicio: %s\n", infoProjeto.dataDeInicio);
    printf("Total de arvores: %d (distribuidas em %d especies)\n", contarArvores(infoProjeto.arvores->inicio), infoProjeto.arvores->quantEspecies);
    printf("Descricao: %s\n", infoProjeto.descricao);
    printf("--------------------------------------------------\n\n");

    return 1;
}

int lerProjetosArquivo(ListaProjetos lista){
    char caminho[200];

    printf("Digite o caminho do arquivo: ");
    lerString(caminho, sizeof(caminho));

    FILE *arquivo;
    arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir o arquivo.\n");
        return 0;
    }

    Projeto novoProjeto;
    Arvore novaArvore;
    int opcao, qtdArvores, qtdEspecie;

    //Lê nome do projeto até acabar o arquivo
    while(lerLinhaArquivo(arquivo, novoProjeto.nomeProjeto, sizeof(novoProjeto.nomeProjeto)) != 0){

        lerLinhaArquivo(arquivo, novoProjeto.dataDeInicio, sizeof(novoProjeto.dataDeInicio)); //Data de inicio

        fscanf(arquivo, "%d\n", &opcao); //Se tem descrição ou nao
        if(opcao == 1)
            lerLinhaArquivo(arquivo, novoProjeto.descricao, sizeof(novoProjeto.descricao)); //Descrição
        else
            strcpy(novoProjeto.descricao, "Sem descricao");

        fscanf(arquivo, "%d\n", &qtdArvores); //Número de árvores no projeto

        novoProjeto.arvores = criarListaArvores(); //Inicializa arvore do projeto

        for (int i = 0; i < qtdArvores; i++) { //Para cada espécie
            lerLinhaArquivo(arquivo, novaArvore.nomeCientifico, sizeof(novaArvore.nomeCientifico)); //Nome da espécie

            fscanf(arquivo, "%d %d\n", &novaArvore.origem, &qtdEspecie); //Origem e quantidade

            adicionarArvoreOrdenada(novoProjeto.arvores, novaArvore, qtdEspecie);
        }

        adicionarProjetoOrdenado(lista, novoProjeto);
    }

    printf("Arquivo carregado com sucesso!\n\n");
    fclose(arquivo); //Fecha o arquivo

    return 1;
}

int gerarRelatorioProjetos(ListaProjetos lista){
    char caminho[200], nome[50];
    printf("Digite o caminho onde deseja salvar o arquivo: ");
    lerString(caminho, sizeof(caminho));

    printf("Digite o nome do arquivo: ");
    lerString(nome, sizeof(nome));

    strcat(caminho, nome);
    strcat(caminho, ".txt"); //Concatena todos para formar o caminho do novo arquivo

    FILE *arquivo;
    arquivo = fopen(caminho, "w");
    if (arquivo == NULL) {
        printf("Erro: nao foi possivel criar o arquivo.\n");
        return 0;
    }

    NoProjeto *atual = lista->inicio;
    NoArvore *especie;

    while(atual != NULL){ //Enquanto a lista estiver com elementos
        fprintf(arquivo, "%s\n", atual->info.nomeProjeto); //Escreve nome do projeto
        fprintf(arquivo, "%s\n", atual->info.dataDeInicio); //Escreve data de inicio

        if(strcmp(atual->info.descricao, "Sem descricao") == 0) //Escreve se tem ou nao descricao
            fprintf(arquivo, "0\n");
        else{
            fprintf(arquivo, "1\n");
            fprintf(arquivo, "%s\n", atual->info.descricao); //Descricao
        }

        fprintf(arquivo, "%d\n", atual->info.arvores->quantEspecies); //Escreve quantidade de especies

        especie = atual->info.arvores->inicio;
        while(especie != NULL){
            fprintf(arquivo, "%s\n", especie->info.nomeCientifico); //Escreve nome cientifico
            fprintf(arquivo, "%d %d\n", especie->info.origem, especie->quantDaEspecie); //Escreve origem e quant de especies da arvore
            especie = especie->prox; //Percorre a lista
        }

        atual = atual->prox; //Percorre a lista
    }

    printf("Relatorio gerado com sucesso!\n\n");
    fclose(arquivo);

    return 1;
}
