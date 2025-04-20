import gmpy2

def modular_exponentiation(a, x, n):
    result = gmpy2.mpz(1)
    temp = gmpy2.mpz(a)
    exp = gmpy2.mpz(x)
    
    while exp > 0:
        if exp % 2 == 1:
            result = (result * temp) % n
        temp = (temp * temp) % n
        exp //= 2
    
    return result

def find_order(a, m):
    k = gmpy2.mpz(1)
    
    while True:
        if modular_exponentiation(a, k, m) == 1:
            return k
        k += 1

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <a> <m>")
        sys.exit(1)
    
    a = gmpy2.mpz(sys.argv[1])
    m = gmpy2.mpz(sys.argv[2])
    
    order = find_order(a, m)
    print(f"The order of {a} under modulo {m} is {order}")
