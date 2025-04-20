import gmpy2

def extended_euclidean(a, b):
    # Initialize variables
    x0, y0, x1, y1 = gmpy2.mpz(1), gmpy2.mpz(0), gmpy2.mpz(0), gmpy2.mpz(1)
    
    while b != 0:
        q = a // b  # Quotient
        a, b = b, a % b  # Update a and b
        x0, x1 = x1, x0 - q * x1  # Update x
        y0, y1 = y1, y0 - q * y1  # Update y
    
    return x0, y0, a  # x, y, and gcd(a, b)

# Input values
a = gmpy2.mpz(input("Enter the value of a: "))
b = gmpy2.mpz(input("Enter the value of b: "))

# Calculate x, y, gcd
x, y, gcd = extended_euclidean(a, b)

# Ensure x < y
if x > y:
    x, y = y, x

# Output the result
print(f"The values of x and y are: x = {x}, y = {y}")
print(f"The gcd(a, b) is: {gcd}")
