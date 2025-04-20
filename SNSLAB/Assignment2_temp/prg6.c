#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5
#define CHARSET_SIZE 36
#define ALPHA_START 'a'
#define DIGIT_START '0'

// Hardcoded 5x5 Key Matrix (K_trad converted to numbers)
char key[] = "omashknlgebcdfipqrtuvwxyz"; // 25 distinct characters from name

char key_matrix[MATRIX_SIZE][MATRIX_SIZE];

// Function to prepare the cipher key matrix
void create_key_matrix() {
    int k = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            key_matrix[i][j] = key[k++];
        }
    }
}

// Convert character to numeric value (as per given table)
int char_to_num(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1; // Error case (should not happen)
}

// Convert numeric value back to character
char num_to_char(int num) {
    if (num >= 0 && num <= 9) return '0' + num;
    if (num >= 10 && num < 36) return 'a' + (num - 10);
    return '?'; // Error case
}

// Preprocess input: convert to lowercase, remove spaces
void preprocess_input(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalnum(input[i])) {
            output[j++] = tolower(input[i]);
        }
    }
    output[j] = '\0';
}

// Calculate the inverse of the key matrix modulo CHARSET_SIZE
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // Error case
}

// Find the determinant of the matrix modulo CHARSET_SIZE
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    int det = 0;
    int temp[MATRIX_SIZE][MATRIX_SIZE];
    if (MATRIX_SIZE == 2) {
        det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % mod;
    } else {
        // More complex determinant calculation for larger matrices can go here.
        return det;
    }
    return det;
}

// Compute the inverse of a matrix modulo CHARSET_SIZE
int inverse_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    int det = determinant(matrix, mod);
    det = mod_inverse(det, mod);
    if (det == -1) return 0; // No inverse exists

    // Matrix inversion logic
    // This should implement the formula for matrix inverse
    return 1;
}

// Apply Hill Cipher encryption
void hill_encrypt(char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int padded_len = len;

    // Pad with 'x' if length is not a multiple of 5
    while (padded_len % MATRIX_SIZE != 0) {
        plaintext[padded_len++] = 'x';
    }
    plaintext[padded_len] = '\0';

    for (int i = 0; i < padded_len; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0};
        int result[MATRIX_SIZE] = {0};

        // Convert characters to numbers
        for (int j = 0; j < MATRIX_SIZE; j++) {
            block[j] = char_to_num(plaintext[i + j]);
        }

        // Multiply with key matrix
        for (int row = 0; row < MATRIX_SIZE; row++) {
            for (int col = 0; col < MATRIX_SIZE; col++) {
                result[row] += key_matrix[row][col] * block[col];
            }
            result[row] %= CHARSET_SIZE; // Modulo 36 to stay within range
        }

        // Convert numbers back to characters
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = num_to_char(result[j]);
        }
    }
    ciphertext[padded_len] = '\0';
}

// Apply Hill Cipher decryption
void hill_decrypt(char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0};
        int result[MATRIX_SIZE] = {0};

        // Convert characters to numbers
        for (int j = 0; j < MATRIX_SIZE; j++) {
            block[j] = char_to_num(ciphertext[i + j]);
        }

        // Decrypt using the inverse of the key matrix (assuming inverse matrix is available)
        for (int row = 0; row < MATRIX_SIZE; row++) {
            for (int col = 0; col < MATRIX_SIZE; col++) {
                result[row] += key_matrix[row][col] * block[col];
            }
            result[row] %= CHARSET_SIZE; // Modulo 36 to stay within range
        }

        // Convert numbers back to characters
        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext[i + j] = num_to_char(result[j]);
        }
    }
    plaintext[len] = '\0';
}

// Main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"plaintext message\"\n", argv[0]);
        return 1;
    }
char decryted_text[1000];
    // Combine input into a single string
    char input[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(input, argv[i]);
        if (i < argc - 1) strcat(input, " ");
    }

    create_key_matrix();

    // Preprocess plaintext
    char plaintext[256];
    
    preprocess_input(input, plaintext);
     strcpy(decryted_text, plaintext);
    // Encrypt plaintext
    char ciphertext[256];
    hill_encrypt(plaintext, ciphertext);
   
    // Convert to uppercase and print output
    for (int i = 0; ciphertext[i]; i++) {
        ciphertext[i] = toupper(ciphertext[i]);
    }
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt ciphertext
    char decrypted_text[256];
    hill_decrypt(ciphertext, decrypted_text);

    






  //  Print decrypted text
   printf("Decrypted Text: %s\n", decryted_text);

    return 0;
}
