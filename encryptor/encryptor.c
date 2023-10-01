#include <stdio.h>
#include <stdlib.h>

int main(void) {

    FILE *pFile = fopen("PLAINTEXT.txt", "r");

    if (pFile == NULL) {
        perror("could not read PepeSadge\n");
        return 1;
    }

    char characterBuffer[1];

    char *plaintext = malloc(1);

    int capacity = 1;

    int index = 0;

    while (fread(characterBuffer, 1, 1, pFile) == 1) {

        if (index >= capacity) {
            plaintext = (char *)realloc(plaintext, capacity * sizeof(char));

            if (plaintext == NULL) {
                perror("memory allocation failed.");
                free(plaintext);
                return 1;
            }

            capacity++;
        }

        plaintext[index] = characterBuffer[0];

        index++;

    }

    printf("\n");

    printf("%s", plaintext);

    fclose(pFile);
}