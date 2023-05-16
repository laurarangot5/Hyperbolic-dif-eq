#include <iostream>
#include <iomanip>

#include "colorcitos.h"
#include "ExactCompare.h"

ExactCompare::ExactCompare(const HyperbolicSolver& Obj_sol, const double (*exact_solution)(double, double)): sol_object(Obj_sol), exact_solution(exact_solution) {
	calculateValues();
}

void ExactCompare::calculateValues(){
    /*Evaluates the function in all the points of the mesh.*/
    //Get the mesh
    tiempos = sol_object.getTime();
    posiciones = sol_object.getPositions();
    aproximaciones = sol_object.getW();

    // Vector for the exact solution in the mesh
    w = std::vector <std::vector <double>> (posiciones.size(), std::vector <double> (tiempos.size()));

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
        std::cout << "Position: " << std::setprecision(10) << std::fixed << posiciones.at(value_pos) << std::endl << std::endl;
	// Table header
        std::cout << purple << std::left << std::setw(18) << "Time" 
                            << std::left << std::setw(2) << "W(" << std::defaultfloat << value_pos << std::setw(15) << std::left <<",j)" 
                            << std::left << std::setw(18) << "Exact value" 
                            << std::left << "Difference" <<std::endl;
	std::cout << "------------------------------------------------------------------" << std::endl;
        std::cout << reset;
	// Table data
        for(int i = 0; i < tiempos.size(); i++){
            std::cout << std::setw(18) << std::setprecision(10) << std::fixed << tiempos.at(i)
                      << std::setw(18) << std::setprecision(10) << aproximaciones.at(value_pos).at(i)
                      << std::setw(18) << std::setprecision(10) << w.at(value_pos).at(i) 
                      << std::setw(18) << std::setprecision(10) << w.at(value_pos).at(i) - aproximaciones.at(value_pos).at(i) << std::endl;
        }
	std::cout << purple << "------------------------------------------------------------------" << std::endl;
        std::cout << reset;
        std::cout << std::endl;

    std::cout << std::endl;

    }
    else if(fix == TIME){

        std::cout << verdecito_chimbita << "Time fixed at: " << std::endl;
        std::cout << "Index: " << std::defaultfloat << value_pos << std::endl;
        std::cout << "Time: " << std::setprecision(10) << std::fixed << tiempos.at(value_pos) << std::endl << std::endl;
        
        std::cout << purple << std::left << std::setw(18) << "Time" 
                            << std::left << std::setw(2) << "W(i," << std::defaultfloat << value_pos << std::setw(15) << std::left << ")" 
                            << std::left << std::setw(18) << "Exact value" 
                            << std::left << "Difference" <<std::endl;
	      std::cout << "------------------------------------------------------------------" << std::endl;
      
	    std::cout << reset;
        for(int i = 0; i < posiciones.size(); i++){
            std::cout << std::setw(18) << std::setprecision(10) << std::fixed << posiciones.at(i) 
                      << std::setw(18) << std::setprecision(10) << std::fixed << aproximaciones.at(i).at(value_pos) 
                      << std::setw(18) << std::setprecision(10) << std::fixed << w.at(i).at(value_pos)
                      << std::setw(18) << std::setprecision(10) << w.at(i).at(value_pos) - aproximaciones.at(i).at(value_pos) << std::endl;
	}
        std::cout << std::endl;
	std::cout << purple << "------------------------------------------------------------------" << std::endl;
        std::cout << reset;
        std::cout << std::endl;

    }
    
    else{
        std::cout << "Error: Invalid option" << std::endl;
    }
    
}

std::vector <double> ExactCompare::getTime() const{
    return tiempos;    
}

std::vector <double> ExactCompare::getPositions() const{
    return posiciones;
}
std::vector <std::vector <double>> ExactCompare::getW() const{
    return w;
}

