#define DADOS_LADOS 6

#include <stdio.h>
#include <Windows.h>

#include "interfaces\dado.h"
#include "interfaces\peca.h"
#include "interfaces\DADOPONTOS.H"
#include "interfaces\tabuleiro.h"
#include "interfaces\user_interface.h"

void setUp (PEC_color* first_player, int* pontuacao_global_color1, int* pontuacao_global_color2){

	// Inicialização de variaveis //
	int dice[2];
	TBL_CondRet tab_ret ;
	DICE_CondRet d_ret;
	/******************************/

	// Criação do tabuleiro //
	tab_ret = TBL_CriarTabuleiro();
	if(tab_ret != TBL_ok){
		printf("ERRO AO CRIAR O TABULEIRO\n");
		exit(1);
	}

	// Settando variaveis globais do jogo //
	*pontuacao_global_color1 = *pontuacao_global_color2 = 0;
	
	// Settando a aparencia do cmd //
	system("echo off");	
	system("mode 800");
	system("color 90");

/* DEFINIÇÃO DO PRIMEIRO JOGADOR */
DICE_RETRY_CHOOSER:
	d_ret = DICE_RolarDado(&dice[0],DADOS_LADOS);
	if( d_ret == DICE_ok){
		d_ret = DICE_RolarDado(&dice[1],DADOS_LADOS);
	}
	if(d_ret != DICE_ok){
		printf("ERRO AO DEFINIR O PRIMEIRO JOGADOR\n");
		exit(1);
	}
	printf("Definindo o primeiro jogador\n");
	printf("Branco: %d\n",dice[0]);
	printf("Preto: %d\n",dice[1]);
	if(dice[0] == dice[1]){
		printf("Dados iguais, jogando novamente para definir o primeiro a jogar\n");
		system("timeout 3");
		goto DICE_RETRY_CHOOSER;
	}
/********************************/
	system("timeout 3");
	*first_player = (dice[0]>dice[1])? COLOR_White: COLOR_Black;

}

PEC_color TrocarJogador(PEC_color jogador){
	return (jogador == COLOR_Black)? COLOR_White: COLOR_Black;
}

int LerCasaDoTeclado(){
	int ret;
	scanf("%d",&ret);
	return ret-1;
}


int PrimeiraCasaValida(int casa_from, PEC_color jogador_da_vez){
	PEC_color aux;
	TBL_CondRet tbl_ret = TBL_CorPecasCasa(&aux,casa_from);
	if( tbl_ret != TBL_ok ) return 0;
	if( jogador_da_vez != aux ) return 0;
	if( casa_from < 0 ) return 0;
	return 1;
}

int SegundaCasaValida(int casa_from, int casa_to, PEC_color jogador_da_vez){

}
int ObterDado(int value, int vector[4], int* used_idx){
	int idx, real_value=-100;
	if(value == -1) return -1;
	for(idx = 0 ; idx < 4 ; idx++){
		if(value == vector[idx]){
			real_value = vector[idx];
			vector[idx] = 0;
			if(used_idx != NULL){
				*used_idx = idx;
			}
			break;
		}
	}
	return real_value;
}
void RestaurarDado(int value, int idx, int vector[4]){
	if(idx >= 0 && idx < 4 && vector[idx] == 0){
		vector[idx] = value;
	}
}

