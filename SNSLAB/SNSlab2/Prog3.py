# Prog3.py: This program implements an Autokey Cipher for encryption. 
# It uses a shifting technique based on the character index in the plaintext, with an initial key K1.

import sys

CHARSET = "0123456789 abcdefghijklmnopqrstuvwxyz"
CHARSET_SIZE = len(CHARSET)
K1 = 7 


def get_char_index(c):
    """Returns the index of character `c` in CHARSET."""
    if c == ' ':
        return 10
    try:
        return CHARSET.index(c)
    except ValueError:
        return -1  # Character not found


def get_char_from_index(index):
    """Returns the character corresponding to `index` in CHARSET."""
    return CHARSET[index % CHARSET_SIZE]


def autokey_cipher_encrypt(plaintext):
    """Encrypts `plaintext` using an Autokey Cipher with an initial key K1."""
    ciphertext = []
    key = K1  # Initialize with K1

    for char in plaintext:
        index = get_char_index(char)
        if index != -1:
            # Encryption formula: (index + key) % CHARSET_SIZE
            new_index = (index + key) % CHARSET_SIZE
            ciphertext.append(get_char_from_index(new_index))
            key = index  # Update key with current plaintext value
        else:
            ciphertext.append(char)  # Keep unknown characters unchanged

    return ''.join(ciphertext)


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} \"plaintext message\"")
        return

    # Combine command-line arguments into a single string
    plaintext = " ".join(sys.argv[1:])

    # Convert to lowercase for consistency
    plaintext = plaintext.lower()

    # Encrypt the plaintext using the Autokey Cipher
    ciphertext = autokey_cipher_encrypt(plaintext)

    # Convert ciphertext to uppercase for final output
    ciphertext = ciphertext.upper()

    print(ciphertext)


if __name__ == "__main__":
    main()
