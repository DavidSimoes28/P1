#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Constantes.h"
#include "Estruturas.h"
#include "funcoes_navegacao.h"
#include "funcoes_auxiliares.h"

void menu(Veiculos vetor[MAX_VEICULOS], char opcao,int *PosicaoVeiculo)
{
    int Retorno;

    do
    {
        printf("\nMenu Veiculo \nI - Inserir Veiculo\nC - Consultar\nL - Listar Veiculos\nV - Voltar\n");
        printf("Opcao --> ");
        scanf(" %c", &opcao);
        limpaBufferStdin();
        opcao = toupper(opcao);
        switch(opcao)
        {
        case 'I':
            if(*PosicaoVeiculo <= MAX_VEICULOS)
            {
                do
                {
                    lerString("\nMatricula: ",vetor[*PosicaoVeiculo].Matricula,9);
                    Retorno = verificarVeiculo(vetor,*PosicaoVeiculo,vetor[*PosicaoVeiculo].Matricula);
                }
                while(Retorno!=0);
                vetor[*PosicaoVeiculo].CargaMaxima = lerFloat("Carga Maxima: ",1,200);
                printf("Data de Fabrico: ");
                vetor[*PosicaoVeiculo].DataDeFabrico = lerData();
                vetor[*PosicaoVeiculo].Estado = 'D';
                vetor[*PosicaoVeiculo].QuantEncomendasTranportadas = 0;
                vetor[*PosicaoVeiculo].QuantViagensEfetuadas = 0;
                (*PosicaoVeiculo)++;
            }
            break;
        case 'C':
            consultarVeiculo(vetor, *PosicaoVeiculo);
            break;
        case 'L':
            ListarVeiculos(vetor,*PosicaoVeiculo);
            break;
        case 'V':
            break;
        }
    }
    while(opcao != 'V');
}

void consultarVeiculo(Veiculos vetor[], int posicaoVeiculo)
{
    int estado, i;
    printf("Consultar Veiculos pelo estado\n\n");
    do
    {
        estado = lerCaracter("\n\nD - Disponivel\nC - Carga\nT - A Transportar\nR - De Regresso\nA - Avariado\nInsira a opcao --> ");
        estado = toupper(estado);
        limpaBufferStdin();
    }
    while(estado != 'D' && estado != 'C' && estado != 'T' && estado != 'R' && estado != 'A');

    printf("\nMatricula\tCarga Maxima\tData de Fabrico\t\tEstado\tViagens Efetuadas\tEncomendas Transportas");
    for(i=0; i<(posicaoVeiculo); i++)
    {
        if(vetor[i].Estado == estado)
        {
            ListarVeiculo(vetor,i);
        }
    }
}

void ListarVeiculos(Veiculos vetor[], int posicaoVeiculo)
{
    int i;
    for(i=0; i<(posicaoVeiculo); i++)
    {
        ListarVeiculo(vetor,i);
    }
}

void consultarEncomendas(Encomendas vetor[], int posicaoEncomenda)
{
    int NumeroDeEncomenda, i;
    NumeroDeEncomenda = lerInteiro("\nNumero de Registo: ",MIN_ENCOMENDAS,MAX_ENCOMENDAS);
    for(i=0; i <= (posicaoEncomenda); i++)
    {
        if(vetor[i].NumeroDeRegisto == NumeroDeEncomenda)
        {
            ListarEncomenda(vetor,i);
        }
    }
}

void ListarEncomenda(Encomendas vetor[], int i)
{
    printf("\nNumero De Registo\tData De Registo\tPeso\tDestino\tEstado\tData de Entrega\tConjunto de Observacoes");
    printf("\n\t%d\t\t%2d-%2d-%2d\t%.2f\t%s\t%c\t%2d-%2d-%2d\t%s",vetor[i].NumeroDeRegisto,vetor[i].DataDeRegisto.Dia,vetor[i].DataDeRegisto.Mes,vetor[i].DataDeRegisto.Ano,vetor[i].Peso,vetor[i].Destino,vetor[i].Estado,vetor[i].DataDeEntrega.Dia,vetor[i].DataDeEntrega.Mes,vetor[i].DataDeEntrega.Ano,vetor[i].ConjObserv);
}

