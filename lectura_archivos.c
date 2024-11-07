#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#define access _access
#else
#include <unistd.h>
#endif

#ifndef F_OK
#define F_OK 0
#endif

/**
 * Función para leer un archivo y mostrar su contenido.
 * @param filename Nombre del archivo a leer.
 */
char *readFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        printf("Código de error: %d\n", errno);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == -1) {
        perror("Error al determinar el tamaño del archivo");
        fclose(file);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Error en la asignación de memoria");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("Error al leer el archivo");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[fileSize] = '\0';

    fclose(file);
    return buffer;
}

/**
 * Función para dividir el contenido de un archivo en líneas.
 * @param content Contenido del archivo.
 * @param numLines Puntero al número de líneas.
 * @return Array de líneas.
 */
char **splitLines(const char *content, int *numLines) {
    char *contentCopy = strdup(content);
    if (contentCopy == NULL) {
        perror("Error en la duplicación de contenido");
        return NULL;
    }

    int linesCount = 0;
    char *temp = contentCopy; // Usar un puntero temporal para no modificar el original
    while (*temp) {
        if (*temp == '\n') {
            linesCount++;
        }
        temp++;
    }
    linesCount++; // Para la última línea si no termina en '\n'

    char **lines = (char **)malloc(linesCount * sizeof(char *));
    if (lines == NULL) {
        perror("Error en la asignación de memoria");
        free(contentCopy);
        return NULL;
    }

    int index = 0;
    char *line = strtok(contentCopy, "\n");
    while (line != NULL) {
        lines[index++] = strdup(line);
        line = strtok(NULL, "\n");
    }

    *numLines = linesCount;
    free(contentCopy);
    return lines;
}

/**
 * Función para crear el arreglo bidimensional de los vectores leídos.
 * @param lines Array de líneas del archivo.
 * @param numLines Número de líneas.
 * @param n Puntero al número de subarreglos.
 * @param sizes Puntero a un array donde se almacenarán los tamaños de cada subarreglo.
 * @return Arreglo bidimensional de enteros.
 */
int **createArray(char **lines, int numLines, int *n, int **sizes) {
    *n = atoi(lines[0]); // Leer el número de subarreglos de la primera línea
    int **array = (int **)malloc(*n * sizeof(int *));
    *sizes = (int *)malloc(*n * sizeof(int));
    if (array == NULL || *sizes == NULL) {
        perror("Error en la asignación de memoria");
        return NULL;
    }

    // Inicializar cada subarreglo a NULL y tamaño 0 para evitar problemas de memoria
    for (int i = 0; i < *n; i++) {
        array[i] = NULL;
        (*sizes)[i] = 0;
    }

    for (int i = 1; i < numLines; i++) {  // Empezar desde la segunda línea
        char *lineCopy = strdup(lines[i]);
        char *token = strtok(lineCopy, ", ");
        int index = atoi(token) - 1;  // Leer el índice inicial de la línea
        int count = 0;

        int *subArray = NULL;
        while ((token = strtok(NULL, ", ")) != NULL) {
            subArray = realloc(subArray, (count + 1) * sizeof(int));
            subArray[count++] = atoi(token);
        }

        array[index] = subArray;
        (*sizes)[index] = count;
        free(lineCopy);
    }

    return array;
}

int main() {
    const char *filename = "../ejemplo.csv";  // Nombre del archivo a leer
    char *content = readFile(filename);

    if (content != NULL) {
        printf("Contenido:\n%s\n", content);  // Mostrar contenido del archivo (Solo para pruebas)

        int numLines;
        char **lines = splitLines(content, &numLines);

        if (lines != NULL) {
            int n;
            int *sizes = NULL;  // Array para almacenar los tamaños de cada subarreglo
            int **array = createArray(lines, numLines, &n, &sizes);

            if (array != NULL && sizes != NULL) {
                // Imprimimos el array
                for (int i = 0; i < n; i++) {
                    printf("Array %d: ", i + 1);
                    if (array[i] != NULL && sizes[i] > 0) {
                        for (int j = 0; j < sizes[i]; j++) {
                            printf("%d ", array[i][j]);
                        }
                    } else {
                        printf("(vacio)");  // Indicar explícitamente que el array está vacío
                    }
                    printf("\n");
                    free(array[i]);
                }

                free(array);
                free(sizes);
            }

            for (int i = 0; i < numLines; i++) {
                free(lines[i]);
            }
            free(lines);
        }

        free(content);
    }

    return 0;
}