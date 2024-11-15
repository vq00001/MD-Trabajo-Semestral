#include <stdio.h>
#include <stdlib.h>
long long factSimpl(int a, int b){
	if(a==b)return 1;
	return a*factSimpl(a-1,b);
}

long long fact(int a){
    if(a==1) return 1;
    return a*fact(a-1);

}
void liberarMatriz(int** matriz, int filas) { 
    for (int i = 0; i < filas; i++) { 
        free(matriz[i]);
    } 
    free(matriz);
}

int numCombinaciones(int cantPorGrupo,int total){
	int n;
	if (cantPorGrupo > total-cantPorGrupo){
		n = factSimpl(total,cantPorGrupo);
		return n/fact(total-cantPorGrupo);
	}
	else {
		n = factSimpl(total,total-cantPorGrupo);
		return n/fact(cantPorGrupo);
	}
}


// Función recursiva para encontrar todas las combinaciones posibles de tamaño r en arr[]
void combinar( int n, int r, int indice, int datos[], int i,int* numComb,int** matriz) {
    // Cuando se consigue una combinación de tamaño r, imprimirla
    if (indice == r) {
        for (int i = 0; i < r; ++i){
           matriz[*numComb][i] = datos[i];
        }
        *numComb = *numComb + 1;
        return;
    }

    // Cuando no quedan más elementos para poner en datos[]
    if (i >= n) {
        return;
    }

    // Incluir el elemento actual en el conjunto de datos[] y mover al siguiente índice
    datos[indice] = i+1;
    combinar( n, r, indice + 1, datos, i + 1,numComb,matriz);

    // Excluir el elemento actual y mover al siguiente
    combinar( n, r, indice, datos, i + 1,numComb,matriz);
}

// Función principal que encuentre todas las combinaciones de tamaño r
int** encontrarCombinaciones( int n, int r, int numCombinaciones) {
    // Un arreglo temporal para guardar las combinaciones
    int datos[r];
    int i = 0;
    int** combinaciones= (int**)malloc(numCombinaciones*sizeof(int*));
    for (int i = 0; i < numCombinaciones; ++i){
        combinaciones[i] = (int*)malloc(r*sizeof(int));
    }
    combinar( n, r, 0, datos, 0,&i,combinaciones);
    return combinaciones;
}
/*
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int r = 4;
    printf("Todas las combinaciones de tamaño %d en el arreglo son:\n", r);
    int numComb = numCombinaciones(r,6);
    int** m = encontrarCombinaciones( 6, r,numComb);
    for (int i = 0; i < numComb; ++i){
        printf("a\n");
        for (int j = 0; j < r; ++j){
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    liberarMatriz(m,numComb);

    return 0;
}
*/