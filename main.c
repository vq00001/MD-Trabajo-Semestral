#include "lectura_archivos.h"
#include "DFS.h"
#include "combinaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/**
 * Funcion para imprimir un grafo
 * @param grafo Matriz de adyacencia
 * @param sizes Tamaños de los subarreglos
 * @param numVertices Cantidad de vertices
 */
void imprimirGrafo(int** grafo, int* sizes, int numVertices){
	for (int i = 0; i < numVertices ; ++i){
		printf("%d:  ",i+1);
		for (int j = 0; j < sizes[i]; ++j){
			printf("%d  ",grafo[i][j]);
		}
		printf("\n");
	}
}

/**
 * Funcion para evaluar la conectividad de un grafo sin un conjunto de vertices
 * @param grafo Matriz de adyacencia
 * @param vertices Vertices a quitar
 * @param numVertices Cantidad de vertices
 * @param sizes Tamaños de los subarreglos
 */
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

/**
 * Funcion para evaluar la conectividad de un grafo
 * @param grafo Matriz de adyacencia
 * @param k Numero de vertices a quitar
 * @param numVertices Cantidad de vertices
 * @param sizes Tamaños de los subarreglos
 */

bool kConexo(int** grafo, int k, int numVertices, int* sizes){
	if (k ==  0) return true;
	int numComb;
    int** m ;
    if (isConexo(numVertices,sizes,grafo,0)==0) return false;
    for (int i = 1; i < k	; ++i)   {
    	numComb = numCombinaciones(i,numVertices);
        m = encontrarCombinaciones(numVertices, i, numComb);
        for (int j = 0; j < numComb ; ++j){
	    	if (!conexoSinVertices(grafo,m[j],i,numVertices,sizes)){
	    		return false;
	    	}
	    }
	    liberarMatriz(m,numComb);
    }
    return true;
}
int buscarConectividad(int** grafo,  int numVertices, int* sizes){
	for (int i = 0; i < numVertices; ++i)
	{
		if(!kConexo(grafo,i,numVertices,sizes)){
			return i-1;
		}
	}
}

/**
 * Funcion para llamar a la funcion que evalua la conectividad de un grafo 
 * @param filename Nombre del archivo a leer
 */

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
    		
	    		// inciar el reloj para calcular el tiempo de ejecución
	        clock_t start_time = clock();

				printf("Mi conectividad	es %d!\n", buscarConectividad(array,n,sizes));
	         

	        clock_t end_time = clock();
	        double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

			printf("--------------------\n");
	        printf("<Tiempo de ejecucion: %f segundos>\n\n", time_spent);
    		
		
        }
    }

}

void consultarKConexo(const char* filename){

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
    		if ( k >= n ) printf("	Eso no tendria mucho sentido...\n");
    		else{
	    			// inciar el reloj para calcular el tiempo de ejecución
	            clock_t start_time = clock();

				if(kConexo(array,k ,n,sizes)) printf("soy %d-conexo!\n", k);
	            else printf("El grafo no es %d-conexo.\n", k);
	           

	            clock_t end_time = clock();
	            double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

				printf("--------------------\n");
	            printf("<Tiempo de ejecucion: %f segundos>\n\n", time_spent);
    		}
			
        }
    }

}

/**
 * Funcion para evaluar la conexidad de un grafo
 * @param filename Nombre del archivo a leer 
*/

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


/**
 * Funcion para calcular el grado minimo o maximo de un grafo
 * @param filename Nombre del archivo a leer 
 * @param min 1 para minimo, 0 para maximo
*/
void calc_grado_minimo_maximo(const char* filename, int min){ 


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
			
			int minimo = sizes[0];
			int maximo = sizes[0];

			for(int i = 0; i < n; i++) {
				
				if (sizes[i] < minimo) {
					minimo = sizes[i];

				}
				if (sizes[i] > maximo) {
					maximo = sizes[i];
				}
			}

            clock_t end_time = clock();
            double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;


			if (min == 1) printf("\nGrado minimo del grafo: %d\n", minimo);
			else printf("\nGrado maximo del grafo: %d\n", maximo);

			printf("--------------------\n");
            printf("<Tiempo de ejecucion: %f segundos>\n\n", time_spent);
			
		}
	}
}



int main(int argc, char const *argv[]){

	while (1) {
		printf("                 MENU                  \n");
		printf("Seleccionar consulta a realizar: \n");
		printf(" 1) Evaluar conectividad\n");
		printf(" 2) Evaluar conexidad\n");
		printf(" 3) Calcular grado maximo\n");
		printf(" 4) Calcular grado minimo\n");
		printf(" 5) Consultar por k conexidad\n");	
		printf(" Escriba 'exit' o 'return' para salir\n");

		char input[10];
		scanf("%s", input);

		if (strcmp(input, "exit") == 0 || strcmp(input, "return") == 0) {
			printf("Saliendo del programa...\n");
			break;
		}

		int opcion = atoi(input);

		if (opcion < 1 || opcion > 5) {
			printf("Opción no válida\n");
			continue;
		}

		for (int i = 1; i < argc; i++) {
			printf("\n############ %s ############\n", argv[i]);

			switch (opcion) {
				case 1:
					evaluar_conectividad(argv[i]);
					break;
				case 2:
					evaluar_conexidad(argv[i]);
					break;
				case 3:
					calc_grado_minimo_maximo(argv[i], 0);
					break;
				case 4:
					calc_grado_minimo_maximo(argv[i], 1);
					break;
				case 5: 
					consultarKConexo(argv[i]);
					break;
				default:
					printf("Opcion no valida, para salir escriba exit\n");
					break;
			}
		}
	}
	return 0;
}