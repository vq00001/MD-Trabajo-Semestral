// dfs.h

#ifndef DFS_H
#define DFS_H

#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un nodo de la lista de adyacencia
struct Node {
    int dest;                                   // index de la lista visitados        
    struct Node* next;
};

// Estructura para representar la lista de adyacencia
struct AdjList {
    struct Node* head;
};

// Declaraciones de funciones
struct Node* createNode(int dest);

void DFSRec(struct AdjList adj[], int visited[], int s);

int* DFS(struct AdjList adj[], int V, int s);

void addEdge(struct AdjList adj[], int e, int v);

int** format_input(int nodos, int* sizes, int** array, int* E, int* malloc_size_ptr);

int isConexo(int nodos, int* sizes, int** array, int source);

#endif
