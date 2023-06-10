#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// adjacente

typedef struct estr
{
      int adj; // elemento
	  int peso; // custo
      struct estr *prox;
} NO;

// vertices do grafo (salas)

typedef struct
{
       bool aberto; // vale true se a sala em questao esta aberta
       int via; // para criar a lista ligada com o caminho de custo minimo
	   int dist; // para calcular o custo minimo
       NO * inicio; // lista de adjacentes do vertice
} VERTICE;

VERTICE * criarGrafo(int N, int A, int * ijpeso){

	VERTICE * g = (VERTICE *)malloc(sizeof(VERTICE) * N);

	for(int i  = 0;i < N;i++)g[i].inicio = NULL;

	for(int i = 0; i < 3*A; i += 3){
		NO * novo1 = (NO *)malloc(sizeof(NO));
		novo1->peso = ijpeso[i + 2];
		novo1->adj = ijpeso[i + 1] - 1;
		novo1->prox = g[ijpeso[i] - 1].inicio;
		g[ijpeso[i] - 1].inicio = novo1;

		NO * novo2 = (NO *)malloc(sizeof(NO));
		novo2->peso = ijpeso[i + 2];
		novo2->adj = ijpeso[i] - 1;
		novo2->prox = g[ijpeso[i + 1] - 1].inicio;
		g[ijpeso[i + 1] - 1].inicio = novo2;
	}

	return g;

}

void inicializaGrafo(VERTICE * g, int N, int inicio,int * aberto){

	for(int i  = 0;i < N;i++){

		if(aberto[i])
			g[i].aberto = true;
		else
			g[i].aberto = false;

	}

}

void imprimeGrafo(VERTICE * g, int N){

	for(int i = 0; i < N;i++){
		NO * p = g[i].inicio;
		printf("[%d] : ", i + 1);
		while(p){
			printf("%d(%d)  -> ", p->adj + 1, p->peso);
			p = p->prox;
		}
		printf("NULL");
		printf("\n");
	}
}

void inicializaDist(VERTICE * g, int N, int inicio){
	g[inicio].dist = 0;

	for(int i = 0;i < N;i++){
		if(i != inicio)
			g[i].dist = 1000000; // equivale a inicializar com infinite
	}
}

void abreeTodas(VERTICE * g, int N){
	for(int i  = 0; i < N;i++){
		g[i].aberto = true;
	}
}

bool temVerticeSemCustoMinimo(int * semCustoMinimo, int N){
	bool aindaTem = false;
	for(int i = 0; i < N;i++){
		if(semCustoMinimo[i])
			aindaTem = true;
	}
	return aindaTem;

}

int pegaVerticeMin(VERTICE * g, int * semCustoMinimo, int N, int * via){

	int menorDist = 1000000; // inicia com infinite
	int menor = -1;

	for(int i = 0; i < N;i++){

		if(semCustoMinimo[i] > 0 && g[i].dist < menorDist && g[i].aberto == true){
			menorDist = g[i].dist;
			menor = i;
		}

	}
	return menor;
}

void concluiVertice(int * semCustoMinimo, int  V){

	semCustoMinimo[V] = 0;
}

void checaAdjacentesdeV(VERTICE * g, int V, int * semCustoMinimo, int * via){
	NO * p = g[V].inicio;
	while(p){
		if(g[V].dist + p->peso < g[p->adj].dist && semCustoMinimo[p->adj] > 0 && g[p->adj].aberto == true) {
			g[p->adj].dist = g[V].dist + p->peso;
			via[p->adj] = V;
		}

		p = p->prox;

	}
}

int * dijkstra(VERTICE * g, int N, int inicio, int fim, int chave){

	int * semCustoMinimo = (int *)malloc(sizeof(int) * N);
	int * via = (int *)malloc(sizeof(int) * N);
	for(int i = 0;i < N;i++) {
		semCustoMinimo[i] = 1;
		via[i] = -1;
	}
	inicializaDist(g, N, inicio);

	int V;

	while(temVerticeSemCustoMinimo(semCustoMinimo, N)){
		if((V = pegaVerticeMin(g, semCustoMinimo, N, via)) == -1) return via;
		concluiVertice(semCustoMinimo, V);
		checaAdjacentesdeV(g, V, semCustoMinimo, via);

	}

	free(semCustoMinimo);

	return via;

}

NO * criaListaCaminho(VERTICE * g, int inicio, int fim, int * via){

	NO * lista = NULL;

	if(via[fim] == -1){
		return lista;
	}
	lista = (NO *) malloc(sizeof(NO));
	lista->prox = NULL;
	lista->adj = inicio + 1;
	int vertice = fim;

	while(vertice != inicio){
		NO * novo = (NO *)malloc(sizeof(NO));
		novo->adj = vertice + 1;
		novo->prox = lista->prox;
		lista->prox = novo;
		vertice = via[vertice];
	}
	return lista;
}

void destroiGrafo(VERTICE * g, int N){
	NO * ant;
	NO * p;
	for(int i = 0;i < N;i++){
		ant = NULL;
		p = g[i].inicio;
		g[i].inicio = NULL;
		while(p){
			ant = p;
			p = p->prox;
			ant->prox = NULL;
			free(ant);
			ant = p;
			}
	}

	free(g);
}

// funcao principal

NO * caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave){
	NO * resp_pr1;
	NO * resp_ini_key;
	NO * resp_key_end;
	NO * resp_ini_end_key;
	NO * resp_final;

	int custo1, custo_ini_key, custo_key_end;
	custo1 = custo_ini_key = custo_key_end = 1000000;
	VERTICE * g = criarGrafo(N, A, ijpeso);
	inicializaGrafo(g, N, inicio - 1, aberto);

	if(inicio == chave)
		abreeTodas(g, N);

	int * via = dijkstra(g, N, inicio - 1, fim, chave);

	if(inicio == fim){
		resp_final = (NO *)malloc(sizeof(NO));
		resp_final->prox = NULL;
		resp_final->adj = inicio;
		return resp_final;
	}

	resp_pr1 = criaListaCaminho(g, inicio - 1, fim - 1, via);
	custo1 = g[fim - 1].dist;

    if(chave != 0)
        resp_ini_key = criaListaCaminho(g, inicio - 1, chave - 1, via);
    else
        resp_ini_key = NULL;
	if(resp_ini_key){
		custo_ini_key = g[chave - 1].dist;


		abreeTodas(g, N);
		via = dijkstra(g, N, chave - 1, fim, chave);
		resp_key_end = criaListaCaminho(g, chave - 1, fim -1, via);
		custo_key_end = g[fim - 1].dist;
		if(resp_key_end){
			NO * p = resp_ini_key;
			NO * ant = NULL;
			while(p){
				ant = p;
				p = p->prox;
			}
			ant->prox = resp_key_end->prox;
			resp_ini_end_key = resp_ini_key;
		}

	}

	free(via);
	destroiGrafo(g, N);

	if(custo1 <= custo_ini_key + custo_key_end)
		resp_final = resp_pr1;
	else
		resp_final = resp_ini_end_key;
	return resp_final;
}