void DadosE(Encomendas vetor[MAX_ENCOMENDAS],Veiculos Veiculo[MAX_VEICULOS],CarregamentoE Carregamento[MAX_ENCOMENDAS],int *PosicaoEncomenda, int *PosicaoVeiculo, int *PosicaoCarregamento)
{
    char MenuEncomendas,aux_resgisto,aux;
    int retorno;
    int i;
    do
    {
        printf("\nMenu Encomendas\nI - Inserir\nC - Consultar\nE - Eliminar Encomenda Devolvida\nA - Alterar Destino de Encomenda Devolvida\nL - Listar\nR - Registar Carregamento\nD - Descarregamento das Encomendas\nV - Voltar\n\tOpcao-->");
        scanf(" %c",&MenuEncomendas);
        MenuEncomendas = toupper(MenuEncomendas);
        switch(MenuEncomendas)
        {
        case 'I':
            if(*PosicaoEncomenda <= MAX_ENCOMENDAS)
            {
                do
                {
                    vetor[*PosicaoEncomenda].NumeroDeRegisto = lerInteiro("Numero de registo: ",MIN_ENCOMENDAS,MAX_ENCOMENDAS);
                    retorno = verificarEncomenda(vetor,*PosicaoEncomenda,vetor[*PosicaoEncomenda].NumeroDeRegisto);
                }
                while(retorno!=0);
                printf("Data de registo:");
                vetor[*PosicaoEncomenda].DataDeRegisto = lerData();
                vetor[*PosicaoEncomenda].Peso = lerFloat("Peso",0.01,100);
                lerString("Destino: ",vetor[*PosicaoEncomenda].Destino,MAX_STRING);
                printf("Estado: Registado ");
                vetor[*PosicaoEncomenda].Estado = 'R';
                vetor[*PosicaoEncomenda].DataDeEntrega.Dia = 0;
                vetor[*PosicaoEncomenda].DataDeEntrega.Mes = 0;
                vetor[*PosicaoEncomenda].DataDeEntrega.Ano = 0;
                strcpy(vetor[*PosicaoEncomenda].ConjObserv,"");
                (*PosicaoEncomenda)++;
            }

            break;
        case 'C':
            if (PosicaoEncomenda == 0)
            {
                printf("\n\nATENCAO: nao existem encomendas!\n");

            }
            else
            {
                consultarEncomendas(vetor,*PosicaoEncomenda);
            }
            break;
        case 'L':

            if ((*PosicaoEncomenda) == 0)
            {
                printf("\n\nATENCAO: nao existem encomendas!\n");
            }
            else
            {
                printf("\n Listagem das Encomendas \n");
                for (i=0; i < (*PosicaoEncomenda); i++)
                {
                    ListarEncomenda(vetor,i);
                }
            }
            break;
        case 'R':
            aux_resgisto = RegistarCarregamento(Carregamento,*PosicaoCarregamento,*PosicaoEncomenda,*PosicaoVeiculo,vetor,Veiculo);
            if(aux_resgisto != 0)
            {
                (*PosicaoCarregamento)=(aux_resgisto);
            }
            break;
        case 'A':
            alterarDestinoEncomenda(vetor,Carregamento, *PosicaoEncomenda, *PosicaoCarregamento);
            break;
        case 'E':
            aux = EliminarEncomenda(vetor,*PosicaoEncomenda,Carregamento,*PosicaoCarregamento);
            if(aux == 0)
            {
                (*PosicaoCarregamento)--;
                (*PosicaoEncomenda)--;
            }
            break;
        case 'D':
            RegistarDescarregamento(Carregamento,*PosicaoEncomenda,vetor,*PosicaoCarregamento,Veiculo,*PosicaoVeiculo);
            break;
        case 'V':
            break;

        }
    }
    while(MenuEncomendas != 'V');
}

void alterarDestinoEncomenda(Encomendas vetor[],CarregamentoE Carregamento[], int PosicaoEncomenda, int PosicaoCarregamento)
{
    int i, a, aux, NumeroEncomenda, aux_comp;
    char Destino[100];
    do
    {
        NumeroEncomenda = lerInteiro("\nNumero de Encomenda: ",MIN_ENCOMENDAS,MAX_ENCOMENDAS);
        for(i=0; i <= (PosicaoCarregamento); i++)
        {
            if(Carregamento[i].NumeroDeRegisto ==  NumeroEncomenda)
            {
                if(Carregamento[i].Estado ==  'D')
                {
                    strcpy(Destino,Carregamento[i].Destino);
                    a = i;
                    aux = 1;
                }
            }
        }

        for(i=0; i <= (PosicaoEncomenda); i++)
        {
            if(vetor[i].NumeroDeRegisto ==  NumeroEncomenda)
            {
                if(vetor[i].Estado ==  'D')
                {
                    strcpy(Destino,vetor[i].Destino);
                    aux_comp = i;
                    aux = aux + 1;
                }
            }
        }
    }
    while(aux != 2);

    printf("Destino antigo: %s",Destino);
    lerString("\nNovo Destino: ", Destino, MAX_STRING);
    strcpy(Carregamento[a].Destino,Destino);
    strcpy(vetor[aux_comp].Destino,Destino);
}

int EliminarEncomenda(Encomendas vetor[],int PosicaoEncomenda,CarregamentoE Carregamento[],int PosicaoCarregamento)
{
    int NumeroEncomenda,i,a,aux;
    char Estado;
    do
    {

        NumeroEncomenda = lerInteiro("\nNumero de Encomenda: ",MIN_ENCOMENDAS,MAX_ENCOMENDAS);
        for(i=0; i <= PosicaoCarregamento; i++)
        {
            if(Carregamento[i].NumeroDeRegisto ==  NumeroEncomenda)
            {
                if(Carregamento[i].Estado ==  'D')
                {
                    Estado = Carregamento[i].Estado;
                    a = i;
                }
            }
        }
    }
    while(a == -1);

    if(Estado == 'D')
    {
        for(i=a; i <= PosicaoCarregamento; i++)
        {
            Carregamento[i].NumeroDeRegisto = Carregamento[i+1].NumeroDeRegisto;
            strcpy(Carregamento[i].Matricula, Carregamento[i+1].Matricula);
            strcpy(Carregamento[i].Destino, Carregamento[i+1].Destino);
            Carregamento[i].Estado = Carregamento[i+1].Estado;
        }

        for(i=0; i <= PosicaoEncomenda; i++)
        {
            if(vetor[i].NumeroDeRegisto ==  NumeroEncomenda)
            {
                a = i;
            }
        }

        for(i=a; i <= PosicaoEncomenda; i++)
        {
            vetor[i].NumeroDeRegisto = vetor[i+1].NumeroDeRegisto;
            vetor[i].DataDeRegisto.Dia = vetor[i+1].DataDeRegisto.Dia;
            vetor[i].DataDeRegisto.Mes = vetor[i+1].DataDeRegisto.Mes;
            vetor[i].DataDeRegisto.Ano = vetor[i+1].DataDeRegisto.Ano;
            vetor[i].Peso = vetor[i+1].Peso;
            strcpy(vetor[i].Destino, vetor[i+1].Destino);
            vetor[i].Estado = vetor[i+1].Estado;
            vetor[i].DataDeEntrega.Dia = vetor[i+1].DataDeEntrega.Dia;
            vetor[i].DataDeEntrega.Mes = vetor[i+1].DataDeEntrega.Mes;
            vetor[i].DataDeEntrega.Ano = vetor[i+1].DataDeEntrega.Ano;
            strcpy(vetor[i].ConjObserv, vetor[i+1].ConjObserv);
        }
        aux = 0;
    }
    else
    {
        if(Estado != 'D')
        {
            printf("Impossivel eliminar encomendo pois nao esta disponivel");
            aux = -1;
        }
    }
    return aux;
}

