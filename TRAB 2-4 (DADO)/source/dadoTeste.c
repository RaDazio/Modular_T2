/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              dadoTeste.C
*  Letras identificadoras:      TDICE
*

*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*
*	Autores:	gcmc - Gabriel Garcia Mascheroni Costa
*				rdms - Rafael Damazio Monteiro da Silva
*				fo	 - Felipe de Oliveira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data		 Observa��es
*       1.00   rmds   05/05/2019 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo visa o teste utilizando as fun��es espec�ficas do
*      m�dulo de dados
*
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo �rvore:
*
*     "=rolar"		    - chama a fun��o DICE_RolarDado()
***************************************************************************/

#include<stdio.h>
#include<string.h>

#include    "../TESTES_GENERICO/TST_ESPC.H"
#include    "../TESTES_GENERICO/generico.h"
#include    "../TESTES_GENERICO/lerparm.h"

#include	"../../Source/interfaces/dado.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define ROLAR	"=rolar"

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TDICE Efetuar opera��es de teste espec�ficas para pe�as
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     pe�as sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

	   DICE_CondRet CondRetObtido   = DICE_ok ;
	   DICE_CondRet CondRetEsperada = DICE_wrong ;
                                      /* inicializa para qualquer coisa */

	  int numLados = -1;
	  int value=-1;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar DICE Rolar dado */

         if ( strcmp( ComandoTeste , ROLAR ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,&numLados, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = DICE_RolarDado(&value,numLados);

			if(value > numLados){
				return TST_CondRetErro;
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar pe�a." );
		
         } /* fim ativa: Testar DICE Rolar dado */
		 else{
			 return TST_CondRetNaoConhec;
		 }

   } /* Fim fun��o: TDICE Efetuar opera��es de teste espec�ficas para dado */