int main (void){	
	int dices[4];
	int qtd_dice_valid;

	int pontuacao_global_branca, pontuacao_global_preta;
	
	int casa_from, casa_to;
	int use_dice_value=0;
	int qtd_casas_from_possiveis;
	int casas_from_possiveis[24];

	int qtd_casas_to_possiveis;
	int casas_to_possiveis[24];

	int idx;

	PEC_color jogador_da_vez;
	TBL_CondRet tbl_ret;
	DICE_CondRet dice_ret;
	
	setUp(&jogador_da_vez, &pontuacao_global_branca, &pontuacao_global_preta);

	while(1){
		/*********** Rolando  Dados ***************/
		dice_ret = DICE_RolarDado(&dices[0],DADOS_LADOS);
		if(dice_ret == DICE_ok) dice_ret = DICE_RolarDado(&dices[1],DADOS_LADOS);
		if(dice_ret == DICE_wrong){
			printf("ERRO AO ROLAR DADOS");
			exit(1);
		}
		if(dices[0] == dices[1]){
			dices[2]=dices[3]=dices[0];
			qtd_dice_valid = 4;
		}
		else{
			qtd_dice_valid = 2;
		}
		/******************************************/

		for(idx = 0 ; idx < qtd_dice_valid ; idx++){
			PEC_color color_aux;
			int flag_peca_finalizada;
			int utilized_dice_idx;
			flag_peca_finalizada = 0;	
			
			/*** Obtendo as casas do jogador da vez ***/
			tbl_ret = TBL_ObterCasasPorDono(jogador_da_vez, casas_from_possiveis, &qtd_casas_from_possiveis);
			if( tbl_ret != TBL_ok ){
				printf(" Erro ao obter as casas do jogador da vez ");
				exit(1);
			}
			/******************************************/
ESCOLHER_NOVAMENTE:
			/**** Renderizando tabuleiro e jogadas possiveis de mover****/
			RenderizarTabuleiro();
			RenderizarJogadaAtual(jogador_da_vez, dices, qtd_dice_valid, casas_from_possiveis, qtd_casas_from_possiveis,0);
			/************************************************************/
		
			/*********************** Movendo peça ***********************/
			printf("Esolha uma casa de origem dentre as disponiveis, -1 para pular a vez: ");
			casa_from = LerCasaDoTeclado();
			if(casa_from == -2) break;

			if( !PrimeiraCasaValida(casa_from,jogador_da_vez) ){
				printf("Casa invalida, escolha novamente: ");
				system("timeout 2");
				goto ESCOLHER_NOVAMENTE;
			}
				/*** Renderizando casas possiveis para mover ***/

			printf("Esolha um dado, -1 para escolher a casa novamente a vez: ");

ESCOLHER_DADO_NOVAMENTE:
			scanf("%d", &use_dice_value);
			use_dice_value = ObterDado(use_dice_value,dices,&utilized_dice_idx);
			if(use_dice_value == -100){
				printf("Escolha um dado válido: ");
				goto ESCOLHER_DADO_NOVAMENTE;
			}
			if(use_dice_value == -1) goto ESCOLHER_NOVAMENTE;

		/**** Finalização das peças *****/
			if(jogador_da_vez == COLOR_White){
				casa_to = casa_from + use_dice_value;
				if(casa_to > 24){
					flag_peca_finalizada = 1;
				}
			}
			else {
				casa_to = casa_from - use_dice_value;
				if(casa_to < 0){
					// Finalizar peça preta
					flag_peca_finalizada = 1;
				}
			}
		/*******************************/
		/******* Checando destino ******/
			tbl_ret = TBL_CorPecasCasa(&color_aux,casa_to);
			if(tbl_ret != TBL_ok){
				printf("Erro ao obter a casa para onde mover");
				exit(1);
			}
			if(color_aux == ((jogador_da_vez == COLOR_Black)? COLOR_White: COLOR_Black)){
				int qtd;
				tbl_ret = TBL_QuantidadePecasCasa(&qtd, casa_to);
				if(tbl_ret != TBL_ok){
					printf("Erro ao obter a casa para onde mover");
					exit(1);
				}
				if(qtd == 1){
					// comer peça
					tbl_ret = RetirarPecaDoTabuleiro(&color_aux,casa_to);
					if(tbl_ret != TBL_ok){
						printf("ERRO AO COMER PECA\n");
						exit(1);
					}
					
				}
				if(qtd > 1){
					printf("Casa invalida\n");
					system("timeout 2");
					RestaurarDado(use_dice_value, utilized_dice_idx,dices);
					flag_peca_finalizada = 0;
					goto ESCOLHER_NOVAMENTE;
				}
			}
		/******* Captura de peças ******/


			if(!flag_peca_finalizada){
				TBL_MoverPeca(casa_from, casa_to);
			}
		}
		/**************** Trocando o jogador da vez *****************/
		jogador_da_vez = TrocarJogador(jogador_da_vez);
		/************************************************************/
	}
	return 0;
}