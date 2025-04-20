import gmpy2
import sys

def find_common_divisors(numbers):
    # Compute the GCD of all numbers
    gcd = numbers[0]
    for num in numbers[1:]:
        gcd = gmpy2.gcd(gcd, num)
    
    # Find all divisors of the GCD
    divisors = []
    gcd_int = int(gcd)
    for i in range(1, gcd_int + 1):
        if gcd_int % i == 0:
            divisors.append(i)
    
    return divisors

# Input
input_data = input("Enter the number of integers followed by the integers themselves: ").split()
n = int(input_data[0])  # First value is the number of integers
numbers = [gmpy2.mpz(num) for num in input_data[1:1 + n]]  # Read the integers



# Find and print common divisors
common_divisors = find_common_divisors(numbers)
print("The common divisors are:", *common_divisors)
