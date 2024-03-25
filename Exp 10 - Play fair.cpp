#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5
#define ALPHABET_SIZE 26

void preprocessKey(const char *key, char *processedKey) {
    int index = 0;
    int keyLength = strlen(key);
    for (int i = 0; i < keyLength; i++) {
        if (isalpha(key[i])) {
            processedKey[index++] = toupper(key[i]);
        }
    }

    processedKey[index] = '\0';
    int marked[ALPHABET_SIZE] = {0};
    index = 0;
    for (int i = 0; i < strlen(processedKey); i++) {
        if (!marked[processedKey[i] - 'A']) {
            processedKey[index++] = processedKey[i];
            marked[processedKey[i] - 'A'] = 1;
        }
    }

    processedKey[index] = '\0';
}

void fillMatrix(const char *processedKey, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int keyLength = strlen(processedKey);
    int row = 0, col = 0;
    
    for (int i = 0; i < keyLength; i++) {
        matrix[row][col] = processedKey[i];
        col++;
        if (col == MATRIX_SIZE) {
            col = 0;
            row++;
        }
    }

    char currentLetter = 'A';
    for (int i = row; i < MATRIX_SIZE; i++) {
        for (int j = col; j < MATRIX_SIZE; j++) {
            while (strchr(processedKey, currentLetter) != NULL) {
                currentLetter++;
            }
            matrix[i][j] = currentLetter++;
        }
        col = 0;
    }
}

void findPositions(char matrix[MATRIX_SIZE][MATRIX_SIZE], char letter, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptDigraph(char matrix[MATRIX_SIZE][MATRIX_SIZE], char first, char second, char *cipherPair) {
    int row1, col1, row2, col2;
    findPositions(matrix, toupper(first), &row1, &col1);
    findPositions(matrix, toupper(second), &row2, &col2);

    if (row1 == row2) {
        cipherPair[0] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
        cipherPair[1] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
    } else if (col1 == col2) {
        cipherPair[0] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
        cipherPair[1] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
    } else {
        cipherPair[0] = matrix[row1][col2];
        cipherPair[1] = matrix[row2][col1];
    }
}
void playfairEncrypt(const char *plaintext, const char *key, char *ciphertext) {
    char processedKey[ALPHABET_SIZE];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    preprocessKey(key, processedKey);
    fillMatrix(processedKey, matrix);

    int length = strlen(plaintext);
    int cipherIndex = 0;
    for (int i = 0; i < length; i += 2) {
        char first = plaintext[i];
        char second = (i + 1 < length) ? plaintext[i + 1] : 'X'; 

        if (first == second) {
            second = 'X';
            i--; 
        }
        encryptDigraph(matrix, first, second, &ciphertext[cipherIndex]);
        cipherIndex += 2;
    }

    ciphertext[cipherIndex] = '\0';
}

int main() {
    const char *plaintext = "Must see you over Cadogan West.";
    const char *key = "CIPHER";
    char ciphertext[2 * strlen(plaintext)];
    playfairEncrypt(plaintext, key, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Key: %s\n", key);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

