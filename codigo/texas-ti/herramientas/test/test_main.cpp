// Pruebas en la Mac (no corren en la calculadora): make test
// Los valores esperados se calcularon aparte con Python (fracciones exactas / formulas directas).
#include <cmath>
#include <cstdio>
#include "expr.hpp"
#include "fluidos.hpp"
#include "numerico.hpp"
#include "termo.hpp"

static int fallos = 0, total = 0;

static void cerca(const char* nombre, double obtenido, double esperado, double tol) {
    ++total;
    if (!(std::fabs(obtenido - esperado) <= tol)) {
        ++fallos;
        std::printf("FALLA %-34s obtenido=%.10g esperado=%.10g\n", nombre, obtenido, esperado);
    }
}
static void verdad(const char* nombre, bool cond) {
    ++total;
    if (!cond) { ++fallos; std::printf("FALLA %s\n", nombre); }
}
static Expr E(const char* s) {
    Expr e;
    bool ok = compilar(s, e);
    if (!ok) std::printf("(no compila: %s)\n", s);
    return e;
}

int main() {
    // ---- expresiones ----
    cerca("2+3*4", E("2+3*4").eval(), 14, 1e-12);
    cerca("-2^2", E("-2^2").eval(), -4, 1e-12);
    cerca("2^3^2", E("2^3^2").eval(), 512, 1e-12);
    cerca("2^-1", E("2^-1").eval(), 0.5, 1e-12);
    cerca("(1+2)*3", E("(1+2)*3").eval(), 9, 1e-12);
    cerca("sin(pi/2)", E("sin(pi/2)").eval(), 1, 1e-12);
    cerca("ln(e)", E("ln(e)").eval(), 1, 1e-12);
    cerca("1e-3*2", E("1e-3*2").eval(), 0.002, 1e-15);
    cerca("2*e", E("2*e").eval(), 2 * 2.718281828459045, 1e-12);
    cerca("0.046/100", E("0.046/100").eval(), 0.00046, 1e-15);
    cerca("x^2+y", E("x^2+y").eval(3, 1), 10, 1e-12);
    cerca("sqrt(16)", E("sqrt(16)").eval(), 4, 1e-12);
    Expr tmp;
    verdad("rechaza '2+'", !compilar("2+", tmp));
    verdad("rechaza 'sin('", !compilar("sin(", tmp));
    verdad("rechaza 'foo(1)'", !compilar("foo(1)", tmp));
    verdad("rechaza '2x'", !compilar("2x", tmp));
    verdad("rechaza '.'", !compilar(".", tmp));
    verdad("rechaza vacio", !compilar("", tmp));
    verdad("eval invalida -> NaN", std::isnan(Expr{"2+"}.eval()));

    // ---- raices: x^3-x-2 = 0 -> 1.5213797068 ----
    Expr f = E("x^3-x-2");
    Raiz r = biseccion(f, 1, 2, 1e-10, 200, false);
    verdad("biseccion ok", r.ok);
    cerca("biseccion", r.x, 1.5213797068045676, 1e-9);
    verdad("biseccion sin cambio de signo", !biseccion(f, 2, 3, 1e-8, 100, false).ok);
    r = newton(f, 1.5, 1e-12, 100, false);
    verdad("newton ok", r.ok);
    cerca("newton", r.x, 1.5213797068045676, 1e-9);
    r = secante(f, 1, 2, 1e-12, 100, false);
    verdad("secante ok", r.ok);
    cerca("secante", r.x, 1.5213797068045676, 1e-9);
    verdad("newton con f'=0 falla limpio", !newton(E("x^2+1"), 0, 1e-8, 20, false).ok);

    // ---- sistemas ----
    {
        double A[MAXN][MAXN] = {{2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
        double b[MAXN] = {8, -11, -3}, x[MAXN];
        verdad("gauss ok", gauss(3, A, b, x));
        cerca("gauss x", x[0], 2, 1e-12);
        cerca("gauss y", x[1], 3, 1e-12);
        cerca("gauss z", x[2], -1, 1e-12);
        double S[MAXN][MAXN] = {{1, 2}, {2, 4}};
        double bs[MAXN] = {1, 2};
        verdad("gauss singular detectado", !gauss(2, S, bs, x));
        double P[MAXN][MAXN] = {{0, 1}, {1, 0}};   // necesita pivoteo
        double bp[MAXN] = {3, 5};
        verdad("gauss pivoteo ok", gauss(2, P, bp, x));
        cerca("pivoteo x", x[0], 5, 1e-12);
        cerca("pivoteo y", x[1], 3, 1e-12);
    }
    {
        double A[MAXN][MAXN] = {{10, -1, 2}, {-1, 11, -1}, {2, -1, 10}};
        double b[MAXN] = {6, 25, -11}, x[MAXN] = {0, 0, 0};
        Seidel s = gaussSeidel(3, A, b, x, 1e-12, 1000);
        verdad("seidel ok", s.ok);
        cerca("seidel x1", x[0], 1.0432692307692308, 1e-9);
        cerca("seidel x2", x[1], 2.269230769230769, 1e-9);
        cerca("seidel x3", x[2], -1.0817307692307692, 1e-9);
        double M[MAXN][MAXN] = {{1, 5}, {7, 1}};   // no dominante: diverge
        double bm[MAXN] = {1, 1}, xm[MAXN] = {0, 0};
        verdad("seidel divergente falla limpio", !gaussSeidel(2, M, bm, xm, 1e-8, 1000).ok);
    }

    // ---- interpolacion y ajuste ----
    {
        double xs[] = {0, 1, 2, 3}, ys[] = {0, 1, 4, 9};
        cerca("lagrange x^2 en 2.5", lagrange(4, xs, ys, 2.5), 6.25, 1e-12);
        cerca("newton interp x^2 en 2.5", newtonInterp(4, xs, ys, 2.5), 6.25, 1e-12);
        cerca("lagrange en nodo", lagrange(4, xs, ys, 3), 9, 1e-12);
    }
    {
        double xs[] = {1, 2, 3, 4, 5}, ys[] = {2.1, 3.9, 6.2, 7.8, 10.1}, c[MAXN], r2;
        verdad("minimos cuadrados recta ok", minimosCuadrados(5, xs, ys, 1, c, r2));
        cerca("MC intercepto", c[0], 0.05, 1e-10);
        cerca("MC pendiente", c[1], 1.99, 1e-10);
        cerca("MC R2", r2, 0.9973053289009771, 1e-10);
        double xq[] = {0, 1, 2, 3, 4}, yq[] = {1, 0, 1, 4, 9};   // (x-1)^2
        verdad("minimos cuadrados parabola ok", minimosCuadrados(5, xq, yq, 2, c, r2));
        cerca("MC c0", c[0], 1, 1e-9);
        cerca("MC c1", c[1], -2, 1e-9);
        cerca("MC c2", c[2], 1, 1e-9);
        cerca("MC R2 parabola", r2, 1, 1e-9);
        verdad("MC pocos puntos falla", !minimosCuadrados(2, xs, ys, 2, c, r2));
    }

    // ---- integracion y EDO ----
    {
        Expr s = E("sin(x)");
        double pi = 3.14159265358979323846;
        cerca("simpson sin 0..pi n=10", simpson(s, 0, pi, 10), 2.0001095173150043, 1e-12);
        cerca("trapecio sin 0..pi n=10", trapecio(s, 0, pi, 10), 1.9835235375094546, 1e-12);
        cerca("simpson n impar -> par", simpson(s, 0, pi, 9), simpson(s, 0, pi, 10), 1e-15);
        cerca("simpson x^3 exacto", simpson(E("x^3"), 0, 2, 2), 4, 1e-12);
        cerca("rk4 y'=y", rk4(E("y"), 0, 1, 1, 10, false), 2.718279744135166, 1e-12);
        cerca("rk4 y'=x+y", rk4(E("x+y"), 0, 1, 1, 20, false), 3.4365633853126685, 1e-12);
    }

    // ---- termodinamica ----
    cerca("interp lineal", interpLineal(10, 100, 20, 300, 12), 140, 1e-12);
    cerca("interp extrapola", interpLineal(10, 100, 20, 300, 5), 0, 1e-12);
    verdad("interp x1==x2 -> NaN", std::isnan(interpLineal(1, 1, 1, 2, 1)));
    cerca("mezcla", propMezcla(191.81, 2584.6, 0.5), 1388.205, 1e-9);
    cerca("calidad inversa", calidad(1388.205, 191.81, 2584.6), 0.5, 1e-12);
    cerca("bilineal plano x+y", bilineal(0, 2, 0, 4, 0, 2, 4, 6, 1, 1), 2, 1e-12);
    cerca("bilineal esquina", bilineal(0, 2, 0, 4, 0, 2, 4, 6, 2, 4), 6, 1e-12);

    // ---- fluidos ----
    {
        Friccion c = factorFriccion(100000, 0.0002, false, 1e-8);
        verdad("colebrook ok", c.ok);
        cerca("haaland f0", c.f0, 0.01873546, 1e-8);
        cerca("colebrook f", c.f, 0.01900544, 1e-8);
        cerca("colebrook 2", factorFriccion(250000, 0.15 / 52.5, false, 1e-8).f, 0.02637369, 1e-8);
        cerca("colebrook 3", factorFriccion(1e6, 0.002, false, 1e-8).f, 0.02360699, 1e-8);
        cerca("laminar 64/Re", factorFriccion(1000, 0.001, false).f, 0.064, 1e-12);

        Tuberia t = tuberiaHf(0.05, 0.2, 100, 0.00026, 1.004e-6);
        cerca("tuberia hf", t.hf, 1.4022276779467175, 1e-6);
        cerca("tuberia v", t.v, 1.5915494309189533, 1e-9);
        cerca("tuberia Re", t.Re, 317041.7193065644, 1e-3);
        cerca("tuberia f", t.f, 0.021722373191715178, 1e-8);
        Tuberia q;
        verdad("tuberiaQ ok", tuberiaQ(t.hf, 0.2, 100, 0.00026, 1.004e-6, q));
        cerca("tuberiaQ recupera Q", q.Q, 0.05, 1e-8);
        double D;
        Tuberia d;
        verdad("tuberiaD ok", tuberiaD(0.05, t.hf, 100, 0.00026, 1.004e-6, D, d));
        cerca("tuberiaD recupera D", D, 0.2, 1e-8);
        verdad("tuberiaD imposible (hf minusculo)", !tuberiaD(0.05, 1e-12, 100, 0.00026, 1.004e-6, D, d));
        verdad("tuberiaD imposible (hf enorme)", !tuberiaD(0.05, 1e30, 100, 0.00026, 1.004e-6, D, d));

        // Comparacion Haaland vs Colebrook en el mismo punto
        cerca("tuberia fH", t.fH, 0.02166886117241206, 1e-8);
        cerca("tuberia error H vs C (%)", t.errRel, 0.2463451798328612, 1e-6);
        cerca("tuberia hf con fH", t.hfH, 1.3987733576518122, 1e-6);
        cerca("tuberiaQ conserva fH", q.fH, t.fH, 1e-8);
        // Ecuaciones explicitas (Swamee-Jain), mismo caso
        cerca("explicita hf", swameeHf(0.05, 0.2, 100, 0.00026, 1.004e-6), 1.4057476596357192, 1e-9);
        cerca("explicita Q", swameeQ(t.hf, 0.2, 100, 0.00026, 1.004e-6), 0.0500097664084734, 1e-9);
        cerca("explicita D", swameeD(0.05, t.hf, 100, 0.00026, 1.004e-6), 0.20476097683709313, 1e-9);

        // Ejemplo 8-4 (aire, e = 0): L=150, Q=0.35, hf=20, nu=1.655e-5
        {
            double D84;
            Tuberia t84;
            verdad("ej 8-4 tuberiaD ok", tuberiaD(0.35, 20, 150, 0, 1.655e-5, D84, t84));
            cerca("ej 8-4 D Colebrook", D84, 0.26725964595904694, 1e-8);
            cerca("ej 8-4 D explicita", swameeD(0.35, 20, 150, 0, 1.655e-5), 0.2707765368177234, 1e-9);
            cerca("ej 8-4 Re", t84.Re, 100750.39931740036, 1e-3);
            cerca("ej 8-4 fH", t84.fH, 0.01779715557845217, 1e-9);
            cerca("ej 8-4 fC", t84.f, 0.01796173801004122, 1e-9);
            cerca("ej 8-4 error %", t84.errRel, 0.9162945784925823, 1e-6);
            cerca("ej 8-4 hf con fH", t84.hfH, 19.816741084301473, 1e-6);
            cerca("ej 8-4 hf con D explicita", tuberiaHf(0.35, 0.2707765368177234, 150, 0, 1.655e-5).hf,
                  18.785663828106394, 1e-6);
            // Ejemplo 8-5: misma D, longitud doble, mismo hf -> cae el caudal
            Tuberia t85;
            verdad("ej 8-5 tuberiaQ ok", tuberiaQ(20, D84, 300, 0, 1.655e-5, t85));
            cerca("ej 8-5 Q", t85.Q, 0.23750262796273414, 1e-8);
            cerca("ej 8-5 Q explicita", swameeQ(20, D84, 300, 0, 1.655e-5), 0.237470802012206, 1e-8);
        }
        // Tipo 3 iterando D desde Swamee-Jain (diap. 25: converge a 0.267 m)
        {
            double D0 = swameeD(0.35, 20, 150, 0, 1.655e-5), Dit;
            Tuberia ti;
            int it;
            verdad("tuberiaDiter ok", tuberiaDiter(0.35, 20, 150, 0, 1.655e-5, D0, Dit, ti, it, false));
            cerca("tuberiaDiter D", Dit, 0.26725964595904694, 1e-6);
            cerca("tuberiaDiter hL = pedida", ti.hf, 20, 1e-4);
            verdad("tuberiaDiter pocas vueltas", it <= 6);
            // arrancando lejos tambien converge
            verdad("tuberiaDiter desde D=1", tuberiaDiter(0.35, 20, 150, 0, 1.655e-5, 1.0, Dit, ti, it, false));
            cerca("tuberiaDiter desde D=1", Dit, 0.26725964595904694, 1e-6);
            // Tipo 2 con la tabla de la diap. 34: f supuesta 0.04, D=0.267, L=300, hL=20, aire, e=0
            Tuberia t2;
            verdad("tipo 2 diap. 34 ok", tuberiaQ(20, 0.267, 300, 0, 1.655e-5, t2, false, 0.04, 1e-6));
            cerca("tipo 2 f", t2.f, 0.01951, 2e-5);
            cerca("tipo 2 V", t2.v, 4.23, 0.01);
            cerca("tipo 2 Q (diap.: 0.24)", t2.Q, 0.2369, 5e-4);
        }
        // Darcy despejada (ultimo paso de los tipos 3 y 2)
        cerca("dDarcy (f=0.018011, ej 8-4)", dDarcy(0.018011, 150, 0.35, 20), 0.26740608303910374, 1e-9);
        {
            double Vd, Qd = qDarcy(0.019510713, 0.267, 300, 20, Vd);
            cerca("qDarcy V (ej 8-5)", Vd, 4.230804254416619, 1e-9);
            cerca("qDarcy Q (ej 8-5)", Qd, 0.2368837865115492, 1e-9);
            cerca("ida y vuelta Q -> D", dDarcy(0.019510713, 300, Qd, 20), 0.267, 1e-9);
            // la D de Colebrook iterada es punto fijo del despeje: dDarcy(f(D)) = D
            double Dit, D0 = swameeD(0.35, 20, 150, 0, 1.655e-5);
            Tuberia tt;
            int it;
            tuberiaDiter(0.35, 20, 150, 0, 1.655e-5, D0, Dit, tt, it, false);
            cerca("D es punto fijo del despeje", dDarcy(tt.f, 150, 0.35, 20), Dit, 1e-6);
        }
        // Ejemplo 8-3 en SI (e = 2e-6 m es un supuesto para acero inoxidable)
        {
            double rho = 62.36 * 16.01846337, mu = 7.536e-4 * 1.488163944;
            Tuberia t83 = tuberiaHf(0.2 * 0.028316846592, 2 * 0.0254, 200 * 0.3048, 2e-6, mu / rho);
            cerca("ej 8-3 Re", t83.Re, 126431.87574377304, 1e-2);
            cerca("ej 8-3 hf", t83.hf, 8.299860925062047, 1e-6);
            cerca("ej 8-3 dP (Pa)", rho * G * t83.hf, 81332.99810804892, 1e-2);
            cerca("ej 8-3 error %", t83.errRel, 1.206668880384545, 1e-6);
        }
        // Sistema ingles (diap. 15-19, Ejemplo 8-3): ft, lbm, g = gc = 32.2
        {
            fijarUnidades(true);
            cerca("ingles g", G, 32.2, 1e-12);
            double rho = 62.36, mu = 7.536e-4, D = 2.0 / 12;
            Tuberia ti = tuberiaHf(0.2, D, 200, 0.000007, mu / rho);
            cerca("ej 8-3 ingles V (diap.: 9.17 ft/s)", ti.v, 9.167324722093174, 1e-6);
            cerca("ej 8-3 ingles Re (diap.: 126400)", ti.Re, 126431.87581159992, 1e-2);
            cerca("ej 8-3 ingles f Colebrook (diap.: 0.0174)", ti.f, 0.017396782403351574, 1e-8);
            cerca("ej 8-3 ingles f Haaland (diap.: 0.0172)", ti.fH, 0.017184921927523356, 1e-8);
            cerca("ej 8-3 ingles hL ft (diap.: 27.3)", ti.hf, 27.242661880126082, 1e-6);
            double dP = rho * G * ti.hf / GC;   // lbf/ft2
            cerca("ej 8-3 ingles dP lbf/ft2 (diap.: 1700)", dP, 1698.8523948446625, 1e-4);
            cerca("ej 8-3 ingles psi (diap.: 11.8)", dP / 144, 11.80, 0.02);
            cerca("ej 8-3 ingles potencia W (diap.: 461)", 0.2 * dP * 1.355818, 461, 1.0);
            cerca("manning ingles k=1.486", KMANNING, 1.486, 1e-12);
            fijarUnidades(false);
            cerca("SI g restaurada", G, 9.81, 1e-12);
            cerca("SI gc", GC, 1.0, 1e-12);
        }
        verdad("laminar: fH es NaN", std::isnan(tuberiaHf(0.0005, 0.1, 50, 0.0001, 1e-4).fH));

        Tuberia l = tuberiaHf(0.0005, 0.1, 50, 0.0001, 1e-4);   // laminar
        cerca("laminar hf", l.hf, 0.10383197102835168, 1e-9);
        verdad("laminar tuberiaQ ok", tuberiaQ(l.hf, 0.1, 50, 0.0001, 1e-4, q));
        cerca("laminar recupera Q", q.Q, 0.0005, 1e-9);

        cerca("manning Q(y=1) rect", caudalManning(1, 0.013, 0.001, 2, 0), 3.064784761275729, 1e-9);
        Canal c1 = manning(3.064784761275729, 0.013, 0.001, 2, 0);
        verdad("manning ok", c1.ok);
        cerca("manning y rect", c1.y, 1, 1e-9);
        Canal c2 = manning(9.251676833420621, 0.015, 0.0008, 3, 1.5);
        cerca("manning y trap", c2.y, 1.2, 1e-9);
        cerca("manning v trap", c2.v, 1.60619389469108, 1e-9);
        cerca("manning Fr trap", c2.Fr, 0.5489391343840238, 1e-9);
    }

    std::printf("%d pruebas, %d fallas\n", total, fallos);
    return fallos ? 1 : 0;
}
