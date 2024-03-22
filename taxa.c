#include <stdio.h>
#include <stdlib.h>
#include "taxa.h"
#include <locale.h>

int clienteOuAdm(){

	int tipoDeCliente;

    printf("Voce esta entrando como cliente ou administrador?\n");
    printc('-', 100);
    printf("DIGITE '0' PARA ENTRAR COMO ADMINISTRADOR\n");
    printf("DIGITE '1' PARA ENVIAR UM PRODUTO\n");
    printc('-', 100);
    do{
        scanf("%d", &tipoDeCliente);
        limparBufferTeclado();
		if(tipoDeCliente < 0 || tipoDeCliente > 1){
			printf("Digite uma entrada válida\n");
		}
    }while(tipoDeCliente < 0 || tipoDeCliente > 1);
	limparTela();
	return tipoDeCliente;
}

//chama programa
void chamaPrograma(Fila *fila, Pilha *pilha1, Pilha *pilha2){

	int tipoDeCliente;
	tipoDeCliente = clienteOuAdm();

	if(tipoDeCliente == 0){
		chamaAdm(fila, pilha1, pilha2);
	}
	else if(tipoDeCliente == 1){
		chamaCliente(fila, pilha1);
	}
}

//quando for a opcao do adm
void chamaAdm(Fila *fila, Pilha *pilha1, Pilha *pilha2){

	printf("Ola administrador, antes de entrar precisamos que voce insira a senha\n");
	printf("(A senha eh 12345)\n");
	
	int tenta3X;
	int cont = 3;

	while(scanf("%d", &tenta3X), tenta3X != 12345  && cont != 0){
		printf("Senha incorreta, voce tem mais %d chances\n", cont);
		cont--;
	}
	limparBufferTeclado();
	if(tenta3X == 12345){
		limparTela();
		opcaoDoAdm(fila, pilha1, pilha2);
	}
	else{
		printf("Chances esgotadas!!!\n");
		limparTela();
	}
}

void opcaoDoAdm(Fila *fila, Pilha *pilha1, Pilha *pilha2){

	insereFilaNaPilha(fila, pilha1, pilha2);
	
	int opcaoAdm;	
	do{
		printf("Digite a opcao que voce desejar entrar:\n");
		printc('-', 100);
		printf("0 - Sair\n1 - Ver ultimos cadastrados\n2 - Clientes que devem ter seu produto(s) embalado(s)\n");
		printc('-', 100);	

		scanf("%d", &opcaoAdm);
		limparBufferTeclado();
		switch(opcaoAdm){
			case 0:
				limparTela();
				printf("Saindo...(pressione enter para continuar)\n");
				getchar();
				limparTela();
				break;

			case 1:
				limparTela();
				verUltimosCadastrados(fila, pilha1);
				printf("Pressione enter para continuar\n");
				getchar();
				limparTela();
				break;

			case 2:
				limparTela();
				verClientesEmbalados(fila, pilha2);
				printf("Pressione enter para continuar\n");
				getchar();
				limparTela();
				break;

			default:
				printf("Digite um valor valido!\n");
				break;
		}
	}while(opcaoAdm != 0);

	limparTela();

}

void verUltimosCadastrados(Fila *fila, Pilha *pilha1){

	if(pilha1->topo == NULL){
		printf("NAO HA CLIENTES CADASTRADOS\n");
	}
	else{
		printf("OS ULTIMOS CADASTRADOS FORAM\n\n");
		printc('-', 100);
		imprimirPilha1(pilha1);
		printc('-', 100);
	}
}

void verClientesEmbalados(Fila *fila, Pilha *pilha2){
	if(pilha2->topo == NULL){
		printf("NAO HA CLIENTES QUE PRECISAM DE SEUS PRODUTOS EMBRULHADOS\n");
	}
	else{
		printf("CLIENTES QUE PRECISAM QUE O PRODUTO(S) SEJA EMBRULHADO(S)\n");
		printc('-', 100);
		imprimirPilha2(pilha2);
		printc('-', 100);
	}
}

