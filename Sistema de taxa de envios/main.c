#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "taxa.h"

int main(void){
	
	setlocale(LC_ALL, "Portuguese");
	
	printf("SISTEMA DE TAXA DE ENVIOS\n\n");
	printf("OLA, SEJA BEM VINDO AO NOSSO SISTEMA DE TAXA DE ENVIOS\n");
	
	Fila *fila = criarFila();		//cria uma fila para as pessoas que serao acumuladas
	Pilha *pilha1 = criarPilha();	//cria uma primeira pilha para as pessoas que serao acumuladas
	Pilha *pilha2 = criarPilha();	//cria uma segunda pilha para as pessoas que serao acumuladas
	
	char continuaOrNo;
	do{
		chamaPrograma(fila, pilha1, pilha2);
		limparBufferTeclado();
		printf("VOCE DESEJA ACESSAR O SISTEMA DE TAXA DE ENVIOS NOVAMENTE?\n");
		printf("Digite 's' para sim ou 'n' para nao: ");
		scanf("%c", &continuaOrNo);
		limparTela();
	}while(continuaOrNo == 's');
	printf("OBRIGADO POR UTILIZAR O NOSSO SISTEMA :)\n");
}