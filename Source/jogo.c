#define DADOS_LADOS 6

#include <stdio.h>
#include <Windows.h>

#include "interfaces\dado.h"
#include "interfaces\peca.h"
#include "interfaces\DADOPONTOS.H"
#include "interfaces\tabuleiro.h"
#include "interfaces\user_interface.h"
#include "interfaces\PecasFinalizadas.h"


void SetUp(){
	DPT_CondRet dpt_ret;
	TBL_CondRet tbl_ret;
	PF_CondRet pf_ret;

	// Criação do dadoPontos //
	dpt_ret = DPT_CriarDadoPontos();
	if(dpt_ret != DPT_OK){
		printf("ERRO AO CRIAR O DADO PONTOS\n");
		exit(1);
	}
	// Criação do tabuleiro //
	tbl_ret = TBL_CriarTabuleiro();
	if(tbl_ret != TBL_ok){
		printf("ERRO AO CRIAR O TABULEIRO\n");
		exit(1);
	}

	pf_ret = PF_CriarPecasFinalizadas();
	if (pf_ret != PF_OK){
		printf("ERRO AO INICIALIZAR PEÇAS FINALIZADAS\n");
		exit(1);
	}
}

void TearDown(){
	DPT_CondRet dpt_ret;
	TBL_CondRet tbl_ret;
	PF_CondRet pf_ret;

	dpt_ret = DPT_DestruirDadoPontos();
	if(dpt_ret != DPT_OK){
		exit(1);
	}
	tbl_ret = TBL_DestruirTabuleiro();
	if(tbl_ret != TBL_ok){
		exit(1);
	}
	pf_ret = PF_DestruirPecasFinalizadas();
	if(pf_ret != PF_OK){
		exit(1);
	}
}

