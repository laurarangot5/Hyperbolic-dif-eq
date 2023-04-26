#include <iostream>
#include <iomanip>

#include "colorcitos.h"
#include "Hyperbolic_solver.h"


ExactCompare::ExactCompare(const HyperbolicSolver& Obj_sol, const float (*exact_solution)(float, float)): sol_object(Obj_sol), exact_solution(exact_solution) {}

void ExactCompare::calculateValues(short int fix, float value_pos){
    /*Evaluates the function in all the points of the mesh.*/
    //Get the mesh
    tiempos = sol_object.getTime();
    posiciones = sol_object.getPositions();

    // Vector for the exact solution in the mesh
    w = std::vector <std::vector <float>> (posiciones.size(), std::vector <float> (tiempos.size()));

    // Evaluate the exact solution in the mesh
    for(i = 0; i < posiciones.size(); i++){
	for(j=0; j < tiempos.size(); j++){
	    w.at(i).at(j) = exact_solution(posiciones.at(i), tiempos.at(j));
    }
}

void ExactCompare::print_comp_table(short int fix, float value_pos){
    /*Prints the comparison table for a fixed time or position (index)*/

    if(fix == POSITION){
	std::cout << "Position fixed at:"
    }
    
}
