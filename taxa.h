//prototipo da estrutura pessoa
typedef struct pessoa{

	char nome[101];
	int idade;
	int cpf;
	char sexo;
	int tipoProduto;
	int destino;
	double peso;
	double taxa[100];
	double taxaFinal;
	int quantProdutos;
	int embrulhado;
	int quantEmbrulhados;

}Pessoa;

//no da fila
typedef struct no{
	Pessoa pessoa;
	struct no *prox;
}No;

//criar uma struct que aponta para o primeiro elemento e o ultimo da fila
typedef struct fila{
	No *prim;
	No *ult;
	int tamFila;
}Fila;

//cria um no para a pilha
typedef struct noDaPilha{
	Pessoa pessoa;
	struct noDaPilha *prox;
}NoDaPilha;

//cria uma struct que aponto para o topo da pilha
typedef struct pilha{
	NoDaPilha *topo;
	int tamPilha;
}Pilha;

//chama programa
void chamaPrograma(Fila *fila, Pilha *pilha1, Pilha *pilha2);

//ver se a entrada eh como cliente ou adm
int clienteOuAdm();

//SISTEMA DO ADM:

//funcao que chama a opcao adm que chama outras funcoes
void chamaAdm(Fila *fila, Pilha *pilha1, Pilha *pilha2);

//adm escolhe a opcao que deseja
void opcaoDoAdm(Fila *fila, Pilha *pilha1, Pilha *pilha2);

//ver os ultimos cadastrados caso a opcao do adm seja 1
void verUltimosCadastrados(Fila *fila, Pilha *pilha1);

//ver os clientes que precisam que seus produtos sejam embrulhados
//caso a opcao do adm seja 2
void verClientesEmbalados(Fila *fila, Pilha *pilha2);


//SISTEMA DO CLIENTE:

//funcao que chama o cliente que chama outras funcoes
void chamaCliente(Fila *fila, Pilha *pilha1);

//limpa buffer do teclado
void limparBufferTeclado();

//faz um print de barras para melhorar o visual do terminal
void printc(char c, int tamanho);

//imprime algumas informacoes sobre o produto aos quais o usuario precisa saber
void imprimeInformacoesProduto();

//imprime algumas informacoes sobre a distancia aos quais o usuario precisa saber

void imprimeInformacoesDistancia();

//calcula a taxa baseando-se no peso
double taxaPeso(double peso);

//calcula a taxa da distancia baseando-se nas informacoes de distancia a tipo de produto
double taxaDistancia(int tipoProduto, int distancia);

//ler as pessoas
Pessoa lerPessoas();

//cria uma fila
Fila* criarFila();

//insere uma pessoa na fila
void inserirNaFila(Fila *fila, Pessoa pessoa);

//remove e retorna o elemento removido da fila
No* removerDaFila(Fila *fila);

//remove todos os elementos da fila
void removeTodosFila(Fila *fila);

//imprime a fila
void imprimirFila(Fila *fila);

//cria uma pilha
Pilha* criarPilha();

//insere uma pessoa na pilha
void push(Pilha *pilha, Pessoa pessoa);

//retira e retorna o elemento retirado da pilha
NoDaPilha* pop(Pilha *pilha);

//retira todos os elementos da pilha
void removeTodosPilha(Pilha *pilha);

//imprime as pessoas da pilha1
void imprimirPilha1(Pilha *pilha);

//imprime as pessoas da pilha2
void imprimirPilha2(Pilha *pilha);

void insereFilaNaPilha(Fila *fila, Pilha *pilha1, Pilha *pilha2);

//limpa a tela do terminal de acordo com o sistema operacional
void limparTela();