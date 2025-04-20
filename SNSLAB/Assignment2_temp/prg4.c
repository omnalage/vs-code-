#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define K_TRAD "omashknlgebcdfipqrtuvwxyz"

// Playfair Matrix
char playfairMatrix[SIZE][SIZE];

// Function to check if character is in key
int charExists(char ch, char *key, int length) {
    for (int i = 0; i < length; i++) {
        if (key[i] == ch) return 1;
    }
    return 0;
}

// Function to create Playfair Matrix
void createMatrix() {
    char keySquare[SIZE * SIZE] = K_TRAD;
    char alphabet[] = "abcdefghiklmnopqrstuvwxyz"; // I and J treated as same

    int index = strlen(K_TRAD);

    // Fill the matrix with K_trad
    for (int i = 0; i < 25; i++) {
        if (!charExists(alphabet[i], keySquare, index)) {
            keySquare[index++] = alphabet[i];
        }
    }

    // Fill matrix
    index = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            playfairMatrix[row][col] = keySquare[index++];
        }
    }
}

// Function to find position of a character in matrix
void findPosition(char ch, int *row, int *col) {
    if (ch == 'j') ch = 'i'; // Treat J as I
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (playfairMatrix[r][c] == ch) {
                *row = r;
                *col = c;
                return;
            }
        }
    }
}

// Function to prepare text (convert to pairs, insert 'X' if needed)
void prepareText(char *input, char *output) {
    int len = strlen(input);
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == 'j') input[i] = 'i';  // Convert 'j' to 'i'
        if (!isalpha(input[i])) continue;  // Ignore non-alphabetic characters

        output[index++] = tolower(input[i]);

        // Insert 'X' if two consecutive letters are the same
        if (index % 2 == 1 && i + 1 < len && input[i] == input[i + 1]) {
            output[index++] = 'x';
        }
    }

    // If length is odd, append 'X'
    if (index % 2 == 1) output[index++] = 'x';

    output[index] = '\0';  // Null terminate
}

// Playfair Encryption
void encryptPlayfair(char *plaintext, char *ciphertext) {
    int row1, col1, row2, col2;
    for (int i = 0; i < strlen(plaintext); i += 2) {
        findPosition(plaintext[i], &row1, &col1);
        findPosition(plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {  // Same Row - Shift Right
            ciphertext[i] = playfairMatrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = playfairMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {  // Same Column - Shift Down
            ciphertext[i] = playfairMatrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = playfairMatrix[(row2 + 1) % SIZE][col2];
        } else {  // Rectangle Rule - Swap Columns
            ciphertext[i] = playfairMatrix[row1][col2];
            ciphertext[i + 1] = playfairMatrix[row2][col1];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Playfair Decryption
void decryptPlayfair(char *ciphertext, char *plaintext) {
    int row1, col1, row2, col2;
    for (int i = 0; i < strlen(ciphertext); i += 2) {
        findPosition(ciphertext[i], &row1, &col1);
        findPosition(ciphertext[i + 1], &row2, &col2);

        if (row1 == row2) {  // Same Row - Shift Left
            plaintext[i] = playfairMatrix[row1][(col1 + SIZE - 1) % SIZE];
            plaintext[i + 1] = playfairMatrix[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {  // Same Column - Shift Up
            plaintext[i] = playfairMatrix[(row1 + SIZE - 1) % SIZE][col1];
            plaintext[i + 1] = playfairMatrix[(row2 + SIZE - 1) % SIZE][col2];
        } else {  // Rectangle Rule - Swap Columns
            plaintext[i] = playfairMatrix[row1][col2];
            plaintext[i + 1] = playfairMatrix[row2][col1];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <plain text>\n", argv[0]);
        return 1;
    }

    // Combine all arguments into a single string
    char input[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(input, argv[i]);
        if (i < argc - 1) strcat(input, " ");  // Preserve spaces
    }

    char preparedText[256], encrypted[256], decrypted[256];

    createMatrix();  // Generate Playfair matrix
    prepareText(input, preparedText);
    encryptPlayfair(preparedText, encrypted);
    decryptPlayfair(encrypted, decrypted);

    // Convert encrypted text to uppercase
    for (int i = 0; encrypted[i] != '\0'; i++) {
        if (encrypted[i] >= 'a' && encrypted[i] <= 'z') {
            encrypted[i] -= 32;
        }
    }

    printf("Encrypted Text: %s\n", encrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
