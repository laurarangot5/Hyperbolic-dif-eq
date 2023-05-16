#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cassert>

#include "HyperbolicSolver.h"
#include "colorcitos.h"

// Be careful with index management. Burden takes a notation from 0 to n and m, so the index must be from 0 or 1 to m+1 and n+1 given the case.

HyperbolicSolver::HyperbolicSolver(double (*f)(double), double (*g)(double), float alpha, float end_point, 
                                    float maxtime, const unsigned int x_mesh_size, const unsigned int t_mesh_size):
                                    m(x_mesh_size), n(t_mesh_size)
    {
    this->alpha = alpha;
    l = end_point;
    T = maxtime;
    // We cannot declare a vector with a defined size in the header file.
    // It must be general and the constructor set the size. In this case, We fill with zeros.
    tiempos = std::vector<double> (n+1, 0);
    posiciones = std::vector<double> (m+1, 0);

    w = std::vector<std::vector<double>> (m+1, std::vector<double> (n+1, 0));

    h = l/m;
    k = T/n;
    lambda = k * alpha/h;

    solve(f, g);
    
}


void HyperbolicSolver::setInitialConditions(double (*f)(double), double (*g)(double)){
    /*This function prepares the initial conditions, meaning it sets the first column of the matrix w*/

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

void HyperbolicSolver::solve(double (*f)(double), double (*g)(double)){
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

std::vector <double> HyperbolicSolver::getTime() const{
    return tiempos;
}

std::vector <double> HyperbolicSolver::getPositions() const{
    return posiciones;
}

std::vector <std::vector <double>> HyperbolicSolver::getW() const{
    return w;
}

// This set of functions print the parameters for the solution of the differential equation

void HyperbolicSolver::print_m() const{
    std::cout << "x divisions "<< m << std::endl;
}

void HyperbolicSolver::print_n() const{
    std::cout << "t divisions " << n << std::endl;
}

void HyperbolicSolver::print_alpha() const{
    std::cout << "alpha " << this->alpha << std::endl;
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

void HyperbolicSolver::info() const{
   print_m();
   print_n();
   print_alpha();

   std::cout << std::endl;
   print_y0();
   std::cout << std::endl;
   print_bounds();
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
        std::cout << "Position: " << std::setprecision(10) << std::fixed << posiciones.at(value_pos) << std::endl << std::endl;
        std::cout << std::left << purple << std::setw(18) << "Time" << std::setw(2) << std::left << "W(" << std::defaultfloat << value_pos << ",j)" << std::endl;
	    std::cout << "----------------------------" << std::endl;
        std::cout << reset;
        for(int i = 0; i < n+1; i++){
            std::cout << std::setw(18) << std::setprecision(10) << std::fixed << tiempos.at(i) << std::setw(18) << std::setprecision(10) << w.at(value_pos).at(i) << std::endl;
        }
	    std::cout << purple << "----------------------------" << std::endl;
        std::cout << reset;
        std::cout << std::endl;

    std::cout << std::endl;

    }
    else if(fix == TIME){
        std::cout << verdecito_chimbita << "Time fixed at: " << std::endl;
        std::cout << "Index: " << std::defaultfloat << value_pos << std::endl;
        std::cout << "Time: " << std::setprecision(10) << std::fixed << tiempos.at(value_pos) << std::endl << std::endl;
        std::cout << std::left << purple << std::setw(18) << "Position" << std::setw(2) << std::left << "W(i," << std::defaultfloat << value_pos << ")"<< std::endl;
	    std::cout << "----------------------------" << std::endl;
	    std::cout << reset;
        for(int i = 0; i < m+1; i++){
            std::cout << std::setw(18) << std::setprecision(10) << std::fixed << std::left << posiciones.at(i) << std::setw(18) << w.at(i).at(value_pos) << std::endl; 
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

void HyperbolicSolver::savedata(std::string _path) const{
  std::ofstream outfile(_path);

  for(int i = 0; i < get_m(); i++){
    for(int j = 0; j < get_n(); j++){
      outfile << std::setprecision(7) << std::fixed << getW().at(i).at(j);
      if(j == get_n()-1){
        outfile << std::endl;
      }
      else outfile << ",";
    }
  }

}

