#include <iostream>
#include <vector>
#include <iomanip>

using Img = std::vector<std::vector<double>>;

// convolucion "valida" (sin relleno): la salida es mas chica que la entrada
Img convolucion(const Img& in, const Img& k) {
    int H = in.size(), W = in[0].size(), kh = k.size(), kw = k[0].size();
    Img out(H - kh + 1, std::vector<double>(W - kw + 1, 0.0));
    for (int i = 0; i + kh <= H; ++i)
        for (int j = 0; j + kw <= W; ++j)
            for (int a = 0; a < kh; ++a)
                for (int b = 0; b < kw; ++b)
                    out[i][j] += in[i + a][j + b] * k[a][b];
    return out;
}

int main() {
    Img img(6, std::vector<double>(6, 0.0));                // izquierda oscura (0), derecha clara (9)
    for (auto& fila : img) for (int j = 3; j < 6; ++j) fila[j] = 9;
    Img sobelX = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};      // detecta bordes verticales

    Img r = convolucion(img, sobelX);
    for (auto& fila : r) { for (double v : fila) std::cout << std::setw(4) << v; std::cout << "\n"; }
}
