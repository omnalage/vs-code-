#include <stdio.h>
#include <gmp.h> 
void rsa_keygen(mpz_t n, mpz_t e, mpz_t d, mpz_t phi) {
    mpz_t p, q, gcd;
    mpz_inits(p, q, gcd, NULL);

    // Generate two large primes
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_urandomb(p, state, 512);
    mpz_nextprime(p, p);
    mpz_urandomb(q, state, 512);
    mpz_nextprime(q, q);

    // n = p * q
    mpz_mul(n, p, q);

    // phi = (p-1)*(q-1)
    mpz_t p1, q1;
    mpz_inits(p1, q1, NULL);
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi, p1, q1);

    // e = 65537 
    mpz_set_ui(e, 65537);
    mpz_gcd(gcd, e, phi);
    while (mpz_cmp_ui(gcd, 1) != 0) {
        mpz_add_ui(e, e, 2);
        mpz_gcd(gcd, e, phi);
    }

    // d = e^{-1} mod phi
    mpz_invert(d, e, phi);

    mpz_clears(p, q, p1, q1, gcd, NULL);
    gmp_randclear(state);
}

int main() {
    mpz_t n, e, d, phi, message, cipher, decrypted;
    mpz_inits(n, e, d, phi, message, cipher, decrypted, NULL);

    rsa_keygen(n, e, d, phi);

    gmp_printf("Public Key (n, e):\n n = %Zd\n e = %Zd\n", n, e);
    gmp_printf("Private Key (d): %Zd\n", d);

    // Message
    mpz_set_ui(message, 12345);
    gmp_printf("Original message: %Zd\n", message);

    // Encrypt: c = m^e mod n
    mpz_powm(cipher, message, e, n);
    gmp_printf("Encrypted message: %Zd\n", cipher);

    // Decrypt: m = c^d mod n
    mpz_powm(decrypted, cipher, d, n);
    gmp_printf("Decrypted message: %Zd\n", decrypted);

    mpz_clears(n, e, d, phi, message, cipher, decrypted, NULL);
    return 0;
}
