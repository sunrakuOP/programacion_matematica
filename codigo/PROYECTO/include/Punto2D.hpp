#pragma once

// Un punto es SOLO una posicion en el espacio -- no tiene magnitud ni
// direccion propia. A proposito NO tiene metodos de algebra vectorial
// (no magnitud(), no productoPunto(), etc). Separado de Vector2D para que
// el compilador no deje escribir cosas sin sentido geometrico como
// "punto + punto".
struct Punto2D {
    double x, y;
};
