# Prog9.py: This program implements a Keyless Transposition Cipher for encryption. 
# It rearranges the characters in the input text by placing them in a grid and reading them column by column.

import math
import sys

# Preprocess input: Convert to lowercase and remove spaces
def preprocess_input(input_text):
    return ''.join(c.lower() for c in input_text if c.isalnum())

# Encrypt using Keyless Transposition Cipher
def keyless_transposition_encrypt(plaintext):
    length = len(plaintext)
    row = col = math.ceil(math.sqrt(length))  # Number of rows and columns are both ceil(sqrt(length))
    
    # Create a table with padding
    table = [[' ' for _ in range(col)] for _ in range(row)]
    idx = 0
    
    # Fill the table row by row
    for i in range(row):
        for j in range(col):
            if idx < length:
                table[i][j] = plaintext[idx]
                idx += 1
    
    # Read the table column by column to generate ciphertext
    ciphertext = []
    for j in range(col):
        for i in range(row):
            ciphertext.append(table[i][j])
    
    return ''.join(ciphertext).strip()  # Return the ciphertext without trailing spaces

# Main function
def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} \"plaintext message\"")
        return

    # Combine input into a single string
    input_text = ' '.join(sys.argv[1:])
    
    # Preprocess plaintext
    plaintext = preprocess_input(input_text)
    
    # Encrypt plaintext
    ciphertext = keyless_transposition_encrypt(plaintext)
    
    # Convert to uppercase and print the output
    print(ciphertext.upper())

if __name__ == "__main__":
    main()