int verificarVeiculo(Veiculos Veiculo[],int posicaoVeiculo, char matricula[9])
{
    int retorno=0,i;
    for(i=0; i< posicaoVeiculo; i++)
    {
        if(strcmp(Veiculo[i].Matricula, matricula)==0)
        {
            retorno = -1;
        }
    }
    return retorno;
}

int verificarEncomenda(Encomendas Encomenda[],int posicaoEncomenda, int numeroDeRegisto)
{
    int retorno=0,i;
    for(i=0; i< posicaoEncomenda; i++)
    {
        if(Encomenda[i].NumeroDeRegisto == numeroDeRegisto)
        {
            retorno = -1;
        }
    }
    return retorno;
}

int verificarCarregamento(CarregamentoE Carregamento[],int posicaoCarregamento, int numeroDeRegisto, char matricula[9])
{
    int retorno=0,i;
    if(posicaoCarregamento == 0)
    {
        retorno = 0;
    }
    else
    {
        for(i=0; i< posicaoCarregamento; i++)
        {
            if(Carregamento[i].NumeroDeRegisto == numeroDeRegisto)
            {
                if(strcmp(Carregamento[i].Matricula, matricula)==0)
                {
                    retorno = -1;
                }
            }
        }
    }
    return retorno;
}

void RegistarInicioDaViagem(Veiculos Veiculo[MAX_VEICULOS],CarregamentoE Carregamento[MAX_ENCOMENDAS],int PosicaoVeiculo, int PosicaoCarregamento)
{
    char op,estado,Matricula[9];
    int posicaoV=-1,posicaoC,i,a=-1;
    do
    {
        printf("\nMenu\n\nI - Inicio da viagem\nR - Regresso ao Centro\nV - Voltar\nOpcao-->");
        do
        {
            printf("\n\tOpcao --> ");
            scanf(" %c",&op);
            op = toupper(op);
        }
        while(op != 'I' && op !='R' && op !='V');

        switch(op)
        {
        case 'I':
            posicaoV = ProcurarMatricula(Veiculo,PosicaoVeiculo);
            strcpy(Matricula,Veiculo[posicaoV].Matricula);
            if(posicaoV == -1)
            {
            }
            else
            {
                estado = Veiculo[posicaoV].Estado;
                if(estado != 'C')
                {
                    printf("\nNao e possivel iniciar viagem.\nE necessario efetuar a Descarga primeiramente");
                }
                else
                {
                    Veiculo[posicaoV].Estado= 'T';
                }
            }
            break;
        case 'R':
            do
            {
                posicaoV = ProcurarMatricula(Veiculo,PosicaoVeiculo);
                strcpy(Matricula, Veiculo[posicaoV].Matricula);
                for(i=0; i <= PosicaoCarregamento; i++)
                {
                    if(strcmp(Carregamento[i].Matricula,Matricula)== 0)
                    {
                        a=i;
                        if(Carregamento[i].Estado == 'I')
                        {
                            posicaoC=1;
                        }
                    }
                }
            }
            while(a == -1);
            if(posicaoC != 1)
            {
                estado = Carregamento[a].Estado;
                strcpy(Matricula,Carregamento[a].Matricula);
                Veiculo[posicaoV].Estado = 'D';
            }

            break;
        case 'V':
            break;
        }
    }
    while(op != 'V');
}

int ProcurarMatricula(Veiculos Veiculo[MAX_VEICULOS], int posicaoVeiculo)
{
    char Matricula[9];
    int i, a=-1;
    do
    {
        lerString("Matricula: ",Matricula,9);
        for(i=0; i <= posicaoVeiculo; i++)
        {
            if(strcmp(Veiculo[i].Matricula,Matricula)== 0)
            {
                a=i;
            }
        }
    }
    while(a == -1);
    return a;
}

int ProcurarMatriculaC(CarregamentoE Veiculo[MAX_VEICULOS])
{
    char Matricula[9];
    int i,a=-1;
    do
    {
        lerString("Matricula: ",Matricula,9);
        for(i=0; i <= MAX_ENCOMENDAS; i++)
        {
            if(strcmp(Veiculo[i].Matricula,Matricula)== 0)
            {
                a=i;
            }
        }
    }
    while(a == -1);
    return a;
}

int CargaOcupada(Encomendas Encomenda[],int pos,float soma)
{
    int i;
    for(i=0; i <= pos; i++)
    {
        if(Encomenda[i].Estado == 'R')
        {
            soma +=  Encomenda[i].Peso;
        }

    }
    return soma;
}

