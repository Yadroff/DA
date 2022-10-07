import random


def generate(step: int):
    n = 10 ** step - 1
    m = random.randint(1, min(n // 10, 10**5))
    return [n, m]


l = [2, 3, 4, 5, 6, 7, 8, 9]
for i in range(len(l)):
    with open("tests/10^" + str(l[i]) , "w") as test_file:
        n, m = generate(l[i])
        test_file.write(str(n) + ' ' + str(m) + '\n')
