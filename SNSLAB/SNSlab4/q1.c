#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>

/*

Public Keys
--> Alice computes [x = G^a mod P]
--> Bob computes   [y = G^b mod P]

*/

void compute_gcd(mpz_t result, const mpz_t a, const mpz_t b)
{
    mpz_t temp_a, temp_b, temp_mod;
    mpz_init_set(temp_a, a);
    mpz_init_set(temp_b, b);
    mpz_init(temp_mod);

    while (mpz_sgn(temp_b) != 0)
    {
        mpz_mod(temp_mod, temp_a, temp_b);
        mpz_set(temp_a, temp_b);
        mpz_set(temp_b, temp_mod);
    }

    mpz_set(result, temp_a);
    mpz_clears(temp_a, temp_b, temp_mod, NULL);
}

void compute_totient(mpz_t totient, const mpz_t m)
{
    mpz_t i, gcd;
    mpz_init(i);
    mpz_init(gcd);
    mpz_set_ui(totient, 0);

    for (mpz_set_ui(i, 1); mpz_cmp(i, m) < 0; mpz_add_ui(i, i, 1))
    {
        compute_gcd(gcd, i, m);
        if (mpz_cmp_ui(gcd, 1) == 0)
        {
            mpz_add_ui(totient, totient, 1);
        }
    }

    mpz_clears(i, gcd, NULL);
}

void compute_order(mpz_t order, const mpz_t a, const mpz_t m, const mpz_t totient)
{
    mpz_t i, power_result;
    mpz_inits(i, power_result, NULL);

    for (mpz_set_ui(i, 1); mpz_cmp(i, totient) <= 0; mpz_add_ui(i, i, 1))
    {
        mpz_powm(power_result, a, i, m);
        if (mpz_cmp_ui(power_result, 1) == 0)
        {
            mpz_set(order, i);
            break;
        }
    }

    mpz_clears(i, power_result, NULL);
}

void find_primitive_root(mpz_t root, const mpz_t P)
{
    mpz_t totient, i, gcd, ord;
    mpz_inits(totient, i, gcd, ord, NULL);
    compute_totient(totient, P);

    for (mpz_set_ui(i, 1); mpz_cmp(i, P) < 0; mpz_add_ui(i, i, 1))
    {
        compute_gcd(gcd, i, P);
        if (mpz_cmp_ui(gcd, 1) == 0)
        {
            compute_order(ord, i, P, totient);
            if (mpz_cmp(ord, totient) == 0)
            {
                mpz_set(root, i);
                break;
            }
        }
    }

    mpz_clears(totient, i, gcd, ord, NULL);
}

void mod_exp(mpz_t result, const mpz_t base, const mpz_t exp, const mpz_t mod)
{
    mpz_powm(result, base, exp, mod);
}

int main()
{

    mpz_t P, G, a, b, A, B, Ka, Kb;
    mpz_inits(P, G, a, b, A, B, Ka, Kb, NULL);
    
    // Select a prime number P
    gmp_printf("\nEnter a prime number (P): ");
    gmp_scanf("%Zd", P);

    // Find a primitive root G
    find_primitive_root(G, P);
    gmp_printf("Primitive root (G) of P: %Zd\n\n", G);

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    // Generate random private keys for Alice(a) and Bob(b)
    mpz_urandomm(a, state, P);
    mpz_urandomm(b, state, P);
    
    gmp_printf("Alice's private key (a) : %Zd\n", a);
    gmp_printf("Bob's private key (b)   : %Zd\n\n", b);

    // Compute public keys for Alice(A) and Bob(B)
    mod_exp(A, G, a, P);  // A = G^a mod P
    mod_exp(B, G, b, P);  // B = G^b mod P

    gmp_printf("Alice's public key (A) : %Zd\n", A);
    gmp_printf("Bob's public key (B)   : %Zd\n\n", B);

    // Exchange public keys and compute shared secret key
    mod_exp(Ka, B, a, P);  // Ka = B^a mod P
    mod_exp(Kb, A, b, P);  // Kb = A^b mod P

    gmp_printf("Alice's computed secret key (Ka) : %Zd\n", Ka);
    gmp_printf("Bob's computed secret key (Kb)   : %Zd\n\n", Kb);

    if (mpz_cmp(Ka, Kb) == 0) {
        printf("Diffie-Hellman Key Exchange Successful! Shared Secret Key Matched.\n\n");
    } else {
        printf("Error: Shared Secret Key Mismatch!\n");
    }

    mpz_clears(P, G, a, b, A, B, Ka, Kb, NULL);
    gmp_randclear(state);
    
    return 0;
}
