#include "Hyperbolic_solver.h"
#include "matplotlibcpp.h"
#include <vector>

namespace plt = matplotlibcpp;


enum fixed_var{POSITION, TIME};


graphics::graphics(const HyperbolicSolver& sol_object): 
                                sol_object(sol_object){}

void graphics::plot_slice(short int fix, float value_pos) const{

    std::vector <float> time = sol_object.getTime();
    std::vector <float> pos = sol_object.getPositions();
    if (fix == POSITION){

        //here we get from the matrix w, a column that represents the times for that solution
        
        std::vector <float> w = sol_object.getW();
        std::vector <float> W;
        for(int i = 0; i < n+1; i++){
                W.push_back(w.at(i).at(value_pos));
        }
        delete[] w;

        plt::plot(time, W);
        plt::title("Solution of the differential equation at a the fixed position "+std::to_string(pos.at(value_pos)));
        plt::xlabel("Time");
        plt::ylabel("Solution");
        plt::show();
    }

    else if (fix == TIME){
        
        std::vector <float> W = sol_object.getW().at(value_pos);
        

        plt::plot(pos, W);
        plt::title("Solution of the differential equation for the fixed time "+std::to_string(time.at(value_pos)));
        plt::xlabel("Position");
        plt::ylabel("Solution");
        plt::show();
    }
}


