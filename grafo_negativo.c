#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
// Referências: https://programacaodescomplicada.wordpress.com/2014/08/21/ed1-aula-65-grafos-busca-pelo-menor-caminho/
// 				https://www.youtube.com/watch?v=5y8dch2uHR4&feature=youtu.be

int menorDistancia(int *dist, int *visitado, int nv){
	int i, menor = -1, primeiro = 1;
	for (i = 0; i < nv; ++i){
		if (dist[i]>=0 && visitado[i]==0){
			if(primeiro){
				menor = i;
				primeiro = 0;
			}else{
				if(dist[menor]>dist[i]){
					menor = i;
				}
			}
		}
	}
	return menor;
}

void menorCaminho(grafo *gr, int ini, int *ant, int *dist, int nv){
	int i, cont, ind, *visitado, u;
	cont = nv;
	visitado = (int*) malloc(nv*sizeof(int));
	for (i = 0; i < nv; ++i){
		ant[i] = -1;
		dist[i] = -1;
		visitado[i] = 0;
	}
	dist[ini] = 0;
	while(cont>0){
		u = menorDistancia(dist,visitado,nv);
		if(u==-1)
			break;

		visitado[u] = 1;
		cont--;
		for(i=0; i<gr[u].n_arestas; i++){
			ind = gr[u].arestas[i].id_vizinho;
			if(dist[ind]<0){
				dist[ind] = dist[u]+gr[u].arestas[i].peso;
				ant[ind] = u;
			}
			else{
				if(dist[ind]>dist[u]+gr[u].arestas[i].peso){
					dist[ind] = dist[u]+gr[u].arestas[i].peso;
					ant[ind] = u;
				}
			}
		}
	}
	free(visitado);
}

int main(){
	int nv=0;
	FILE *arq;
	arq = fopen("grafo_negativo.txt", "r");

	//No arquivo, cada linha representa um vértice do grafo
	//aqui conta a quantidade de linhas, ou seja, o num de vértices
	char c = fgetc(arq);
	while(c!=EOF){
		if(c=='\n')
			nv++;
		c = fgetc(arq);
	}
	rewind(arq);

	grafo *gr = criar_grafo(nv);

	//Aqui cria as arestas entre os grafos. No arquivo dois números representam uma arestas,
	//o vizinho que o vértice da linha está conectado, e o peso da arestas.
	//Em uma linha, a cada dois números, representa uma aresta que sai daquele grafo
	int i=0, id=0, id_vizinho, peso;
	do{
		fscanf(arq,"%d %d%c",&id_vizinho,&peso,&c);
		gr[i].arestas[id].id_vizinho = id_vizinho;
		gr[i].arestas[id].peso = peso;
		gr[i].n_arestas += 1;
		id++;
		if(c=='\n'){
			i++;
			id = 0;
		}
	}while(i<nv);

	printf("Vertices S=0, A=1, B=2\n");
	for (int i = 0; i < nv; ++i){
		printf("Vertice %d, numero de arestas: %d\n", i, gr[i].n_arestas);
		mostrar(gr[i].arestas,gr[i].n_arestas);
		printf("\n");
	}

	int ant[nv]; int dist[nv];
	menorCaminho(gr, 0, ant, dist, nv);
	printf("Vertices S=0, A=1, B=2\n");
	printf("Saindo de S\n");
	for (int i = 0; i < nv; ++i){
		printf("Vertice[%d] -> %d\n", i, dist[i]);
	}
	printf("\nSaindo de A\n");
	menorCaminho(gr, 1, ant, dist, nv);
	for (int i = 0; i < nv; ++i){
		printf("Vertice[%d] -> %d\n", i, dist[i]);
	}
	printf("\nSaindo de B\n");
	menorCaminho(gr, 2, ant, dist, nv);
	for (int i = 0; i < nv; ++i){
		printf("Vertice[%d] -> %d\n", i, dist[i]);
	}

	for (int i = 0; i < nv; ++i){
		free(gr[i].arestas);
	}
	free(gr);
	return 0;
}