#include <cmath>
#include <iostream>

#include "HyperbolicSolver.h"
#include "ExactCompare.h"


constexpr double pi = 3.14159265358979323846;

std::vector <double> time0;
std::vector <double> position0;
std::vector <std::vector <double>> solutions0;

double f(double x){ return std::sin(x*pi);}
double g(double x){ return 0;}

const double example1_sol(double x,double t){ return std::sin(x*pi)*std::cos(pi*t);}


int main(){
    const HyperbolicSolver example1 ( f, g, 1, 1, 1, 10, 20);
    ExactCompare example1_exact (example1, example1_sol);
    //example1.print_table(POSITION, 4);
    //example1.print_table(TIME, 20);

    example1.print_bounds();
    example1.print_y0();

    time0 = example1.getTime();
    position0 = example1.getPositions();
    solutions0 = example1.getW();

    example1.savedata("./data/example1.csv");

    std::cout << "Check of the numerical solution compared with the exact solution:\n";
    example1_exact.print_comp_table(TIME, 20);
    example1_exact.print_comp_table(POSITION, 4);
    return 0;
}

