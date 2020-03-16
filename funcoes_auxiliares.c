#include <stdio.h>
#include <string.h>

#include "funcoes_auxiliares.h"

// Acrescentada variavel controlo para repetir insercao se ao for inserido numero int
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        printf("%s (%d a %d) :", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)

        if (controlo == 0)
        {
            printf("Devera inserir um numero inteiro \n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        printf("%s (%.2f a %.2f) :", mensagem, minimo, maximo);
        controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero decimal (float) \n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

char lerCaracter(char mensagem[MAX_STRING])
{
    char caracter;
    int controlo;
    do
    {
        printf("%s:", mensagem);
        controlo = scanf (" %c", &caracter);
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um caracter (char) \n");
        }
    }
    while(controlo ==0);

    return caracter;
}

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
    int tamanhoString;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {
        //   puts(mensagem);
        printf("%s", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if(vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
        {
            limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
        }
        else
        {
            vetorCaracteres[tamanhoString-1]='\0';
        }
        if (tamanhoString == 1)
        {
            printf("Nao foram introduzidos caracteres!!! . apenas carregou no ENTER \n\n");
        }

    }
    while (tamanhoString == 1);
}

void limpaBufferStdin(void)
{
    int chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}

TipoData lerData(void)
{
    TipoData data;
    int maxdiasmes;
    data.Ano = lerInteiro(" ano",2010,2016);
    data.Mes = lerInteiro(" mes",1,12);

    switch(data.Mes)
    {
    case 2:
        if((data.Ano %400 == 0) || (data.Ano%4 == 0 && data.Ano %100 !=0))
        {
            maxdiasmes=29;
        }
        else
        {
            maxdiasmes = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxdiasmes=30;
        break;
    default:
        maxdiasmes=31;
    }
    data.Dia = lerInteiro(" Dia:",1,maxdiasmes);
    return data;
}

