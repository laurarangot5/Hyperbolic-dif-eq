#include <cmath>

#include "Hyperbolic_solver.h"

HyperbolicSolver::HyperbolicSolver(float (*f)(float), float (*g)(float), float alpha, float end_point, float maxtime, const unsigned int x_mesh_size, const unsigned int t_mesh_size){
    alpha = alpha;
    m = x_mesh_size;
    n = t_mesh_size;
    l = end_point;
    T = maxtime;

    w(m, std::vector<float>(n));

    h = l/m;
    k = T/n;
    lambda = k * alpha/h;

    solve(f, g);
}

void HyperbolicSolver::setInitialConditions(float (*f)(float), float (*g)(float)){
    w.at(0).at(0) = f(0);
    w.at(m).at(0) = f(l);

    for(int i = 1; i < m; i++){
        w.at(i).at(0) = f(i*h);
        w.at(i).at(1) = (1 - std::pow(lambda, 2)) * f(i*h) + std::pow(lambda, 2)/2 * (f((i + 1) * h) + f((i - 1) * h)) + k * g(i*h); 
    }
}

void HyperbolicSolver::matrixMultiplication(){
    for(int j = 1; j < n; j++){
        for(int i = 1; i < m; i++){
            w.at(i).at(j + 1) = 2 * (1 - std::pow(lambda, 2)) * w.at(i).at(j) + std::pow(lambda, 2) * (w.at(i + 1).at(j) + w.at(i - 1).at(j)) - w.at(i).at(j - 1);
        }
    }
}

