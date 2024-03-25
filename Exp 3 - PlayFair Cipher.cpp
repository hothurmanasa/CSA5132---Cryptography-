#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void prepareKey(char *key, char *preparedKey) {
    int i, j;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    char *ptr;
    for (i = 0; key[i] != '\0'; i++) {
        key[i] = toupper(key[i]);
    }
    for (i = 0, j = 0; key[i] != '\0'; i++) {
        if (strchr(preparedKey, key[i]) == NULL) {
            preparedKey[j++] = key[i];
        }
    }
    for (ptr = alphabet; *ptr != '\0'; ptr++) {
        if (*ptr == 'J')
            continue;
        if (strchr(preparedKey, *ptr) == NULL) {
            preparedKey[j++] = *ptr;
        }
    }
    preparedKey[j] = '\0';
}
void generateGrid(char grid[SIZE][SIZE], char *preparedKey) {
    int i, j, k = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            grid[i][j] = preparedKey[k++];
        }
    }
}
void findPosition(char grid[SIZE][SIZE], char letter, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (grid[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encrypt(char grid[SIZE][SIZE], char *plaintext) {
    int i, row1, col1, row2, col2;
    char ch1, ch2;
    for (i = 0; plaintext[i] != '\0'; i += 2) {
        ch1 = plaintext[i];
        ch2 = (plaintext[i + 1] == '\0') ? 'X' : plaintext[i + 1];
        if (ch1 == ch2) {
            ch2 = 'X';
            i--;
        }
        findPosition(grid, toupper(ch1), &row1, &col1);
        findPosition(grid, toupper(ch2), &row2, &col2);
        if (row1 == row2) {
            printf("%c%c", grid[row1][(col1 + 1) % SIZE], grid[row2][(col2 + 1) % SIZE]);
        } else if (col1 == col2) {
            printf("%c%c", grid[(row1 + 1) % SIZE][col1], grid[(row2 + 1) % SIZE][col2]);
        } else {
            printf("%c%c", grid[row1][col2], grid[row2][col1]);
        }
    }
}
void decrypt(char grid[SIZE][SIZE], char *ciphertext) {
    int i, row1, col1, row2, col2;
    char ch1, ch2;
    for (i = 0; ciphertext[i] != '\0'; i += 2) {
        ch1 = ciphertext[i];
        ch2 = ciphertext[i + 1];
        findPosition(grid, ch1, &row1, &col1);
        findPosition(grid, ch2, &row2, &col2);
        if (row1 == row2) {
            printf("%c%c", grid[row1][(col1 - 1 + SIZE) % SIZE], grid[row2][(col2 - 1 + SIZE) % SIZE]);
        } else if (col1 == col2) {
            printf("%c%c", grid[(row1 - 1 + SIZE) % SIZE][col1], grid[(row2 - 1 + SIZE) % SIZE][col2]);
        } else {
            printf("%c%c", grid[row1][col2], grid[row2][col1]);
        }
    }
}
int main() {
    char key[100], preparedKey[26], grid[SIZE][SIZE], plaintext[1000], ciphertext[1000];
    int i;
    printf("Enter the key: ");
    scanf("%s", key);
    prepareKey(key, preparedKey);
    generateGrid(grid, preparedKey);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    printf("Encrypted text: ");
    encrypt(grid, plaintext);
    printf("\n");
    printf("Enter the ciphertext: ");
    scanf("%s", ciphertext);
    printf("Decrypted text: ");
    decrypt(grid, ciphertext);
    printf("\n");
    return 0;
}
