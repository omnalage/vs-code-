#include <stdio.h>
#include <gmp.h>
#include <time.h>

void generate_rsa_keys(mpz_t n, mpz_t e, mpz_t d) {
    mpz_t p, q, phi, gcd, p_minus1, q_minus1;
    gmp_randstate_t state;

    mpz_inits(p, q, phi, e, d, gcd, p_minus1, q_minus1, NULL);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_urandomb(p, state, 512);
    mpz_nextprime(p, p);
    mpz_urandomb(q, state, 512);
    mpz_nextprime(q, q);

    mpz_mul(n, p, q);

    mpz_sub_ui(p_minus1, p, 1);
    mpz_sub_ui(q_minus1, q, 1);
    mpz_mul(phi, p_minus1, q_minus1);

    mpz_set_ui(e, 3);
    while (1) {
        mpz_gcd(gcd, e, phi);
        if (mpz_cmp_ui(gcd, 1) == 0) break;
        mpz_add_ui(e, e, 1);
    }

    if (mpz_invert(d, e, phi) == 0) {
        printf("Error: Modular inverse for d not found.\n");
        return;
    }

    mpz_clears(p, q, phi, gcd, p_minus1, q_minus1, NULL);
    gmp_randclear(state);
}

void sign_message(mpz_t signature, const mpz_t message, const mpz_t d, const mpz_t n) {
    mpz_powm(signature, message, d, n); 
}

int verify_signature(const mpz_t signature, const mpz_t message, const mpz_t e, const mpz_t n) {
    mpz_t decrypted;
    mpz_init(decrypted);

    mpz_powm(decrypted, signature, e, n);

    int is_valid = (mpz_cmp(decrypted, message) == 0);
    mpz_clear(decrypted);
    return is_valid;
}

int main() {
    mpz_t ca_n, ca_e, ca_d; 
    mpz_t message, signature; 

    mpz_inits(ca_n, ca_e, ca_d, message, signature, NULL);

    generate_rsa_keys(ca_n, ca_e, ca_d);
    printf("\nCertificate Authority (CA) Public Key:\n");
    gmp_printf("  n: %Zd\n  e: %Zd\n\n", ca_n, ca_e);
    printf("Certificate Authority (CA) Public Key:\n");
    gmp_printf("  n: %Zd\n  d: %Zd\n\n", ca_n, ca_d);

    mpz_set_ui(message, 123456789);
    gmp_printf("Certificate Content (Message): %Zd\n\n", message);

    sign_message(signature, message, ca_d, ca_n);
    gmp_printf("Digital Signature: %Zd\n\n", signature);

    if (verify_signature(signature, message, ca_e, ca_n)) {
        printf("Signature Verification: SUCCESS ✅ (Certificate is valid)\n\n");
    } else {
        printf("Signature Verification: FAILED ❌ (Certificate is invalid)\n");
    }

    mpz_clears(ca_n, ca_e, ca_d, message, signature, NULL);
    return 0;
}
