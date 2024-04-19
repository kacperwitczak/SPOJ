from decimal import Decimal, getcontext
 
 
def solve(a_p, b_p, c_p, k_p):
    getcontext().prec = k_p + 11
    delta = b_p * b_p - 4 * a_p * c_p
    if delta < 0:
        return [0]
    elif delta == 0:
        x = -b_p / (2 * a_p)
        return [1, x]
    else:
        x1 = (-b_p - delta.sqrt()) / (2 * a_p)
        x2 = (-b_p + delta.sqrt()) / (2 * a_p)
        x1_r = min(x1, x2)
        x2_r = max(x1, x2)
        return [2, x1_r, x2_r]
 
 
t = int(input())
while t > 0:
    paramsList = input()
    params = paramsList.split(' ')
    a = Decimal(params[0])
    b = Decimal(params[1])
    c = Decimal(params[2])
    k = int(params[3])
    result = solve(a, b, c, k)
    print(*result)
    t -= 1
