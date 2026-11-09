#include <fstream>
#include <vector>
#include <random>
#include <string>

struct P { double x, y; int clase; };

// Escribe un SVG: puntos coloreados por clase + una recta (y = m x + c).  Se abre en el navegador.
void escribirSVG(const std::string& ruta, const std::vector<P>& pts, double m, double c,
                 double xmin, double xmax, double ymin, double ymax) {
    const int W = 480, H = 360;
    auto X = [&](double x) { return (x - xmin) / (xmax - xmin) * W; };
    auto Y = [&](double y) { return H - (y - ymin) / (ymax - ymin) * H; };    // el eje y de SVG crece hacia abajo
    std::ofstream f(ruta);
    f << "<svg xmlns='http://www.w3.org/2000/svg' width='" << W << "' height='" << H << "' style='background:#fff'>\n";
    for (const P& p : pts)
        f << "<circle cx='" << X(p.x) << "' cy='" << Y(p.y) << "' r='3' fill='" << (p.clase ? "#d95f02" : "#1b9e77") << "'/>\n";
    f << "<line x1='" << X(xmin) << "' y1='" << Y(m * xmin + c) << "' x2='" << X(xmax) << "' y2='" << Y(m * xmax + c)
      << "' stroke='black' stroke-width='2'/>\n</svg>\n";
}

int main() {
    std::mt19937 g(1);
    std::normal_distribution<double> r(0, 1);
    std::vector<P> pts;
    for (int i = 0; i < 150; ++i) { int c = i % 2; double mu = c ? 1.5 : -1.5; pts.push_back({mu + r(g), mu + r(g), c}); }
    escribirSVG("puntos.svg", pts, -1.0, 0.0, -5, 5, -5, 5);     // la frontera ideal: x + y = 0
}
