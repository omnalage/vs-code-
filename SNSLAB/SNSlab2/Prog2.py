# Prog2.py: This program uses an Affine Cipher for encryption. 
# It encrypts a given plaintext by applying a mathematical transformation to each character using the keys K1 and K2.

import sys
import gmpy2  # type: ignore


CHARSET = "0123456789 abcdefghijklmnopqrstuvwxyz"
CHARSET_SIZE = len(CHARSET)

K1 = 7  # Secret key (should be coprime with 37)
K2 = 1  # Secret key (any integer)


def get_char_index(c):
    """Returns the index of character `c` in CHARSET."""
    if c == ' ':
        return 10
    try:
        return CHARSET.index(c)
    except ValueError:
        return -1  # Not found


def get_char_from_index(index):
    """Returns the character corresponding to `index` in CHARSET."""
    return CHARSET[index % CHARSET_SIZE]


def affine_cipher_encrypt(plaintext):
    """Encrypts `plaintext` using an Affine Cipher with keys K1 and K2."""
    ciphertext = []
    for char in plaintext:
        index = get_char_index(char)
        if index != -1:
            # Apply Affine transformation: (K1 * index + K2) % CHARSET_SIZE
            new_index = (gmpy2.mul(K1, index) + K2) % CHARSET_SIZE
            ciphertext.append(get_char_from_index(new_index))
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

    # Encrypt the plaintext using the Affine Cipher
    ciphertext = affine_cipher_encrypt(plaintext)

    # Convert ciphertext to uppercase for final output
    ciphertext = ciphertext.upper()

    print(ciphertext)


if __name__ == "__main__":
    main()
