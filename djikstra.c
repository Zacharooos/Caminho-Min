// Versão completa
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INF 2147483647

typedef struct aresta{
	int v1;
	int v2;
	int peso;

}aresta;

typedef struct tabela{
    int dist;
    bool presenca;
}tabela;

//==============================================//
// QuickSort                                    //
//==============================================//

void swap(aresta *v, int i1, int i2){
    aresta aux = v[i1];
    v[i1] = v[i2];
    v[i2] = aux;
}

int particao(aresta *v, int iEsq, int iDir){ //Função Auxiliar partição, responsável
    int pivot = v[(iEsq+iDir)/2].v1; // Salva o valor do pivot, para fins comparativos.
    
    while (iEsq <= iDir){ // Laço que deslocará o marcador da esquerda para direita até achar um número >= ao pivot.
        while(v[iEsq].v1 < pivot){
            iEsq++;
        }
        
        while(v[iDir].v1 > pivot){ // Laço que deslocará o marcador da direita para esquerda até achar um número <= ao pivot.
            iDir--;
        }
        
        if (iEsq < iDir){ // Checa se o indíce da esquerda é menor que o da direita, se sim, realiza a troca.
            swap(v, iEsq, iDir);
            iEsq++;
            iDir--;
        } else {
            break; // Caso não seja, significa que todas as trocas pertinentes foram realizadas.
        }
    }
    return iDir; // Retorna o novo pivot.
}

void quicksort(aresta *v, int inicio, int fim){ //Função principal
    if (inicio < fim){
        int pivot = particao(v, inicio, fim); //Realiza uma sequencia de trocas e retorna e vetor para continuar a divisão.
        quicksort(v, inicio, pivot); // Realiza o mesmo processo até a primeira metade.
        quicksort(v, pivot + 1, fim); // Realiza o mesmo processo a partir da segunda metade.
        //Continua recursivamente até encontrar subvetores de tamanho 1.
    }
}


aresta* inicializarArestas(int numArestas){
	aresta *arestas = (aresta*) malloc (sizeof(aresta) * numArestas);
	for (int i = 0; i < numArestas; ++i){
		arestas[i].v1 = 0;
		arestas[i].v2 = 0;
		arestas[i].peso = 0;
	}
	return arestas;
}

void computarArestas(aresta *arestas, int numNodes, int numArestas){
	int vertice1 , vertice2, peso;

	for (int i = 0; i < numArestas; ++i){
		scanf("%d%d%d", &vertice1, &vertice2, &peso);

		arestas[i].v1 = vertice1;
		arestas[i].v2 = vertice2;
		arestas[i].peso = peso;
	}
	return;
}

void mostrarArestas(int numArestas, aresta *arestas){
    puts("=-=-= Inicio das arestas =-=-=");
	for (int i = 0; i < numArestas; ++i){
		printf("Aresta [%d] -> [%d] | peso = %d\n", arestas[i].v1, arestas[i].v2, arestas[i].peso); 
	}
	puts("=-=-= Fim das arestas =-=-=");
}

void mesmoPais(int numArestas, aresta *arestas){
    if (numArestas == 0){
        return;
    }

    for(int i = 0; i < numArestas; ++i){
        int j = 0;

        while (arestas[j].v1 != arestas[i].v2){
            j++;

            if(j > numArestas){
                break;
            }
        }

        while (arestas[j].v1 == arestas[i].v2){
            if (arestas[j].v2 == arestas[i].v1){
                arestas[i].peso = 0;
                arestas[j].peso = 0;
            }
            j++;

            if(j > numArestas){
                break;
            }
        }
    }
    
    return;
}

int menorDist(tabela *dadosDijkstra, int numNodes){
    int min = INF, menorIndex;

    for (int i = 0; i < numNodes;++i){
        if (dadosDijkstra[i].presenca == false && dadosDijkstra[i].dist <= min){
            min = dadosDijkstra[i].dist;
            menorIndex = i;
        }
    }

    return menorIndex;
}

int resultados(tabela *dadosDijkstra, int destino){
    if(dadosDijkstra[destino].dist == INF){
        printf("Nao e possivel entregar a carta\n");
    } else {
        printf("%d\n", dadosDijkstra[destino].dist);
    }
}

void dijkstra(struct aresta *arestas, int numArestas, int numNodes, int origem, int destino){
    tabela dadosDijkstra[numNodes]; 

    for (int i = 0; i < numNodes; ++i){
        dadosDijkstra[i].presenca = false;
        dadosDijkstra[i].dist = INF;
        dadosDijkstra[origem].dist = 0;
    }

    for (int i = 0; i < numNodes - 1; ++i){
        int menor = menorDist(dadosDijkstra, numNodes);
        dadosDijkstra[menor].presenca = true;

        for (int i = 0; i < numArestas; ++i){
            int v1 = arestas[i].v1;
            int v2 = arestas[i].v2;
            int peso = arestas[i].peso;

            if ( (dadosDijkstra[v1].dist != INF) && (dadosDijkstra[v1].dist + peso < dadosDijkstra[v2].dist) && (dadosDijkstra[v2].presenca == false)){
                dadosDijkstra[v2].dist = dadosDijkstra[v1].dist + peso;
            }
        }
    }
    resultados(dadosDijkstra, destino);
}

int main(){
	int numNodes, numArestas, numTestes, agm;
	scanf("%d%d", &numNodes, &numArestas);
	
	do {
        //printf("nodes= %d arestas = %d\n", numNodes, numArestas);
		aresta *arestas = inicializarArestas(numArestas);	
		computarArestas(arestas, numNodes, numArestas);
        quicksort(arestas, 0, numArestas-1);
        mesmoPais(numArestas, arestas);
		//mostrarArestas(numArestas, arestas);

        scanf("%d", &numTestes);
        for (int i = 0; i < numTestes; ++i){
            int origem, destino;
            scanf("%d%d", &origem, &destino);
            dijkstra(arestas, numArestas, numNodes+1, origem, destino);
        }
        puts("");
		scanf("%d%d", &numNodes, &numArestas);
	} while((numNodes != 0) || (numArestas != 0));
	return 0;
}