//quando for a opcao do cliente
void chamaCliente(Fila *fila, Pilha *pilha1){

	//retira todos os elementos que tem na pilha
	int i;
	removeTodosPilha(pilha1);

	int quantPessoas;
	printf("Ok, quantas pessoas irao efetuar o envio do produto?\n");
	scanf("%d", &quantPessoas);
	limparTela();
	
	fila->tamFila = 0;
	pilha1->tamPilha = 0;
	Pessoa person[quantPessoas];
	
	int entra1x = 1;

	for(i = 0; i < quantPessoas; i++){
		person[i].quantEmbrulhados = 0;
		fila->tamFila += 1;
		pilha1->tamPilha += 1;
		int entraEmbalagem1x = 1;

		limparBufferTeclado();
		//entra somente uma vez
		if(entra1x){

			//preenche a struct pessoa com suas informacoes
			int j;
			for(j = 0; j < quantPessoas; j++){
				printf("Digite o nome do %d ° que ira enviar: ", j+1);
				person[j] = lerPessoas();
				printf("\n\n");
			}
			entra1x = 0;
			limparTela();
		}
		printf("\nOk, sua vez %s. Para isso fique ciente de algumas informacoes a seguir:\n", person[i].nome);
					
		char repit = 's';
		
		int cont = 0;		//acumula as taxas nessa posicao
				
		while(repit == 's'){
			if(cont == 0){
				printc('-', 100);
				imprimeInformacoesProduto();		//imprime as informacoes sobre o produto somente 1x
				printc('-', 100);
			}
			printf("\nDigite o tipo do produto: \n");
			do{
				scanf("%d", &person[i].tipoProduto);
				
				if(person[i].tipoProduto < 0 || person[i].tipoProduto > 3){
					printf("Digite um valor valido:\n");
				}
			}while(person[i].tipoProduto < 0 || person[i].tipoProduto > 3);

			limparTela();

			if(cont == 0){
				printc('-', 100);
				imprimeInformacoesDistancia();		//imprime as informacoes sobre a distancia somente 1x
				printc('-', 100);
			}
			
			printf("\nAgora digite o tipo de destino:\n");
			do{
				scanf("%d", &person[i].destino);
				if(person[i].destino < 0 || person[i].destino > 3){
					printf("Digite um valor valido:\n");
				}
			}while(person[i].destino < 0 || person[i].destino > 3);
			
			limparTela();

			printf("\nDigite o peso do produto em Kg no formato 'p.p': " );

			do{
				scanf("%lf", &person[i].peso);
				if(person[i].peso <= 0){
					printf("Digite um valor positivo\n");
				}
			}while(person[i].peso <= 0);

			limparTela();

			char embrulhadoOuNao;
			if(entraEmbalagem1x){
				printf("\nVoce deseja que seu produto seja embrulhado? Digite 's' para sim ou 'n' para nao: ");
				do{	
					limparBufferTeclado();
					scanf("%c", &embrulhadoOuNao);
					
					if(embrulhadoOuNao != 's' && embrulhadoOuNao != 'n'){
						printf("\nDigite uma entrada valida: ");
					}
				}while(embrulhadoOuNao != 's' && embrulhadoOuNao != 'n');
				entraEmbalagem1x = 0;
			}
			limparBufferTeclado();
			limparTela();

			if(embrulhadoOuNao == 's'){
				person[i].quantEmbrulhados += 1;
				person[i].embrulhado = 1;		//ele quer que o produto seja embrulhado
			}
			else{
				person[i].embrulhado = 0;
			}
			
			if(person[i].tipoProduto >= 0 && person[i].tipoProduto <=3 && person[i].destino >= 0 && person[i].destino <=3){
				
				double taxa1, taxa2;
				
				taxa1 = taxaPeso(person[i].peso);		//aplica a devida taxa sob o peso
				
				taxa2 = taxaDistancia(person[i].tipoProduto, person[i].destino);		//procura a devida taxa na matriz;
				
				person[i].taxa[cont] = (taxa1 + taxa2);		//acumula a taxa da pessoa i na posicao cont, até n taxas
				
				cont ++;
			}
			else{
				printf("\nValores invalidos");
			}

			printf("\nDeseja enviar novamente? Se sim, digite 's', caso nao 'n'");
			scanf("%c", &repit);
			limparTela();
		}
		person[i].quantProdutos = cont;		//quantidade de produtos que a pessoa enviou
		
		int j;
		for(j = 0; j < person[i].quantProdutos; j++){
			person[i].taxaFinal += person[i].taxa[j];		//acumula a taxa total da pessoa
		}
		inserirNaFila(fila, person[i]);		//insere na fila a pessoa em questao
	}

	printc('-', 100);
	imprimirFila(fila);
	printc('-', 100);
}

void printc(char c, int tamanho){
	
	int cont;
	
	for(cont = 0; cont < tamanho; cont++){
		printf("%c", c);
	}
	printf("\n");
}

void imprimeInformacoesProduto(){

	printf("\nOs tipos de Produtos sao divididos em 4, sendo eles:\n ");
	printf("Tipo 0: Frageis (Espelhos pequenos, tacas, garrafas de bebidas)\n ");
	printf("Tipo 1: Leves ate 1 kilo (Peca de roupa, tenis, chapeu, relogio, etc)\n ");
	printf("Tipo 2: Grande dimensoes maiores que 1.5 x 1.5 (Cortina, Tapete, Quadro, Televisoes, etc)\n ");
	printf("Tipo 3: Outros ( Produtos que nao se encaixam nas opcoes anteriores)\n");
}

void imprimeInformacoesDistancia(){

	printf("\nAs distancias tambem sao divididos em 4:\n ");
	printf("Tipo 0: 0 a 50km\n ");
	printf("Tipo 1: 50km a 150km\n ");
	printf("Tipo 2: 150km a 500km\n ");
	printf("Tipo 3: 500km ou mais\n ");
}

