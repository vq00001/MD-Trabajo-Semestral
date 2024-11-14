char *readFile(const char *filename);
char **splitLines(const char *content, int *numLines);
int **createArray(char **lines, int numLines, int *n, int **sizes);
