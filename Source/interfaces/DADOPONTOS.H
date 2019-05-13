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
*	Assertivas de Entrada:
*		Deve existir um ponteiro para qual  o dado de pontos  criado será retornada por
*		referência.
*	Assertivas de Saída:
*		- Dado de pontos foi criado e pDadosPontos foi atualizado.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para o dado de pontos a ser criado. Passado por referência.
*
*  $FV Valor retornado
*     DPT_OK
*     DPT_FalhaMemoria
*
***********************************************************************/

   DPT_CondRet DPT_CriarDadoPontos(DPT_DadoHead* pDadoPontos);

/***********************************************************************
*
*  $FC Função: DPT Atualizar jogador que pode dobrar a partida
*
*	Assertivas de Entrada:
*		- Deve existir uma cor associada ao jogador que está dobrando a pontuação.
*	Assertivas de Saída:
*		- O jogador que pode dobrar a partida é atualizado através da cor da peça;
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

   DPT_CondRet DPT_AtualizarJogadorDobra(DPT_DadoHead pDadoPontos, PEC_color CorPeca);

/***********************************************************************
*
*  $FC Função: DPT Dobrar pontuação da partida
*	Assertivas de Entrada:
*		- Deve existir ponteiro para o dado de pontos que será utilizado;
*		- Deve existir uma cor de peça associada ao jogador que está dobrando a pontuação.
*	Assertivas de Saída:
*		- Se dado pontos não existir ou cor da peça não for igual a cor autorizada a dobrar a pontuação o ponteiro pDadosPontos não é atualizado;
*		- Caso contrário, a pontuação é dobrada e o ponteiro é atualizado.
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

   DPT_CondRet DPT_DobrarPontuacaoPartida(DPT_DadoHead pDadoPontos, PEC_color CorPeca);

/***********************************************************************
*
*  $FC Função: DPT Obter jogador que pode dobrar partida
*	Assertivas de Entrada:
*		-Deve existir uma área de memória do tipo PEC_Color para qual será retornado o tipo da cor.
*	Assertivas de Saída:
*		-Se dado pontos não existir ou não tiver possuídor no momento, o ponteiro não será atualizado.
*	-Caso contrário, o ponteiro é atualizado com a cor correta.
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

   DPT_CondRet DPT_ObterJogadorDobraPartida(DPT_DadoHead pDadoPontos, PEC_color *pCorPeca);

/***********************************************************************
*
*  $FC Função: DPT Obter pontuação da partida
*
*	Assertivas de Entrada:
*		- Deve existir uma área de memória do tipo int para qual será retornada a pontuação.
*	Assertivas de Saída:
*		- Se dado de pontos existir, a pontuação será obtida e o conteúdo do ponteiro pPontuacao será atualizado.
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

   DPT_CondRet DPT_ObterPontuacaoPartida(DPT_DadoHead pDadoPontos, int *pPontuacao);

/***********************************************************************
*
*  $FC Função: DPT Destruir dado de pontos
*
*	Assertivas de Entrada:
*		O espaço de dados passado deve possuir um dadopontos alocado.
*	Assertivas de Saída:
*		- após a destruição do dadopontos,o ponteiro passado terá o valor  de NULL.
*
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

   DPT_CondRet DPT_DestruirDadoPontos(DPT_DadoHead* pDadoPontos);

#undef DADOPONTOS_EXT

/********** Fim do módulo de definição: Módulo dado de pontos **********/

#else
#endif
