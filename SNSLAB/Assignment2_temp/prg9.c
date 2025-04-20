#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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

// Encrypt using Keyless Transposition Cipher
void keyless_transposition_encrypt(char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int row = ceil(sqrt(len)); // Number of rows is the ceiling of sqrt(plaintext length)
    int col = row;  // Number of columns is equal to the number of rows
    
    // Create a table and fill it row by row
    char table[row][col];
    int idx = 0;
    
    // Fill the table with plaintext, row by row
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (idx < len) {
                table[i][j] = plaintext[idx++];
            } else {
                table[i][j] = ' ';  // Padding with spaces
            }
        }
    }

    // Read the table column by column to generate ciphertext
    idx = 0;
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < row; i++) {
            ciphertext[idx++] = table[i][j];
        }
    }
    ciphertext[idx] = '\0'; // Null-terminate the ciphertext
}

// Decrypt using Keyless Transposition Cipher
void keyless_transposition_decrypt(char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    int row = ceil(sqrt(len)); // Number of rows is the ceiling of sqrt(ciphertext length)
    int col = row;  // Number of columns is equal to the number of rows
    
    // Create a table to store the decrypted characters
    char table[row][col];
    int idx = 0;

    // Fill the table column by column from ciphertext
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < row; i++) {
            if (idx < len) {
                table[i][j] = ciphertext[idx++];
            } else {
                table[i][j] = ' '; // Padding with spaces
            }
        }
    }

    // Read the table row by row to generate the decrypted plaintext
    idx = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (table[i][j] != ' ') { // Ignore padding spaces
                plaintext[idx++] = table[i][j];
            }
        }
    }
    plaintext[idx] = '\0'; // Null-terminate the plaintext
}

// Main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"plaintext message\"\n", argv[0]);
        return 1;
    }

    // Combine input into a single string
    char input[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(input, argv[i]);
        if (i < argc - 1) strcat(input, " ");
    }

    // Preprocess plaintext
    char plaintext[256];
     char decrypted[256];

    preprocess_input(input, plaintext);

    // Encrypt plaintext
    char ciphertext[256];
    keyless_transposition_encrypt(plaintext, ciphertext);

    // Decrypt ciphertext back to plaintext
   
    keyless_transposition_decrypt(ciphertext, decrypted);

    // Convert ciphertext to uppercase and print output
    for (int i = 0; ciphertext[i]; i++) {
        ciphertext[i] = toupper(ciphertext[i]);
    }
    printf("Encrypted message: %s\n", ciphertext);

    // Print decrypted message
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}