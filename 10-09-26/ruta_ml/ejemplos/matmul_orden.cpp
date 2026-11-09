#include <iostream>
#include <vector>
#include <chrono>

using Mat = std::vector<double>;                            // n*n en una sola tira (fila a fila)

template <class F> double ms(F f) {
    auto t = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t).count();
}

int main() {
    const int n = 400;
    Mat A(n * n, 1.0), B(n * n, 2.0), C1(n * n, 0.0), C2(n * n, 0.0);

    double t1 = ms([&] {                                    // orden i-j-k: B se recorre "saltando" filas
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            double s = 0;
            for (int k = 0; k < n; ++k) s += A[i * n + k] * B[k * n + j];
            C1[i * n + j] = s;
        }
    });
    double t2 = ms([&] {                                    // orden i-k-j: todo se recorre seguido
        for (int i = 0; i < n; ++i) for (int k = 0; k < n; ++k) {
            double a = A[i * n + k];
            for (int j = 0; j < n; ++j) C2[i * n + j] += a * B[k * n + j];
        }
    });
    std::cout << "i-j-k: " << t1 << " ms   i-k-j: " << t2 << " ms   mismo resultado: " << (C1 == C2) << "\n";
}
