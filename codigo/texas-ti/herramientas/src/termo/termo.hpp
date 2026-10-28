#pragma once

// Interpolacion lineal entre dos filas de una tabla: y en x, dados (x1,y1) y (x2,y2).
// NaN si x1 == x2. Fuera de [x1, x2] extrapola (el menu avisa).
double interpLineal(double x1, double y1, double x2, double y2, double x);

// Mezcla liquido-vapor con calidad x: prop = f + x (g - f), para v, u, h o s.
double propMezcla(double f, double g, double x);

// Calidad a partir de una propiedad: x = (prop - f) / (g - f). NaN si g == f.
double calidad(double prop, double f, double g);

// Doble interpolacion (tablas de vapor sobrecalentado: T y P).
// qXY es el valor de la tabla en (x = X, y = Y), con q11 en (x1,y1), q21 en (x2,y1),
// q12 en (x1,y2), q22 en (x2,y2).
double bilineal(double x1, double x2, double y1, double y2,
                double q11, double q21, double q12, double q22,
                double x, double y);
