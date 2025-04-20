# Prog4.py: This program implements the Playfair Cipher for encryption. 
# It generates a 5x5 key matrix using a predefined key and encrypts the input text using digraphs.

import gmpy2 # type: ignore


MATRIX_SIZE = 5
CHARSET = "abcdefghijklmnopqrstuvwxyz0123456789"

# Hardcoded Playfair Key
key = "omashknlgebcdfipqrtuvwxyz "  # 25 distinct characters from name
playfair_matrix = []

# Function to prepare the Playfair cipher key matrix
def create_playfair_matrix():
    global playfair_matrix
    playfair_matrix = [[key[i * MATRIX_SIZE + j] for j in range(MATRIX_SIZE)] for i in range(MATRIX_SIZE)]

# Function to find the position of a character in Playfair matrix
def find_position(ch):
    for i in range(MATRIX_SIZE):
        for j in range(MATRIX_SIZE):
            if playfair_matrix[i][j] == ch:
                return i, j
    return None, None

# Function to preprocess plaintext (remove spaces and handle I/J)
def preprocess_plaintext(input_text):
    input_text = input_text.lower().replace(" ", "").replace("j", "i")
    return ''.join(ch for ch in input_text if ch in CHARSET)

# Function to create digraphs
def create_digraphs(plaintext):
    digraphs = []
    i = 0
    while i < len(plaintext):
        a = plaintext[i]
        if i + 1 < len(plaintext) and plaintext[i] == plaintext[i + 1]:
            b = 'x'
        elif i + 1 < len(plaintext):
            b = plaintext[i + 1]
            i += 1
        else:
            b = 'x'
        digraphs.append(a + b)
        i += 1
    return digraphs

# Function to encrypt using Playfair cipher
def playfair_encrypt(digraphs):
    ciphertext = ""
    for digraph in digraphs:
        row1, col1 = find_position(digraph[0])
        row2, col2 = find_position(digraph[1])
        
        if row1 == row2:  # Same row -> Shift right
            ciphertext += playfair_matrix[row1][gmpy2.f_mod(col1 + 1, MATRIX_SIZE)]
            ciphertext += playfair_matrix[row2][gmpy2.f_mod(col2 + 1, MATRIX_SIZE)]
        elif col1 == col2:  # Same column -> Shift down
            ciphertext += playfair_matrix[gmpy2.f_mod(row1 + 1, MATRIX_SIZE)][col1]
            ciphertext += playfair_matrix[gmpy2.f_mod(row2 + 1, MATRIX_SIZE)][col2]
        else:  # Rectangle -> Swap corners
            ciphertext += playfair_matrix[row1][col2]
            ciphertext += playfair_matrix[row2][col1]
    return ciphertext.upper()

# Main function
def main():
    import sys
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} \"plaintext message\"")
        return

    # Combine input into single string
    input_text = ' '.join(sys.argv[1:])
    
    # Prepare the Playfair matrix
    create_playfair_matrix()

    # Preprocess plaintext
    plaintext = preprocess_plaintext(input_text)

    # Create digraphs
    digraphs = create_digraphs(plaintext)

    # Encrypt using Playfair cipher
    ciphertext = playfair_encrypt(digraphs)

    # Print the ciphertext
    print(ciphertext)

if __name__ == "__main__":
    main()
