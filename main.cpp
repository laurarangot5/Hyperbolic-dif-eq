#include "Hyperbolic_solver.h"
#include <cmath>

constexpr double pi = 3.14159265358979323846;

float f(float x){ return std::sin(x*pi);}
float g(float x){ return 0;}

float example0_sol(float x,float t){ return std::sin(x*pi)*std::cos(2*pi*t);}


int main(){



    HyperbolicSolver  example0 ( f, g, 2, 1, 1, 10, 20);
    //example0.print_table(POSITION, 4);
    example0.print_table(TIME, 20);

    return 0;
}