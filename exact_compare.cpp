#include <iostream>
#include <iomanip>

#include "colorcitos.h"
#include "Hyperbolic_solver.h"


ExactCompare::ExactCompare(const HyperbolicSolver& Obj_sol, const float (*exact_solution)(float, float)): sol_object(Obj_sol), exact_solution(exact_solution) {}

void ExactCompare::calculateValues(short int fix, float value_pos){
    /*Evaluates the function in the points of the mesh for a fixed time or position (index)*/

    //Get the mesh
    tiempos = sol_object.getTime();
    posiciones = sol_object.getPositions();

    std::vector <float> w;


    if(fix == POSITION){
        w = std::vector<float> (tiempos.size(), 0);

        for (int i = 0; i < tiempos.size(); i++){
            w.at(i) = exact_solution(posiciones.at(value_pos), tiempos.at(i));
        }
    }
    else if(fix==TIME){
        w = std::vector<float> (posiciones.size(), 0);
        for(int i = 0; i < posiciones.size(); i++){
            w.at(i) = exact_solution(posiciones.at(i), tiempos.at(value_pos));
        }
    }
    else{
        std::cout << "Error: invalid fixed variable.\n";
    }


}

