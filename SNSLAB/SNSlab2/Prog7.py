# Prog7.py: This program simulates a Rotor Cipher encryption using a predefined character mapping.
# It substitutes each character in the plaintext according to a rotor-based mapping.

import string

# Hardcoded Rotor Cipher Mapping (K_trad*)
rotor_mapping = [
    'o', 'm', 'a', 's', 'h', 'k', 'n', 'l', 'g', 'e',  # 0-9
    'b', 'c', 'd', 'f', 'i', 'j', 'p', 'q', 'r', 't',  # space, a-i
    'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',  # j-r
    '4', '5', '6', '7', '8', '9'                       # s-z
]

# Character-to-index lookup function
def char_to_index(c):
    if c.isdigit():
        return int(c)
    elif c == ' ':
        return 10
    elif c.isalpha():
        return ord(c) - ord('a') + 11
    return -1  # Error case

# Rotor Cipher encryption function
def rotor_encrypt(plaintext):
    ciphertext = []
    for char in plaintext:
        index = char_to_index(char)
        if index != -1:
            ciphertext.append(rotor_mapping[index])
        else:
            ciphertext.append(char)  # Ignore unsupported characters
    return ''.join(ciphertext)

# Preprocess input: Convert to lowercase, remove unsupported characters
def preprocess_input(input_text):
    return ''.join(c.lower() for c in input_text if c.isalnum() or c == ' ')

# Main function
def main():
    import sys
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} \"plaintext message\"")
        return

    # Combine input into a single string
    input_text = ' '.join(sys.argv[1:])
    
    # Preprocess plaintext
    plaintext = preprocess_input(input_text)
    
    # Encrypt plaintext
    ciphertext = rotor_encrypt(plaintext)
    
    # Convert to uppercase and print output
    print(ciphertext.upper())

if __name__ == "__main__":
    main()
