#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "ElementoBarra.hpp"
#include "Matriz.hpp"

TEST_CASE("matrizLocal calcula EA/L correctamente", "[elementobarra]") {
    Nodo n1{0.0, 0.0, 0.0};
    Nodo n2{2.0, 0.0, 0.0};
    ElementoBarra barra(200e9, 0.001, n1, n2);

    Matriz<double> K = barra.matrizLocal();

    CHECK(K(0,0) == Catch::Approx(1e8));
    CHECK(K(0,1) == Catch::Approx(-1e8));
    CHECK(K(1,0) == Catch::Approx(-1e8));
    CHECK(K(1,1) == Catch::Approx(1e8));
}

TEST_CASE("longNodo calcula distancia 3D real", "[elementobarra]") {
    Nodo n1{0.0, 0.0, 0.0};
    Nodo n2{2.0, 1.0, 0.0};
    ElementoBarra barra(200e9, 0.001, n1, n2);

    CHECK(barra.longNodo() == Catch::Approx(std::sqrt(5.0)));
}

TEST_CASE("Matriz lanza excepcion en acceso fuera de rango", "[matriz][excepciones]") {
    Matriz<double> m(2, 2);
    REQUIRE_THROWS_AS(m(5, 5), std::out_of_range);
}
