#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

typedef struct
{
    int Dia,Mes,Ano;
}TipoData;

typedef struct
{
    char Matricula[9];
    TipoData DataDeFabrico;
    float CargaMaxima;
    char Estado; /* D - Disponivel, C - Carga, T - a Transportar, R - de Regresso, A - Avariado*/
    int QuantViagensEfetuadas;
    int QuantEncomendasTranportadas;
} Veiculos; /* 10 veiculos */

typedef struct
{
    int NumeroDeRegisto;
    TipoData DataDeRegisto;
    float Peso;
    char Destino[100];
    char Estado; /* R - Registada, C - Carregada, E - Entregue, D - Devolvida*/
    TipoData DataDeEntrega;
    char ConjObserv[100];
} Encomendas; /* 100 encomendas */

typedef struct{
	int NumeroDeRegisto;
	char Matricula[9];
	char Destino[100];
	char Estado; /* D - Devolvida, E - Entregue, I - Indeterminado*/
} CarregamentoE;

#endif // ESTRUTURAS_H_INCLUDED

