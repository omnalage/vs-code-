# Prog1.py: This program implements a Caesar Cipher with both encryption and decryption. 
# It shifts characters by a fixed number of positions for encryption and reverses the shift for decryption.

# Prog1.py: This program implements a Caesar Cipher encryption algorithm. 
# It takes a plaintext message as input and encrypts it by shifting each character by a fixed number of positions defined by K_ROLL1.

import sys

CHARSET = "0123456789 abcdefghijklmnopqrstuvwxyz"
CHARSET_SIZE = len(CHARSET)
K_ROLL1 = 7 # Caesar cipher shift

def get_char_index(c):
    """Returns the index of character `c` in CHARSET."""
    if c == ' ':
        return 10
    try:
        return CHARSET.index(c)
    except ValueError:
        return -1  # Not found

def get_char_from_index(index):
    """Returns the character corresponding to `index` in CHARSET, with wrap-around."""
    return CHARSET[index % CHARSET_SIZE]

def caesar_cipher(plaintext, shift):
    """Encrypts `plaintext` using a Caesar cipher with a given `shift`."""
    ciphertext = []
    for char in plaintext:
        index = get_char_index(char)
        if index != -1:
            new_index = (index + shift) % CHARSET_SIZE
            ciphertext.append(get_char_from_index(new_index))
        else:
            ciphertext.append(char)  # Keep unknown chars unchanged
    return ''.join(ciphertext)

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} \"plaintext message\"")
        return

    # Combine command-line arguments into a single string
    plaintext = " ".join(sys.argv[1:])
    
    # Convert to lowercase for consistency
    plaintext = plaintext.lower()

    # Encrypt using Caesar cipher
    ciphertext = caesar_cipher(plaintext, K_ROLL1)

    # Convert ciphertext to uppercase for final output
    ciphertext = ciphertext.upper()

    print(ciphertext)

if __name__ == "__main__":
    main()

# Example usage in the main function to display both encrypted and decrypted outputs (to be added).
