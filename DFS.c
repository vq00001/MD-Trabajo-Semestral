#include <stdio.h>
#include <stdlib.h>



/**
 * Estructura para representar un nodo de la lista de adyacencia
 */
struct Node {
    int dest;                                   // index de la lista visitados        
    struct Node* next;
};

/** 
 * Estructura para representar la lista de adyacencia
 */
struct AdjList {
    struct Node* head;
};


/**
 * Funcion para crear un nuevo nodo de lista de aydacencia
 * @param dest Destino del nodo
 * @return Puntero al nuevo nodo
 */
struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));  // crear un puntero a un nuevo nodo
    newNode->dest = dest;                                              // asignar el destino al nodo                             
    newNode->next = NULL;                                              // el siguiente nodo es nulo                            
    return newNode;
}


/**
 * Funcion para recorrer el grafo con DFS
 * @param adj Lista de adyacencia
 * @param visited Arreglo de nodos visitados
 * @param s Nodo fuente
 * @return visited Arreglo de nodos visitados
 */
void DFSRec(struct AdjList adj[], int visited[], int s) {
    
    // Marcar el nodo como visitado
    visited[s] = 1;

    // Imprimir el nodo actual
    // printf("%d ", s);

    // Pasar por los nodos que no han sido visitados
    struct Node* current = adj[s].head;                 // buscar el nodo actual en la lista
    while (current != NULL) {                           
        int dest = current->dest;                       
        if (!visited[dest]) {                           // si el nodo al que apunta el nodo actual no ha sido visitado
            DFSRec(adj, visited, dest);
        }
        current = current->next;                        // pasar al siguiente nodo
    }
}

// Funcion principal, inicializa el arreglo visited y llama a DEFRec
/**
 * Funcion para ejecutar DFS
 * @param adj Lista de adyacencia
 * @param V Cantidad de nodos
 * @param s Nodo fuente
 * @return visited Arreglo de nodos visitados
 */
int* DFS(struct AdjList adj[], int V, int s) {
    

    int* visited = malloc (sizeof (int) * V); 
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    DFSRec(adj, visited, s);

    // Liberar memoria

    for (int i = 0; i < V; i++) {
        struct Node* current = adj[i].head;
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return visited;
}

/**
 * Funcion para agregar una arista a una lista de adyacencia
 * @param adj Lista de adyacencia
 * @param e Nodo de inicio
 * @param v Nodo de destino
*/ 
void addEdge(struct AdjList adj[], int e, int v) {

    // agregar nodo de s a t a la lista de adyacencia
    struct Node* newNode = createNode(v);               
    newNode->next = adj[e].head;                        
    adj[e].head = newNode;

    // Para grafos no dirigidos, agregar nodo de t a s a la lista de adyacencia
    newNode = createNode(e);
    newNode->next = adj[v].head;
    adj[v].head = newNode;
}

/**
 * Funcion para formatear la entrada
 * @param nodos Cantidad de nodos
 * @param sizes Cantidad de nodos adyacentes
 * @param array Nodos adyacentes
 * @param E Puntero a la cantidad de aristas 
 * @param malloc_size_ptr puntero al tamaño del alocado del arreglo de aristas
 * @return Puntero al arreglo 2D de aristas de las aristas del grafo
*/

int** format_input(int nodos, int* sizes, int** array, int* E, int* malloc_size_ptr) {
    
    // alocar memoria para arreglo de aristas
    int edges_size = nodos;
    int** edges = malloc(sizeof(int*) * (edges_size)); 

    for(int i = 0; i < (edges_size); i++){ 
        edges[i] = malloc(sizeof(int) * 2);
    }

    int edge_counter = 0;

    if (array != NULL && sizes != NULL) {
        for (int i = 0; i < nodos; i++) {
            if (array[i] != NULL && sizes[i] > 0) {
                for (int j = 0; j < sizes[i]; j++) {
                    
                    // agregar arista al arreglo de aristas
                    
                    edges[edge_counter][0] = i;
                    edges[edge_counter][1] = array[i][j]-1;
                    edge_counter++;

                    if (edge_counter >= (edges_size)) {
                        
                        // redimensionar el arreglo de aristas al doble
                        (edges_size) *= 2;
                        edges = realloc(edges, sizeof(int*) * (edges_size));
                        
                        for(int i = edge_counter; i < edges_size; i++){ 
                            edges[i] = malloc(sizeof(int) * 2);
                        }
                    }
                }

            } 
        }
    }
    for (int i = 0; i < edge_counter; ++i)
    {
       printf("(%d.. %d)  ",edges[i][0], edges[i][1]);
    }
    (*malloc_size_ptr) = edges_size; // guardar el tamaño del arreglo de aristas para liberar la memoria despues
(*E) = edge_counter;                 // guardar la cantidad de aristas  

    return edges;                    // retornar arreglo de aristas
}

/**
* Funcion para ejecturar DFS
* @param nodos Cantidad de nodos
* @param sizes Cantidad de nodos adyacentes
* @param array Nodos adyacentes
* @param source Nodo de inicio
* @return Arreglo de nodos visitados
*/ 


int exec_DFS(int nodos, int* sizes, int** array, int source){
    int V = nodos; // cant nodos
    int E = 0; // cant aristas
    int malloc_size = 0; // tamaño de la memoria alocada para edges
    int** edges = format_input(nodos, sizes, array, &E, &malloc_size);

    if(1 < nodos){
        for (int i = 0; i < nodos ; ++i)
        {
           if (sizes[i] == 0) return 0;
        }
    }

    struct AdjList adj[V];

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; i++) {
        adj[i].head = NULL;
    }
    
    for (int i = 0; i < E; i++) {
        addEdge(adj, edges[i][0], edges[i][1]);
    }

    // printf("DFS from source: %d\n", source);

    int* visited = DFS(adj, V, source);

    int conexo = 1;
    for(int i = 0; i < V; i++){ 
        if (visited[i] == 0) {
            conexo = 0;
            break;
        }
    }


    // Liberar memoria
    free(visited);

    for(int i = 0; i < malloc_size; i++){ 
        free(edges[i]);
    }
    free(edges);

    return conexo;
}
/*
int main() {
    int sizes[5] = {2, 3, 2, 1, 0};

    int** array = malloc(sizeof(int*) * 5);
    for(int i = 0; i < 5; i++){ 
        array[i] = malloc(sizeof(int) * sizes[i]);
    }

    int temp0[] = {1, 2};
    int temp1[] = {0, 2, 3};
    int temp2[] = {0, 2};
    int temp3[] = {1};
    int temp4[] = {};

    for (int i = 0; i < sizes[0]; i++) {
        array[0][i] = temp0[i];
    }
    for (int i = 0; i < sizes[1]; i++) {
        array[1][i] = temp1[i];
    }
    for(int i = 0; i < sizes[2]; i++) {
        array[2][i] = temp2[i];
    }
    for(int i = 0; i < sizes[3]; i++) {
        array[3][i] = temp3[i];
    }
    for(int i = 0; i < sizes[4]; i++) {
        array[4][i] = temp4[i];
    }

    int source = 0;
    printf("conexo?: %d", exec_DFS(5, sizes, array, source));

    for(int i = 0; i < 5; i++){ 
        free(array[i]);
    }
    free(array);
    return 0;
}
*/