int ProcurarEncomenda(Encomendas Encomenda[])
{
    int numerodeencomenda;
    int i, a=-1;
    do
    {
        numerodeencomenda = lerInteiro("Numero de Encomenda: ",MIN_ENCOMENDAS,MAX_ENCOMENDAS);
        for(i=0; i <= MAX_ENCOMENDAS; i++)
        {
            if(Encomenda[i].NumeroDeRegisto == numerodeencomenda)
            {
                a=i;
            }
        }
    }
    while(a == -1);
    return a;
}

int ProcurarEncomendaC(CarregamentoE Carregamento[])
{
    int numerodeencomenda;
    int i, a=-1;
    do
    {
        numerodeencomenda = lerInteiro("Numero de Encomenda: ",MIN_ENCOMENDAS,MAX_ENCOMENDAS);
        for(i=0; i <= MAX_ENCOMENDAS; i++)
        {
            if(Carregamento[i].NumeroDeRegisto == numerodeencomenda)
            {
                a=i;
            }
        }
    }
    while(a == -1);
    return a;
}

int RegistarCarregamento(CarregamentoE Carregamento[], int PosicaoCarregamento, int PosicaoEncomenda, int PosicaoVeiculo, Encomendas Encomenda[], Veiculos Veiculo[])
{
    int estado,aux = -1;
    char Matricula[9],Destino[100];
    do
    {
        aux = ProcurarMatricula(Veiculo,PosicaoVeiculo);
        estado = Veiculo[aux].Estado;
        if(estado == 'D')
        {
            aux = 0;
        }
    }
    while(aux != 0);

    strcpy(Matricula,Veiculo[aux].Matricula);
    aux = -1;
    lerString("Insira o distino: ", Destino, MAX_STRING);
    aux = selecaoAutomatica(Veiculo,Carregamento,Encomenda,PosicaoCarregamento,PosicaoEncomenda,Destino,Matricula);
    return aux;
}

void RegistarDescarregamento(CarregamentoE Carregamento[], int PosicaoEncomenda, Encomendas Encomenda[], int PosicaoCarregamento, Veiculos Veiculo[], int PosicaoVeiculo)
{
    int a,b,i,aux,somaEncomendas = 0;
    char Matricula[9];
    char Encomendaaa;
    a = ProcurarMatriculaC(Carregamento);
    strcpy(Matricula, Carregamento[a].Matricula);
    for(i=0; i<=PosicaoCarregamento; i++)
    {
        if(strcmp(Carregamento[i].Matricula, Matricula)==0)
        {
            limpaBufferStdin();
            do
            {
                printf("\nNumero de Registo: %d\n", Carregamento[i].NumeroDeRegisto);
                printf("(E)Entregue ou (D)Devolvida: ");
                scanf(" %c", &Carregamento[i].Estado);
                Carregamento[i].Estado = toupper(Carregamento[i].Estado);
            }
            while(Carregamento[i].Estado!='E' && Carregamento[i].Estado!='D');

            Carregamento[i].Estado = toupper(Carregamento[i].Estado);
            Encomendaaa=Carregamento[i].NumeroDeRegisto;
            for(b=0; b<=PosicaoEncomenda; b++)
            {
                if(Encomendaaa == Encomenda[b].NumeroDeRegisto)
                {

                    do
                    {
                        printf("Data de Entrega:\n");
                        Encomenda[b].DataDeEntrega = lerData();
                        aux=DataInserida(Encomenda,b);
                    }
                    while(aux!=0);
                    if(Carregamento[i].Estado == 'D')
                    {
                        lerString("Motivo da devolucao: ",Encomenda[b].ConjObserv,MAX_STRING);
                        Encomenda[b].Estado='D';
                        somaEncomendas++;
                        logDevolucao(Encomenda[b].NumeroDeRegisto,Encomenda[b].Destino,Encomenda[b].DataDeEntrega.Dia,Encomenda[b].DataDeEntrega.Mes,Encomenda[b].DataDeEntrega.Ano,Carregamento[i].Matricula,Encomenda[b].ConjObserv);
                    }
                    else
                    {
                        strcpy(Encomenda[b].ConjObserv,"Entregue");
                        Encomenda[b].Estado='E';
                        somaEncomendas++;
                    }
                }
            }
        }
    }

    for(i=0; i<=PosicaoVeiculo; i++)
    {
        if(strcmp(Veiculo[i].Matricula, Matricula)==0)
        {
            Veiculo[i].Estado = 'R';
            Veiculo[i].QuantEncomendasTranportadas = Veiculo[i].QuantEncomendasTranportadas + somaEncomendas;
            Veiculo[i].QuantViagensEfetuadas = Veiculo[i].QuantViagensEfetuadas + 1;
        }
    }
}

void maiorNumeroDeEncomendasEntregues(Encomendas Encomenda[], int PosicaoEncomenda)
{
    int NumeroVezesDestino[PosicaoEncomenda],i,a,maior,i_maior,soma=0,aux=-1;
    int Destino[PosicaoEncomenda];

    for(i=0; i<=PosicaoEncomenda; i++)
    {
        soma = 0;
        for(a=0; a<=PosicaoEncomenda; a++)
        {
            if(Encomenda[i].Estado == 'E' && strcmp(Encomenda[i].Destino,Encomenda[a].Destino)==0 && Encomenda[a].Estado == 'E')
            {
                Destino[i] = i;
                soma++;
                NumeroVezesDestino[i] = soma;
                aux=0;
            }
        }
    }
    if(aux == 0)
    {
        maior = NumeroVezesDestino[0];
        i_maior = Destino[0];
        for(i=0; i<=soma; i++)
        {
            if(NumeroVezesDestino[i] >= maior)
            {
                maior=NumeroVezesDestino[i];
                i_maior = Destino[i];
            }
        }
        printf("\nDestino com maior numero de encomendas entregues:\nDestino : %s Numero de Encomendas Entregues:%d\n",Encomenda[i_maior].Destino, maior);
    }
    else
    {
        printf("\nNao existem encomendas entregues");
    }

}

