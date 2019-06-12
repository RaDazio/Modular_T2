#define TABSIZE		24
#define MAXPERCASA	15
#define WIDTH		300
#define EMPTY		"        "
#define BLACK		"    O   "
#define WHITE		"   \033[1;33m O \033[0m  "

#define DEBUG

#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "..\interfaces\user_interface.h"
#include "..\interfaces\DADOPONTOS.H"
#include "..\interfaces\tabuleiro.h"
#include "..\interfaces\peca.h"
#include "..\interfaces\lista.h"

void RenderizarTabuleiro();
void LimparRender();
void RenderizarStatus();
void RenderizarNumCasas(int ini, int fim);
void Menu(int* resposta);

void Menu(int* resposta){
	int r;
	printf("Voce deseja:\n");
	printf("1 - Novo jogo\n");
	printf("2 - Carregar jogo\n");
	printf("Digite a opcao: ");
	scanf("%d",&r);
	*resposta = r;
}


void DumpBuffer(char buffer[][WIDTH], int n_linhas){
	int idx;
	for(idx = 0; idx < n_linhas ; idx++){
		printf("%s", buffer[idx]);
		strcpy_s(buffer[idx], WIDTH,"\0");
	}
}

void LimparRender(){
	system("cls");
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

void RenderizarStatus(){
	printf("\n  ==============================================================================================================================================\n");
	printf("  | Brancas finalizadas: %d   |   Brancas Capturadas: %d   |   Pretas Finalizadas: %d   |   Pretas Capturadas: %d   |   Pontuacao da partida: %d    |",0, 0, 0, 0 ,0);
	printf("\n  ==============================================================================================================================================\n");
}

void RenderizarJogadaAtual(PEC_color jogadorAtual, int dices[4], int qtd_dice_valid, int vector[24], int qtd_casas, int pode_dobrar){
	int idx;
	printf("Jogador da vez: %s\n",(jogadorAtual == COLOR_White)? "\033[1;33mBranco\033[0m": "Preto");
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
	if(pode_dobrar){
		printf("Jogador: %s, deseja dobrar a potuação para: %d\n",(jogadorAtual == COLOR_Black)? "Preto":"Branco", 0);
	}
	printf("\n");

}


void RenderizarTabuleiro(){
	
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
	LimparRender();
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
	RenderizarStatus();

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
}
