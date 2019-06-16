/********************************************************************************************
*	$MCI Módulo de implementação:	user_interface
*
*	Arquivo gerado:			user_interface.c
*	Letras identificadoras:	I
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*  $HA Histórico de evolução:
*     Versão       Autor          Data         Observações
*       1.00   		rdms   		29/05/2019	 	Inú€io do desenvolvimento
*		2.00		rdms		16/06/2019		Fim do desenvolvimento
*
*******************************************************************************************/

#define TABSIZE		24
#define MAXPERCASA	15
#define WIDTH		300
#define EMPTY		"        "
#define BLACK		"    p   "
#define WHITE		"    b   "

#define DEBUG

#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "..\interfaces\user_interface.h"
#include "..\interfaces\tabuleiro.h"
#include "..\interfaces\peca.h"
#include "..\interfaces\lista.h"

/******** Interface das fuções internas do modulo **********/
static void RenderizarStatus(int pecas_brancas_fin, int pecas_brancas_cap, int pecas_pretas_fin, int pecas_pretas_cap, int pontuacao);
static void RenderizarNumCasas(int ini, int fim);
static void DumpBuffer(char buffer[][WIDTH], int n_linhas);

/********* Código das funções internas do modulo ***********/
void RenderizarStatus(int pecas_brancas_fin, int pecas_brancas_cap, int pecas_pretas_fin, int pecas_pretas_cap, int pontuacao){
	printf("\n  ==============================================================================================================================================\n");
	printf("  | Brancas finalizadas: %d   |   Brancas Capturadas: %d   |   Pretas Finalizadas: %d   |   Pretas Capturadas: %d   |   Pontuacao da partida: %d    |",pecas_brancas_fin, pecas_brancas_cap, pecas_pretas_fin, pecas_pretas_cap ,pontuacao);
	printf("\n  ==============================================================================================================================================\n");
}
void RenderizarNumCasas(int ini, int fim){
	int idx;
	if(ini < fim){
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
	}
	else{
		for(idx = ini ; idx > fim ; idx--){
			printf("  |--------|");
		}
		printf("\n");
		for(idx = ini ; idx > fim ; idx--){
			printf("  |   %2d   |",idx);
		}
		printf("\n");
		for(idx = ini ; idx > fim ; idx--){
			printf("  |--------|");
		}
	}
	printf("\n");
	return; 
}
void DumpBuffer(char buffer[][WIDTH], int n_linhas){
	int idx;
	for(idx = 0; idx < n_linhas ; idx++){
		printf("%s", buffer[idx]);
		strcpy_s(buffer[idx], WIDTH,"\0");
	}
}
/***********************************************************/

/************ Código das funções exportadas pelo módulo *************/

/***********************************************************************
*	$FC Função:	I Menu_Inicial
*
**********************************************************************/
void I_Menu_Inicial(int* resposta){
	int r;
	printf("Voce deseja:\n");
	printf("1 - Novo jogo\n");
	printf("2 - Carregar jogo\n");
	printf("3 - Sair\n");
	printf("Digite a opcao: ");
	scanf_s("%d",&r,sizeof(int));
	*resposta = r;
}

/***********************************************************************
*	$FC Função:I Menu_Sair
*
**********************************************************************/
void I_Menu_Sair(int *resposta){
	int r;
	printf("Voce deseja:\n");
	printf("1 - Sair sem salvar\n");
	printf("2 - Sair e salvar\n");
	printf("3 - Continuar\n");
	printf("Digite a opcao: ");
	scanf_s("%d",&r,sizeof(int));
	*resposta = r;
}

/***********************************************************************
*	$FC Função:I LimparRender
*
**********************************************************************/

void I_LimparRender(){
	system("cls");
}

/***********************************************************************
*	$FC Função:I RenderizarMenuDePontos
*
**********************************************************************/

void I_RenderizarMenuDePontos(int *response, PEC_color jogador_da_vez){
	int r;
	printf("Jogador %s, deseja duplicar os pontos?\n",(jogador_da_vez == COLOR_White)? "Branco": "Preto");
	printf("1 - Sim\n");
	printf("2 - Nao\n");
	scanf_s("%d",&r);
	if(r == 2){
		*response= -1;
		return;
	}
	if (r == 1){
		printf("O jogador %s aceita dobrar?\n", (jogador_da_vez == COLOR_White)? "Preto" : "Branco");
		printf("1 - Sim\n");
		printf("2 - Nao\n");
		scanf_s("%d",&r);
	}
	*response = r;
}

/***********************************************************************
*	$FC Função:I RenderizarJogadaAtual
*
**********************************************************************/

