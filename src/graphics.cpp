#include "graphics.h"
#include <vector>
#include <iostream>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;


//enum fixed_var{POSITION, TIME};


graphics::graphics(const HyperbolicSolver& sol_object): 
                                sol_object(sol_object){}

void graphics::plot_slice(short int fix, float value_pos) const{
    /*  This function selects either a colum or a row of the matriz W and plots it against the time or position
        depending on the value of the variable fixed.
        For the rows value_pos < m+1 and for the columns value_pos < n+1
    */


    //int n = sol_object.get_n();
    //int m = sol_object.get_m();

    std::vector <float> Time = sol_object.getTime();
    std::vector <float> pos = sol_object.getPositions();

    const int m = pos.size() - 1;
    const int n = Time.size() - 1;

    if (fix == POSITION){

        //the fixed poition index must be smaller than m
        
        std::vector <std::vector <float>> w = sol_object.getW();
        std::vector <float> W;

        // Extracts a column of the matrix W corresponding to the fixed position
        for(int i = 0; i < n+1; i++){
                W.push_back(w.at(value_pos).at(i));
                
        }

        plt::plot(Time, W);
        plt::title("Solution of the differential equation at a the fixed position "+std::to_string(pos.at(value_pos)));
        plt::xlabel("Time");
        plt::ylabel("W ("+std::to_string(pos.at(value_pos))+",j)");
        plt::show();
    }

    else if (fix == TIME){

        //the fixed time index must be smaller than n
        std::vector <std::vector <float>> w = sol_object.getW();
        std::vector <float> W;

        for(int i = 0; i < m+1; i++){
            W.push_back(w.at(i).at(value_pos));}
        

        plt::plot(pos, W);
        plt::title("Solution of the differential equation for the fixed time "+std::to_string(Time.at(value_pos)));
        plt::xlabel("Position");
        // Consider using sstream
        plt::ylabel("W (i,"+std::to_string(Time.at(value_pos))+")");
        plt::show();
        
    }
}

void graphics::plot_heatmap() const{
    /*  This function plots the matrix W as a heatmap
    */
    std::vector <std::vector <float>> w = sol_object.getW();
    std::vector <float> Time = sol_object.getTime();
    std::vector <float> pos = sol_object.getPositions();

    //we plot the matrix W as a heatmap
    // we adjust the size of the figure
    
    plt::figure_size(1200, 780);
    plt::figure();
    plt::imshow(w);

    //we adjust the ticks to fit the figure
    
    plt::xticks(Time);
    plt::yticks(pos);

    //we add a colorbar
    plt::colorbar();
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



