#pragma once
/***************************************************************************
*
*	$MCD Módulo de definição:	Módulo user_interface
*	
*	Arquivo gerado:			user_interface.h
*	Letras identificadoras:	I
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
*				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*  $HA Histórico de evolução:
*     Versão       Autor          Data         Observações
*       1.00   		rdms   		29/05/2019	 	Inú€io do desenvolvimento
*		2.00		rdms		16/06/2019		Fim do desenvolvimento
*
*	$ED Descrição do módulo:
*		Este módulo implementa e gerencia a interface do jogo de gamão.
*
***************************************************************************/

#include "peca.h"

/***********************************************************************
*
*	$FC Função:	I LimparRender
*
*	Assertiva de saída:
*		A janela será limpa
*
*	$ED Descrição da função:
*		Esta função limpa a tela
*
***********************************************************************/

void I_LimparRender();

/***********************************************************************
*
*	$FC Função:	I Menu_Sair
*
*	Assertiva de Saída
*		Será devolvida para o modulo cliente a resposta do usuario
*
*	$ED Descrição da função:
*		Esta função renderiza o menu de saida
*
*	$EP Parâmetros
*
*		$P	resposta -	Área de retorno da resposta.
*
***********************************************************************/

void I_Menu_Sair(int *resposta);

/***********************************************************************
*
*	$FC Função:	I Menu_Sair
*
*	Assertiva de Saída
*		Será devolvida para o modulo cliente a resposta do usuario
*
*	$ED Descrição da função:
*		Esta função renderiza o menu de inicial
*
*	$EP Parâmetros
*
*		$P	resposta -	Área de retorno da resposta.
*
***********************************************************************/

void I_Menu_Inicial(int* resposta);

/***********************************************************************
*
*	$FC Função:	I RenderizarMenuDePontos
*
*	Assertiva de Saída
*		Será devolvida para o modulo cliente a resposta do usuario
*
*	$ED Descrição da função:
*		Esta função renderiza o menu de dobrar pontos
*
*	$EP Parâmetros
*
*		$P	resposta		-	Área de retorno da resposta.
*		$P	jogador_da_vez	-	Cor do jogador da vez
*
***********************************************************************/

void I_RenderizarMenuDePontos(int *response, PEC_color jogador_da_vez);


/***********************************************************************
*
*	$FC Função:	I RenderizarJogadaAtual
*
*	Assertiva de Saída
*		Será mostrado os status da jogada atual
*
*	$EP Parâmetros
*
*		$P	jogador_da_vez	-	Cor do jogador da vez
*		$P	dices			-	Vetor de dados de tamanho 4, dados invalidados são marcados como 0
*		$P	qtd_dice_valid	-	Quantidade de daods ainda validos
*		$P	vector			-	Vetor de casas parcialmente cheio, tamanho 24
*		$P	qtd_casas		-	Numero de casas validas
*
***********************************************************************/

void I_RenderizarJogadaAtual(PEC_color jogadorAtual, int dices[4], int qtd_dice_valid, int vector[24], int qtd_casas);

/***********************************************************************
*
*	$FC Função:	I RenderizarTabuleiro
*
*	Assertiva de Saída
*		Será mostrado o tabuleiro e a barra do meio
*
*	$EP Parâmetros
*
*		$P	pontuacao_preta		-	Pontuação do jogador preto
*		$P	pontuacao_branca	-	Pontuação do jogador branco
*		$P	pecas_brancas_fin	-	Quantidade de peças brancas finalizadas
*		$P	pecas_brancas_cap	-	Quantidade de peças brancas capturadas
*		$P	pecas_pretas_fin	-	Quantidade de peças pretas finalizadas
*		$P	pecas_pretas_cap	-	Quantidade de peças pretas capturadas
*
***********************************************************************/

void I_RenderizarTabuleiro(int pontuacao_preta, int pontuacao_branca, int pecas_brancas_fin, int pecas_brancas_cap, int pecas_pretas_fin, int pecas_pretas_cap, int pontuacao);