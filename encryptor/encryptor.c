#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int checkProgramMode(char userChoice[]);
int encryption(void);
int decryption(char key[]);

int checkProgramMode(char userChoice[]) {

    if (strcmp(userChoice, "encrypt") == 0) {
        return 3;
    }
    else if (strcmp(userChoice, "decrypt") == 0) {
        return 2;
    }
    else {
        return 1;
    }

}

int decryption(char key[]) {

    printf("key %s\n", key);
    int index;
    int shifterIndex;
    int multiplierIndex;
    int colonIndex;

    int shifterCapacity = 1;
    int multiCapacity = 1;

    //char asciiMultiplier = 

    for (index = 0; key[index] != '\0'; index++) {

        if (key[index] == ':') {
            printf("found colon\n");
            colonIndex = index;
        }
    }

    char *shifter = (char *) malloc(colonIndex * sizeof(char));

    for (shifterIndex = 0; shifterIndex < colonIndex; shifterIndex++) {
        printf("%c", key[shifterIndex]);
        shifter[shifterIndex] = key[shifterIndex];
    }
    
    shifter[colonIndex] = '\0';
/* SHIFTER IS NOW COMPLETE */
    printf("SHIFTER: %s", shifter);


    free(shifter);
    //free(asciiMultiplier);

    return 0;
}

int encryption(void) {

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

    FILE *pFileWrite = fopen("PLAINTEXT.txt", "w");

    fprintf_s(pFileWrite, encryptedText);

    memset(pShifter, 0, dataSize);
    memset(pMulti, 0, dataSize);

    printf("\n");

    printf("check if asciiShifter erased: %d", asciiShifter);
    printf("\n");
    printf("check if asciiMultiplier erased: %d", asciiMultiplier);

}

int main(int argc, char *argv[]) {

    printf("%s", argv[1]);

    int selectedMode = checkProgramMode(argv[1]);

    printf("%d", selectedMode);

    /* IF MODE IS ENCRYPT RUN ENCRYPTION FUNCTION
    
    IF MODE IS DECRYPT RUN DECRYPTION FUNCTION */

    if (selectedMode == 3) {
        encryption();
    }
    else if (selectedMode == 2) {
        decryption(argv[2]);
    }
    else {
        printf("no valid option selected\n");
    }

}