#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Vector2D.hpp"
#include "Vector3D.hpp"

TEST_CASE("Vector2D operaciones basicas", "[vector2d]") {
    Vector2D a{3, 4};
    Vector2D b{4, 3};

    CHECK(a.magnitud() == Catch::Approx(5.0));
    CHECK((a + b).x == Catch::Approx(7.0));
    CHECK((a + b).y == Catch::Approx(7.0));
    CHECK((a - b).x == Catch::Approx(-1.0));
    CHECK((a - b).y == Catch::Approx(1.0));
    CHECK((a * 2.0).x == Catch::Approx(6.0));
    CHECK(a.productoPunto(b) == Catch::Approx(24.0));
}

TEST_CASE("Vector2D angulo interno", "[vector2d]") {
    Vector2D perpA{1, 0};
    Vector2D perpB{0, 1};
    CHECK(perpA.anguloInterno(perpB) == Catch::Approx(90.0));

    Vector2D a{3, 4};
    CHECK(a.anguloInterno(a) == Catch::Approx(0.0));  // prueba el clamp contra NaN
}

TEST_CASE("Punto2D y Vector2D se relacionan bien", "[vector2d][punto2d]") {
    Punto2D p1{0.0, 0.0};
    Punto2D p2{3.0, 4.0};

    Vector2D direccion = p2 - p1;   // punto - punto = vector
    CHECK(direccion.x == Catch::Approx(3.0));
    CHECK(direccion.y == Catch::Approx(4.0));
    CHECK(direccion.magnitud() == Catch::Approx(5.0));

    Punto2D vuelta = p1 + direccion;   // punto + vector = punto
    CHECK(vuelta.x == Catch::Approx(p2.x));
    CHECK(vuelta.y == Catch::Approx(p2.y));
}

TEST_CASE("Vector3D operaciones basicas", "[vector3d]") {
    Vector3D c{2, 3, 4};
    Vector3D d{5, 6, 7};

    CHECK(c.magnitud() == Catch::Approx(std::sqrt(4.0+9.0+16.0)));
    CHECK((c + d).x == Catch::Approx(7.0));
    CHECK(c.productoPunto(d) == Catch::Approx(56.0));
}

TEST_CASE("Vector3D producto cruz", "[vector3d]") {
    Vector3D i{1, 0, 0};
    Vector3D j{0, 1, 0};
    Vector3D resultado = i.productoCruz(j);

    CHECK(resultado.x == Catch::Approx(0.0));
    CHECK(resultado.y == Catch::Approx(0.0));
    CHECK(resultado.z == Catch::Approx(1.0));
    CHECK(i.anguloInterno(j) == Catch::Approx(90.0));
}
