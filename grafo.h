struct Grafo{
    int id;
    int n_arestas;
    struct Aresta *arestas;    
};
typedef struct Grafo grafo;

struct Aresta{
    int peso;
    int id_vizinho;
    struct Aresta *proximo;
};
typedef struct Aresta aresta;


grafo *criar_grafo(int n_vertices){
    grafo *gr = (grafo*)malloc(n_vertices*sizeof(grafo));
    for (int i = 0; i < n_vertices; ++i){
        gr[i].id = i;
        gr[i].n_arestas = 0;
        gr[i].arestas = (aresta*)malloc(n_vertices*sizeof(aresta));
    }
    return gr;
}

aresta* inserir_aresta(int *n_arestas, int id_vizinho, int peso){
    aresta *novo;
    novo->id_vizinho = id_vizinho;
    novo->peso = peso;
    n_arestas += 1;
    return novo;
}

void mostrar(aresta a[], int n_vertices){
    for(int i = 0; i < n_vertices; ++i){
        printf("\tvizinho-> %d, peso-> %d\n", a[i].id_vizinho,a[i].peso);
    }
}