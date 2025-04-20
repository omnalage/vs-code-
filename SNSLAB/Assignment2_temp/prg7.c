#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Hardcoded Rotor Cipher Mapping (K_trad*)
char rotor_mapping[36] = {
    'o', 'm', 'a', 's', 'h', 'k', 'n', 'l', 'g', 'e',  // 0-9
    'b', 'c', 'd', 'f', 'i', 'j', 'p', 'q', 'r', 't',  //space, a-i
    'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',  // j-r
    '4', '5', '6', '7', '8', '9'                       // s-z                 
};


// Character-to-index lookup function
int char_to_index(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == ' ') return 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 11;
    return -1; // Error case
}

// Index-to-character lookup function for decryption
char index_to_char(int index) {
    if (index >= 0 && index < 37) {
        return rotor_mapping[index];
    }
    return '?'; // Error case
}

// Rotor Cipher encryption function
void rotor_encrypt(char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        int index = char_to_index(plaintext[i]);
        if (index != -1) {
            ciphertext[i] = rotor_mapping[index++];
        } else {
            ciphertext[i] = plaintext[i]; // Ignore unsupported characters
        }
    }
    ciphertext[len] = '\0';
}

// Rotor Cipher decryption function
void rotor_decrypt(char *ciphertext, char *plaintext, char *original) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        int index = -1;
        // Find the index of the character in the rotor mapping
        for (int j = 0; j < 37; j++) {
            if (ciphertext[i] == rotor_mapping[j]) {
                index = j;
                break;
            }
        }
        
        if (index != -1) {
            // Preserve original case of the plaintext while decrypting
            char c;
            if(index<=9) {
                c='0'+index;
            } else if(index==10) {
                c=' ';
            } else {
                c='a'+(index-11);
            }
            if (isupper(original[i])) {
                plaintext[i] = toupper(c);
            } else {
                plaintext[i] = tolower(c);
            }
        } else {
            plaintext[i] = ciphertext[i]; // Ignore unsupported characters
        }
    }
    plaintext[len] = '\0';
}

// Preprocess input: Convert to lowercase, remove spaces
void preprocess_input(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalnum(input[i]) || input[i] == ' ') {
            output[j++] = tolower(input[i]);
        }
    }
    output[j] = '\0';
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
    preprocess_input(input, plaintext);

    // Declare ciphertext and decrypted message arrays
    char ciphertext[256];
    char decrypted[256];

    // Encrypt plaintext
    rotor_encrypt(plaintext, ciphertext);
    
    // Decrypt the ciphertext back to plaintext
    rotor_decrypt(ciphertext, decrypted, input);

    // Print encrypted message
    printf("Encrypted message: ");
    for (int i = 0; ciphertext[i]; i++) {
        printf("%c", toupper(ciphertext[i])); // Convert to uppercase
    }
    printf("\n");

    // Print decrypted message
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}
