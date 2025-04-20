# prog10.py: This program uses a Keyed Transposition Cipher for encryption. 
# It permutes the characters in the input text based on a predefined permutation table K_permute.

import sys

# Define the K_permute (Permutation table)
K_permute = [
    29, 35, 15, 14, 30, 11, 27, 19, 22, 31, 36, 16, 17, 32, 12, 28, 20, 23, 33,
    13, 18, 21, 34, 24, 35, 25, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 36
]

# Preprocess input: Convert to lowercase and remove spaces
def preprocess_input(input_text):
    return ''.join(c.lower() for c in input_text if c.isalnum() or c == ' ')

# Convert letter to numeric value based on the given table
def letter_to_value(letter):
    if letter == ' ':
        return 36  # Space maps to 36
    elif 'a' <= letter <= 'z':
        return ord(letter) - ord('a')  # a-z maps to 0-25
    elif '0' <= letter <= '9':
        return ord(letter) - ord('0') + 26  # 0-9 maps to 26-35
    return -1  # Invalid input

# Convert numeric value to the corresponding letter
def value_to_letter(value):
    if value == 36:
        return ' '  # Value 36 is a space
    elif 0 <= value <= 25:
        return chr(ord('a') + value)  # 0-25 maps to a-z
    elif 26 <= value <= 35:
        return chr(ord('0') + (value - 26))  # 26-35 maps to 0-9
    return '?'  # Invalid value

# Encrypt the plaintext using the Keyed Transposition Cipher
def keyed_transposition_encrypt(plaintext):
    length = len(plaintext)
    numeric_plaintext = [letter_to_value(char) for char in plaintext]
    
    ciphertext = []
    for i in range(length):
        permuted_index = K_permute[i % len(K_permute)]
        ciphertext.append(value_to_letter(permuted_index))
    
    return ''.join(ciphertext)

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
    ciphertext = keyed_transposition_encrypt(plaintext)
    
    # Convert to uppercase and print the output
    print("Ciphertext:", ciphertext.upper())

if __name__ == "__main__":
    main()
