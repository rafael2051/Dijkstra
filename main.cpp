#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.cpp"

typedef struct {
	int inicio;
	int fim;
	int chave;
	int * aberto;
} TESTE;


TESTE * inicializaTestes(FILE * f, int * N, int * A, int * qtd, int * ijpeso){
	printf("Insercao das arestas em ijpeso[]:\n");
	for(int i = 0;i < 3 * (*A);i += 3){
		fscanf(f, "%d %d %d\n", 
			&ijpeso[i], &ijpeso[i + 1], &ijpeso[i + 2]);
		printf("%d %d %d\n", ijpeso[i], ijpeso[i + 1], ijpeso[i + 2]);
	}
	printf("\n");
	fscanf(f, "%d\n", qtd);
	TESTE * testes = (TESTE *)malloc(sizeof(TESTE) * (*qtd));
	for(int i = 0;i < (*qtd);i++){
		fscanf(f, "%d %d %d ", &testes[i].inicio, &testes[i].fim, &testes[i].chave);
		testes[i].aberto = (int *)malloc(sizeof(int) * (*N));
		for(int j = 0;j < (*N);j++){
			fscanf (f, "%d", &testes[i].aberto[j]);
		}
	}
	return testes;

}

void imprimeResposta(NO * resposta, int ini, int fim){
	NO * p = resposta;

	if(p){
		printf("O caminho mais curto de %d ate %d e: ", ini, fim);
		while(p){
			printf("%d", p->adj);
			if(p->prox)
				printf(" -> ");
			p = p->prox;
		}
		printf("\n\n");
	}
	else{
		printf("Bem nao ha caminho de %d ate %d.\n\n", ini + 1, fim + 1);
	}
}


void imprimeTeste(TESTE * testes, int N, int i){
	printf("*Teste %d*******\n", i + 1);
	printf("Inicio: %d\n", testes[i].inicio);
	printf("Fim: %d\n", testes[i].fim);
	printf("Chave: %d\n", testes[i].chave);
	printf("Salas trancadas: ");
	for(int j = 0;j < N;j++)
		if(!testes[i].aberto[j])
			printf("%d ", j + 1);
	printf("\n");
}


int main(int argc, char ** argv) {
	if(argc < 2) {
		puts("ERRO! Falta de argumentos.");
		exit(1);
	}
	FILE * f = fopen(argv[1], "r");
	if(!f){
		puts("ERRO! Arquivo nao encontrado.");
		exit(1);
	}


	int count = 0;
	int N, A, qtd_testes;
	fscanf(f, "%d %d\n", &N, &A);
	int * ijpeso = (int *)malloc(sizeof(int) * A * 3);


	TESTE * testes = inicializaTestes(f, &N, &A, &qtd_testes, ijpeso);

	printf("qtd_testes: %d\n\n", qtd_testes);
	NO * lista_caminho = NULL;

	for(int i = 0;i < N;i++){

		imprimeTeste(testes, N, i);
		lista_caminho = caminho(N, A, ijpeso, testes[i].aberto, 
			testes[i].inicio, testes[i].fim, testes[i].chave);
		imprimeResposta(lista_caminho, testes[i].inicio, testes[i].fim);
	}

	fclose(f);

	return 0;
}