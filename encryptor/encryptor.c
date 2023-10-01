#include <stdio.h>

int main(void) {

    FILE *pFile = fopen("PLAINTEXT.txt", "r");

    if (pFile == NULL) {
        perror("could not read PepeSadge\n");
        return 1;
    }

    char characterBuffer[1];

    while (fread(characterBuffer, 1, 1, pFile) == 1) {
        printf("%c", characterBuffer[0]);
    }

    printf("\n");

    fclose(pFile);
}