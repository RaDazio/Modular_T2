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

	// Rolagem do primeiro dado //
	d_ret = DICE_RolarDado(&dice[0],DADOS_LADOS);

	// Settando variaveis globais do jogo //
	*pontuacao_global_color1 = *pontuacao_global_color2 = 0;
	
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

int LerCasaDoTeclado(){
	int ret;
	scanf("%d",&ret);
	return ret-1;
}


int PrimeiraCasaValida(int casa_from, PEC_color jogador_da_vez){
	PEC_color aux;
	TBL_CondRet tbl_ret = TBL_CorPecasCasa(&aux,casa_from);
	if(tbl_ret != TBL_ok) return 0;
	if( jogador_da_vez != aux ) return 0;
	return 1;
}

int main (void){
	int casa_from, casa_to;
	int dices[2];
	int pontuacao_global_branca, pontuacao_global_preta;
	
	int qtd_casas_possiveis;
	int casas_possiveis[24];

	PEC_color jogador_da_vez;
	TBL_CondRet tbl_ret;
	DICE_CondRet dice_ret;
	

	setUp(&jogador_da_vez, &pontuacao_global_branca, &pontuacao_global_preta);

	while(1){
		tbl_ret = TBL_ObterCasasPorDono(jogador_da_vez, casas_possiveis, &qtd_casas_possiveis);
		dice_ret = DICE_RolarDado(&dices[0],DADOS_LADOS);
		if(dice_ret == DICE_ok) dice_ret = DICE_RolarDado(&dices[1],DADOS_LADOS);
		if(dice_ret == DICE_wrong){
			printf("ERRO AO ROLAR DADOS");
			exit(1);
		}
		RenderizarTabuleiro();
		RenderizarJogadaAtual(jogador_da_vez, dices, casas_possiveis, qtd_casas_possiveis,0);
		printf("Esolha uma casa dentre as disponiveis: ");
		casa_from = LerCasaDoTeclado();
		while( !PrimeiraCasaValida(casa_from,jogador_da_vez)){
			printf("Casa invalida, escolha novamente: ");
			casa_from = LerCasaDoTeclado();
		}
		printf("Esolha uma casa dentre as disponiveis: ");
		casa_to = LerCasaDoTeclado();
		TBL_MoverPeca(casa_from,casa_to);
		jogador_da_vez = TrocarJogador(jogador_da_vez);

	}

	return 0;
}