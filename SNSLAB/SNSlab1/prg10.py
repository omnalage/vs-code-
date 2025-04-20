import gmpy2
from gmpy2 import mpz

def gcd(a, b):
    return gmpy2.gcd(a, b)

def euler_totient(m):
    count = mpz(0)
    for i in range(1, m):
        if gcd(i, m) == 1:
            count += 1
    return count

def modular_exponentiation(a, x, n):
    return gmpy2.powmod(a, x, n)

def find_order(a, m):
    k = mpz(1)
    while True:
        if modular_exponentiation(a, k, m) == 1:
            return k
        k += 1

def find_primitive_roots(m):
    phi_m = euler_totient(m)
    num_primitive_roots = euler_totient(phi_m)
    
    print(f"Number of primitive roots modulo {m}: {num_primitive_roots}")
    print(f"Primitive roots modulo {m}:", end=" ")
    
    for g in range(2, m):
        if gcd(g, m) == 1:
            if find_order(g, m) == phi_m:
                print(g, end=" ")
    print()

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <m>")
        sys.exit(1)
    
    m = mpz(sys.argv[1])
    find_primitive_roots(m)