void NovoJogo (PEC_color* first_player, int* pontuacao_global_color1, int* pontuacao_global_color2){
	// Inicialização de variaveis //
	int dice[2];
	TBL_CondRet tab_ret ;
	DICE_CondRet d_ret;
	DPT_CondRet dpt_ret;
	/******************************/

	SetUp();

	// Settando variaveis globais do jogo //
	*pontuacao_global_color1 = *pontuacao_global_color2 = 0;

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

void RecuperarJogo(PEC_color *first_player, int *pontuacao_global_color1, int *pontuacao_global_color2){

	// Inicializacao de variaveis //
	TBL_CondRet tab_ret ;
	DPT_CondRet dpt_ret;
	FILE *fp;
	/******************************/

	SetUp();
	
	// RECUPERACAO DAS PONTUACOES GLOBAIS E VEZ DO JOGADOR //
	printf("Recuperando dados.....\n");

	fp = fopen("gamao-save.txt", "r");
	// EXIT SE FALHAR //
	if (fp == NULL){
		perror("Erro ao acessar arquivo de save");
		printf("O jogo nao pode ser recuperado\n");
		exit(1);
	}

	// CARREGA PONTUACOES //
	fscanf(fp, "%d\n", pontuacao_global_color1);
	fscanf(fp, "%d\n", pontuacao_global_color2);
	//CARREGA VEZ DO JOGADOR
	fscanf(fp, "%d\n", first_player);

	// CLEANUP //
	fclose(fp);

	return;
}

void SalvarJogo(PEC_color jogador_da_vez, int pontuacao_global_branca, int pontuacao_geral_preta){

	FILE *fp;
	printf("Salvando jogo.....");

	fp = fopen("./gamao-save.txt", "w");
	if (fp == NULL){
		perror("Erro ao acessar arquivo de save");
		printf("O jogo nao sera salvo\n");
		return;
	}

	// SALVA PONTUACOES //
	fprintf(fp, "%d %d\n", pontuacao_global_branca, pontuacao_geral_preta);
	// SALVA VEZ (2 = JOGADOR BRANCO, 1 = JOGADOR PRETO)
	fprintf(fp, "%d\n", jogador_da_vez);

	// CLEANUP //
	fclose(fp);

	printf("pronto!\n");

	return;
}

PEC_color TrocarJogador(PEC_color jogador){
	return (jogador == COLOR_Black)? COLOR_White: COLOR_Black;
}

int LerCasaDoTeclado(){
	int ret;
	scanf_s("%d",&ret,sizeof(int));
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

	int idx;
	int response;

	PEC_color color_aux;
	PEC_color jogador_da_vez;
	
	TBL_CondRet tbl_ret;
	DICE_CondRet dice_ret;
	DPT_CondRet dpt_ret;
	PF_CondRet pf_ret;
	
	// Settando a aparencia do cmd //
	system("echo off");	
	system("mode 800");
	system("color 90");


	Menu_Inicial(&response);
	while(response != 1 && response != 2){
		Menu_Inicial(&response);
	}
	if(response == 1){
		NovoJogo(&jogador_da_vez, &pontuacao_global_branca, &pontuacao_global_preta);
	}
	else if(response == 2){
		// RECUPERAR JOGO (CARREGAR) //
		RecuperarJogo(&jogador_da_vez, &pontuacao_global_branca, &pontuacao_global_preta);
	}

	while(1){
		int flag_pode_dobrar = 1;
		int qtd_peca_branca_fin, qtd_peca_preta_fin;
		
		pf_ret= PF_ObterTamanhoPecasFinalizadas(COLOR_White, &qtd_peca_branca_fin);
		if(pf_ret != PF_OK){
			printf("ERRO AO OBTER AS PEÇAS FINALIZADAS\n");
			exit(1);
		}
		pf_ret= PF_ObterTamanhoPecasFinalizadas(COLOR_Black, &qtd_peca_preta_fin);
		if(pf_ret != PF_OK){
			printf("ERRO AO OBTER AS PEÇAS FINALIZADAS\n");
			exit(1);
		}
		if(qtd_peca_branca_fin >= 1){
			int aux;
			dpt_ret = DPT_ObterPontuacaoPartida(&aux);
			if(dpt_ret != DPT_OK){
				printf("ERRO AO ATRIBUIR PONTUAÇÃO AO JOGADOR BRANCO\n");
				exit(1);
			}
			pontuacao_global_branca += aux;
			TearDown();
			SetUp();
		}
		if(qtd_peca_preta_fin >= 15){
			int aux;
			if(dpt_ret != DPT_OK){
				printf("ERRO AO ATRIBUIR PONTUAÇÃO AO JOGADOR PRETO\n");
				exit(1);
			}
			pontuacao_global_branca += aux;
			TearDown();
			SetUp();
		}

		/*********** Rolando  Dados ***************/
		dice_ret = DICE_RolarDado(&dices[0],DADOS_LADOS);
		if(dice_ret == DICE_ok) dice_ret = DICE_RolarDado(&dices[1],DADOS_LADOS);
		if(dice_ret == DICE_wrong){
			printf("ERRO AO ROLAR DADOS\n");
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
			/***** Declaração de variaveis auxiliares *******/
			int flag_peca_finalizada;
			int utilized_dice_idx;
			flag_peca_finalizada = 0;	
			/***********************************************/
	
			/*** Obtendo as casas do jogador da vez ***/
			tbl_ret = TBL_ObterCasasPorDono(jogador_da_vez, casas_from_possiveis, &qtd_casas_from_possiveis);
			if( tbl_ret != TBL_ok ){
				printf(" Erro ao obter as casas do jogador da vez\n");
				exit(1);
			}
			/******************************************/
ESCOLHER_NOVAMENTE:
			/**** Renderizando tabuleiro e jogadas possiveis de mover****/
			RenderizarTabuleiro(pontuacao_global_preta, pontuacao_global_branca);
			RenderizarJogadaAtual(jogador_da_vez, dices, qtd_dice_valid, casas_from_possiveis, qtd_casas_from_possiveis);
			/************************************************************/

			/*********************** Duplicando pontos ***********************/
			dpt_ret = DPT_ObterJogadorDobraPartida(&color_aux);
			if ((dpt_ret == DPT_NaoHaJogadorDadoPontos || color_aux == jogador_da_vez) && flag_pode_dobrar){
				RenderizarMenuDePontos(&response,jogador_da_vez);
				while(response != 1 && response != 2){
					RenderizarMenuDePontos(&response,jogador_da_vez);
				}
				flag_pode_dobrar = 0;
				if(response == 1){
					dpt_ret = DPT_AtualizarJogadorDobra(jogador_da_vez);
					if(dpt_ret != DPT_OK){
						printf("ERRO AO ATUALIZAR O JOGADOR DO DADOPONTOS\n");
						exit(1);
					}
					dpt_ret = DPT_DobrarPontuacaoPartida(jogador_da_vez);
					if(dpt_ret != DPT_OK){
						printf("ERRO AO ATUALIZAR O VALOR DA PARTIDA\n");
						exit(1);
					}
					dpt_ret = DPT_AtualizarJogadorDobra((jogador_da_vez==COLOR_Black)?COLOR_White:COLOR_Black);
					if(dpt_ret != DPT_OK){
						printf("ERRO AO ATUALIZAR O JOGADOR DO DADOPONTOS\n");
						exit(1);
					}
					RenderizarTabuleiro(pontuacao_global_preta, pontuacao_global_branca);
					RenderizarJogadaAtual(jogador_da_vez, dices, qtd_dice_valid, casas_from_possiveis, qtd_casas_from_possiveis);
					flag_pode_dobrar = 0;
				}
			}
			if (dpt_ret == DPT_NaoHaDadoPontos){
				printf("ERRO AO OBTER O DADO PONTOS\n");
				exit(1);
			}
			
			/************************************************************/
		
			/*************** Capturando dados para mover peça ***********/
			printf("Esolha uma casa de origem dentre as disponiveis, -1 para pular a vez e -2 para abrir o Menu: ");
			casa_from = LerCasaDoTeclado();

			/*************** Caso entre no menu *************************/
			if(casa_from == -2) break;
			if(casa_from == -3){
				LimparRender();
				Menu_Sair(&response);
				while(response != 1 && response != 2 && response != 3){
					Menu_Sair(&response);
				}
				if(response == 1) exit(0);
				else if(response == 2){
					
					// SALVA PONTUACAO E VEZ //
					SalvarJogo(jogador_da_vez, pontuacao_global_branca, pontuacao_global_preta);
					exit(0);
				}
				else{
					goto ESCOLHER_NOVAMENTE;
				}
			}
			/************************************************************/

			/************ Checando se a primeira casa é valida **********/
			if( !PrimeiraCasaValida(casa_from,jogador_da_vez) ){
				printf("Casa invalida, escolha novamente: ");
				system("timeout 2");
				goto ESCOLHER_NOVAMENTE;
			}
			/************************************************************/

			printf("Esolha um dado, -1 para escolher a casa novamente: ");

ESCOLHER_DADO_NOVAMENTE:
		/************** Obter o dado a ser utilizado *******************/
			scanf_s("%d", &use_dice_value,sizeof(int));
			use_dice_value = ObterDado(use_dice_value,dices,&utilized_dice_idx);
			if(use_dice_value == -100){
				printf("Escolha um dado válido: ");
				goto ESCOLHER_DADO_NOVAMENTE;
			}
			if(use_dice_value == -1) goto ESCOLHER_NOVAMENTE;
		/**************************************************************/

		/****************Checar finalização de peça********************/
			if(jogador_da_vez == COLOR_White){
				casa_to = casa_from + use_dice_value;
				if(casa_to >= 24){
					flag_peca_finalizada = 1;
					tbl_ret = RetirarPecaDoTabuleiro(&color_aux,casa_from);
					if(tbl_ret != TBL_ok){
						printf("ERRO AO FINALIZAR PECA\n");
						exit(1);
					}
				}
			}
			else {
				casa_to = casa_from - use_dice_value;
				if(casa_to < 0){
					flag_peca_finalizada = 1;
					tbl_ret = RetirarPecaDoTabuleiro(&color_aux,casa_from);
					if(tbl_ret != TBL_ok){
						printf("ERRO AO FINALIZAR PECA\n");
						exit(1);
					}
				}
			}
			if(flag_peca_finalizada){
				pf_ret = PF_AdicionarPecaFinalizada(color_aux);
				if(pf_ret != PF_OK){
					printf("ERRO AO FINALZIAR PECA\n");
					exit(1);
				}
			}
		/**************************************************************/
		/******************* Checando destino *************************/
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
				if(qtd > 1 && !flag_peca_finalizada){
					printf("Casa invalida\n");
					system("timeout 2");
					RestaurarDado(use_dice_value, utilized_dice_idx,dices);
					flag_peca_finalizada = 0;
					goto ESCOLHER_NOVAMENTE;
				}
			}
		/**************************************************************/

		/************************ Movendo peça ************************/
			if(!flag_peca_finalizada){
				TBL_MoverPeca(casa_from, casa_to);
			}
		/**************************************************************/
		}
		/**************** Trocando o jogador da vez *****************/
		jogador_da_vez = TrocarJogador(jogador_da_vez);
		/************************************************************/
	}
	return 0;
}