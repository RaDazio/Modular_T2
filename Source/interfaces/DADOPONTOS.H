#if ! defined(DADOPONTOS_)
#define DADOPONTOS_

#include "peca.h"
/********************************************************************************************
*	$MCI Módulo de definição:	 Módulo dado pontos
*	Arquivo gerado:			DADOPONTOS.C
*	Letras identificadoras:	DPT
*
*	Projeto:	Disciplinas INF 1628 / 1301
*	Gestor:		DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*	$HA Histórico e evolução:
*		Versão  Autor	Data		Observações
*		1.00	fo	27/04/2019	Inicio do desenvolvimento

*   $ED Descrição do módulo:
		Este módulo implementa funções para operar um dado de pontos de um jogo.
*
*******************************************************************************************/

#if defined(DADOPONTOS_OWN)
   #define DADOPONTOS_EXT
#else
   #define DADOPONTOS_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um dado de pontos*/

typedef struct dadopontos DPT_DadoPontos;

/***********************************************************************
/***********************************************************************
*
*  $TC Tipo de dados: DPT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {
   	     DPT_FalhaMemoria = -1,
          /* Faltou memória ao alocar dados */

         DPT_OK = 0,
               /* Executou correto */

		 DPT_NaoHaDadoPontos = 1,
			   /* Dado de pontos não existe */

		 DPT_JogadorNaoPossuiDadoPontos = 2,
			   /* Jogador não possui dado de pontos no momento */

		 DPT_NaoHaJogadorDadoPontos = 3 ,
			   /* Não há jogador atual do dado de pontos */

 } DPT_CondRet;

/***********************************************************************
*
*  $FC Função: DPT Criar dado de pontos
*
*  $ED Descrição da função
*     Cria um novo dado de pontos.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser criado. Passado por referência.
*
*  $FV Valor retornado
*     DPT_OK
*     DPT_FalhaMemoria
*
***********************************************************************/

   DPT_CondRet DPT_CriarDadoPontos(DPT_DadoPontos **pDadoPontos);

/***********************************************************************
*
*  $FC Função: DPT Atualizar jogador que pode dobrar a partida
*
*  $ED Descrição da função
*     Atualiza o jogador que pode dobrar a partida.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser utilizado.
*     $P CorPeca - cor do jogador.
*
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_AtualizarJogadorDobra(DPT_DadoPontos *pDadoPontos, PEC_color CorPeca);

/***********************************************************************
*
*  $FC Função: DPT Dobrar pontuação da partida
*
*  $ED Descrição da função
*     Dobra a pontuação da partida.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser utilizado.
*     $P CorPeca - cor do jogador.
*
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*	  DPT_JogadorNaoPossuiDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_DobrarPontuacaoPartida(DPT_DadoPontos *pDadoPontos, PEC_color CorPeca);

/***********************************************************************
*
*  $FC Função: DPT Obter jogador que pode dobrar partida
*
*  $ED Descrição da função
*     Obtém o jogador que pode dobrar a partida.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser utilizado.
*     $P pCorPeca - ponteiro que receberá, por referência, a cor da peça do jogador.
*
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*	  DPT_NaoHaJogadorDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_ObterJogadorDobraPartida(DPT_DadoPontos *pDadoPontos, PEC_color *pCorPeca);

/***********************************************************************
*
*  $FC Função: DPT Obter pontuação da partida
*
*  $ED Descrição da função
*     Obtém a pontuação da partida.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser utilizado.
*     $P pPontuacao - ponteiro que receberá, por referência, a pontuação da partida.
*
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_ObterPontuacaoPartida(DPT_DadoPontos *pDadoPontos, int *pPontuacao);

/***********************************************************************
*
*  $FC Função: DPT Destruir dado de pontos
*
*  $ED Descrição da função
*     Destrói a peça.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser destruído. Passado por referência.
*
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_DestruirDadoPontos(DPT_DadoPontos **pDadoPontos);

#undef DADOPONTOS_EXT

/********** Fim do módulo de definição: Módulo dado de pontos **********/

#else
#endif