int DataInserida(Encomendas Encomendas[], int b)
{
    int aux=-1;
    if(Encomendas[b].DataDeRegisto.Dia <= Encomendas[b].DataDeEntrega.Dia && Encomendas[b].DataDeRegisto.Mes == Encomendas[b].DataDeEntrega.Mes && Encomendas[b].DataDeRegisto.Ano <= Encomendas[b].DataDeEntrega.Ano)
    {
        aux = 0;
    }
    else
    {
        if(Encomendas[b].DataDeRegisto.Mes < Encomendas[b].DataDeEntrega.Mes && Encomendas[b].DataDeRegisto.Ano <= Encomendas[b].DataDeEntrega.Ano)
        {
            aux = 0;
        }
    }
    return aux; // se aux = 0 verdade || se aux = -1 falso
}

void ListarUltimaEncomenda(CarregamentoE Carregamento[], Veiculos Veiculo[],Encomendas Encomenda[], int posicaoVeiculo,int posicaoEncomenda)
{
    int aux_carregamento,i,a=-1,dia=0,mes=0,ano=0,NumeroDeRegisto;
    char matricula[9];
    aux_carregamento = ProcurarEncomendaC(Carregamento);

    for(i=0; i <= posicaoEncomenda; i++)
    {
        if(Encomenda[i].NumeroDeRegisto == Carregamento[aux_carregamento].NumeroDeRegisto)
        {
            a = i;
            if(Encomenda[i].DataDeEntrega.Dia > dia && Encomenda[i].DataDeEntrega.Mes == mes && Encomenda[i].DataDeEntrega.Ano > ano)
            {
                NumeroDeRegisto = Encomenda[i].NumeroDeRegisto;
                dia = Encomenda[i].DataDeEntrega.Dia;
                mes = Encomenda[i].DataDeEntrega.Mes;
                ano = Encomenda[i].DataDeEntrega.Ano;
            }
            else
            {
                if(Encomenda[i].DataDeEntrega.Mes > mes && Encomenda[i].DataDeEntrega.Ano > ano)
                {
                    NumeroDeRegisto = Encomenda[i].NumeroDeRegisto;
                    dia = Encomenda[i].DataDeEntrega.Dia;
                    mes = Encomenda[i].DataDeEntrega.Mes;
                    ano = Encomenda[i].DataDeEntrega.Ano;
                }
            }
        }
    }

    if (a != -1)
    {
        for(i=0; i <= MAX_ENCOMENDAS; i++)
        {
            if(Carregamento[aux_carregamento].NumeroDeRegisto == NumeroDeRegisto)
            {
                aux_carregamento=i;
            }
        }
        aux_carregamento -= 1;
        strcpy(matricula,Carregamento[aux_carregamento].Matricula);
        for(i=0; i <= posicaoVeiculo; i++)
        {
            if(strcmp(Veiculo[i].Matricula,matricula)== 0)
            {
                a=i;
            }
        }

        if (a != -1)
        {
            ListarVeiculo(Veiculo,a);
        }
        else {}
    }
}

void ListarVeiculo(Veiculos Veiculo[],int i)
{
    printf("\nMatricula\tCarga Maxima\tData de Fabrico\t\tEstado\tViagens Efetuadas\tEncomendas Transportas");
    printf("\n    %s   \t%.2f\t\t%d-%d-%d\t\t\t%c\t\t%d\t\t%d\n\n",Veiculo[i].Matricula,Veiculo[i].CargaMaxima,Veiculo[i].DataDeFabrico.Dia,Veiculo[i].DataDeFabrico.Mes,Veiculo[i].DataDeFabrico.Ano,Veiculo[i].Estado,Veiculo[i].QuantViagensEfetuadas,Veiculo[i].QuantEncomendasTranportadas);
}

void Estatisticas(CarregamentoE Carregamento[],int *PosicaoVeiculo,int *PosicaoEncomenda,int *PosicaoCarregamento)
{
    float PercentagemEntregues;
    int i, TotalDevolvidos=0, TotalEntregues=0, TotalVeiculos=0, TotalEncomendas=0;

    for (i=0; i<=(*PosicaoCarregamento); i++)
    {

        if(Carregamento[i].Estado=='D')
        {
            TotalDevolvidos++;
        }
        else
        {
            if(Carregamento[i].Estado=='E')
            {
                TotalEntregues++;
            }
        }
    }
    TotalVeiculos=(*PosicaoVeiculo);
    TotalEncomendas=(*PosicaoEncomenda);
    PercentagemEntregues = (TotalEntregues*100)/(*PosicaoCarregamento);
    printf("\nTotal De Veiculos: %d", TotalVeiculos);
    printf("\t\tTotal de Encomendas Devolvidas: %d", TotalDevolvidos);
    printf("\nTotal De Encomendas: %d", TotalEncomendas);
    printf("\t\tPercentagem de Encomendas Entregues: %.2f %%", PercentagemEntregues);
}

float pesoMedioEncomendas(Encomendas Encomenda[], int PosicaoEncomenda)
{
    float pesoMedio, pesoTotal=0;
    int i;
    for(i=0; i<=PosicaoEncomenda; i++)
    {
        pesoTotal = pesoTotal + Encomenda[i].Peso;
    }
    pesoMedio=pesoTotal/(PosicaoEncomenda);

    return pesoMedio;
}

