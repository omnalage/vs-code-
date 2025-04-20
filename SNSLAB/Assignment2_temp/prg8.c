#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Maximum length of input text
#define MAX_LEN 256

// Preprocess input: Convert to lowercase and remove spaces
void preprocess_input(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalnum(input[i])) { // Only alphanumeric characters
            output[j++] = tolower(input[i]);
        }
    }
    output[j] = '\0';
}

// Encrypt using Rail Fence Cipher (2 Rails)
void rail_fence_encrypt(char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    char rail1[MAX_LEN], rail2[MAX_LEN];
    int idx1 = 0, idx2 = 0;
    
    // Zigzag pattern placement
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            rail1[idx1++] = plaintext[i];
        else
            rail2[idx2++] = plaintext[i];
    }

    // Combine rails to form ciphertext
    strncpy(ciphertext, rail1, idx1);
    strncpy(ciphertext + idx1, rail2, idx2);
    ciphertext[idx1 + idx2] = '\0';
}

// Decrypt using Rail Fence Cipher (2 Rails)
void rail_fence_decrypt(char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    char rail1[MAX_LEN], rail2[MAX_LEN];
    int idx1 = 0, idx2 = 0;
    
    // Calculate the number of characters for each rail
    int mid = (len + 1) / 2;
    
    // Split the ciphertext back into two rails
    strncpy(rail1, ciphertext, mid);
    rail1[mid] = '\0';  // Null-terminate after the first rail
    strncpy(rail2, ciphertext + mid, len - mid);
    rail2[len - mid] = '\0';  // Null-terminate after the second rail

    // Rebuild the original plaintext by zigzagging the characters back
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            plaintext[i] = rail1[idx1++];
        else
            plaintext[i] = rail2[idx2++];
    }
    plaintext[len] = '\0';  // Null-terminate the plaintext
}

// Main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"plaintext message\"\n", argv[0]);
        return 1;
    }

    // Combine input into a single string
    char input[MAX_LEN] = "";
    for (int i = 1; i < argc; i++) {
        strcat(input, argv[i]);
        if (i < argc - 1) strcat(input, " ");
    }

    // Preprocess plaintext
    char plaintext[MAX_LEN];
    preprocess_input(input, plaintext);

    // Encrypt plaintext
    char ciphertext[MAX_LEN];
    rail_fence_encrypt(plaintext, ciphertext);

    // Decrypt the ciphertext back to plaintext
    char decrypted[MAX_LEN];
    rail_fence_decrypt(ciphertext, decrypted);

    // Convert encrypted message to uppercase and print
    for (int i = 0; ciphertext[i]; i++) {
        ciphertext[i] = toupper(ciphertext[i]);
    }
    printf("Encrypted message: %s\n", ciphertext);

    // Print decrypted message (no need to convert case as it already maintains the original case)
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}
