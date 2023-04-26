#include <cmath>
#include <iostream>

#include "Hyperbolic_solver.h"

constexpr double pi = 3.14159265358979323846;

std::vector <float> time0;
std::vector <float> position0;
std::vector <std::vector <float>> solutions0;

float f(float x){ return std::sin(x*pi);}
float g(float x){ return 0;}

const float example0_sol(float x,float t){ return std::sin(x*pi)*std::cos(2*pi*t);}

/* This file shows the functioning of all the interesting functions of the class*/

int main(){
    const HyperbolicSolver example0 ( f, g, 2, 1, 1, 10, 20);
    ExactCompare example0_exact (example0, example0_sol);
    //example0.print_table(POSITION, 4);
    //example0.print_table(TIME, 20);

    std::cout << "Check of secondary functions:\n";

    std::cout << "m = ";
    example0.print_m();
    std::cout << "n = ";
    example0.print_n();
    std::cout << "alpha = ";
    example0.print_alpha();
    example0.print_bounds();
    example0.print_y0();

    time0 = example0.getTime();
    position0 = example0.getPositions();
    solutions0 = example0.getW();

    std::cout << "Check of the numerical solution compared with the exact solution:\n";
    example0_exact.print_comp_table(TIME, 20);
    example0_exact.print_comp_table(POSITION, 4);
    return 0;
}

