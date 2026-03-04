#ifndef _FERRAMENTAS_H
#define _FERRAMENTAS_H

// Esta biblioteca implementa funções auxiliares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limparBuffer();
void removerQuebraLinha(char *strDestino);
void lerString(char *strDestino, int strTamanho);
int lerLinhaArquivo(FILE *arquivo, char *strDestino, int tamanho);
void lerQuantidade(char *mensagem, int *quantidade);

#endif // _FERRAMENTAS_H
