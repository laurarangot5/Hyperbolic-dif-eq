#include <cmath>
#include <iostream>

#include "HyperbolicSolver.h"
#include "graphics.h"

constexpr double pi = 3.14159265358979323846;

std::vector <double> time0;
std::vector <double> position0;
std::vector <std::vector <double>> solutions0;

const double p0 = 0.9;

double f(double x){ return p0 * (std::cos(2*x*pi) - 1);}
double g(double x){ return 0;}

int main(){
    const HyperbolicSolver example2 ( f, g, 1, 1, 3.5, 200, 700);
    graphics example2_graphics(example2); 

    example2.print_bounds();
    example2.print_y0();

    example2.print_table(TIME, 400);
    example2_graphics.plot_slice(TIME, 400);
    example2_graphics.plot_heatmap();
    return 0;
}

