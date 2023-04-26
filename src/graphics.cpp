#include "Hyperbolic_solver.h"
#include "matplotlibcpp.h"
#include <vector>
#include <iostream>

namespace plt = matplotlibcpp;


//enum fixed_var{POSITION, TIME};


graphics::graphics(const HyperbolicSolver& sol_object): 
                                sol_object(sol_object){}

void graphics::plot_slice(short int fix, float value_pos) const{
    /*  This function selects either a colum or a row of the matriz W and plots it against the time or position
        depending on the value of the variable fixed.
        For the rows value_pos < m+1 and for the columns value_pos < n+1
    */

    int n = sol_object.get_n();
    int m = sol_object.get_m();

    std::vector <float> time = sol_object.getTime();
    std::vector <float> pos = sol_object.getPositions();
    if (fix == POSITION){
        
        std::vector <std::vector <float>> w = sol_object.getW();
        std::vector <float> W;
        std::vector <float> t;

        for(int i = 0; i < m+1; i++){
                W.push_back(w.at(i).at(value_pos));
                t.push_back(time.at(i));
                
        }

        plt::plot(t, W);
        plt::title("Solution of the differential equation at a the fixed position "+std::to_string(pos.at(value_pos)));
        plt::xlabel("Time");
        plt::ylabel("W ("+std::to_string(pos.at(value_pos))+",j)");
        plt::show();
    }

    else if (fix == TIME){
        
        std::vector <float> w = sol_object.getW().at(value_pos);
        std::vector <float> W;

        for(int i = 0; i < m+1; i++){
            W.push_back(w.at(i));}
        

        plt::plot(pos, W);
        plt::title("Solution of the differential equation for the fixed time "+std::to_string(time.at(value_pos)));
        plt::xlabel("Position");
        plt::ylabel("W (i,"+std::to_string(time.at(value_pos))+")");
        plt::show();
        
    }
}

void graphics::plot_heatmap() const{
    /*  This function plots the matrix W as a heatmap
    */
    std::vector <std::vector <float>> w = sol_object.getW();
    std::vector <float> time = sol_object.getTime();
    std::vector <float> pos = sol_object.getPositions();

    plt::figure();
    plt::imshow(w);
    plt::xticks(time);
    plt::yticks(pos);
    plt::show();


/*
    plt::imshow();
    plt::title("Solution of the differential equation");
    plt::xlabel("Position");
    plt::ylabel("Time");
    plt::zlabel("W (i,j)");
    plt::show();
*/ 
}



