#include <stdio.h>
#include <string.h>

// Custom Alphanumeric Mapping (0-36)
char alphabet[] = "0123456789 abcdefghijklmnopqrstuvwxyz";
#define ALPHA_SIZE 37
#define SHIFT 7  // K_roll1

// Function to find index of a character in our custom alphabet
int find_index(char ch) {
    for (int i = 0; i < ALPHA_SIZE; i++) {
        if (alphabet[i] == ch) return i;
    }
    return -1;  // Character not found
}

// Encrypt function
void encrypt(char *plaintext, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        int index = find_index(plaintext[i]);
        if (index != -1) {
            ciphertext[i] = alphabet[(index + SHIFT) % ALPHA_SIZE];
        } else {
            ciphertext[i] = plaintext[i];  // Keep unknown characters unchanged
        }
    }
    ciphertext[i] = '\0';  // Null terminate the string
}

// Decrypt function
void decrypt(char *ciphertext, char *decryptedtext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        int index = find_index(ciphertext[i]);
        if (index != -1) {
            decryptedtext[i] = alphabet[(index - SHIFT + ALPHA_SIZE) % ALPHA_SIZE];
        } else {
            decryptedtext[i] = ciphertext[i];  // Keep unknown characters unchanged
        }
    }
    decryptedtext[i] = '\0';  // Null terminate the string
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <plain text>\n", argv[0]);
        return 1;
    }

    // Combine all arguments into a single string (simulate input as one phrase)
    char input[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(input, argv[i]);
        if (i < argc - 1) strcat(input, " "); // Preserve spaces
    }

    char encrypted[256], decrypted[256];

    // Perform encryption and decryption
    encrypt(input, encrypted);
    decrypt(encrypted, decrypted);

    // Convert to uppercase output
    for (int i = 0; encrypted[i] != '\0'; i++) {
        if (encrypted[i] >= 'a' && encrypted[i] <= 'z') {
            encrypted[i] -= 32;  // Convert lowercase to uppercase
        }
    }

    printf("Encrypted Text: %s\n", encrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
