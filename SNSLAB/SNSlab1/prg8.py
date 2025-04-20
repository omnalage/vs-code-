import gmpy2

def extended_euclid(a, b):
    if b == 0:
        return (a, 1, 0)
    d, x1, y1 = extended_euclid(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return d, x, y

def normalize(x, mod):
    x %= mod
    return x + mod if x < 0 else x

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)

def lcm(a, b):
    return (a // gcd(a, b)) * b

def check_coprime(n):
    t = len(n)
    for i in range(t):
        for j in range(i + 1, t):
            if gcd(n[i], n[j]) != 1:
                return False
    return True

def inverse(a, m):
    d, x, _ = extended_euclid(a, m)
    return normalize(x, m) if d == 1 else -1

def convert(a, b, n):
    for i in range(len(a)):
        inv = inverse(a[i], n[i])
        if inv == -1:
            return False  # No solution exists
        b[i] = normalize(b[i] * inv, n[i])
    return True

def solve(a, n):
    if not check_coprime(n):
        return None, None
    
    lcm_mod = n[0]
    for i in range(1, len(n)):
        lcm_mod = lcm(lcm_mod, n[i])
    
    m1 = [lcm_mod // ni for ni in n]
    m1_inv = [inverse(m1[i], n[i]) for i in range(len(n))]
    
    if any(x == -1 for x in m1_inv):
        return None, None
    
    result = sum(a[i] * m1[i] * m1_inv[i] for i in range(len(n)))
    result = normalize(result, lcm_mod)
    
    return result, lcm_mod

if __name__ == "__main__":
    t = int(input("Enter number of equations: "))
    a, b, n = [], [], []
    
    print("Enter a, b, n for each equation (ax ≡ b (mod n)):")
    for _ in range(t):
        ai, bi, ni = map(int, input().split())
        if ni <= 0:
            print(f"Invalid modulus at equation {_ + 1}")
            exit(1)
        a.append(ai)
        b.append(normalize(bi, ni))
        n.append(ni)
    
    if not convert(a, b, n):
        print("No solution exists")
        exit(1)
    
    result, mod = solve(b, n)
    if result is None:
        print("No solution exists: moduli are not pairwise coprime")
    else:
        print(f"The solution is {result}")
        print(f"The mod is {mod}")
