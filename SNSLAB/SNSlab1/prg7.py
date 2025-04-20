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

def solve_linear_congruence(a, b, m):
    gcd, x, _ = extended_euclidean(a, m)
    
    if b % gcd == 0:
        print("Solution exists")
        print(f"Number of solutions = {gcd}")
        
        solution = (x * (b // gcd)) % m
        step = m // gcd
        
        for i in range(int(gcd)):
            print(f"x = {solution}")
            solution = (solution + step) % m
    else:
        print("Solution does not exist")

def main():
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} <a> <b> <m>")
        sys.exit(1)
    
    a = gmpy2.mpz(sys.argv[1])
    b = gmpy2.mpz(sys.argv[2])
    m = gmpy2.mpz(sys.argv[3])
    
    solve_linear_congruence(a, b, m)

if __name__ == "__main__":
    main()
