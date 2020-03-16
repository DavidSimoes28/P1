#ifndef FUNCOES_NAVEGACAO_H_INCLUDED
#define FUNCOES_NAVEGACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "Constantes.h"
#include "Estruturas.h"

void menu(Veiculos vetor[MAX_VEICULOS], char opcao,int *PosicaoVeiculo);
void consultarVeiculo(Veiculos vetor[], int posicaoVeiculo);
void ListarVeiculos(Veiculos vetor[], int posicaoVeiculo);
void consultarEncomendas(Encomendas vetor[], int posicaoEncomenda);
void ListarEncomenda(Encomendas vetor[], int i);
void DadosE(Encomendas vetor[MAX_ENCOMENDAS],Veiculos Veiculo[MAX_VEICULOS],CarregamentoE Carregamento[MAX_ENCOMENDAS],int *PosicaoEncomenda, int *PosicaoVeiculo, int *PosicaoCarregamento);
void alterarDestinoEncomenda(Encomendas vetor[],CarregamentoE Carregamento[], int PosicaoEncomenda, int PosicaoCarregamento);
int EliminarEncomenda(Encomendas vetor[],int PosicaoEncomenda,CarregamentoE Carregamento[],int PosicaoCarregamento);
int verificarVeiculo(Veiculos Veiculo[],int posicaoVeiculo, char matricula[9]);
int verificarEncomenda(Encomendas Encomenda[],int posicaoEncomenda, int numeroDeRegisto);
int verificarCarregamento(CarregamentoE Carregamento[],int posicaoCarregamento, int numeroDeRegisto, char matricula[9]);
void RegistarInicioDaViagem(Veiculos Veiculo[MAX_VEICULOS],CarregamentoE Carregamento[MAX_ENCOMENDAS],int PosicaoVeiculo, int PosicaoCarregamento);
int ProcurarMatricula(Veiculos Veiculo[MAX_VEICULOS], int posicaoVeiculo);
int ProcurarMatriculaC(CarregamentoE Veiculo[MAX_VEICULOS]);
int CargaOcupada(Encomendas Encomenda[],int pos,float soma);
int ProcurarEncomenda(Encomendas Encomenda[]);
int ProcurarEncomendaC(CarregamentoE Carregamento[]);
int RegistarCarregamento(CarregamentoE Carregamento[], int PosicaoCarregamento, int PosicaoEncomenda, int PosicaoVeiculo, Encomendas Encomenda[], Veiculos Veiculo[]);
void RegistarDescarregamento(CarregamentoE Carregamento[], int PosicaoEncomenda, Encomendas Encomenda[], int PosicaoCarregamento, Veiculos Veiculo[], int PosicaoVeiculo);
void maiorNumeroDeEncomendasEntregues(Encomendas Encomenda[], int PosicaoEncomenda);
int DataInserida(Encomendas Encomendas[], int b);
void ListarUltimaEncomenda(CarregamentoE Carregamento[], Veiculos Veiculo[],Encomendas Encomenda[], int posicaoVeiculo,int posicaoEncomenda);
void ListarVeiculo(Veiculos Veiculo[],int i);
void Estatisticas(CarregamentoE Carregamento[],int *PosicaoVeiculo,int *PosicaoEncomenda,int *PosicaoCarregamento);
float pesoMedioEncomendas(Encomendas Encomenda[], int PosicaoEncomenda);
float cargaMediaVeiculos(Veiculos Veiculo[],CarregamentoE Carregamento[],Encomendas Encomenda[], int PosicaoVeiculo, int PosicaoCarregamento, int PosicaoEncomenda);
void menosViagensEfetuadas(Veiculos Veiculo[], int PosicaoVeiculo);
void encomendasEntreguesNumaDeterminadaData(Encomendas Encomenda[], int PosicaoEncomenda);
int carga80porcento(Encomendas Encomenda[],Veiculos Veiculo[],int posicaoEncomenda,int posicaoCarregamento,char Matricula[9], float cargaOcup);
void guardar_fich_bin_veiculos(Veiculos Veiculo[],int PosicaoVeiculo);
void ler_fich_bin_veiculos(Veiculos Veiculo[],int *PosicaoVeiculo);
void guardar_fich_bin_Encomendas(Encomendas Encomenda[],int PosicaoEncomenda);
void ler_fich_bin_Encomendas(Encomendas Encomenda[],int *PosicaoEncomenda);
void guardar_fich_bin_Carregamento(CarregamentoE Carregamento[],int PosicaoCarregamento);
void ler_fich_bin_Carregamento(CarregamentoE Carregamento[],int *PosicaoCarregamento);
void logDevolucao(int Numeroderegisto,char Destino[100],int dia,int mes,int ano,char Matricula[9],char CausaDevolucao[100]);
void ordenarEstrutura(Veiculos Veiculo[], int posicaoVeiculo);
int selecaoAutomatica(Veiculos Veiculo[],CarregamentoE Carregamento[],Encomendas Encomenda[],int posicaoCarregamento, int posicaoEncomenda,char Destino[100], char Matricula[9]);
void RegistarOCarregamento(CarregamentoE Carregamento[],int posicaoCarregamento, char matricula[9], char Destino[100], int NumeroDeRegisto);
int ProcuraMatricula(Veiculos Veiculo[MAX_VEICULOS], char Matricula[9]);
int CargaOcupadaPorRegistar(Encomendas Encomenda[],int posicaoEncomenda, int pos);

#endif // FUNCOES_NAVEGACAO_H_INCLUDED
