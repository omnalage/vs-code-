import gmpy2
import sys

def extended_euclidean(a, b):
    if b == 0:
        return a, gmpy2.mpz(1), gmpy2.mpz(0)
    
    x2, x1, y2, y1 = gmpy2.mpz(1), gmpy2.mpz(0), gmpy2.mpz(0), gmpy2.mpz(1)
    
    while b > 0:
        q, r = divmod(a, b)
        x = x2 - q * x1
        y = y2 - q * y1
        a, b, x2, x1, y2, y1 = b, r, x1, x, y1, y
    
    return a, x2, y2

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <a> <m>")
        sys.exit(1)
    
    a = gmpy2.mpz(sys.argv[1])
    m = gmpy2.mpz(sys.argv[2])
    gcd, x, y = extended_euclidean(a, m)
    
    print(f"GCD: {gcd}")
    print(f"x: {x}")
    print(f"y: {y}")
    
    if gcd == 1:
        x = x % m if x < 0 else x
        print("Exists")
        print(f"Inverse: {x}")
    else:
        print("Does not exist")

if __name__ == "__main__":
    main()
