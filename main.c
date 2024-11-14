#include "lectura_archivos.h"
#include "DFS.h"
#include "combinaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




bool conexoSinVertices(int** grafo, int vertices[],int cant,int numVertices, int sizes[]){
	int aux[numVertices];
	for (int i = 0,j = 0; i < numVertices; ++i){
		if(i == vertices[j]){
			aux[i] = 1;
			j++;
		}
		else{
			aux[i] = -j;
		}
	}
	int resago=0;
	int resago2 = 0;
	int newSizes[numVertices-cant];
	for (int i = 0; i < numVertices-cant ; ++i){
		newSizes[i] = 0;
	}
	int** newGrafo = (int**)malloc((numVertices-cant)*sizeof(int*));
	for (int i = 0; i < numVertices; ++i){
		if(aux[i] == 1){
			resago++;
			continue;
		}
		newGrafo[i-resago] = (int*)malloc(sizes[i]*sizeof(int));
		for (int j = 0; j < sizes[i]; ++j){
			if(aux[grafo[i][j]] == 1){
				resago2++;
				continue;
			}
			newGrafo[i-resago][j-resago2] = grafo[i][j] + aux[grafo[i][j]];
			newSizes[i-resago]++;
		}
	}
	if (exec_DFS(numVertices-cant,newSizes,newGrafo,0) == 0){
		liberarMatriz(newGrafo,numVertices-cant);
		return false;
	}
	liberarMatriz(newGrafo,numVertices-cant);
	return true;

}

bool kConexo(int** grafo,int k, int numVertices, int* sizes){
	int numComb = numCombinaciones(k,numVertices);
    int** m = encontrarCombinaciones( numVertices, k,numComb);
    for (int i = 0; i < numComb ; ++i){
    	if (conexoSinVertices(grafo,m[i],k,numVertices,sizes)){
    		return false;
    	}
    }
    return true;

}

int main(int argc, char const *argv[]){
	const char *filename = "ejemplo.csv";  // Nombre del archivo a leer
    char *content = readFile(filename);

    if (content != NULL) {
        printf("Contenido:\n%s\n", content);  // Mostrar contenido del archivo (Solo para pruebas)

        int numLines;
        char **lines = splitLines(content, &numLines);

        if (lines != NULL) {
            int n;
            int *sizes = NULL;  // Array para almacenar los tamaños de cada subarreglo
            int **array = createArray(lines, numLines, &n, &sizes);
            printf("llegue a salvo\n");
        }
    }

	return 0;
}