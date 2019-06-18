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

#include	"../../Source/interfaces/PecasFinalizadas.h"
#include	"../../Source/interfaces/peca.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define CRIAR		               "=criar"
#define INSERIR_PECA			   "=inserir"
#define OBTER_QTD_PECAS			   "=contar"
#define DESTRUIR                   "=destruir"


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

	 PF_CondRet CondRetObtido   = PF_OK ;
	 PF_CondRet CondRetEsperada = PF_FaltouMemoria ;
                                      /* inicializa para qualquer coisa */


	  PEC_color cor;
	  
	  int qtd;

      int  NumLidos = -1 ;

      /* Testar PF Criar peçaFinalizada */

         if ( strcmp( ComandoTeste , CRIAR ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = PF_CriarPecasFinalizadas();

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar peçaCapturada." );

         } 


      /* Testar PF Adicionar Peca */

         else if ( strcmp( ComandoTeste , INSERIR_PECA ) == 0 )
         {

			 NumLidos = LER_LerParametros( "ii" , &cor , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PF_AdicionarPecaFinalizada(cor) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao inserir pecaCapturada." );

         } 


	    /* Teste PF Obter Quantidade Pecas */

         else if ( strcmp( ComandoTeste , OBTER_QTD_PECAS ) == 0 )
         {
		  int qtd_esperada;
		  TST_tpCondRet ret;
          NumLidos = LER_LerParametros( "iii" , &cor , &qtd_esperada,  &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PF_ObterTamanhoPecasFinalizadas(cor, &qtd) ;

			ret = TST_CompararInt(qtd_esperada,qtd,"Valores diferentes");
			if(ret != TST_CondOK){
				return ret;
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter quantidade de pecas." );

         } 

      /* Testar PF Destruir peçaFinalizadas */

         else if ( strcmp( ComandoTeste , DESTRUIR ) == 0 )
         {
            NumLidos = LER_LerParametros("i" , &CondRetEsperada);
         
            if(NumLidos != 1)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido = PF_DestruirPecasFinalizadas();

            return TST_CompararInt(CondRetEsperada , CondRetObtido , "Erro ao destruir pecas capturadas.");
		 } 

		 else{
			 return TST_CondRetNaoConhec;
		 }
   } /* Fim função: PF Efetuar operações de teste específicas  */
