import numpy as np


def generate(n: int, m: int, max_val: int):
    matrix = np.random.randint(0, max_val + 1, (n, n))
    q, r = np.linalg.qr(matrix)
    while np.linalg.matrix_rank(r) != n:
        q, r = np.linalg.qr(matrix)
    for i in range(n, m):
        row = np.random.randint(0, max_val + 1, (1, n))
        matrix = np.vstack((matrix, row))
    cost = np.random.randint(0, max_val + 1, (m, 1))
    matrix = np.hstack((matrix, cost))
    return matrix


n_list = [2, 10, 20, 30, 40, 50]
m_list = np.asarray([np.random.randint(n, n * 2) for n in n_list])
print(m_list)
for k in range(len(n_list)):
    n = n_list[k]
    m = m_list[k]
    with open("input" + str(n), "w") as test_file:
        test_file.write('{0} {1}\n'.format(m, n))
        matrix = generate(n, m, 50)
        for row in range(0, m):
            for col in range(0, n + 1):
                test_file.write('{0} '.format(matrix[row][col]))
            test_file.write('\n')
