#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256
#define SECRET_KEY "omashknlgebcdfipqrtuvwxyz"

// Function to format text (convert to uppercase, remove spaces)
void formatText(const char *input, char *output) {
    int index = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[index++] = toupper(input[i]);
        }
    }
    output[index] = '\0'; // Null terminate
}

// Function to repeat key until it matches the length of text
void generateKey(const char *text, char *key) {
    int textLen = strlen(text);
    int keyLen = strlen(SECRET_KEY);

    for (int i = 0; i < textLen; i++) {
        key[i] = toupper(SECRET_KEY[i % keyLen]); // Repeat key
    }
    key[textLen] = '\0'; // Null terminate
}

// Vigenère Encryption
void encryptVigenere(const char *plaintext, const char *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        ciphertext[i] = ((plaintext[i] - 'A') + (key[i] - 'A')) % 26 + 'A';
    }
    ciphertext[len] = '\0'; // Null terminate
}

// Vigenère Decryption
void decryptVigenere(const char *ciphertext, const char *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        plaintext[i] = ((ciphertext[i] - 'A') - (key[i] - 'A') + 26) % 26 + 'A';
    }
    plaintext[len] = '\0'; // Null terminate
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <plaintext>\n", argv[0]);
        return 1;
    }

    // Combine all arguments into a single string
    char input[MAX_LEN] = "";
    for (int i = 1; i < argc; i++) {
        strcat(input, argv[i]);
        if (i < argc - 1) strcat(input, " "); // Preserve spaces
    }

    char formattedText[MAX_LEN], key[MAX_LEN], encrypted[MAX_LEN], decrypted[MAX_LEN];

    formatText(input, formattedText);
    generateKey(formattedText, key);
    encryptVigenere(formattedText, key, encrypted);
    decryptVigenere(encrypted, key, decrypted);

    printf("Plaintext:  %s\n", formattedText);
    printf("Key:        %s\n", key);
    printf("Encrypted:  %s\n", encrypted);
    printf("Decrypted:  %s\n", decrypted);

    return 0;
}
