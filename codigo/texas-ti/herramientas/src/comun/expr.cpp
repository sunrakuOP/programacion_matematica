#include "expr.hpp"
#include <cctype>
#include <cmath>
#include <cstdlib>

// Descenso recursivo. Precedencia (menor a mayor): + -  |  * /  |  menos unario  |  ^
// El unario va por debajo de ^ para que -2^2 = -4, y ^ asocia a la derecha (2^3^2 = 512).
namespace {

struct Parser {
    const char* p;
    double x, y;
    bool err;

    void skip() { while (*p == ' ') ++p; }
    bool eat(char c) {
        skip();
        if (*p == c) { ++p; return true; }
        return false;
    }

    double expr() {
        double v = term();
        for (;;) {
            if (eat('+')) v += term();
            else if (eat('-')) v -= term();
            else return v;
        }
    }
    double term() {
        double v = unary();
        for (;;) {
            if (eat('*')) v *= unary();
            else if (eat('/')) v /= unary();
            else return v;
        }
    }
    double unary() {
        if (eat('-')) return -unary();
        if (eat('+')) return unary();
        return power();
    }
    double power() {
        double base = atom();
        if (eat('^')) return std::pow(base, unary());
        return base;
    }
    double atom() {
        skip();
        if (*p == '(') {
            ++p;
            double v = expr();
            if (!eat(')')) err = true;
            return v;
        }
        if (std::isdigit((unsigned char)*p) || *p == '.') return number();
        if (std::isalpha((unsigned char)*p)) return name();
        err = true;
        return 0;
    }
    double number() {
        const char* s = p;
        while (std::isdigit((unsigned char)*p)) ++p;
        if (*p == '.') {
            ++p;
            while (std::isdigit((unsigned char)*p)) ++p;
        }
        // exponente solo si de verdad sigue un numero (para no confundir con la constante e)
        if ((*p == 'e' || *p == 'E') &&
            (std::isdigit((unsigned char)p[1]) ||
             ((p[1] == '+' || p[1] == '-') && std::isdigit((unsigned char)p[2])))) {
            p += 2;
            while (std::isdigit((unsigned char)*p)) ++p;
        }
        if (p - s == 1 && *s == '.') { err = true; return 0; }
        return std::strtod(std::string(s, p - s).c_str(), nullptr);
    }
    double name() {
        std::string id;
        while (std::isalpha((unsigned char)*p)) id += *p++;
        skip();
        if (*p == '(') {
            ++p;
            double a = expr();
            if (!eat(')')) { err = true; return 0; }
            if (id == "sin")  return std::sin(a);
            if (id == "cos")  return std::cos(a);
            if (id == "tan")  return std::tan(a);
            if (id == "asin") return std::asin(a);
            if (id == "acos") return std::acos(a);
            if (id == "atan") return std::atan(a);
            if (id == "exp")  return std::exp(a);
            if (id == "ln")   return std::log(a);
            if (id == "log")  return std::log10(a);
            if (id == "sqrt") return std::sqrt(a);
            if (id == "abs")  return std::fabs(a);
            err = true;
            return 0;
        }
        if (id == "x")  return x;
        if (id == "y")  return y;
        if (id == "pi") return 3.14159265358979323846;
        if (id == "e")  return 2.71828182845904523536;
        err = true;
        return 0;
    }
};

}  // namespace

double Expr::eval(double x, double y) const {
    Parser ps{src.c_str(), x, y, false};
    double v = ps.expr();
    ps.skip();
    if (ps.err || *ps.p != '\0') return std::nan("");
    return v;
}

bool compilar(const std::string& s, Expr& out) {
    Parser ps{s.c_str(), 1.0, 1.0, false};
    ps.expr();
    ps.skip();
    if (ps.err || *ps.p != '\0' || s.empty()) return false;
    out.src = s;
    return true;
}
