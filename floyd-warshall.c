#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INF 9999

// Função que inicializa a matriz
int **inicializarMatriz(int numVertices, int numArestas){
    int **matriz;
    matriz = malloc(numVertices * sizeof(int *));
    
    for (int i = 0; i < numVertices; i++){
        matriz[i] = malloc(numVertices * sizeof(int));
    }

    // "Zera a matriz"
    for(int i = 0; i < numVertices; ++i){
        for(int j = 0; j < numVertices; ++j){
            if (i == j){
                matriz[i][j] = 0;
            } else {
                matriz[i][j] = INF;
            }
        }
    }

    return matriz;
}


// Função que registra so vértices na matriz
void registrarArestas(int numVertices, int numArestas, int** matriz ){
    int vertice1, vertice2, peso;
    
    for(int i = 0; i < numArestas; ++i){
        scanf("%d%d%d", &vertice1, &vertice2, &peso);
        vertice1--;
        vertice2--;

        //printf("aresta %d -> %d , peso = %d\n", vertice1, vertice2, peso);
        matriz[vertice1][vertice2] = peso;
    }
}

// Função que percorre a matriz
void mostrarMatriz(int numVertices, int** matriz ){
    puts("=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    for(int i = 0; i < numVertices; ++i){
        for(int j = 0; j < numVertices; ++j){
            printf("%d ", matriz[i][j]);
        }
        puts("");
    }
    puts("=-=-=-=-=-=-=-=-=-=-=-=-=-=");
}

// Função que mostra os testes caso a caso
void mostrarTestes(int numTestes, int **matriz){
    int vertice1, vertice2;
    for (int i = 0; i < numTestes; i++){
        scanf("%d%d", &vertice1, &vertice2);
        
        int dist = matriz[vertice1-1][vertice2-1];
        if(dist == INF){
            puts("Nao e possivel entregar a carta");
        } else {
            printf("%d\n", dist);
        }
    }

}

// Função que determina se duas cidades são do mesmo país
void mesmoPais(int numVertices, int** matriz){
    for(int i = 0; i < numVertices; ++i){
        for(int j = 0; j < numVertices; ++j){
            if (matriz[i][j] != INF && matriz[j][i] != INF){
                matriz[i][j] = 0;
                matriz[j][i] = 0;
            }
        }
    }
}

// Função de calculo de caminho mínimo
void floydWarshall(int numVertices, int** matriz){
    for(int k = 0; k < numVertices; ++k){
        for(int j = 0; j < numVertices; ++j){
            for(int i = 0; i < numVertices; ++i){
                if (matriz[j][k] + matriz[k][i] < matriz[j][i]){
                    matriz[j][i] = matriz[j][k] + matriz[k][i];
                }
            }
        }
    }
}

// Função de desalocar a matriz
void desalocarMatriz(int numVertices, int** matriz){
    for(int i = 0; i < numVertices; ++i){
        free(matriz[i]);
    }
    free(matriz);
}

int main(){
    int numVertices, numArestas, numTestes;
    int** matriz;

    scanf("%d%d", &numVertices, &numArestas);

    while ((numVertices != 0) || (numArestas != 0)){
        matriz = inicializarMatriz(numVertices, numArestas);

        //puts("pre-registro");
        //mostrarMatriz(numVertices, matriz);

        registrarArestas(numVertices, numArestas, matriz);
        
        //puts("pos-registro");
        //mostrarMatriz(numVertices, matriz);

        mesmoPais(numVertices, matriz);
        floydWarshall(numVertices, matriz);

        //puts("pos-FW");
        //mostrarMatriz(numVertices, matriz);
        
        scanf("%d", &numTestes);
        mostrarTestes(numTestes, matriz);
        
        desalocarMatriz(numVertices, matriz);
        puts("");

        scanf("%d%d", &numVertices, &numArestas);
    }
    return 0;
}