float cargaMediaVeiculos(Veiculos Veiculo[],CarregamentoE Carregamento[],Encomendas Encomenda[], int PosicaoVeiculo, int PosicaoCarregamento, int PosicaoEncomenda)
{
    int i,a,a2,totalVeiculo=0;
    float cargaMedia = 0, cargaTotal=0;

    for(i=0; i<=PosicaoVeiculo; i++)
    {
        if(Veiculo[i].Estado=='T')
        {
            for(a=0; a <= PosicaoEncomenda; a++)
            {
                if(strcmp(Carregamento[a].Matricula,Veiculo[i].Matricula)==0)
                {
                    for(a2=0; a2 <= PosicaoCarregamento; a2++)
                    {
                        if(Carregamento[a].NumeroDeRegisto == Encomenda[a2].NumeroDeRegisto)
                        {
                            cargaTotal = cargaTotal + Encomenda[a2].Peso;
                            totalVeiculo++;
                        }
                    }
                }
            }
        }
    }

    if(totalVeiculo == 0)
    {

    }
    else
    {
        cargaMedia = cargaTotal/(totalVeiculo);
    }

    return cargaMedia;
}

void menosViagensEfetuadas(Veiculos Veiculo[], int PosicaoVeiculo)
{
    int i, Viagens,aux_i;
    aux_i = 0;
    Viagens = Veiculo[aux_i].QuantViagensEfetuadas;
    for(i=0; i<=PosicaoVeiculo; i++)
    {
        if(Veiculo[i].QuantViagensEfetuadas <= Viagens)
        {
            aux_i = i;
            Viagens = Veiculo[i].QuantViagensEfetuadas;
        }
    }
    printf("\nVeiculo %s com %d viagens\n",Veiculo[aux_i].Matricula,Viagens);
}

void encomendasEntreguesNumaDeterminadaData(Encomendas Encomenda[], int PosicaoEncomenda)
{
    int dia,mes,ano,i,soma=0;
    printf("\nInsira Data para comparar");
    printf("\nDia: ");
    scanf("%d",&dia);
    printf("\nMes: ");
    scanf("%d",&mes);
    printf("\nAno: ");
    scanf("%d",&ano);

    for(i=0; i<PosicaoEncomenda; i++)
    {
        if(Encomenda[i].DataDeEntrega.Dia != dia && Encomenda[i].DataDeEntrega.Mes != mes && Encomenda[i].DataDeEntrega.Ano != ano)
        {
        }
        else
        {
            soma++;
        }
    }
    if(soma != 0)
    {
        printf("\nForam entregues %d encomendas dia %d-%d-%d", soma,dia,mes,ano);
    }
    else
    {
        printf("\nNenhum encomenda entregue no dia %d-%d-%d",dia,mes,ano);
    }


}

int carga80porcento(Encomendas Encomenda[],Veiculos Veiculo[],int posicaoEncomenda,int posicaoCarregamento,char Matricula[9], float cargaOcup)
{
    float cargaTotal,PercentagemCargaOcupada,cargaPorRegistar;
    int retorno,pos;

    pos = ProcuraMatricula(Veiculo,Matricula);
    cargaTotal=Veiculo[pos].CargaMaxima;


    PercentagemCargaOcupada = (cargaOcup*100)/cargaTotal;
    if(PercentagemCargaOcupada>100)
    {
        retorno = -1;
    }
    else
    {
        if(PercentagemCargaOcupada <= 100 && PercentagemCargaOcupada >= 80)
        {
            cargaPorRegistar = CargaOcupadaPorRegistar(Encomenda,posicaoEncomenda,pos);
            PercentagemCargaOcupada = ((cargaOcup+cargaPorRegistar)*100)/cargaTotal;
            if(PercentagemCargaOcupada <= 100 && PercentagemCargaOcupada >= 80)
            {
                retorno = 1;
            }
            else
            {
                retorno = 2;
            }
        }
        else
        {
            if(PercentagemCargaOcupada < 80 && PercentagemCargaOcupada >= 0)
            {
                retorno = 0;
            }
        }
    }

    return retorno;
}

void guardar_fich_bin_veiculos(Veiculos Veiculo[],int PosicaoVeiculo)
{
    FILE *ficheiro;
    int quantescrito;
    ficheiro=fopen("Veiculo.bin","wb");
    if(ficheiro==NULL)
    {
        printf("\nErro na criacao do ficheiro/abertura do ficheiro");
    }
    else
    {
        quantescrito = fwrite(&PosicaoVeiculo,sizeof(int),1,ficheiro);
        if(quantescrito != 1)
        {
            printf("\nerro ao escrever no ficheiro");
        }
        else
        {
            quantescrito = fwrite(Veiculo,sizeof(Veiculos),PosicaoVeiculo,ficheiro);
            if(quantescrito != PosicaoVeiculo)
            {
                printf("\nerro ao escrever no ficheiro");
            }
        }
    }
    fclose(ficheiro);
}

void ler_fich_bin_veiculos(Veiculos Veiculo[],int *PosicaoVeiculo)
{
    FILE *ficheiro;
    int quantlidos;
    ficheiro=fopen("Veiculo.bin","rb");
    if(ficheiro==NULL)
    {
        printf("\nErro na abertura do ficheiro");
    }
    else
    {
        quantlidos = fread(&*PosicaoVeiculo,sizeof(int),1,ficheiro);
        if(quantlidos != 1)
        {
            printf("\nerro ao ler no ficheiro");
        }
        else
        {
            quantlidos = fread(Veiculo,sizeof(Veiculos),*PosicaoVeiculo,ficheiro);
            if(quantlidos != (*PosicaoVeiculo))
            {
                printf("\nerro ao ler no ficheiro");
                *PosicaoVeiculo = 0;
            }
        }
    }
    fclose(ficheiro);
}

