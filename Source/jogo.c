#define DADOS_LADOS 6

#include <stdio.h>
#include <Windows.h>

#include "interfaces\dado.h"
#include "interfaces\peca.h"
#include "interfaces\DADOPONTOS.H"
#include "interfaces\tabuleiro.h"
#include "interfaces\user_interface.h"
#include "interfaces\PecasFinalizadas.h"
#include "interfaces\PECASCAPTURADAS.H"


static void Throw(char* str){
	printf("%s\n",str);
	system("timout 10");
	exit(1);
}

static void SetUp(){
	DPT_CondRet dpt_ret = DPT_NaoHaDadoPontos;
	TBL_CondRet tbl_ret = TBL_erro;
	PF_CondRet pf_ret = PF_Erro;
	PCAP_CondRet pcap_ret = PCAP_CondRetErroNaoExisteSingleton;

	// Criação do dadoPontos //
	dpt_ret = DPT_CriarDadoPontos();
	if(dpt_ret != DPT_OK){
		Throw("ERRO AO CRIAR O DADO PONTOS");
	}
	// Criação do tabuleiro //
	tbl_ret = TBL_CriarTabuleiro();
	if(tbl_ret != TBL_ok){
		Throw("ERRO AO CRIAR O TABULEIRO");
	}

	pf_ret = PF_CriarPecasFinalizadas();
	if (pf_ret != PF_OK){
		Throw("ERRO AO INICIALIZAR PEÇAS FINALIZADAS");
	}
	pcap_ret = PCAP_CriarListasPecasCapturadas();
	if(pcap_ret != PCAP_CondRetOK){
		Throw("ERRO AO INICIALIZAR PEÇAS CAPTURADAS");
	}
}

static void TearDown(){
	DPT_CondRet dpt_ret;
	TBL_CondRet tbl_ret;
	PF_CondRet pf_ret;
	PCAP_CondRet pcap_ret;

	dpt_ret = DPT_DestruirDadoPontos();
	if(dpt_ret != DPT_OK){
		Throw("");
	}
	tbl_ret = TBL_DestruirTabuleiro();
	if(tbl_ret != TBL_ok){
		Throw("");
	}
	pf_ret = PF_DestruirPecasFinalizadas();
	if(pf_ret != PF_OK){
		Throw("");
	}
	pcap_ret = PCAP_DestruirPecasCapturadas();
	if(pcap_ret != PCAP_CondRetOK){
		Throw("");
	}
}

static PEC_color TrocarJogador(PEC_color jogador){
	return (jogador == COLOR_Black)? COLOR_White: COLOR_Black;
}

