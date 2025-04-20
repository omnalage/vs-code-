#include <stdio.h>
#include <string.h>

// Custom Alphanumeric Mapping (0-36)
char alphabet[] = "0123456789 abcdefghijklmnopqrstuvwxyz";
#define ALPHA_SIZE 37
#define K_ROLL1 7  // Initial key value

// Function to find index of a character in our custom alphabet
int find_index(char ch) {
    for (int i = 0; i < ALPHA_SIZE; i++) {
        if (alphabet[i] == ch) return i;
    }
    return -1;  // Character not found
}

// Encrypt function
void encrypt(char *plaintext, char *ciphertext) {
    int key[strlen(plaintext)];  // Store key sequence
    key[0] = K_ROLL1;  // Initial key is K_roll1

    for (int i = 1; i < strlen(plaintext); i++) {
        key[i] = find_index(plaintext[i - 1]);  // Key sequence extends with plaintext
    }

    for (int i = 0; plaintext[i] != '\0'; i++) {
        int index = find_index(plaintext[i]);
        if (index != -1) {
            ciphertext[i] = alphabet[(index + key[i]) % ALPHA_SIZE];
        } else {
            ciphertext[i] = plaintext[i];  // Keep unknown characters unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0';  // Null terminate the string
}

// Decrypt function
void decrypt(char *ciphertext, char *decryptedtext) {
    int key[strlen(ciphertext)];
    key[0] = K_ROLL1;  // Initial key is K_roll1

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        int index = find_index(ciphertext[i]);
        if (index != -1) {
            int decrypted_index = (index - key[i] + ALPHA_SIZE) % ALPHA_SIZE;
            decryptedtext[i] = alphabet[decrypted_index];
            key[i + 1] = decrypted_index;  // Extend key sequence with decrypted text
        } else {
            decryptedtext[i] = ciphertext[i];  // Keep unknown characters unchanged
        }
    }
    decryptedtext[strlen(ciphertext)] = '\0';  // Null terminate the string
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
