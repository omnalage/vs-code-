import gmpy2
import sys

def fermat_little_theorem(a, x, n):
    a = gmpy2.mpz(a)
    x = gmpy2.mpz(x)
    n = gmpy2.mpz(n)
    
    print("Using Fermat's Little Theorem")
    print(f"{a}^({x}-1) mod {n} = 1")
    
    new_x = x % (n - 1)
    result = gmpy2.powmod(a, new_x, n)
    
    print(f"Result: {result}")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} <a> <x> <n>")
        sys.exit(1)
    
    a, x, n = sys.argv[1], sys.argv[2], sys.argv[3]
    
    if not (a.isdigit() and x.isdigit() and n.isdigit()):
        print("Please enter valid positive integers.")
        sys.exit(1)
    
    fermat_little_theorem(a, x, n)