static int CheckFinalizacaoPossivel(PEC_color jogador, int casas[24], int qtd_casas){
	int idx;
	if(jogador == COLOR_White){
		for(idx = 0; idx < qtd_casas; idx++){
			if( casas[idx] < 19 ){
				return 0;
			}
		}
		return 1;
	}
	else if(jogador == COLOR_Black){
		for(idx = 0; idx < qtd_casas; idx++){
			if( casas[idx] > 6 ){
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

static void FinalizarPartida(int* pt_w){
	int aux;
	DPT_CondRet dpt_ret = DPT_ObterPontuacaoPartida(&aux);
	if (dpt_ret != DPT_OK){
		Throw("ERRO NA FINALIZACAO DA PARTIDA");
	}
	*pt_w += aux;
	TearDown();
	SetUp();
}

void NovoJogo (PEC_color* first_player, int* pontuacao_global_color1, int* pontuacao_global_color2){
	// Inicialização de variaveis //
	int dice[2];
	DICE_CondRet d_ret;
	/******************************/

	SetUp();

	// Settando variaveis globais do jogo //
	*pontuacao_global_color1 = *pontuacao_global_color2 = 0;

/* DEFINIÇÃO DO PRIMEIRO JOGADOR */
	do{
		d_ret = DICE_RolarDado(&dice[0],DADOS_LADOS);
		if( d_ret == DICE_ok){
			d_ret = DICE_RolarDado(&dice[1],DADOS_LADOS);
		}
		if(d_ret != DICE_ok){
			Throw("ERRO AO DEFINIR O PRIMEIRO JOGADOR");
		}
		printf("Definindo o primeiro jogador\n");
		printf("Branco: %d\n",dice[0]);
		printf("Preto: %d\n",dice[1]);
		if(dice[0] == dice[1]){
			printf("Dados iguais, jogando novamente para definir o primeiro a jogar\n");
			system("timeout 3");
		}
	}while(dice[0] == dice[1]);
	system("timeout 2");
/********************************/
	*first_player = (dice[0]>dice[1])? COLOR_White: COLOR_Black;
}

int RecuperarJogo(PEC_color *first_player, int *pontuacao_global_color1, int *pontuacao_global_color2){

	// Inicializacao de variaveis //
	DPT_CondRet dpt_ret;

	FILE *fp;
	errno_t erro;

	PEC_color jogador_pode_dobrar;
	int pontuacao_dados_pontos;
	/******************************/

	SetUp();
	
	// RECUPERACAO DAS PONTUACOES GLOBAIS E VEZ DO JOGADOR //
	printf("Recuperando dados.....\n");

	erro = fopen_s(&fp, "gamao-save.txt", "r");
	// EXIT SE FALHAR //
	if (erro != 0){
		perror("Erro ao acessar arquivo de save");
		system("timeout 5");
		I_LimparRender();
		return 0;
	}

	// CARREGA PONTUACOES //
	fscanf_s(fp, "%d\n", pontuacao_global_color1, sizeof(pontuacao_global_color1));
	fscanf_s(fp, "%d\n", pontuacao_global_color2), sizeof(pontuacao_global_color2);
	//**********************//
	
	//CARREGA VEZ DO JOGADOR
	fscanf_s(fp, "%d\n", first_player, sizeof(first_player));
	//**********************//
	
	// CARREGA DADO PONTOS //
	fscanf_s(fp, "%d", &jogador_pode_dobrar, sizeof(jogador_pode_dobrar)); //jogador dado pontos
	fscanf_s(fp, "%d", &pontuacao_dados_pontos, sizeof(pontuacao_dados_pontos));
	
	// RECUPERA DADO PONTOS
	if(jogador_pode_dobrar != COLOR_Colorless){ // se ha jogador dados pontos
		dpt_ret = DPT_AtualizarJogadorDobra(jogador_pode_dobrar);
		if(dpt_ret != DPT_OK){
			printf("Erro ao atualizar o jogador do dado pontos\n");
			Throw("O jogo nao pode ser recuperado.");
		}
		dpt_ret = DPT_AtualizarPontuacaoPartida(pontuacao_dados_pontos);
	}

	// CLEANUP //
	fclose(fp);
	return 1;
}

void SalvarJogo(PEC_color jogador_da_vez, int pontuacao_global_branca, int pontuacao_geral_preta, PEC_color jogador_dobra_partida, int pontuacao_dados_pontos){

	FILE *fp;
	errno_t erro;
	printf("Salvando jogo.....");

	erro = fopen_s(&fp, "./gamao-save.txt", "w");
	if (erro != 0){
		perror("Erro ao acessar arquivo de save");
		printf("O jogo nao sera salvo\n");
		return;
	}

	// SALVA PONTUACOES //
	fprintf(fp, "%d %d\n", pontuacao_global_branca, pontuacao_geral_preta);
	// SALVA VEZ (2 = JOGADOR BRANCO, 1 = JOGADOR PRETO)
	fprintf(fp, "%d\n", jogador_da_vez);
	// SALVA JOGADOR QUE PDOE DOBRAR A PARTIDA //
	fprintf(fp, "%d\n", jogador_dobra_partida);
	// SALVA PONTUACAO DA PARTIDA (DADOS PONTOS) //
	fprintf(fp, "%d\n", pontuacao_dados_pontos);

	// CLEANUP //
	fclose(fp);

	printf("pronto!\n");

	return;
}

int LerCasaDoTeclado(){
	int ret;
	scanf_s("%d",&ret,sizeof(int));
	return ret-1;
}

int PrimeiraCasaValida(int casa_from, PEC_color jogador_da_vez){
	PEC_color aux;
	TBL_CondRet tbl_ret = TBL_CorPecasCasa(&aux,casa_from);
	if( casa_from >24 || casa_from < 0) return 0;
	if( tbl_ret != TBL_ok ) return 0;
	if( jogador_da_vez != aux ) return 0;
	if( casa_from < 0 ) return 0;
	return 1;
}

int CasaParaRestaurarValida(int casa_from, PEC_color jogador_da_vez){
	PEC_color aux;
	TBL_CondRet tbl_ret = TBL_CorPecasCasa(&aux,casa_from);
	if( tbl_ret != TBL_ok ) return 0;
	if( aux == COLOR_Colorless) return 1;
	if( jogador_da_vez != aux ) return 0;
	if( casa_from < 0 ) return 0;
	return 1;
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


static void RenderizarTudo(int pt_b, int pt_p, PEC_color jogadorAtual, int dices[4], int qtd_dice_valid, int vector[24], int qtd_casas){
	PCAP_CondRet pcap_ret;
	DPT_CondRet dpt_ret;
	PF_CondRet pf_ret;
	
	int pfin_b, pfin_p, pcap_b, pcap_p, dpt;

	pcap_ret = PCAP_ObterQuantidadePecasCapturadas(COLOR_White,&pcap_b);
	pcap_ret = PCAP_ObterQuantidadePecasCapturadas(COLOR_Black,&pcap_p);

	pf_ret = PF_ObterTamanhoPecasFinalizadas(COLOR_White, &pfin_b);
	pf_ret = PF_ObterTamanhoPecasFinalizadas(COLOR_Black, &pfin_p);

	dpt_ret = DPT_ObterPontuacaoPartida(&dpt);

	I_RenderizarTabuleiro(pt_p, pt_b,pfin_b,pcap_b,pfin_p,pcap_p,dpt);
	I_RenderizarJogadaAtual(jogadorAtual, dices, qtd_dice_valid, vector, qtd_casas);

}



int main (void){	
	int dices[4];
	int qtd_dice_valid;

	int pontuacao_global_branca, pontuacao_global_preta;
	int pontuacao_dados_pontos;
	
	int casa_from, casa_to;
	int use_dice_value=0;
	int qtd_casas_from_possiveis;
	int casas_from_possiveis[24];

	int idx;
	int response;

	PEC_color jogador_da_vez;
	PEC_color color_aux;
	
	DICE_CondRet dice_ret;
	PCAP_CondRet pcap_ret;
	TBL_CondRet tbl_ret;
	DPT_CondRet dpt_ret;
	PF_CondRet pf_ret;
	
	// Settando a aparencia do cmd //
	system("echo off");	
	system("mode 800");

	do{
		I_Menu_Inicial(&response);
		if(response == 1){
			NovoJogo(&jogador_da_vez, &pontuacao_global_branca, &pontuacao_global_preta);
		}
		else if(response == 2){
			// RECUPERAR JOGO (CARREGAR) //
			int r = RecuperarJogo(&jogador_da_vez, &pontuacao_global_branca, &pontuacao_global_preta);
			if ( !r ){
				response = -1;
			}
		}
		else if(response == 3){
			exit(3);
		}
	}while(response != 1 && response != 2 && response != 3);

	while(1){
	
		int flag_pode_dobrar = 1;
		int qtd_peca_branca_fin, qtd_peca_preta_fin;		
		int flag_peca_finalizada = 0 , flag_restaurar_peca = 0 ;
		int utilized_dice_idx = 0;
		int qtd_cap =0 ;

		pf_ret= PF_ObterTamanhoPecasFinalizadas(COLOR_White, &qtd_peca_branca_fin);
		if(pf_ret != PF_OK){
			Throw("ERRO AO OBTER AS PEÇAS FINALIZADAS");
		}
		pf_ret= PF_ObterTamanhoPecasFinalizadas(COLOR_Black, &qtd_peca_preta_fin);
		if(pf_ret != PF_OK){
			Throw("ERRO AO OBTER AS PEÇAS FINALIZADAS");
		}
		if(qtd_peca_branca_fin >= 15){
			FinalizarPartida(&pontuacao_global_branca);
		}
		if(qtd_peca_preta_fin >= 15){
			FinalizarPartida(&pontuacao_global_preta);
		}

		/*********** Rolando  Dados ***************/
		dice_ret = DICE_RolarDado(&dices[0],DADOS_LADOS);
		if(dice_ret == DICE_ok) dice_ret = DICE_RolarDado(&dices[1],DADOS_LADOS);
		if(dice_ret == DICE_wrong){
			Throw("ERRO AO ROLAR DADOS");
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
			flag_peca_finalizada = flag_restaurar_peca = 0, response = 0;	

			/***********************************************/
			/*** Obtendo as casas do jogador da vez ***/
			tbl_ret = TBL_ObterCasasPorDono(jogador_da_vez, casas_from_possiveis, &qtd_casas_from_possiveis);
			if( tbl_ret != TBL_ok ){
				Throw("Erro ao obter as casas do jogador da vez");
			}
			/******************************************/
			pcap_ret = PCAP_ObterQuantidadePecasCapturadas(jogador_da_vez,&qtd_cap);
			if(pcap_ret != PCAP_CondRetOK){
				Throw("ERRO AO OBTER AS PECAS FINALIZADAS DO JOGADOR DA VEZ");
			}
			
			if(qtd_cap > 0){
				flag_restaurar_peca = 1;
			}

ESCOLHER_NOVAMENTE:
			/**** Renderizando tabuleiro e jogadas possiveis de mover****/
			RenderizarTudo(pontuacao_global_preta, pontuacao_global_branca,jogador_da_vez, dices, qtd_dice_valid, casas_from_possiveis, qtd_casas_from_possiveis);
			/************************************************************/

			/*********************** Duplicando pontos ***********************/
			dpt_ret = DPT_ObterJogadorDobraPartida(&color_aux);
			if ((dpt_ret == DPT_NaoHaJogadorDadoPontos || color_aux == jogador_da_vez) && flag_pode_dobrar){

				do{ 
					I_RenderizarMenuDePontos(&response,jogador_da_vez);
				}while(response != -1 && response != 1 && response != 2);

				flag_pode_dobrar = 0;
				if(response == 1){
					dpt_ret = DPT_AtualizarJogadorDobra(jogador_da_vez);
					if(dpt_ret != DPT_OK){
						Throw("ERRO AO ATUALIZAR O JOGADOR DO DADOPONTOS");
					}
					dpt_ret = DPT_DobrarPontuacaoPartida(jogador_da_vez);
					if(dpt_ret != DPT_OK){
						Throw("ERRO AO ATUALIZAR O VALOR DA PARTIDA");
					}
					dpt_ret = DPT_AtualizarJogadorDobra(TrocarJogador(jogador_da_vez));
					if(dpt_ret != DPT_OK){
						Throw("ERRO AO ATUALIZAR O JOGADOR DO DADOPONTOS");
					}
					RenderizarTudo(pontuacao_global_preta, pontuacao_global_branca,jogador_da_vez, dices, qtd_dice_valid, casas_from_possiveis, qtd_casas_from_possiveis);
					flag_pode_dobrar = 0;
				}
				else if(response == 2){
					if(jogador_da_vez == COLOR_White){
						FinalizarPartida(&pontuacao_global_branca);
						break;
					}
					else if(jogador_da_vez == COLOR_Black){
						FinalizarPartida(&pontuacao_global_preta);
						break;
					}
				}
			}
			if (dpt_ret == DPT_NaoHaDadoPontos){
				Throw("ERRO AO OBTER O DADO PONTOS");
			}
			
			/************************************************************/
			/*************** Capturando dados para mover peça ***********/
			if( !flag_restaurar_peca ){
				printf("Escolha uma casa de origem dentre as disponiveis, -1 para pular a vez e -2 para abrir o Menu: ");
				casa_from = LerCasaDoTeclado();
			}
			else{
				do{
					printf("Voce deve restaurar uma peca, 0 para continuar -1 para pular a vez e -2 para abrir o Menu: ");
					casa_from = LerCasaDoTeclado();
				} while( casa_from != -3 && casa_from != -2 && casa_from != -1 );
			}
			/************************************************************/
			/*************** Caso entre no menu *************************/
			if(casa_from == -2) break;
			if(casa_from == -3){
				I_LimparRender();
				do{
					I_Menu_Sair(&response);
				}while(response != 1 && response != 2 && response != 3);

				if(response == 1) exit(0);
				else if(response == 2){
					//************** SALVAR JOGO **************//
					// OBTEM DADO PONTO //
					if( DPT_ObterJogadorDobraPartida(&color_aux) == DPT_NaoHaJogadorDadoPontos){
						color_aux = COLOR_Colorless;
					}
					dpt_ret = DPT_ObterPontuacaoPartida(&pontuacao_dados_pontos);

					// SALVA //
					SalvarJogo(jogador_da_vez, pontuacao_global_branca, pontuacao_global_preta, color_aux, pontuacao_dados_pontos);

					exit(0);
					//*****************************************//
				}
				else{
					goto ESCOLHER_NOVAMENTE;
				}
			}
			/************************************************************/
			/************ Checando se a primeira casa é valida **********/
			if( !PrimeiraCasaValida(casa_from,jogador_da_vez) && !flag_restaurar_peca ){
				printf("Casa invalida, escolha novamente: ");
				system("timeout 2");
				goto ESCOLHER_NOVAMENTE;
			}
			/************************************************************/

			printf("Escolha um dado, -1 para escolher a casa novamente: ");

		/************** Obter o dado a ser utilizado *******************/
			do{
				scanf_s("%d", &use_dice_value,sizeof(int));
				use_dice_value = ObterDado(use_dice_value,dices,&utilized_dice_idx);
				
				if(use_dice_value == -100){
					printf("Escolha um dado válido: ");
				}
			}while(use_dice_value == -100);

			if(use_dice_value == -1) goto ESCOLHER_NOVAMENTE;
			if(flag_restaurar_peca){
				if(jogador_da_vez == COLOR_White){
					casa_to = use_dice_value-1;
				}
				else if(jogador_da_vez == COLOR_Black){
					casa_to = 24 - use_dice_value;
				}
			}
		/**************************************************************/
		/****************Checar finalização de peça********************/
			else{
				int fin_possivel = CheckFinalizacaoPossivel(jogador_da_vez,casas_from_possiveis,qtd_casas_from_possiveis);

				if(jogador_da_vez == COLOR_White){
					casa_to = casa_from + use_dice_value;
					if(casa_to > 23 ){
						if(fin_possivel){
							flag_peca_finalizada = 1;
							tbl_ret = RetirarPecaDoTabuleiro(&color_aux,casa_from);
							if(tbl_ret != TBL_ok){
								Throw("ERRO AO FINALIZAR PECA");
							}
						}
						else{
							printf("Impossivel finalizar peca\n");
							system("timeout 2");
							RestaurarDado(use_dice_value, utilized_dice_idx,dices);
							flag_peca_finalizada = 0;
							goto ESCOLHER_NOVAMENTE;
						}
					}
				}
				else {
					casa_to = casa_from - use_dice_value;
					if(casa_to < 0){
						if(fin_possivel){
							flag_peca_finalizada = 1;
							tbl_ret = RetirarPecaDoTabuleiro(&color_aux,casa_from);
							if(tbl_ret != TBL_ok){
								Throw("ERRO AO FINALIZAR PECA");
							}
						}
						else{
							printf("Impossivel finalizar peca\n");
							system("timeout 2");
							RestaurarDado(use_dice_value, utilized_dice_idx,dices);
							flag_peca_finalizada = 0;
							goto ESCOLHER_NOVAMENTE;
						}
					}
				}
			}
			
			if(flag_peca_finalizada){
				pf_ret = PF_AdicionarPecaFinalizada(color_aux);
				if(pf_ret != PF_OK){
					Throw("ERRO AO FINALIZAR PECA");
				}
			}
		/**************************************************************/
		/******************* Checando destino *************************/

			tbl_ret = TBL_CorPecasCasa(&color_aux,casa_to);
			if(tbl_ret != TBL_ok){
				Throw("Erro ao obter a casa para onde mover");
			}
			if(color_aux == TrocarJogador(jogador_da_vez)){
				int qtd;
				tbl_ret = TBL_QuantidadePecasCasa(&qtd, casa_to);
				if(tbl_ret != TBL_ok){
					Throw("Erro ao obter a casa para onde mover");
				}
				if(qtd == 1 && !flag_peca_finalizada){
					tbl_ret = RetirarPecaDoTabuleiro(&color_aux,casa_to);
					if(tbl_ret != TBL_ok){
						Throw("ERRO AO COMER PECA");
					}
					pcap_ret = PCAP_InserirPecaCapturada(color_aux);
					if(pcap_ret != PCAP_CondRetOK){
						Throw("ERRO AO COMER PECA");
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
			if(!flag_peca_finalizada && !flag_restaurar_peca){
				tbl_ret = TBL_MoverPeca(casa_from, casa_to);
				if(tbl_ret != TBL_ok){
					Throw("ERRO AO MOVER A PECA");
				}
			}

			if(flag_restaurar_peca){
				pcap_ret= PCAP_RemoverPecaCapturada(jogador_da_vez);
				if(pcap_ret != PCAP_CondRetOK){
					Throw("ERRO AO REMOVER PECA DE PECAS CAPTURADAS");
				}
				tbl_ret = TBL_InserirPecaNoTabuleiro(jogador_da_vez,casa_to);
				if(tbl_ret != TBL_ok){
					Throw("ERRO AO RESTAURAR PECA");
				}
				flag_restaurar_peca = 0;
			}
		}
		/*************************************************************/
		/***************** Trocando o jogador da vez *****************/
		jogador_da_vez = TrocarJogador(jogador_da_vez);
		/*************************************************************/
	}
	return 0;
}