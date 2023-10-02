#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main(void) {

    FILE *pFile = fopen("PLAINTEXT.txt", "r");

    if (pFile == NULL) {
        perror("could not read PepeSadge\n");
        return 1;
    }

    char characterBuffer[1];

    char *encryptedText = malloc(1);

    int capacity = 1;

    int index = 0;

    srand(time(NULL) + getpid());

    int asciiShifter = rand();
    int *pShifter = &asciiShifter;

    int asciiMultiplier = rand();
    int *pMulti = &asciiMultiplier;

    size_t dataSize = sizeof(int);

    while (fread(characterBuffer, 1, 1, pFile) == 1) {

        if (index >= capacity) {
            encryptedText = (char *)realloc(encryptedText, capacity * sizeof(char));

            if (encryptedText == NULL) {
                perror("memory allocation failed.");
                free(encryptedText);
                return 1;
            }

            capacity++;
        }

        encryptedText[index] = (characterBuffer[0] - asciiShifter) * asciiMultiplier;

        index++;

    }

    printf("\n");

    printf("Encrypted Text: %s", encryptedText);

    printf("\n");

    

    printf("Your decryption key: %d:%d", asciiShifter, asciiMultiplier);

    fclose(pFile);

    

    memset(pShifter, 0, dataSize);
    memset(pMulti, 0, dataSize);

    printf("\n");

    printf("check if asciiShifter erased: %d", asciiShifter);
    printf("\n");
    printf("check if asciiMultiplier erased: %d", asciiMultiplier);

}