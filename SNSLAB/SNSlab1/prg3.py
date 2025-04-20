import gmpy2
from gmpy2 import mpz
import sys

def prime_factorization(n):
    n = mpz(n)  # Convert to arbitrary precision integer
    factors = []
    
    # Check divisibility by 2
    while gmpy2.is_divisible(n, 2):
        factors.append(2)
        n //= 2
    
    # Check divisibility by odd numbers starting from 3
    factor = mpz(3)
    while factor * factor <= n:
        while gmpy2.is_divisible(n, factor):
            factors.append(int(factor))
            n //= factor
        factor += 2
    
    # If n is still greater than 1, then it is a prime number
    if n > 1:
        factors.append(int(n))
    
    return factors

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python filename.py <integer>")
        sys.exit(1)
    
    try:
        num = int(sys.argv[1])
        if num < 1:
            print("Enter a positive integer greater than zero.")
        else:
            print(" ".join(map(str, prime_factorization(num))))
    except ValueError:
        print("Please enter a valid integer.")