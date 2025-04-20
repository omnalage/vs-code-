#include <stdio.h>
#include <gmp.h>

int main()
{
    // Declare variables for large integers (mpz_t type) to store keys, messages, and ciphertexts
    mpz_t p, g, x, h, m, y, c1, c2, s, decrypted;
    mpz_inits(p, g, x, h, m, y, c1, c2, s, decrypted, NULL); // Initialize all variables to zero

    // Declare and initialize a random state variable for generating random numbers
    gmp_randstate_t state;
    gmp_randinit_default(state);

    // Generate a large prime number 'p'
    mpz_urandomb(p, state, 512);
    mpz_nextprime(p, p);

    // Set the generator 'g' to a small prime number (commonly 2)
    mpz_set_ui(g, 2);

    // Generate the private key 'x' (random number less than 'p')
    mpz_urandomm(x, state, p);

    // Compute the public key component 'h = g^x mod p'
    mpz_powm(h, g, x, p);

    // Set the plaintext message 'm'
    mpz_set_ui(m, 12345); // Example message to be encrypted

    // Encryption process starts here
    mpz_urandomm(y, state, p);
    mpz_powm(c1, g, y, p);
    mpz_powm(s, h, y, p);
    mpz_mul(c2, m, s);
    mpz_mod(c2, c2, p);

    // Display the ciphertext (c1, c2)
    gmp_printf("Ciphertext (c1, c2):\n c1 = %Zd\n c2 = %Zd\n", c1, c2);

    // Decryption process starts here
    mpz_powm(s, c1, x, p);
    mpz_invert(s, s, p);
    mpz_mul(decrypted, c2, s);
    mpz_mod(decrypted, decrypted, p); // Decrypted message = (c2 * s^-1) mod p

    // Display the decrypted message
    gmp_printf("Decrypted message: %Zd\n", decrypted);

    // Free allocated memory for GMP variables
    mpz_clears(p, g, x, h, m, y, c1, c2, s, decrypted, NULL);
    gmp_randclear(state);

    return 0;
}
