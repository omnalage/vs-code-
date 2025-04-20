# Prog8.py: This program implements the Rail Fence Cipher for encryption and decryption.
# It rearranges the characters in a zigzag pattern across two rails.

import gmpy2 # type: ignore

def rail_fence_encrypt(plaintext):
    rail1 = []
    rail2 = []
    for i, char in enumerate(plaintext):
        if gmpy2.is_even(i):
            rail1.append(char)
        else:
            rail2.append(char)
    
    # Combine the characters in both rails
    ciphertext = ''.join(rail1 + rail2)
    return ciphertext

def rail_fence_decrypt(ciphertext):
    mid = int(gmpy2.ceil(len(ciphertext) / 2))  # Convert to integer
    rail1 = ciphertext[:mid]
    rail2 = ciphertext[mid:]
    
    plaintext = []
    for i in range(mid):
        plaintext.append(rail1[i])
        if i < len(rail2):
            plaintext.append(rail2[i])
    
    return ''.join(plaintext)

def main():
    message = "I AM AT VNIT NAGPUR"
    print("Original Message:", message)

    # Encryption
    ciphertext = rail_fence_encrypt(message.replace(" ", ""))
    print("Encrypted Message:", ciphertext)

    # Decryption
    decrypted_message = rail_fence_decrypt(ciphertext)
    print("Decrypted Message:", decrypted_message)

if __name__ == "__main__":
    main()
