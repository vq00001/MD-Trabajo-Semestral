#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
void readFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        printf("Código de error: %d\n", errno);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == -1) {
        perror("Error al determinar el tamaño del archivo");
        fclose(file);
        return;
    }
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Error en la asignación de memoria");
        fclose(file);
        return;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("Error al leer el archivo");
        free(buffer);
        fclose(file);
        return;
    }

    buffer[fileSize] = '\0';
    printf("Contenido:\n%s\n", buffer); // Mostrar contenido del archivo (Solo para pruebas)

    free(buffer);
    fclose(file);
}

int main() {
    const char *filename = "ejemplo.csv"; // Nombre del archivo a leer
    readFile(filename);
    return 0;
}