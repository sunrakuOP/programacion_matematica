import time
import numpy as np

n = 120
A = np.random.default_rng(0).random((n, n)); B = np.random.default_rng(1).random((n, n))

def matmul_python(A, B):                                    # el triple bucle, igual que en C++
    n = len(A); C = [[0.0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            s = 0.0
            for k in range(n):
                s += A[i][k] * B[k][j]
            C[i][j] = s
    return C

La, Lb = A.tolist(), B.tolist()
t = time.perf_counter(); C1 = matmul_python(La, Lb); t_py = (time.perf_counter() - t) * 1000
t = time.perf_counter(); C2 = A @ B; t_np = (time.perf_counter() - t) * 1000
print(f"n = {n}:  Python puro = {t_py:.1f} ms   NumPy (A @ B) = {t_np:.3f} ms   mismo resultado = {np.allclose(C1, C2)}")

big = np.random.default_rng(2).random((400, 400))
t = time.perf_counter(); big @ big; t_big = (time.perf_counter() - t) * 1000
print(f"n = 400:  NumPy = {t_big:.2f} ms   (mi C++ con el orden i-k-j: 16 ms)")

x = np.linspace(0, 10, 5)
print("broadcasting:  x =", x, "\n               (x - x.mean()) / x.std() =", np.round((x - x.mean()) / x.std(), 3))
