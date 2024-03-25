#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}
void decrypt(const char* ciphertext, int a, int b) {
    int a_inv = modInverse(a, ALPHABET_SIZE);
    if (a_inv == -1) {
        printf("Invalid key\n");
        return;
    }

    int len = strlen(ciphertext);
    char plaintext[len + 1];
    plaintext[len] = '\0';

    for (int i = 0; i < len; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            int x = c - 'A';
            int x_plain = (a_inv * (x - b + ALPHABET_SIZE)) % ALPHABET_SIZE;
            plaintext[i] = 'A' + x_plain;
        } else {
            plaintext[i] = c; 
        }
    }

    printf("Decrypted message: %s\n", plaintext);
}

int main() {
    const char* ciphertext = "YOUR_CIPHERTEXT_HERE";
    int most_freq_index = ('B' - 'A');
    int second_most_freq_index = ('U' - 'A');
    int a = (most_freq_index - second_most_freq_index + ALPHABET_SIZE) % ALPHABET_SIZE;
    int b = ('B' - a * most_freq_index) % ALPHABET_SIZE;
    if (b < 0) {
        b += ALPHABET_SIZE;
    }

    printf("Key values: a = %d, b = %d\n", a, b);
    decrypt(ciphertext, a, b);

    return 0;
}

