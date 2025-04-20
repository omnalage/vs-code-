#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include <openssl/sha.h>

// Helper to hash message and convert to GMP integer
void hash_to_mpz(mpz_t result, const char *message) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)message, strlen(message), hash);
    mpz_import(result, SHA256_DIGEST_LENGTH, 1, 1, 0, 0, hash);
}

// RSA key generation
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

    // e = 65537 (common choice)
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
    mpz_t n, e, d, phi, hashed_msg, signature, verify;
    mpz_inits(n, e, d, phi, hashed_msg, signature, verify, NULL);

    // RSA Keygen (now included)
    rsa_keygen(n, e, d, phi);

    // Message to sign
    char msg[] = "Hello, FDH Signature!";
    hash_to_mpz(hashed_msg, msg);
    gmp_printf("Hashed message: %Zd\n", hashed_msg);

    // Sign: s = H(m)^d mod n
    mpz_powm(signature, hashed_msg, d, n);
    gmp_printf("Signature: %Zd\n", signature);

    // Verify: v = s^e mod n
    mpz_powm(verify, signature, e, n);
    gmp_printf("Verification value: %Zd\n", verify);

    if (mpz_cmp(verify, hashed_msg) == 0)
        printf("Signature verified successfully!\n");
    else
        printf("Signature verification failed!\n");

    mpz_clears(n, e, d, phi, hashed_msg, signature, verify, NULL);
    return 0;
}
