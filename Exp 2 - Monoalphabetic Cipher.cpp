#include <stdio.h>
#include <string.h>
#include<ctype.h>

int main() {
    char plainAlphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char cipherAlphabet[] = "phqgiumeaylnofdxjkrcvstzwb";
    char message[100];
    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            if (isupper(message[i]))
                message[i] = toupper(cipherAlphabet[message[i] - 'A']);
            else
                message[i] = cipherAlphabet[message[i] - 'a'];
        }
    }
    printf("Encrypted message: %s\n", message);
    return 0;
}