void guardar_fich_bin_Encomendas(Encomendas Encomenda[],int PosicaoEncomenda)
{
    FILE *ficheiro;
    int quantescrito;
    ficheiro=fopen("Encomenda.bin","wb");
    if(ficheiro==NULL)
    {
        printf("\nErro na criacao do ficheiro/abertura do ficheiro");
    }
    else
    {
        quantescrito = fwrite(&PosicaoEncomenda,sizeof(int),1,ficheiro);
        if(quantescrito != 1)
        {
            printf("\nerro ao escrever no ficheiro");
        }
        else
        {
            quantescrito = fwrite(Encomenda,sizeof(Encomendas),PosicaoEncomenda,ficheiro);
            if(quantescrito != PosicaoEncomenda)
            {
                printf("\nerro ao escrever no ficheiro");
            }
        }
    }
    fclose(ficheiro);
}

void ler_fich_bin_Encomendas(Encomendas Encomenda[],int *PosicaoEncomenda)
{
    FILE *ficheiro;
    int quantlidos;
    ficheiro=fopen("Encomenda.bin","rb");
    if(ficheiro==NULL)
    {
        printf("\nErro na abertura do ficheiro");
    }
    else
    {
        quantlidos = fread(&*PosicaoEncomenda,sizeof(int),1,ficheiro);
        if(quantlidos != 1)
        {
            printf("\nerro ao ler no ficheiro");
        }
        else
        {
            quantlidos = fread(Encomenda,sizeof(Encomendas),*PosicaoEncomenda,ficheiro);
            if(quantlidos != *PosicaoEncomenda)
            {
                printf("\nerro ao ler no ficheiro");
                *PosicaoEncomenda = 0;
            }
        }
    }
    fclose(ficheiro);
}

void guardar_fich_bin_Carregamento(CarregamentoE Carregamento[],int PosicaoCarregamento)
{
    FILE *ficheiro;
    int quantescrito;
    ficheiro=fopen("Carregamento.bin","wb");
    if(ficheiro==NULL)
    {
        printf("\nErro na criacao do ficheiro/abertura do ficheiro");
    }
    else
    {
        quantescrito = fwrite(&PosicaoCarregamento,sizeof(int),1,ficheiro);
        if(quantescrito != 1)
        {
            printf("\nerro ao escrever no ficheiro");
        }
        else
        {
            quantescrito = fwrite(Carregamento,sizeof(CarregamentoE),PosicaoCarregamento,ficheiro);
            if(quantescrito != PosicaoCarregamento)
            {
                printf("\nerro ao escrever no ficheiro");
            }
        }
    }
    fclose(ficheiro);
}

void ler_fich_bin_Carregamento(CarregamentoE Carregamento[],int *PosicaoCarregamento)
{
    FILE *ficheiro;
    int quantlidos;
    ficheiro=fopen("Carregamento.bin","rb");
    if(ficheiro==NULL)
    {
        printf("\nErro na abertura do ficheiro");
    }
    else
    {
        quantlidos = fread(&*PosicaoCarregamento,sizeof(int),1,ficheiro);
        if(quantlidos != 1)
        {
            printf("\nerro ao ler no ficheiro");
        }
        else
        {
            quantlidos = fread(Carregamento,sizeof(CarregamentoE),*PosicaoCarregamento,ficheiro);
            if(quantlidos != *PosicaoCarregamento)
            {
                printf("\nerro ao ler no ficheiro");
                *PosicaoCarregamento = 0;
            }
        }
    }
    fclose(ficheiro);
}

void logDevolucao(int Numeroderegisto,char Destino[100],int dia,int mes,int ano,char Matricula[9],char CausaDevolucao[100])
{
    FILE *ficheiro;

    ficheiro = fopen("logDevolucao.txt","a");
    if(ficheiro==NULL)
    {
        printf("Erro");
    }
    else
    {
        fprintf(ficheiro,"\nRegisto:\nNumero de Registo: %d\nDestino: %s\nData de Devolucao: %2d-%2d-%4d\nVeiculo: %s\nCausa da Devolucao: %s\n\n",Numeroderegisto,Destino,dia,mes,ano,Matricula,CausaDevolucao);
    }
    fclose(ficheiro);
}

