#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to decrypt the ciphertext using a given substitution mapping
void decrypt(const char* ciphertext, const char* mapping) {
    int len = strlen(ciphertext);
    char plaintext[len + 1];
    plaintext[len] = '\0';

    for (int i = 0; i < len; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = mapping[c - 'A'];
        } else {
            plaintext[i] = c; // Not a letter, keep unchanged
        }
    }

    printf("Decrypted message: %s\n", plaintext);
}

// Function to perform frequency analysis on the ciphertext
void frequencyAnalysis(const char* ciphertext) {
    int freq[ALPHABET_SIZE] = {0};

    // Count the frequency of each letter in the ciphertext
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            freq[ciphertext[i] - 'A']++;
        }
    }

    // Find the most frequent letters
    char mapping[ALPHABET_SIZE + 1];
    mapping[ALPHABET_SIZE] = '\0';

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int maxFreqIndex = 0;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (freq[j] > freq[maxFreqIndex]) {
                maxFreqIndex = j;
            }
        }
        freq[maxFreqIndex] = 0; // Exclude this letter from future max searches
        mapping[maxFreqIndex] = 'A' + i;
    }

    // Print the frequency analysis results
    printf("Frequency analysis results:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c -> %c\n", 'A' + i, mapping[i]);
    }

    // Decrypt the ciphertext using the obtained mapping
    decrypt(ciphertext, mapping);
}

int main() {
    // Replace this with your ciphertext
    const char* ciphertext = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    // Perform frequency analysis to decrypt the ciphertext
    frequencyAnalysis(ciphertext);

    return 0;
}

