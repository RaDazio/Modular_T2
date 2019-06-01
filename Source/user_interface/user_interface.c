#define TABSIZE 24
#define MAXPERCASA 15
#define DEBUG


#include <stdio.h>
#include <Windows.h>

#include "..\interfaces\user_interface.h"
#include "..\interfaces\tabuleiro.h"
#include "..\interfaces\peca.h"
#include "..\interfaces\lista.h"


void RenderizarTabuleiro();
void LimparRender();
void RenderizarStatus();
void RenderizarNumCasas(int ini, int fim);


void RenderizarNumCasas(int ini, int fim){
	int idx;
	for(idx = ini ; idx < fim ; idx++){
		printf("  |--------|");
	}
	printf("\n");
	for(idx = ini ; idx < fim ; idx++){
		printf("  |   %2d   |",idx+1);
	}
	printf("\n");
		for(idx = ini ; idx < fim ; idx++){
		printf("  |--------|");
	}
	printf("\n");
	return; 
}

void RenderizarStatus(){
	printf("\n  ==============================================================================================================================================\n");
	printf("  | Brancas finalizadas: %d   |   Brancas Capturadas: %d   |   Pretas Finalizadas: %d   |   Pretas Capturadas: %d   |   Pontuacao da partida: %d    |",0, 0, 0, 0 ,0);
	printf("\n  ==============================================================================================================================================\n");
}



void RenderizarTabuleiro(){
	LIS_tppLista casas;
	LIS_tppLista vec_list_pec[TABSIZE];
	
	TBL_CondRet tab_cond = TBL_ObterCasas(&casas);
	LIS_tpCondRet lis_cond;

	int idx=0;
	int finish_flags[TABSIZE];
	if(tab_cond != TBL_ok) exit(1);
	
	for(idx = 0; idx<TABSIZE ; idx++){
		finish_flags[idx] = 0;
	}
	idx = 0;

	IrInicioLista(casas);

	lis_cond = LIS_AvancarElementoCorrente(casas,0);
	if(lis_cond != LIS_CondRetOK) exit(-1);

	while(lis_cond != LIS_CondRetFimLista){
		LIS_tppLista aux;
		vec_list_pec[idx] = (LIS_tppLista) LIS_ObterValor(casas);
		aux= vec_list_pec[idx];
		idx++;
		IrInicioLista(aux);
		lis_cond = LIS_AvancarElementoCorrente(casas,1);
	}

	IrInicioLista(casas);

	system("echo off");	
	system("mode 800");
	system("cls");
	printf("\n");
	
	RenderizarNumCasas(0, TABSIZE/2);

	for(idx = 0; idx < MAXPERCASA; idx++){
		int aux;
		for (aux = 0; aux < TABSIZE/2 ; aux++){
			PecaHead p = (PecaHead) LIS_ObterValor(vec_list_pec[aux]);
			PEC_color color;
			LIS_tpCondRet lis_ret;

			lis_ret = LIS_AvancarElementoCorrente(vec_list_pec[aux], 1);

			if(lis_ret == LIS_CondRetFimLista){
				if(finish_flags[aux] == 0){	
					finish_flags[aux] = 1;
				}
				else{
					p = NULL;
				}
			}

			printf("  |");
			if(p == NULL){
				printf("    :   ");
			}
			else{
				PEC_ObterCor(&color, p);
				(color == COLOR_Black)? printf("    p   ") : printf("    b   ");
			}
			printf("|");
		}
		printf("\n");
	}

	RenderizarStatus();

	for(idx = 0; idx < MAXPERCASA; idx++){
		int aux;
		for (aux = TABSIZE/2 ; aux <TABSIZE ; aux++){
			PecaHead p = (PecaHead) LIS_ObterValor(vec_list_pec[aux]);
			PEC_color color;
			LIS_tpCondRet lis_ret;

			lis_ret = LIS_AvancarElementoCorrente(vec_list_pec[aux], 1);

			if(lis_ret == LIS_CondRetFimLista){
				if(finish_flags[aux] == 0){	
					finish_flags[aux] = 1;
				}
				else{
					p = NULL;
				}
			}
			printf("  |");
			if(p == NULL){
				printf("    :   ");
			}
			else{
				PEC_ObterCor(&color, p);
				(color == COLOR_Black)? printf("    p   ") : printf("    b   ");
			}
			printf("|");
		}
		printf("\n");
	}
	RenderizarNumCasas(TABSIZE/2, TABSIZE);
}
