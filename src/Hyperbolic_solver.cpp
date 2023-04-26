#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

#include "HyperbolicSolver.h"
#include "colorcitos.h"

// Be careful with index management. Burden takes a notation from 0 to n and m, so the index must be from 0 or 1 to m+1 and n+1 given the case.

HyperbolicSolver::HyperbolicSolver(float (*f)(float), float (*g)(float), float alpha, float end_point, 
                                    float maxtime, const unsigned int x_mesh_size, const unsigned int t_mesh_size):
                                    m(x_mesh_size), n(t_mesh_size)
    {
    alpha = alpha;
    l = end_point;
    T = maxtime;
    // We cannot declare a vector with a defined size in the header file.
    // It must be general and the constructor set the size. In this case, We fill with zeros.
    tiempos = std::vector<float> (n+1, 0);
    posiciones = std::vector<float> (m+1, 0);

    w = std::vector<std::vector<float>> (m+1, std::vector<float> (n+1, 0));

    h = l/m;
    k = T/n;
    lambda = k * alpha/h;

    solve(f, g);
    
}


void HyperbolicSolver::setInitialConditions(float (*f)(float), float (*g)(float)){
    /*This function prepares the initual conditions, that meaning that sets the fist column of the matrix w*/

    w.at(0).at(0) = f(0);
    w.at(m).at(0) = f(l);

    // Why is it m-1 in Burden?
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
    for (int j = 0; j < n+1; j++){
        tiempos.at(j) = j*k;

        for (int i = 0; i < m+1; i++){
            posiciones.at(i) =i*h;
        }
    }
}

// This set of functions return the solution of the differential equation 

std::vector <float> HyperbolicSolver::getTime() const{
    return tiempos;
}

std::vector <float> HyperbolicSolver::getPositions() const{
    return posiciones;
}

std::vector <std::vector <float>> HyperbolicSolver::getW() const{
    return w;
}

// This set of functions print the parameters for the solution of the differential equation

void HyperbolicSolver::print_m() const{
    std::cout << m << std::endl;
}

void HyperbolicSolver::print_n() const{
    std::cout << n << std::endl;
}

void HyperbolicSolver::print_alpha() const{
    std::cout << alpha << std::endl;
}

void HyperbolicSolver::print_bounds() const{

    std::cout << "Integration interval: "<< std::endl;
    std::cout << "x ∈ [0, " << l << "]" << std::endl;
    std::cout << "t ∈ [0, " << T << "]" << std::endl;
}

void HyperbolicSolver::print_y0() const{

    std::cout << "Initial conditions: " << std::endl;
    std::cout << "y(0) = " << w.at(0).at(0) << std::endl;
    std::cout << "y(l) = " << w.at(m).at(0)<< std::endl;
}

// This set of functions give the parameters for the solution of the differential equation
int HyperbolicSolver::get_m() const{
    return m;
}
int HyperbolicSolver::get_n() const{
    return n;
}

float HyperbolicSolver::get_alpha() const{
    return alpha;
}

float HyperbolicSolver::get_l() const{
    return l;
}

float HyperbolicSolver::get_T() const{
    return T;
}

void HyperbolicSolver::print_table(short int fix, float value_pos) const{
    /*  This function prints the solution of the differential equation in a table format
        it can be chosen whether you want to fix a specific time or position
        value_pos indicates the index within the selected array */
    
    if(fix == POSITION){

        std::cout << verdecito_chimbita << "Position fixed at: " << std::endl;
        std::cout << "Index: " << std::defaultfloat << value_pos << std::endl;
        std::cout << "Position: " << std::setprecision(7) << std::fixed << posiciones.at(value_pos) << std::endl << std::endl;
        std::cout << std::left << purple << std::setw(15) << "Time" << std::setw(2) << std::left << "W(" << std::defaultfloat << value_pos << ",j)" << std::endl;
	    std::cout << "----------------------------" << std::endl;
        std::cout << reset;
        for(int i = 0; i < n+1; i++){
            std::cout << std::setw(15) << std::setprecision(7) << std::fixed << tiempos.at(i) << std::setw(15) << std::setprecision(7) << w.at(value_pos).at(i) << std::endl;
        }
	    std::cout << purple << "----------------------------" << std::endl;
        std::cout << reset;
        std::cout << std::endl;

    std::cout << std::endl;

    }
    else if(fix == TIME){
        std::cout << verdecito_chimbita << "Time fixed at: " << std::endl;
        std::cout << "Index: " << std::defaultfloat << value_pos << std::endl;
        std::cout << "Time: " << std::setprecision(7) << std::fixed << tiempos.at(value_pos) << std::endl << std::endl;
        std::cout << std::left << purple << std::setw(15) << "Position" << std::setw(2) << std::left << "W(i," << std::defaultfloat << value_pos << ")"<< std::endl;
	    std::cout << "----------------------------" << std::endl;
	    std::cout << reset;
        for(int i = 0; i < m+1; i++){
            std::cout << std::setw(15) << std::setprecision(7) << std::fixed << std::left << posiciones.at(i) << std::setw(15) << w.at(i).at(value_pos) << std::endl; 
	}
        std::cout << std::endl;
	    std::cout << purple << "----------------------------" << std::endl;
        std::cout << reset;
        std::cout << std::endl;

    }
    
    else{
        std::cout << "Error: Invalid option" << std::endl;
    }

}



