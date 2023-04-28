#include <cmath>
#include <iostream>

#include "HyperbolicSolver.h"
#include "graphics.h"

constexpr double pi = 3.14159265358979323846;

std::vector <float> time0;
std::vector <float> position0;
std::vector <std::vector <float>> solutions0;

const float p0 = 0.9;

float f(float x){ return p0 * (std::cos(2*x*pi) - 1);}
float g(float x){ return 0;}

int main(){
    const HyperbolicSolver example2 ( f, g, 1, 1, 1, 100, 200);
    graphics example2_graphics(example2); 

    example2.print_bounds();
    example2.print_y0();

    example2.print_table(TIME, 200);
    example2_graphics.plot_heatmap();
    return 0;
}

