#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 37 // A-Z, space, and 0-9

// Permutation Table: Mapping Plaintext → Ciphertext
int K_permute[2][ALPHABET_SIZE] = 
{
    //  A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
    //  T   U   V   W   X   Y   Z   0   1   2   3   4   5   6   7   8   9  ' '  
       19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36}, 

   
    {
    30, 11, 24, 23, 12, 35, 18, 19, 28, 15,  
    29, 20, 21, 13, 31, 33, 14, 32, 34, 16, 
    25, 26, 17, 36, 21, 27, 10, 0, 1, 2, 3,   
    4, 5, 6, 7, 8, 9                      
}
};

// Reverse Mapping for Decryption
int K_decrypt[ALPHABET_SIZE];

// Generate Reverse Permutation Table for Decryption
void generate_reverse_permutation() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        K_decrypt[K_permute[1][i]] = K_permute[0][i];
    }
}

// Get index of a character in the defined set (A-Z, space, and 0-9)
int get_index(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c == ' ') return 36;
    if (c >= '0' && c <= '9') return c - '0' + 26;
    return -1; // Invalid character
}

// Get character from index
char get_char(int index) {
    if (index >= 0 && index < 26) return 'A' + index;
    if (index == 36) return ' ';
    if (index >= 26 && index < 36) return '0' + (index - 26);
    return '?'; // Invalid index
}

// Encrypt Function
void encrypt(char *plaintext, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        int index = get_index(toupper(plaintext[i]));
        if (index == -1) {
            ciphertext[i] = plaintext[i]; // Preserve invalid characters
        } else {
            ciphertext[i] = get_char(K_permute[1][index]);
        }
    }
    ciphertext[i] = '\0';
}

// Decrypt Function (Now Converts to Lowercase)
void decrypt(char *ciphertext, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        int index = get_index(toupper(ciphertext[i]));
        if (index == -1) {
            plaintext[i] = tolower(ciphertext[i]); // Preserve invalid characters in lowercase
        } else {
            plaintext[i] = tolower(get_char(K_decrypt[index])); // Convert to lowercase
        }
    }
    plaintext[i] = '\0';
}

// Main Function
int main() {
    char plaintext[100], encrypted[100], decrypted[100];

    generate_reverse_permutation();
   // char decrypted_text[100]= plaintext;
    printf("Enter plaintext (A-Z, 0-9, space only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

    // Encrypt and decrypt
    encrypt(plaintext, encrypted);
    decrypt(encrypted, decrypted);



    printf("\nEncrypted Text: %s\n", encrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}

