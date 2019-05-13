/***************************************************************************
*  $MCI Módulo de implementação: TDPT Teste dado de pontos
*
*  Arquivo gerado:              TestDPT.c
*  Letras identificadoras:      TDPT
*
*  Projeto: Disciplina INF 1301

*  Autores: gcmc - Gabriel Garcia Mascheroni Costa
        rdms - Rafael Damazio Monteiro da Silva
*       fo   - Felipe de Oliveira
*
* $HA Histórico e evolução:
*   Versão  Autor Data    Observações
*   1.00  fo  27/04/2019  Inicio do desenvolvimento
     $EIU Interface com o usuário pessoa
*     Comandos de teste especúƒicos para testar o módulo DADOPONTOS:
     =resetteste                   - anula o vetor de Dados de Pontos.
*     =criardadopontos             - Chama a função DPT_CriarDadoPontos
*     =atualizarjogadordobra       - Chama a função DPT_AtualizarJogadorDobra
*     =dobrarpontuacaopartida      - Chama a função DPT_DobrarPontuacaoPartida
*     =obterjogadordobrapartida    - Chama a função DPT_ObterJogadorDobraPartida
*     =obterpontuacaopartida       - Chama a função DPT_ObterPontuacaoPartida
*     =destruirdadopontos          - Chama a função DPT_ObterPontuacaoPartida

*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "../TESTES_GENERICO/TST_Espc.h"
#include    "../TESTES_GENERICO/generico.h"
#include    "../TESTES_GENERICO/LerParm.h"

#include    "../../Source/interfaces/DADOPONTOS.h"

//static const char RESET_DADOPONTOS_CMD             [] = "=resetteste";
static const char CRIAR_DADOPONTOS_CMD             [] = "=criardadopontos";
static const char ATUALIZAR_JOGADOR_DOBRA_CMD      [] = "=atualizarjogadordobra";
static const char DOBRAR_PONTUACAO_PARTIDA_CMD     [] = "=dobrarpontuacaopartida";
static const char OBTER_JOGADOR_DOBRA_PARTIDA_CMD  [] = "=obterjogadordobrapartida";
static const char OBTER_PONTUACAO_PARTIDA_CMD      [] = "=obterpontuacaopartida";
static const char DESTRUIR_DADOPONTOS_CMD          [] = "=destruirdadopontos";


static DPT_DadoHead dado = NULL;


/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TDPT &Testar Dado de Pontos
*
*  $ED Descrição da função
*     Podem ser criados ate 5 dados de pontos, identificados pelos indices de  0 a 4
*     Efetua os diversos comandos de teste especúƒicos para o módulo Dado Pontos sendo testado.
*   $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*   $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
*  
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
   {

         int numLidos   = -1 ;
      //int CondRetEsp = -1;
	  
	  int Pontuacao = -1;
	  int ValorEsperado;
	  
	  PEC_color CorPeca;

	  DPT_CondRet CondRetObtido   = DPT_OK;
      DPT_CondRet CondRetEsp = DPT_FalhaMemoria;
		/* Sempre Inicializa */
	  
      int ValEsp = -1;

	  TST_tpCondRet CondRetTesteEsperado;

      
      
      /* Testar Criar Dado de Pontos */

         if(strcmp(ComandoTeste , CRIAR_DADOPONTOS_CMD) == 0)
         {

            numLidos = LER_LerParametros("i" ,
                        &CondRetEsp);

            if(numLidos != 1)
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido =
                 DPT_CriarDadoPontos(&dado);
			
            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro em ponteiro de novo Dado de Pontos.");

         } /* fim ativa: Testar Criar Dado de Pontos */

      /* Testar Destruir Dado de Pontos */

         else if(strcmp(ComandoTeste , DESTRUIR_DADOPONTOS_CMD) == 0)
         {

            numLidos = LER_LerParametros("i" ,
                                &CondRetEsp);
			
            if(numLidos != 1)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido =
                 DPT_DestruirDadoPontos(&dado);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao destruir Dado de Pontos.");

         } /* fim ativa: Testar Destruir Dado de Pontos */

		/* Testar Atualizar jogador de dobra */

         else if(strcmp(ComandoTeste , ATUALIZAR_JOGADOR_DOBRA_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                                &CorPeca, &CondRetEsp);
			
            if(numLidos != 2)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido =
                 DPT_AtualizarJogadorDobra(dado, CorPeca);
			
            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao atualizar jogador de dobra.");

         } /* fim ativa: Testar Atualizar jogador de dobra */

		 /* Testar Dobrar pontuação da partida */

         else if(strcmp(ComandoTeste , DOBRAR_PONTUACAO_PARTIDA_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                                &CorPeca, &CondRetEsp);
			
            if(numLidos != 2)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido =
                 DPT_DobrarPontuacaoPartida(dado, CorPeca);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao dobrar pontuacao da partida.");

         } /* fim ativa: Dobrar pontuação da partida */

		 /* Testar Obter jogador dobra partida */

         else if(strcmp(ComandoTeste , OBTER_JOGADOR_DOBRA_PARTIDA_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                                &ValorEsperado, &CondRetEsp);
			
            if(numLidos != 2)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido =
                 DPT_ObterJogadorDobraPartida(dado, &CorPeca);
			
			CondRetTesteEsperado = TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao Obter jogador dobra da partida.");

			if(CondRetTesteEsperado != TST_CondRetOK || CondRetObtido != DPT_OK)
			{
				return CondRetTesteEsperado;
			}

			return TST_CompararInt(ValorEsperado , CorPeca ,
               "Erro ao Obter jogador dobra da partida - valor invalido.");

         } /* fim ativa: Testar Obter jogador dobra partida */

		 /* Testar Obter pontuação da partida */

		 else if(strcmp(ComandoTeste , OBTER_PONTUACAO_PARTIDA_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                                &ValorEsperado, &CondRetEsp);
			
            if(numLidos != 2)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido =
                 DPT_ObterPontuacaoPartida(dado, &Pontuacao);
			
			CondRetTesteEsperado = TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao Obter pontuação da partida.");

			if(CondRetTesteEsperado != TST_CondRetOK || CondRetObtido != DPT_OK)
			{
				return CondRetTesteEsperado;
			}

			return TST_CompararInt(ValorEsperado , Pontuacao ,
               "Erro ao Obter pontuação da partida - valor invalido.");

         } /* fim ativa: Testar Obter pontuação da partida */
		 
      return TST_CondRetNaoConhec;

   } /* fim função: tdpt &testar dado de pontos */
	
/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TDPT - Validar indice de dado de pontos
*
***********************************************************************/

  

/********** Fim do módulo de implementação: TDPT Teste dado de pontos **********/