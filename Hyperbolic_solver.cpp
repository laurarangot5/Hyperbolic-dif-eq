#include <cmath>
#include <iostream>
#include <iomanip>

#include "Hyperbolic_solver.h"

//enum fixed_var{POSITION, TIME};

HyperbolicSolver::HyperbolicSolver(float (*f)(float), float (*g)(float), float alpha, float end_point, float maxtime, const unsigned int x_mesh_size, const unsigned int t_mesh_size){
    alpha = alpha;
    const unsigned int m = x_mesh_size;
    const unsigned int n = t_mesh_size;
    l = end_point;
    T = maxtime;
    std::vector <float> tiempos(n);
    std::vector <float> posiciones(m);

    w(std:: vector <float> (m), std::vector<float> (n));

    h = l/m;
    k = T/n;
    lambda = k * alpha/h;

    solve(f, g);
}


void HyperbolicSolver::setInitialConditions(float (*f)(float), float (*g)(float)){
    /*This function prepares the initual conditions, that meaning that sets the fist column of the matrix w*/
    w.at(0).at(0) = f(0);
    w.at(m).at(0) = f(l);

    for(int i = 1; i < m; i++){
        w.at(i).at(0) = f(i*h);
        w.at(i).at(1) = (1 - std::pow(lambda, 2)) * f(i*h) + std::pow(lambda, 2)/2 * (f((i + 1) * h) + f((i - 1) * h)) + k * g(i*h); 
    }
}


void HyperbolicSolver::matrixMultiplication(){
    /*This function performs the matrix multiplication for wij calculation*/
    for(int j = 1; j < n; j++){
        for(int i = 1; i < m; i++){
            w.at(i).at(j + 1) = 2 * (1 - std::pow(lambda, 2)) * w.at(i).at(j) + std::pow(lambda, 2) * (w.at(i + 1).at(j) + w.at(i - 1).at(j)) - w.at(i).at(j - 1);
        }
    }
}

void HyperbolicSolver::solve(float (*f)(float), float (*g)(float)){
    setInitialConditions(f, g);
    matrixMultiplication();
    for (int j = 0; j < n; j++){
        tiempos.at(j) = j*k;

        for (int i = 0; i < m; i++){
            posiciones.at(i) =i*h;
        }
    }
}

// This set of functions return the solution of the differential equation 

std::vector <float> HyperbolicSolver::getTime(){
    return tiempos;
}

std::vector <float> HyperbolicSolver::getPositions(){
    return posiciones;
}

std::vector <std::vector <float>> HyperbolicSolver::getW(){
    return w;
}

// This set of functions print the parameters for the solution of the differential equation

void HyperbolicSolver::print_m(){
    std::cout << m << std::endl;
}

void HyperbolicSolver::print_n(){
    std::cout << n << std::endl;
}

void HyperbolicSolver::print_alpha(){
    std::cout << alpha << std::endl;
}

void HyperbolicSolver::print_bounds(){

    std::cout << "Integration interval: "<< std::endl;
    std::cout << "x ∈ [0, " << l << "]" << std::endl;
    std::cout << "t ∈ [0, " << T << "]" << std::endl;
}

void HyperbolicSolver::print_y0(){

    std::cout << "Initial conditions: " << std::endl;
    std::cout << "y(0) = " << w.at(0).at(0) << std::endl;
    std::cout << "y(l) = " << w.at(m).at(0)<< std::endl;
}

void HyperbolicSolver::print_table(short int fix,float value_pos){
    /*  This function prints the solution of the differential equation in a table format
        it can be chosen whether you want to fix a specific time or position
        value_pos indicates the index within the selected array */
    
    if(fix == POSITION){

        std::cout << "Position fixed at: " << value_pos << std::endl;
        std::cout << "Time" << std::setw(15) << "W" << std::endl;
        for(int i = 0; i < n; i++){
            std::cout << tiempos.at(i) << std::setw(15) << w.at(value_pos).at(i) << std::endl;
        }
    }
    else if(fix == TIME){
        std::cout << "Time fixed at: " << value_pos << std::endl;
        std::cout << "Position" << std::setw(15) << "Value" << std::endl;
        for(int i = 0; i < m; i++){
            std::cout << posiciones.at(i) << std::setw(15) << w.at(i).at(value_pos) << std::endl;
        }
    }
    else{
        std::cout << "Error: Invalid option" << std::endl;
    }

}



