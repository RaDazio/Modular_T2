/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              pecaTeste.C
*  Letras identificadoras:      TPEC
*

*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
*				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data		 Observações
*       1.00   rmds   05/05/2019 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo visa o teste utilizando as funções específicas do
*      módulo de peças
*
*
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo peca capturada:
*
*     "=criar"		    - chama a função PEC_CriaPeca()
*     "=destroi"		- chama a função PEC_DestruirPeca()
*	  "=obterCor"		- chama a função PEC_ObterCor()
*
***************************************************************************/

#include<stdio.h>
#include<string.h>

#include    "../TESTES_GENERICO/TST_ESPC.H"
#include    "../TESTES_GENERICO/generico.h"
#include    "../TESTES_GENERICO/lerparm.h"

#include	"../../Source/interfaces/PECASCAPTURADAS.H"
	
/* Tabela dos nomes dos comandos de teste específicos */

#define CRIAR		               "=criar"
#define INSERIR_PECA_BRANCA	   "=inserir"
#define REMOVER_PECA_BRANCA		"=remover"
#define OBTER_QTD_PECAS_BRANCAS  "=contar"
#define DESTRUIR                 "=destruir"

/* Singleton para realização dos testes */
static PecaHead pecasCapturadaSingleton = NULL;


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPECA Efetuar operações de teste específicas para peças
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     peças sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

	  PCAP_tpCondRet CondRetObtido   = PCAP_CondRetOK ;
	  PCAP_tpCondRet CondRetEsperada = PCAP_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */


	  PEC_color cor;
	  
	  int qtd;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar PCAP Criar peçaCapturada */

         if ( strcmp( ComandoTeste , CRIAR ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = PCAP_CriarListasPecasCapturadas();

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar peçaCapturada." );

         } /* fim ativa: Testar PEC Criar peça */


      /* Testar PCAP Inserir peca branca */

         else if ( strcmp( ComandoTeste , INSERIR_PECA_BRANCA ) == 0 )
         {

			 NumLidos = LER_LerParametros( "ii" , &cor , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PCAP_InserirPecaCapturada(cor) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao inserir pecaCapturada." );

         } /* fim ativa: Testar PEC inserir peca (branca) */

      /* Teste PCAP Remover peca branca */

         else if ( strcmp( ComandoTeste , REMOVER_PECA_BRANCA ) == 0 )
         {

          NumLidos = LER_LerParametros( "ii" , &cor , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PCAP_RemoverPecaCapturada(cor) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao remover pecaCapturada."	);

         } /* fim ativa: Testar PEC remover peca (branca) */

      /* Teste PCAP Obter Quantidade Pecas (Brancas) */

         else if ( strcmp( ComandoTeste , OBTER_QTD_PECAS_BRANCAS ) == 0 )
         {

          NumLidos = LER_LerParametros( "ii" , &cor , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PCAP_ObterQuantidadePecasCapturadas(cor, &qtd) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter quantidade de pecas." );

         } /* fim ativa: Testar PCAP Obter Quantidade Pecas (Brancas) */

      /* Testar PEC Destruir peçaCapturadas */

         else if ( strcmp( ComandoTeste , DESTRUIR ) == 0 )
         {
            NumLidos = LER_LerParametros("i" , &CondRetEsperada);
         
            if(NumLidos != 1)
            {
               return TST_CondRetParm;
            } /* if */

         CondRetObtido = PCAP_DestruirPecasCapturadas();

            return TST_CompararInt(CondRetEsperada , CondRetObtido , "Erro ao destruir pecas capturadas.");
		 } /* fim ativa: Testar PCAP Detruir Pecas Capturadas */

   } /* Fim função: TPEC Efetuar operações de teste específicas para peças */