void ordenarEstrutura(Veiculos Veiculo[], int posicaoVeiculo)
{
    int i, j, aux, haTrocas;
    int Matricula[posicaoVeiculo],QuantViagensEfetuadas[posicaoVeiculo],QuantEncomendasTranportadas[posicaoVeiculo],dia[posicaoVeiculo],mes[posicaoVeiculo],ano[posicaoVeiculo];
    char Estado[posicaoVeiculo],aux_char;
    float cargaMaxima[posicaoVeiculo],aux_float;
    /*
        Pagina 21 de (12. Ordenação e Pesquisa em Vetores)
    */

    if(posicaoVeiculo != 0)
    {
        for(i=0; i < posicaoVeiculo; i++)
        {
            Matricula[i] = i;
            cargaMaxima[i] = Veiculo[i].CargaMaxima;
            dia[i] = Veiculo[i].DataDeFabrico.Dia;
            mes[i] = Veiculo[i].DataDeFabrico.Mes;
            ano[i] = Veiculo[i].DataDeFabrico.Ano;
            QuantEncomendasTranportadas[i] = Veiculo[i].QuantEncomendasTranportadas;
            QuantViagensEfetuadas[i] = Veiculo[i].QuantViagensEfetuadas;
            Estado[i] = Veiculo[i].Estado;
        }
        haTrocas=1;
        for(i=0; i < posicaoVeiculo-1 && haTrocas != 0; i++)
        {
            haTrocas=0;
            for (j = 0; j < posicaoVeiculo-i-1; j++)
            {
                if(QuantEncomendasTranportadas[j+1] > QuantEncomendasTranportadas[j])
                {
                    haTrocas=1;
                    aux = Matricula[j];
                    Matricula[j] = Matricula[j+1];
                    Matricula[j+1] = aux;

                    aux_float = cargaMaxima[j];
                    cargaMaxima[j] = cargaMaxima[j+1];
                    cargaMaxima[j+1] = aux_float;

                    aux = dia[j];
                    dia[j] = dia[j+1];
                    dia[j+1] = aux;

                    aux = mes[j];
                    mes[j] = mes[j+1];
                    mes[j+1] = aux;

                    aux = ano[j];
                    ano[j] = ano[j+1];
                    ano[j+1] = aux;

                    aux = QuantViagensEfetuadas[j];
                    QuantViagensEfetuadas[j] = QuantViagensEfetuadas[j+1];
                    QuantViagensEfetuadas[j+1] = aux;

                    aux = QuantEncomendasTranportadas[j];
                    QuantEncomendasTranportadas[j] = QuantEncomendasTranportadas[j+1];
                    QuantEncomendasTranportadas[j+1] = aux;

                    aux_char = Estado[j];
                    Estado[j] = Estado[j+1];
                    Estado[j+1] = aux_char;
                }
            }
        }

        printf("\n\nMatricula \t Data de Fabrico  \t Carga  \t Estado \t Encomendas Transportadas \t Viagens efectuadas\n");
        for(i=0; i < posicaoVeiculo; i++)
        {
            printf("%s \t\t %d/%d/%d\t\t   %3.2f \t %c \t\t %d \t\t\t\t %d\n", Veiculo[Matricula[i]].Matricula,dia[i],mes[i],ano[i],cargaMaxima[i],Estado[i],QuantEncomendasTranportadas[i],QuantViagensEfetuadas[i]);
        }
    }
}

int selecaoAutomatica(Veiculos Veiculo[],CarregamentoE Carregamento[],Encomendas Encomenda[],int posicaoCarregamento, int posicaoEncomenda,char Destino[100], char Matricula[9])
{
    int i,NumeroDeRegisto,posVeiculo,retorno;
    float cargaTotalEncomendas = 0;
    for(i=0; i<=posicaoEncomenda; i++)
    {
        if(strcmp(Encomenda[i].Destino,Destino)==0)
        {
            if(Encomenda[i].Estado == 'R')
            {
                NumeroDeRegisto = Encomenda[i].NumeroDeRegisto;
                posVeiculo = ProcuraMatricula(Veiculo,Matricula);
                cargaTotalEncomendas = CargaOcupada(Encomenda,i,cargaTotalEncomendas);
                retorno = carga80porcento(Encomenda,Veiculo,posicaoEncomenda,posicaoCarregamento,Matricula,cargaTotalEncomendas);
                if(retorno == 1)
                {
                    RegistarOCarregamento(Carregamento, posicaoCarregamento, Matricula,Destino,NumeroDeRegisto);
                    Encomenda[i].Estado = 'C';
                    posVeiculo = ProcuraMatricula(Veiculo,Matricula);
                    Veiculo[posVeiculo].Estado = 'C';
                    posicaoCarregamento++;
                }
                if(retorno == 2)
                {
                    RegistarOCarregamento(Carregamento, posicaoCarregamento, Matricula,Destino,NumeroDeRegisto);
                    Encomenda[i].Estado = 'C';
                    posVeiculo = ProcuraMatricula(Veiculo,Matricula);
                    Veiculo[posVeiculo].Estado = 'T';
                    posicaoCarregamento++;
                }
                if(retorno == 0)
                {
                    RegistarOCarregamento(Carregamento, posicaoCarregamento, Matricula,Destino,NumeroDeRegisto);
                    Encomenda[i].Estado = 'C';
                    posVeiculo = ProcuraMatricula(Veiculo,Matricula);
                    Veiculo[posVeiculo].Estado = 'C';
                    posicaoCarregamento++;
                }
            }

        }
    }
    return posicaoCarregamento;
}

void RegistarOCarregamento(CarregamentoE Carregamento[],int posicaoCarregamento, char matricula[9], char Destino[100], int NumeroDeRegisto)
{
    Carregamento[posicaoCarregamento].NumeroDeRegisto = NumeroDeRegisto;
    strcpy(Carregamento[posicaoCarregamento].Matricula,matricula);
    Carregamento[posicaoCarregamento].Estado = 'I';
    strcpy(Carregamento[posicaoCarregamento].Destino,Destino);
}

int ProcuraMatricula(Veiculos Veiculo[MAX_VEICULOS], char Matricula[9])
{
    int i, a=-1;
    for(i=0; i <= MAX_VEICULOS; i++)
    {
        if(strcmp(Veiculo[i].Matricula,Matricula)== 0)
        {
            a=i;
        }
    }
    return a;
}

int CargaOcupadaPorRegistar(Encomendas Encomenda[],int posicaoEncomenda, int pos)
{
    int i;
    float soma = 0;
    for(i=pos; i <= posicaoEncomenda; i++)
    {
        soma +=  Encomenda[i].Peso;
    }
    return soma;
}
