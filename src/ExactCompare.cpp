#include <iostream>
#include <iomanip>

#include "colorcitos.h"
#include "ExactCompare.h"

ExactCompare::ExactCompare(const HyperbolicSolver& Obj_sol, const float (*exact_solution)(float, float)): sol_object(Obj_sol), exact_solution(exact_solution) {
	calculateValues();
}

void ExactCompare::calculateValues(){
    /*Evaluates the function in all the points of the mesh.*/
    //Get the mesh
    tiempos = sol_object.getTime();
    posiciones = sol_object.getPositions();
    aproximaciones = sol_object.getW();

    // Vector for the exact solution in the mesh
    w = std::vector <std::vector <float>> (posiciones.size(), std::vector <float> (tiempos.size()));

    // Evaluate the exact solution in the mesh
    for(int i = 0; i < posiciones.size(); i++){
	for(int j=0; j < tiempos.size(); j++){
	    w.at(i).at(j) = exact_solution(posiciones.at(i), tiempos.at(j));
    }
}
}

void ExactCompare::print_comp_table(short int fix, float value_pos) const{
    /*Prints the comparison table for a fixed time or position (index)*/


     if(fix == POSITION){

        std::cout << verdecito_chimbita << "Position fixed at: " << std::endl;
        std::cout << "Index: " << std::defaultfloat << value_pos << std::endl;
        std::cout << "Position: " << std::setprecision(7) << std::fixed << posiciones.at(value_pos) << std::endl << std::endl;
	// Table header
        std::cout << std::left << purple << std::setw(15) << "Time" << std::setw(2) << std::left << "W(" << std::defaultfloat << value_pos << std::setw(9) << std::left <<",j)" <<"Exact value" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
        std::cout << reset;
	// Table data
        for(int i = 0; i < tiempos.size(); i++){
            std::cout << std::setw(15) << std::setprecision(7) << std::fixed << tiempos.at(i) << std::setw(15) << std::setprecision(7) << aproximaciones.at(value_pos).at(i) << std::setw(15) << std::setprecision(7) << w.at(value_pos).at(i) << std::endl;
        }
	    std::cout << purple << "------------------------------------------" << std::endl;
        std::cout << reset;
        std::cout << std::endl;

    std::cout << std::endl;

    }
    else if(fix == TIME){
        std::cout << verdecito_chimbita << "Time fixed at: " << std::endl;
        std::cout << "Index: " << std::defaultfloat << value_pos << std::endl;
        std::cout << "Time: " << std::setprecision(7) << std::fixed << tiempos.at(value_pos) << std::endl << std::endl;
        std::cout << std::left << purple << std::setw(15) << "Position" << std::setw(2) << std::left << "W(i," << std::defaultfloat << value_pos << std::setw(9) << std::left << ")" << std::left <<"Exact value" << std::endl;
	    std::cout << "------------------------------------------" << std::endl;
	    std::cout << reset;
        for(int i = 0; i < posiciones.size(); i++){
            std::cout << std::setw(15) << std::setprecision(7) << std::fixed << std::left << posiciones.at(i) << std::setw(15) << aproximaciones.at(i).at(value_pos) << std::setw(15) << w.at(i).at(value_pos) << std::endl; 
	}
        std::cout << std::endl;
	    std::cout << purple << "------------------------------------------" << std::endl;
        std::cout << reset;
        std::cout << std::endl;

    }
    
    else{
        std::cout << "Error: Invalid option" << std::endl;
    }
    
}

