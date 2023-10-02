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

    printf("SHIFTER: %s", key);

    FILE *encryptedFile = fopen("PLAINTEXT.txt", "r");

    if (encryptedFile == NULL) {
        perror("could not read PepeSadge\n");
        return 1;
    }
    
    char characterBuffer[1];

    char *decryptedText = malloc(1);

    int capacity = 1;

    int index = 0;

    while (fread(characterBuffer, 1, 1, encryptedFile) == 1) {

        if (index >= capacity) {
            decryptedText = (char *)realloc(decryptedText, capacity * sizeof(char));

            if (decryptedText == NULL) {
                perror("memory allocation failed.");
                free(decryptedText);
                return 1;
            }

            capacity++;
        }

        printf("%d \n", characterBuffer[0]);

        decryptedText[index] = (characterBuffer[0]) / atoi(key);

        index++;

    }

    printf("decrypted: %s", decryptedText);

    free(decryptedText);

    return 0;
}

int encryption(void) {

    FILE *pFile = fopen("PLAINTEXT.txt", "r");

    if (pFile == NULL) {
        perror("could not read PepeSadge\n");
        return 1;
    }

    char characterBuffer[1];

    char *encryptedText = malloc(sizeof(char));

    int capacity = 0;

    int index = 0;

    srand(time(NULL) + getpid());

    int asciiShifter = rand();

    size_t dataSize = sizeof(char);

    while (fread(characterBuffer, 1, 1, pFile) == 1) {
            // test  -->  0, 1, 2, 3
        if (index >= capacity) {
            capacity++;
            encryptedText = realloc(encryptedText, capacity * dataSize);
            printf("capacity %d\n", capacity);
            printf("allocated\n");

        }

        encryptedText[index] = (characterBuffer[0]) - 1;

        printf("%d %c\n", encryptedText[index], encryptedText[index]);

        index++;

    }

    printf("\n");

    encryptedText[capacity] = '\0';

    printf("Encrypted Text: %s", encryptedText);

    printf("\n");

    printf("Your decryption key: %d", asciiShifter);

    fclose(pFile);

    FILE *pFileWrite = fopen("PLAINTEXT.txt", "w");

    fprintf_s(pFileWrite, encryptedText);

    printf("\n");

    fclose(pFileWrite);

    asciiShifter = 0;

    printf("check if asciiShifter erased: %d", asciiShifter);
    printf("\n");

    free(encryptedText);

}

int main(int argc, char *argv[]) {

    int selectedMode = checkProgramMode(argv[1]);

    printf("%s %d ", argv[1], selectedMode);

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