#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Estruturas.h"
#include "Constantes.h"
#include "funcoes_navegacao.h"

int main()
{
    Veiculos Veiculos[MAX_VEICULOS];
    Encomendas Encomendas[MAX_ENCOMENDAS];
    CarregamentoE Carregamento[MAX_ENCOMENDAS];
    char opcao,op;
    int PosicaoVeiculo,PosicaoCarregamento;
    int PosicaoEncomenda;
    float CargaMedia,pesoMedio;
    PosicaoEncomenda = 0;
    PosicaoVeiculo=0;
    PosicaoCarregamento=0;

    do
    {
        if(PosicaoCarregamento !=0 && PosicaoEncomenda != 0 && PosicaoVeiculo != 0)
        {
            Estatisticas(Carregamento,&PosicaoVeiculo,&PosicaoEncomenda,&PosicaoCarregamento);
        }
        else
        {
            printf("Nao existe dados para estatistica\n\n");
        }

        printf("\n\nMenu\n\nE - Encomendas\nV - Veiculos\nG - Guardar Dados \nD - Ler Dados\nI - Incio|Regresso da viagem\nL - Listagens\nS - Sair");
        do
        {
            printf("\n\tOpcao --> ");
            scanf(" %c",&op);
            op = toupper(op);
        }
        while(op != 'E' && op !='V' && op !='S' && op !='D' && op !='G' && op !='I' && op !='L' && op !='A');

        switch(op)
        {
        case 'E':
            if(PosicaoEncomenda >= MAX_ENCOMENDAS)
            {
            }
            else
            {
                DadosE(Encomendas,Veiculos,Carregamento,&PosicaoEncomenda,&PosicaoVeiculo,&PosicaoCarregamento);
            }

            break;
        case 'V':
            if(PosicaoVeiculo >= MAX_ENCOMENDAS)
            {
            }
            else
            {
                menu(Veiculos,opcao,&PosicaoVeiculo);
            }
            break;
        case 'D':
            ler_fich_bin_veiculos(Veiculos, &PosicaoVeiculo);
            ler_fich_bin_Encomendas(Encomendas, &PosicaoEncomenda);
            ler_fich_bin_Carregamento(Carregamento, &PosicaoCarregamento);
            break;
        case 'G':
            guardar_fich_bin_veiculos(Veiculos, PosicaoVeiculo);
            guardar_fich_bin_Encomendas(Encomendas, PosicaoEncomenda);
            guardar_fich_bin_Carregamento(Carregamento, PosicaoCarregamento);
            break;
        case 'I':
            RegistarInicioDaViagem(Veiculos,Carregamento,PosicaoVeiculo,PosicaoCarregamento);
            break;
        case 'L':
            if(PosicaoCarregamento !=0 && PosicaoEncomenda != 0 && PosicaoVeiculo != 0)
            {
                do
                {
                    printf("\nU - Ultimo veiculo a Transportar encomenda\nV - Veiculos Ordenados\nE - Estatisticas\nS - Sair\nOpcao-->");
                    scanf(" %c",&opcao);
                    opcao=toupper(opcao);
                }
                while(opcao!='V' && opcao !='U' && opcao !='E' && opcao !='S');
            }
            if(opcao=='V')
            {
                ordenarEstrutura(Veiculos,PosicaoVeiculo);
            }
            else
            {
                if(opcao=='U')
                {
                    ListarUltimaEncomenda(Carregamento, Veiculos,Encomendas, PosicaoVeiculo, PosicaoEncomenda);
                }
                else
                {
                    if(opcao=='E')
                    {
                        encomendasEntreguesNumaDeterminadaData(Encomendas,PosicaoEncomenda);
                        pesoMedio = pesoMedioEncomendas(Encomendas, PosicaoEncomenda);
                        printf("\nPeso medio das Encomendas: %.2f", pesoMedio);
                        CargaMedia = cargaMediaVeiculos(Veiculos,Carregamento,Encomendas,PosicaoVeiculo,PosicaoCarregamento,PosicaoEncomenda);
                        if(CargaMedia == 0)
                        {
                            printf("\nNao existem veiculos em transporte");
                        }
                        else
                        {
                            printf("\nCarga media dos veiculos: %.2f", CargaMedia);
                        }
                        menosViagensEfetuadas(Veiculos,PosicaoVeiculo);
                        maiorNumeroDeEncomendasEntregues(Encomendas,PosicaoEncomenda);
                    }
                }
            }
            break;
        case 'S':
            break;
        }
    }
    while(op != 'S');
    return 0;
}

//David Simões nº 2170978 (D)
//Frederico Piedade nº 2171091 (D)

