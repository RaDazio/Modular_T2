#define DADOS_LADOS 6

#include <stdio.h>
#include <Windows.h>

#include "interfaces\dado.h"
#include "interfaces\peca.h"
#include "interfaces\DADOPONTOS.H"
#include "interfaces\tabuleiro.h"
#include "interfaces\user_interface.h"

void setUp (PEC_color* first_player, int* pontuacao_global){

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

	// Rolagem do primeiro dado //
	d_ret = DICE_RolarDado(&dice[0],DADOS_LADOS);

	// Settando variaveis globais do jogo //
	*pontuacao_global = 0;
	
	// Settando a aparencia do cmd //
	system("echo off");	
	system("mode 800");
	system("color 90");

/* DEFINIÇÃO DO PRIMEIRO JOGADOR */
RETRY:	
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
		goto RETRY;
	}
/********************************/
	system("timeout 3");
	*first_player = (dice[0]>dice[1])? COLOR_White: COLOR_Black;

}

PEC_color TrocarJogador(PEC_color jogador){
	return (jogador == COLOR_Black)? COLOR_White: COLOR_Black;
}


int main (void){
	int casa_from, casa_to;
	int dices[2];
	int pontuacao_global;

	PEC_color jogador_da_vez;
	DICE_CondRet dice_ret;
	
	int casas_possiveis[] = {1,2,3};
	setUp(&jogador_da_vez,&pontuacao_global);
	while(1){
		dice_ret = DICE_RolarDado(&dices[0],DADOS_LADOS);
		if(dice_ret == DICE_ok) dice_ret = DICE_RolarDado(&dices[1],DADOS_LADOS);
		if(dice_ret == DICE_wrong){
			printf("ERRO AO ROLAR DADOS");
			exit(1);
		}
		RenderizarTabuleiro();
		RenderizarJogadaAtual(jogador_da_vez, dices, casas_possiveis, 3, 0);
		scanf("%d",&casa_from);
		//TBL_MoverPeca(casa_from-1,casa_to-1);
		jogador_da_vez = TrocarJogador(jogador_da_vez);
		
	}

	return 0;
}