
/* Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao 
EEL270 - Computacao II - Turma 2021/1 
Prof. Marcelo Luiz Drumond Lanza
Autor: Mikaela Rikberg Alves
Descricao: Implementa a funcao decodificar base 16. 

Author:$
$Date: 2021/10/02 19:04:37 $ 
$Log: aula0805.c,v $
Revision 1.1  2021/10/02 19:04:37  mikaela.alves
Initial revision


 
*/


#ifdef __linux__
#define _XOPEN_SOURCE 600
#endif

#if defined (__FreeBSD__) && defined (__STRICT_ANSI__)
#define __ISO_C_VISIBLE         1999
#define __LONG_LONG_SUPPORTED
#endif


#include "aula0801.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <errno.h>

#define OK						0
#define NUMERO_ARGUMENTOS_INVALIDO			1
#define COMPRIMENTO_ARGUMENTO_INVALIDO			2	
#define VALOR_MAXIMO_EXCEDIDO				4
#define BASE_INVALIDA					5
#define ARGUMENTO_NEGATIVO				6
#define END_OF_STRING					'\0'
#define ARGUMENTO_INVALIDO				1
#define MEMORIA_INSUFICIENTE                            8
#define ALFABETO_INVALIDO                               9


int main (int argc, char *argv [])
{

	
	unsigned long long numeroBytes[1];
	char *entrada;
	char *saida;
		
	unsigned short indice;
	byte *vetorBytes;
	tipoAlfabetoBase32 alfabeto;		


	if (argc != 3) 
	{
		printf ("Uso: <numero-inteiro-nao-negativo> <numero-inteiro-nao-negativo> <numero-inteiro-nao-negativo> \n");
		exit (COMPRIMENTO_ARGUMENTO_INVALIDO);		
	}
	

	if(argv[1][0] == '-')
	{	
		printf ("Argumento caractere invalido.\n");
		exit (ARGUMENTO_INVALIDO);
	}

	  
	if(argv[1][0] == '0')
		alfabeto = alfabetoNormal;

	if(argv[1][0] == '1')
		alfabeto =  alfabetoEstendido;

	if(argv[1][0] != '0' && argv[1][0] != '1')
	{
		printf ("Argumento invalido.\n");
		exit (ALFABETO_INVALIDO);
	}

/*------------------------  Alocando memoria   ------------------------------*/
	
	entrada = (char *) malloc (sizeof(char[strlen(argv[1])+1]));

	
	if( entrada == NULL)
	{
		printf (" memoria insuficiente");
		exit (MEMORIA_INSUFICIENTE);
	}

	strcpy(entrada,argv[1]);
	
	vetorBytes = (byte *) malloc (sizeof(byte[strlen(entrada)]));
	
	if(vetorBytes == NULL)
	{
		free(entrada);
		printf ("\n memoria insuficiente");
		exit (MEMORIA_INSUFICIENTE);
	}
	saida = (char *) malloc (sizeof(char[strlen(entrada)]));
	
	if(saida == NULL)
	{
		free(entrada);
		printf ("\n memoria insuficiente");
		exit (MEMORIA_INSUFICIENTE);
	}
/*------------------------------------------------------------------------*/
	
	entrada = argv[2];
	
	DecodificarBase32 (entrada, alfabeto, vetorBytes, numeroBytes);
	
	CodificarBase16 (vetorBytes ,numeroBytes[0],saida);
	
	for (indice = 0; indice < numeroBytes[0]; indice++)
	{

		printf("%d ", vetorBytes[indice]);
	}

	printf("\n\n");
	
	int indiceNovo = 0;
	for (indice = 0; indice < numeroBytes[0]; indice++){
		
		printf("%c%c ", saida[indiceNovo] ,saida[indiceNovo+1] );
		indiceNovo+=2;
	}
	printf("\n\n");

	free(entrada);
	free(vetorBytes);

	
return OK;
}

/* RCSfile$ */
