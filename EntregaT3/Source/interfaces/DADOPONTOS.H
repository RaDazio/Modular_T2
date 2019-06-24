#if ! defined(DADOPONTOS_)
#define DADOPONTOS_

#include "PECA.h"
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

	     DPT_JaExisteDadoPontos

 } DPT_CondRet;

/***********************************************************************
*
*  $FC Função: DPT Criar dado de pontos
*
*  $ED Descrição da função
*     Cria um novo dado de pontos.
*
*  $EP Parâmetros
*     
*
*  $FV Valor retornado
*     DPT_OK
*     DPT_FalhaMemoria
*  Assertiva de saída: Será criado um dado de pontos
*
*
***********************************************************************/

   DPT_CondRet DPT_CriarDadoPontos();

/***********************************************************************
*
*  $FC Função: DPT Atualizar jogador que pode dobrar a partida
*
*  $ED Descrição da função
*     Atualiza o jogador que pode dobrar a partida.
*
*  $EP Parâmetros.
*     $P CorPeca - cor do jogador.
*  Assertiva de Entrada: Será passado como parâmetro uma variável do tipo PEC_color
*  Assertiva de Saída  : Caso exista dadoPontos, ele será atualizado com a cor passada.
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_AtualizarJogadorDobra(PEC_color CorPeca);


/***********************************************************************
*
*  $FC Função: DPT Atualizar pontuacao da partida
*
*  $ED Descrição da função
*     Atualiza a pontuacao da partida a partir de um inteiro
*
*  $EP Parâmetros
*     $P Pontuacao - inteiro com a pontuacao que deseja-se inserir no Dado Pontos
* Assertiva de Entrada: Será passada um variável do tipo Inteiro que será o novo valor da pontuação de dadopontos.
* Assertiva de Saída  : Caso exista dado de pontos, o valor será atualizado com o valor passado como parâmetro
*  $FV Valor retornado
*     DPT_OK
*    DPT_NaoHaDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_AtualizarPontuacaoPartida(int Pontuacao);

/***********************************************************************
*
*  $FC Função: DPT Dobrar pontuação da partida
*
*  $ED Descrição da função
*     Dobra a pontuação da partida.
*
*  $EP Parâmetros
*     $P CorPeca - cor do jogador.
*  AE: Será passado como parâmetro uma variável do tipo PEC_Color
*  AS: Caso o jogador passado possua o dado de pontos,será dobrado o valor da partida,caso exsita dado de pontos
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*	  DPT_JogadorNaoPossuiDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_DobrarPontuacaoPartida(PEC_color CorPeca);

/***********************************************************************
*
*  $FC Função: DPT Obter jogador que pode dobrar partida
*
*  $ED Descrição da função
*     Obtém o jogador que pode dobrar a partida.
*
*  $EP Parâmetros
*     $P pCorPeca - ponteiro que receberá, por referência, a cor da peça do jogador.
*  AE: Existe um ponteiro que aponta para uma área do PEC_Color que será passado
*  AS:Caso exista dadoPontos e Caso esse dado possua um dono, a variável passada passará a ter o valor dessa cor
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*	  DPT_NaoHaJogadorDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_ObterJogadorDobraPartida(PEC_color *pCorPeca);

/***********************************************************************
*
*  $FC Função: DPT Obter pontuação da partida
*
*  $ED Descrição da função
*     Obtém a pontuação da partida.
*
*  $EP Parâmetros
*     $P pPontuacao - ponteiro que receberá, por referência, a pontuação da partida.
*    AE: Existe um ponteiro que aponta para uma área do tipo INT que será passada por referência para a função
*    AS: Caso exista o dado de Pontos, a variável passada por referência será atualizada com o valor da pontuação do jogo
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_ObterPontuacaoPartida(int *pPontuacao);

/***********************************************************************
*
*  $FC Função: DPT Destruir dado de pontos
*
*  $ED Descrição da função
*     Destrói a peça.
*
*  $EP Parâmetros
*  AS: Caso exista o dado de pontos, será destruído.
*  $FV Valor retornado
*     DPT_OK
*	  DPT_NaoHaDadoPontos
*
***********************************************************************/

   DPT_CondRet DPT_DestruirDadoPontos();

#undef DADOPONTOS_EXT

/********** Fim do módulo de definição: Módulo dado de pontos **********/

#else
#endif
