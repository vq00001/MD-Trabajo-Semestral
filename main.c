#include "lectura_archivos.h"
#include "DFS.h"
#include "combinaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void imprimirGrafo(int** grafo, int* sizes, int numVertices){
	for (int i = 0; i < numVertices ; ++i){
		printf("%d:  ",i+1);
		for (int j = 0; j < sizes[i]; ++j){
			printf("%d  ",grafo[i][j]);
		}
		printf("\n");
	}
}

bool conexoSinVertices(int** grafo, int vertices[],int cant,int numVertices, int sizes[]){
	int aux[numVertices];
	for (int i = 0,j = 0; i < numVertices; ++i){
		if(i+1 == vertices[j]){
			aux[i] = 1;
			j++;
		}
		else{
			aux[i] = -j;
		}
		//printf("%d ", aux[i]);
	}

	// printf("vertices quitados: \n");
	// for (int i = 0; i < cant; ++i)
	// {
	// 	printf("%d ", vertices[i]);
	// }
	// printf("\n");

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
		resago2= 0;
		newGrafo[i-resago] = (int*)malloc(sizes[i]*sizeof(int));
		for (int j = 0; j < sizes[i]; ++j){
			if(aux[grafo[i][j]-1] == 1){
				resago2++;
				continue;
			}
			newGrafo[i-resago][j-resago2] = grafo[i][j] + aux[grafo[i][j]-1];
			newSizes[i-resago]++;
		}
	}
	// for (int i = 0; i < numVertices ; ++i)
	// {
	// 	printf("%d ", newSizes[i] );
	// }
	// printf("\n");

	// imprimirGrafo(newGrafo,newSizes,numVertices-cant);


	if (isConexo(numVertices-cant,newSizes,newGrafo,0) == 0){
		// printf("no fue conexo\n");
		liberarMatriz(newGrafo,numVertices-cant);
		return false;
	}
	// printf("o hasta aca quiza\n");
	liberarMatriz(newGrafo,numVertices-cant);
	return true;

}

bool kConexo(int** grafo,int k, int numVertices, int* sizes){
	int numComb = numCombinaciones(k,numVertices);
    int** m = encontrarCombinaciones( numVertices, k,numComb);
    for (int i = 0; i < numComb ; ++i){
    	if (!conexoSinVertices(grafo,m[i],k,numVertices,sizes)){
    		return false;
    	}
    }
    return true;

}


void evaluar_conectividad(const char* filename){

	char *content = readFile(filename);

    if (content != NULL) {

        printf("\nContenido:\n%s\n", content);  // Mostrar contenido del archivo (Solo para pruebas)
	
        int numLines;
        char **lines = splitLines(content, &numLines); 	// Dividir el contenido del archivo en líneas

        if (lines != NULL) {
            int n;
            int *sizes = NULL;  // Array para almacenar los tamaños de cada subarreglo
            int **array = createArray(lines, numLines, &n, &sizes); // Crear el array de adyacencia
			int k = 0;

			printf("\nIngrese el valor de la conexidad a evaluar: k = ");
			scanf("%d",&k);
    
			// inciar el reloj para calcular el tiempo de ejecución
            clock_t start_time = clock();

			if(kConexo(array,k,n,sizes)) printf("soy %d-conexo!\n", k+1 );
            else printf("El grafo no es %d-conexo.\n", k + 1);

            clock_t end_time = clock();
            double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

			printf("--------------------\n");
            printf("<Tiempo de ejecucion: %f segundos>\n\n", time_spent);
        }
    }

}

void evaluar_conexidad(const char* filename){

	char *content = readFile(filename);

    if (content != NULL) {

        printf("\nContenido:\n%s\n", content);  // Mostrar contenido del archivo (Solo para pruebas)
	
        int numLines;
        char **lines = splitLines(content, &numLines); 	// Dividir el contenido del archivo en líneas

        if (lines != NULL) {
            int n;
            int *sizes = NULL;  // Array para almacenar los tamaños de cada subarreglo
            int **array = createArray(lines, numLines, &n, &sizes); // Crear el array de adyacencia
	 		
            
			// inciar el reloj para calcular el tiempo de ejecución
            clock_t start_time = clock();
			int result = isConexo(n, sizes, array, 0);
            clock_t end_time = clock();
            double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;


            if( result == 0) {
				printf("\n Resultado: El grafo no es conexo. %d\n", result);
			}
			else {
				printf("\n Resultado: El grafo es conexo.\n");
			}

			printf("--------------------\n");
            printf("<Tiempo de ejecucion: %f segundos>\n\n", time_spent);
        }
    }
}


int main(int argc, char const *argv[]){


	printf("                 MENU                  \n");
	printf("Seleccionar consulta a realizar: \n");
	printf(" 1) Evaluar conectividad\n");
	printf(" 2) Evaluar conexidad\n");
	printf(" 3) Calcular grado maximo\n");
	printf(" 4) Calcular grado minimo\n");

	int opcion;
	scanf("%d",&opcion);

    for (int i = 1; i < argc; i++) {
		printf("\n############ %s ############\n", argv[i]);

		switch(opcion){
			case 1:
				evaluar_conectividad(argv[i]);
				break;
			case 2:
				evaluar_conexidad(argv[i]);
				break;
			case 3:
				printf("Calcular grado maximo\n");
				break;
			case 4:
				printf("Calcular grado minimo\n");
				break;
			default:
				printf("Opcion no valida\n");
				break;
		}

	}

	return 0;
}