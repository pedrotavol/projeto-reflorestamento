#include "ferramentas.h"

void limparBuffer(){ //Limpa o buffer
    int c;
    while((c = getchar()) != '\n' && c != EOF); //Remove os caracteres enquanto a linha ou o arquivo ainda não acabaram
}

void removerQuebraLinha(char *strDestino){
    strDestino[strcspn(strDestino, "\n")] = '\0'; //Remove o "\n" da string
}

void lerString(char *strDestino, int tamanho){ //Lê entrada e armazena na string "strDestino"
    fgets(strDestino, tamanho, stdin); //Lê string da entrada padrão
    removerQuebraLinha(strDestino);
}

int lerLinhaArquivo(FILE *arquivo, char *strDestino, int tamanho){
    if(fgets(strDestino, tamanho, arquivo) == NULL)
        return 0;

    removerQuebraLinha(strDestino);
    return 1;
}

void lerQuantidade(char *mensagem, int *quantidade){ //Imprime uma mensagem e lê uma quantidade até que quantidade seja positiva
    do{
        printf("%s", mensagem);
        scanf("%d", quantidade);
        limparBuffer();

        if(*quantidade < 0) //Se o conteúdo for menor do que 0
            printf("Erro: quantidade invalida.\n\n");

    }while(*quantidade < 0); //Se o conteúdo continuar menor do que 0
}


