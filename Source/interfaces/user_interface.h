#pragma once
/***************************************************************************
*
*	$MCD M�dulo de defini��o:	M�dulo user_interface
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
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   		rdms   		29/05/2019	 	In��io do desenvolvimento
*		2.00		rdms		16/06/2019		Fim do desenvolvimento
*
*	$ED Descri��o do m�dulo:
*		Este m�dulo implementa e gerencia a interface do jogo de gam�o.
*
***************************************************************************/

#include "peca.h"

/***********************************************************************
*
*	$FC Fun��o:	I LimparRender
*
*	Assertiva de sa�da:
*		A janela ser� limpa
*
*	$ED Descri��o da fun��o:
*		Esta fun��o limpa a tela
*
***********************************************************************/

void I_LimparRender();

/***********************************************************************
*
*	$FC Fun��o:	I Menu_Sair
*
*	Assertiva de Sa�da
*		Ser� devolvida para o modulo cliente a resposta do usuario
*
*	$ED Descri��o da fun��o:
*		Esta fun��o renderiza o menu de saida
*
*	$EP Par�metros
*
*		$P	resposta -	�rea de retorno da resposta.
*
***********************************************************************/

void I_Menu_Sair(int *resposta);

/***********************************************************************
*
*	$FC Fun��o:	I Menu_Sair
*
*	Assertiva de Sa�da
*		Ser� devolvida para o modulo cliente a resposta do usuario
*
*	$ED Descri��o da fun��o:
*		Esta fun��o renderiza o menu de inicial
*
*	$EP Par�metros
*
*		$P	resposta -	�rea de retorno da resposta.
*
***********************************************************************/

void I_Menu_Inicial(int* resposta);

/***********************************************************************
*
*	$FC Fun��o:	I RenderizarMenuDePontos
*
*	Assertiva de Sa�da
*		Ser� devolvida para o modulo cliente a resposta do usuario
*
*	$ED Descri��o da fun��o:
*		Esta fun��o renderiza o menu de dobrar pontos
*
*	$EP Par�metros
*
*		$P	resposta		-	�rea de retorno da resposta.
*		$P	jogador_da_vez	-	Cor do jogador da vez
*
***********************************************************************/

void I_RenderizarMenuDePontos(int *response, PEC_color jogador_da_vez);


/***********************************************************************
*
*	$FC Fun��o:	I RenderizarJogadaAtual
*
*	Assertiva de Sa�da
*		Ser� mostrado os status da jogada atual
*
*	$EP Par�metros
*
*		$P	jogador_da_vez	-	Cor do jogador da vez
*		$P	dices			-	Vetor de dados de tamanho 4, dados invalidados s�o marcados como 0
*		$P	qtd_dice_valid	-	Quantidade de daods ainda validos
*		$P	vector			-	Vetor de casas parcialmente cheio, tamanho 24
*		$P	qtd_casas		-	Numero de casas validas
*
***********************************************************************/

void I_RenderizarJogadaAtual(PEC_color jogadorAtual, int dices[4], int qtd_dice_valid, int vector[24], int qtd_casas);

/***********************************************************************
*
*	$FC Fun��o:	I RenderizarTabuleiro
*
*	Assertiva de Sa�da
*		Ser� mostrado o tabuleiro e a barra do meio
*
*	$EP Par�metros
*
*		$P	pontuacao_preta		-	Pontua��o do jogador preto
*		$P	pontuacao_branca	-	Pontua��o do jogador branco
*		$P	pecas_brancas_fin	-	Quantidade de pe�as brancas finalizadas
*		$P	pecas_brancas_cap	-	Quantidade de pe�as brancas capturadas
*		$P	pecas_pretas_fin	-	Quantidade de pe�as pretas finalizadas
*		$P	pecas_pretas_cap	-	Quantidade de pe�as pretas capturadas
*
***********************************************************************/

void I_RenderizarTabuleiro(int pontuacao_preta, int pontuacao_branca, int pecas_brancas_fin, int pecas_brancas_cap, int pecas_pretas_fin, int pecas_pretas_cap, int pontuacao);