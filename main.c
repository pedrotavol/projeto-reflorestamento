#include "sistema.h"

int main(){
    ListaProjetos lista;
    lista = criarListaProjetos();

    int operacao;
    do{
        operacao = menu();

        switch(operacao){
            case 0:
                liberarListaProjetos(lista);
                break;
            case 1:
                cadastrarProjetos(lista);
                break;
            case 2:
                removerProjetoPorNome(lista);
                break;
            case 3:
                listarProjetos(lista);
                break;
            case 4:
                pesquisarProjetosPorNome(lista);
                break;
            case 5:
                cadastrarArvoreEmProjeto(lista);
                break;
            case 6:
                listarArvoreDeProjeto(lista);
                break;
            case 7:
                contarArvoreProjetoNome(lista);
                break;
            case 8:
                contarTotalArvores(lista);
                break;
            case 9:
                lerProjetosArquivo(lista);
                break;
            case 10:
                gerarRelatorioProjetos(lista);
                break;
            default:
                printf("Erro: operacao invalida.\n\n");
                break;
        }
    }while(operacao != 0);
}