void I_RenderizarJogadaAtual(PEC_color jogadorAtual, int dices[4], int qtd_dice_valid, int vector[24], int qtd_casas){
	int idx;
	printf("Jogador da vez: %s\n",(jogadorAtual == COLOR_White)? "Branco": "Preto");
	printf("Dados disponiveis: ");
	for(idx = 0; idx < qtd_dice_valid ; idx++){
		if(dices[idx] != 0){
			printf(" %d ", dices[idx]);
		}
	}
	printf("\t\tCasas possiveis: ");
	for(idx = 0; idx < qtd_casas; idx++){
		printf(" %d ",vector[idx]);
	}
	printf("\n");

}

/***********************************************************************
*	$FC Função:I RenderizarTabuleiro
*
**********************************************************************/

void I_RenderizarTabuleiro(int pontuacao_preta, int pontuacao_branca, int pecas_brancas_fin, int pecas_brancas_cap, int pecas_pretas_fin, int pecas_pretas_cap, int pontuacao){
	
	/* Inicialização de variaveis */
	LIS_tppLista casas;
	LIS_tppLista vec_list_pec[TABSIZE];
	
	TBL_CondRet tab_cond = TBL_ObterCasas(&casas);
	LIS_tpCondRet lis_cond;
	int idx=0;
	int finish_flags[TABSIZE];
	
	char buffer[MAXPERCASA][WIDTH];

	/*****************************/

	// Preenchimento do buffer //
	for(idx = 0; idx<15 ; idx++ ){
		strcpy_s(buffer[idx], WIDTH,"\0");
	}

	// Preenchimento das flags para cada casa //
	for(idx = 0; idx<TABSIZE ; idx++){
		finish_flags[idx] = 0;
	}

	// Verificação de assertiva //
	if(tab_cond != TBL_ok){
		printf("NAO HA TABULEIRO\n");
		exit(1);	
	}

	// Settando inicialização //
	IrInicioLista(casas);

	// Verificação de assertiva //
	lis_cond = LIS_AvancarElementoCorrente(casas,0);
	if(lis_cond != LIS_CondRetOK){
		printf("ERRO AO ANDAR NAS CASAS\n");
		exit(-1);
	}

	// Preenchimento do vetor de pecas para facilitação na renderizção //
	idx = 0;
	while(lis_cond != LIS_CondRetFimLista){
		LIS_tppLista aux;
		vec_list_pec[idx] = (LIS_tppLista) LIS_ObterValor(casas);
		aux = vec_list_pec[idx];
		idx++;
		IrInicioLista(aux);
		lis_cond = LIS_AvancarElementoCorrente(casas,1);
	}
	
	// Devolvendo ao estado inicial //
	IrInicioLista(casas);

	// Limpando a tela //
	I_LimparRender();
	printf("\n");
	
	// Renderizar casas superiores //
	RenderizarNumCasas(0, TABSIZE/2);

	// Preenchimento do buffer para parte superior //
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
			strcat_s(buffer[idx], WIDTH,"  |");
			if(p == NULL){
				strcat_s(buffer[idx],WIDTH,EMPTY);
			}
			else{
				PEC_ObterCor(&color, p);
				(color == COLOR_Black)? strcat_s(buffer[idx],WIDTH,BLACK) : strcat_s(buffer[idx],WIDTH,WHITE);
			}
			strcat_s(buffer[idx], WIDTH, "|");
		}
		if(idx != MAXPERCASA-1){
			strcat_s(buffer[idx], WIDTH,"\n");
		}
	}

	// Dump do buffer //
	DumpBuffer(buffer,15);

	// Renderização da barra do meio //
	RenderizarStatus(pecas_brancas_fin, pecas_brancas_cap, pecas_pretas_fin, pecas_pretas_cap, pontuacao);

	// Preenchimento do buffer para parte inferior //
	for(idx = 0; idx < MAXPERCASA; idx++){
		int aux;
		for (aux = TABSIZE-1 ; aux >= TABSIZE/2 ; aux--){

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
			strcat_s(buffer[14-idx], WIDTH, "  |");
			if(p == NULL){
				strcat_s(buffer[14-idx], WIDTH, EMPTY);
			}
			else{
				PEC_ObterCor(&color, p);
				(color == COLOR_Black)? strcat_s(buffer[14-idx], WIDTH,BLACK) : strcat_s(buffer[14-idx], WIDTH ,WHITE);
			}
			strcat_s(buffer[14-idx], WIDTH, "|");
		}
		strcat_s(buffer[14 - idx], WIDTH, "\n");
	}

	// Dump do buffer //
	DumpBuffer(buffer,15);

	// Renderização das casas inferiores //
	RenderizarNumCasas(TABSIZE, TABSIZE/2);

	printf("Pontuacao global do jogador preto %d\t",pontuacao_preta);
	printf("Pontuacao global do jogador branco %d\n",pontuacao_branca);

}
