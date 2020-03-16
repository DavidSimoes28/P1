#ifndef FUNCOES_AUXILIARES_H_INCLUDED
#define FUNCOES_AUXILIARES_H_INCLUDED

#include "constantes.h"
#include "Estruturas.h"

int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
char lerCaracter(char mensagem[MAX_STRING]);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
void limpaBufferStdin(void);
TipoData lerData(void);

#endif // FUNCOES_AUXILIARES_H_INCLUDED
