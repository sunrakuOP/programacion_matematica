#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Matriz.hpp"

TEST_CASE("Suma de matrices del mismo tamano", "[matriz]") {
    Matriz<double> a(2, 2);
    a(0,0) = 1; a(0,1) = 2;
    a(1,0) = 3; a(1,1) = 4;

    Matriz<double> b(2, 2);
    b(0,0) = 5; b(0,1) = 6;
    b(1,0) = 7; b(1,1) = 8;

    Matriz<double> c = a + b;

    CHECK(c(0,0) == Catch::Approx(6.0));
    CHECK(c(0,1) == Catch::Approx(8.0));
    CHECK(c(1,0) == Catch::Approx(10.0));
    CHECK(c(1,1) == Catch::Approx(12.0));
}

TEST_CASE("Suma de matrices de tamano distinto lanza excepcion", "[matriz][excepciones]") {
    Matriz<double> a(2, 2);
    Matriz<double> b(3, 3);

    REQUIRE_THROWS_AS(a + b, std::invalid_argument);
}

TEST_CASE("Multiplicacion de matrices compatibles", "[matriz]") {
    Matriz<double> a(2, 2);
    a(0,0) = 1; a(0,1) = 2;
    a(1,0) = 3; a(1,1) = 4;

    Matriz<double> b(2, 2);
    b(0,0) = 5; b(0,1) = 6;
    b(1,0) = 7; b(1,1) = 8;

    Matriz<double> c = a * b;

    CHECK(c(0,0) == Catch::Approx(19.0));
    CHECK(c(0,1) == Catch::Approx(22.0));
    CHECK(c(1,0) == Catch::Approx(43.0));
    CHECK(c(1,1) == Catch::Approx(50.0));
}

TEST_CASE("Multiplicacion de matrices incompatibles lanza excepcion", "[matriz][excepciones]") {
    Matriz<double> a(2, 2);
    Matriz<double> b(3, 3);

    REQUIRE_THROWS_AS(a * b, std::invalid_argument);
}

TEST_CASE("Acceso fuera de rango lanza excepcion", "[matriz][excepciones]") {
    Matriz<double> a(2, 2);

    REQUIRE_THROWS_AS(a(5,5), std::out_of_range);
}
