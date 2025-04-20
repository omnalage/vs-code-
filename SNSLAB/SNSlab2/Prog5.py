# Prog5.py: This program implements the Vigenère Cipher for encryption. 
# It uses a predefined key to perform character-wise substitution on the plaintext.

import gmpy2 # type: ignore

import sys

# Hardcoded Vigenère key
key = "omashknlgebcdfipqrtuvwxyz"

# Function to preprocess input (convert to lowercase, remove spaces)
def preprocess_input(input_text):
    return ''.join(char.lower() for char in input_text if char.isalnum())

# Function to repeat the key to match the plaintext length
def repeat_key(length):
    repeated_key = (key * (length // len(key) + 1))[:length]
    return repeated_key

# Function to encrypt using Vigenère Cipher
def vigenere_encrypt(plaintext):
    length = len(plaintext)
    expanded_key = repeat_key(length)
    ciphertext = []

    for i in range(length):
        if plaintext[i].isalpha():
            shift = ord(expanded_key[i]) - ord('a')
            encrypted_char = chr((ord(plaintext[i]) - ord('a') + shift) % 26 + ord('a'))
        elif plaintext[i].isdigit():
            shift = (ord(expanded_key[i]) - ord('a')) % 10
            encrypted_char = chr((ord(plaintext[i]) - ord('0') + shift) % 10 + ord('0'))
        else:
            encrypted_char = plaintext[i]  # Keep unchanged for non-alphanumeric
        ciphertext.append(encrypted_char)

    return ''.join(ciphertext).upper()

# Main function
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} \"plaintext message\"")
        sys.exit(1)

    # Combine input into a single string
    input_text = ' '.join(sys.argv[1:])

    # Preprocess plaintext
    plaintext = preprocess_input(input_text)

    # Encrypt plaintext
    ciphertext = vigenere_encrypt(plaintext)

    # Print the result
    print(ciphertext)