double taxaPeso(double peso){
	
	double tarifa;
	
	tarifa = 4 * peso;		//a taxa do peso se baseia no peso vezes uma taxa fixa de 4 Reais;
	
	return tarifa;
	
}

double taxaDistancia(int tipoProduto, int distancia){
	
	// preco da taxa dos produtos, somando a distancia com o tipo do produto;
	
	double matriz[4][4] = {
	3.5, 6.5, 9.5, 17,
	2.5, 5.5, 8.5, 16,
	6.5, 9.5, 12.5, 20,
	4.5, 7.5, 10.5, 18
	};
	
	return matriz[tipoProduto][distancia];
}

Pessoa lerPessoas(){
	Pessoa person;

	scanf("%s", person.nome);
	limparBufferTeclado();

	printf("Digite sua idade: ");
	scanf("%d", &person.idade);

	printf("Digite seu cpf: ");
	scanf("%d", &person.cpf);
	limparBufferTeclado();

	return person;
}

Fila* criarFila(){
	Fila *fila = malloc(sizeof(Fila));
	fila->prim = NULL;
	fila->ult = NULL;
	return fila;
}

void inserirNaFila(Fila *fila, Pessoa person){
	No *novo = malloc(sizeof(No));
	if(novo){
		novo->pessoa = person;
		novo->prox = NULL;
		if(fila->prim == NULL){
			fila->prim = novo;
			fila->ult = novo;
		}
		else{
			fila->ult->prox = novo;
			fila->ult = novo;
		}
	}
	else{
		printf("\nErro ao alocar memoria\n");
		exit(1);
	}
}

No* removerDaFila(Fila *fila){
	No *remover = NULL;
	if(fila->prim){
		remover = fila->prim;
		fila->prim = remover->prox;
	}
	return remover;
}

void removeTodosFila(Fila *fila){ 
    while(fila->prim){
		No *aux = fila->prim;
        fila->prim = fila->prim->prox;
        free(aux);
    }
}

void imprimirFila(Fila *fila){
	No *aux = fila->prim;
	while(aux){
		printf("\nNome: %s\n", aux->pessoa.nome);
		printf("Sua taxa final foi de: %.2lf\n\n", aux->pessoa.taxaFinal);
		aux = aux->prox;
	}
}

Pilha* criarPilha(){
	Pilha *pilha = malloc(sizeof(Pilha));
	pilha->topo = NULL;
	return pilha;
}
void push(Pilha *pilha, Pessoa person){
	NoDaPilha *novo = malloc(sizeof(NoDaPilha));
	if(novo){
		novo->pessoa = person;
		novo->prox = pilha->topo;
		pilha->topo = novo;
	}
	else{
		printf("\nErro ao alocar memoria\n");
	}
}
NoDaPilha* pop(Pilha *pilha){
	NoDaPilha *remover = NULL;
	if(pilha->topo){
		remover = pilha->topo;
		pilha->topo = remover->prox;
	}
	else{
		printf("\nNenhum pessoa foi cadastrada recentemente\n");
	}
	return remover;
}
void removeTodosPilha(Pilha *pilha){ 
    while(pilha->topo){
		NoDaPilha *aux = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(aux);
    }
}

void imprimirPilha1(Pilha *pilha){
	NoDaPilha *aux = pilha->topo;
	while(aux){
		printf("\nNOME: %s\n", aux->pessoa.nome);
		printf("IDADE: %d\n", aux->pessoa.idade);
		printf("CPF: %d\n", aux->pessoa.cpf);
		printf("QUANTIDADE DE PRODUTOS ENVIADOS: %d\n", aux->pessoa.quantProdutos);
		aux = aux->prox;
	}
}
void imprimirPilha2(Pilha *pilha){
	NoDaPilha *aux = pilha->topo;
	while(aux){
		printf("\nNOME: %s\n", aux->pessoa.nome);
		printf("QUANTIDADE DE PRODUTOS QUE PRECISAM SER EMBRULHADOS: %d\n", aux->pessoa.quantEmbrulhados);
		aux = aux->prox;
	}
}

void insereFilaNaPilha(Fila *fila, Pilha *pilha1, Pilha *pilha2){
	if(fila->prim){
		No *remover;
		int i;
		for(i = 0; i < fila->tamFila; i++){
			remover = removerDaFila(fila);
			if(remover){
				push(pilha1, remover->pessoa);
				if(remover->pessoa.embrulhado != 0){
					push(pilha2, remover->pessoa);
				}
			}
		}
		free(remover);
	}
}

// Limpa a tela do terminal de acordo com o sistema operacional
void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limparBufferTeclado() {
    #ifdef _WIN32
        fflush(stdin); // No Windows, limpa o buffer usando fflush
    #else
        while (getchar() != '\n'); // No Linux, consome caracteres até encontrar uma quebra de linha
    #endif
}