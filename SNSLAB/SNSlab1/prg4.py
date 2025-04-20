import gmpy2
import sys

def euler_totient(n):
    m = gmpy2.mpz(n)
    phi_m = gmpy2.mpz(0)
    
    for div in range(1, int(m)):
        if gmpy2.gcd(div, m) == 1:
            print(div)
            phi_m += 1
    
    print(f"φ({m}) = {phi_m}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <number>")
        sys.exit(1)
    
    n = sys.argv[1]
    if not n.isdigit():
        print("Please enter a valid positive integer.")
        sys.exit(1)
    
    euler_totient(n)