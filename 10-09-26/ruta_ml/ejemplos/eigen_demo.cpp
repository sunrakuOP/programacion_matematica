#include <iostream>
#include <chrono>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main() {
    // 1) multiplicacion 400x400
    MatrixXd A = MatrixXd::Random(400, 400), B = MatrixXd::Random(400, 400);
    auto t0 = std::chrono::steady_clock::now();
    MatrixXd C = A * B;
    double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
    std::cout << "A * B (400x400) con Eigen: " << ms << " ms   (C[0,0] = " << C(0, 0) << ")\n\n";

    // 2) minimos cuadrados mal condicionado: polinomio de grado 10, 200 puntos, SIN ruido, coeficientes reales = 1
    const int n = 200, d = 11;
    MatrixXd X(n, d);
    for (int i = 0; i < n; ++i) for (int j = 0; j < d; ++j) X(i, j) = std::pow(i / double(n - 1), j);
    VectorXd w_real = VectorXd::Ones(d), y = X * w_real;

    VectorXd w_normales = (X.transpose() * X).ldlt().solve(X.transpose() * y);   // ecuaciones normales
    VectorXd w_qr = X.colPivHouseholderQr().solve(y);                             // QR directo sobre X
    std::cout << "error relativo del coeficiente recuperado (real: todos 1):\n";
    std::cout << "  ecuaciones normales: " << (w_normales - w_real).norm() / w_real.norm() << "\n";
    std::cout << "  QR:                  " << (w_qr - w_real).norm() / w_real.norm() << "\n";
}
