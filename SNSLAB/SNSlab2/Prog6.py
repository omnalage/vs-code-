# Prog6.py: This program implements the Hill Cipher for encryption using a 5x5 key matrix.
# It encrypts blocks of characters by multiplying them with the key matrix.

import sys

MATRIX_SIZE = 5
CHARSET_SIZE = 36
ALPHA_START = ord('a')
DIGIT_START = ord('0')

# Hardcoded 5x5 Key Matrix (K_trad converted to numbers)
key_matrix = [
    [10, 15, 20, 25, 30],
    [9, 14, 19, 24, 29],
    [8, 13, 18, 23, 28],
    [7, 12, 17, 22, 27],
    [6, 11, 16, 21, 26]
]

# Convert character to numeric value (as per given table)
def char_to_num(c):
    if '0' <= c <= '9':
        return ord(c) - DIGIT_START
    if 'a' <= c <= 'z':
        return ord(c) - ALPHA_START + 10
    return -1  # Error case (should not happen)

# Convert numeric value back to character
def num_to_char(num):
    if 0 <= num <= 9:
        return chr(DIGIT_START + num)
    if 10 <= num < 36:
        return chr(ALPHA_START + (num - 10))
    return '?'  # Error case

# Preprocess input: convert to lowercase, remove spaces
def preprocess_input(input_text):
    return ''.join(char.lower() for char in input_text if char.isalnum())

# Apply Hill Cipher encryption
def hill_encrypt(plaintext):
    length = len(plaintext)
    padded_length = length

    # Pad with 'x' if length is not a multiple of 5
    while padded_length % MATRIX_SIZE != 0:
        plaintext += 'x'
        padded_length += 1

    ciphertext = []

    for i in range(0, padded_length, MATRIX_SIZE):
        block = [char_to_num(plaintext[i + j]) for j in range(MATRIX_SIZE)]
        result = [0] * MATRIX_SIZE

        # Multiply with key matrix
        for row in range(MATRIX_SIZE):
            result[row] = sum(key_matrix[row][col] * block[col] for col in range(MATRIX_SIZE)) % CHARSET_SIZE

        # Convert numbers back to characters
        ciphertext.extend(num_to_char(num) for num in result)

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
    ciphertext = hill_encrypt(plaintext)

    # Print the result
    print(ciphertext)
