#include <vector>
#include <iostream>
#include <cmath>

#include "graphics.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;


graphics::graphics(const HyperbolicSolver& sol_object): 
                                sol_object(sol_object){
                  plt::backend("TkAgg");
                                }

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
    plt::imshow(w);

    //we adjust the ticks to fit the figure
    //Proportion for determining the number of ticks of the axis. The denominator is that number.
    
    const size_t x_divisions = (pos.size() > 50) ? pos.size()/10 : pos.size()/2;
    const size_t t_divisions = (Time.size() > 50) ? Time.size()/10 : Time.size()/2;

    //xticks and yticks receive a vector with the points where the axis will be drawn.
    //We cannot take these ticks as the original time and position vectors because these go from 0 to a final value
    //But ticks function takes the coordinate as pixels
    
    //Define ticks vectors. Will be built from the time and position vector via a scaling
    std::vector <float> *timeTicksPtr = new std::vector <float> (int(Time.size()/t_divisions) + 1, 0);
    std::vector <float> *posTicksPtr = new std::vector <float> (int(pos.size()/x_divisions) + 1, 0);

    // Define vectors for labels. Labels locate in tick position and have any desired string
    // We choose the string for corresponding to the real values
    std::vector <std::string> xlabels(int(pos.size()/x_divisions) + 1);
    std::vector <std::string> tlabels(int(Time.size()/t_divisions) + 1);

    //Build vectors for time
    for (int i = 0; i < int(Time.size()/t_divisions) + 1 ; i++){
      tlabels.at(i) = std::to_string(Time.at(t_divisions*i));
      timeTicksPtr->at(i) = i * t_divisions;
    }

    //Build vectors for position
    for (int j = 0; j < int(pos.size()/x_divisions) + 1; j++){
      xlabels.at(j) = std::to_string(pos.at(x_divisions*j));
      posTicksPtr->at(j) = j * x_divisions;
    }

    //SEt the ticks
    plt::xticks(*timeTicksPtr, tlabels);
    plt::yticks(*posTicksPtr, xlabels);


    //we add a colorbar
    plt::colorbar();
    plt::show();

    // Delete the pointers.
    // Not really necessary. Not that memory demanding
    delete timeTicksPtr;
    delete posTicksPtr;
    timeTicksPtr = NULL; posTicksPtr = NULL;
}

void graphics::plot_slice(const ExactCompare& compare_object, short int fix, float value_pos) const{
    /*  This function selects either a colum or a row of the matriz W and plots it against the time or position
        depending on the value of the variable fixed.
        For the rows value_pos < m+1 and for the columns value_pos < n+1
    */

    std::vector <float> Time = sol_object.getTime();
    std::vector <float> pos = sol_object.getPositions();

    const int m = pos.size() - 1;
    const int n = Time.size() - 1;
    
    std::vector <std::vector <float>> w = sol_object.getW();
    std::vector <std::vector <float>> w_exact = compare_object.getW();
    std::vector <float> *W = new std::vector <float>();
    std::vector <float> *W_exact = new std::vector <float>();

    if (fix == POSITION){

        //the fixed poition index must be smaller than m    

        // Extracts a column of the matrix W corresponding to the fixed position
        for(int i = 0; i < n+1; i++){
                W->push_back(w.at(value_pos).at(i));
                W_exact->push_back(w_exact.at(value_pos).at(i));
        }


        plt::plot(Time, *W);
        plt::plot(Time, *W_exact);

        delete W;
        delete W_exact;
        W = NULL;
        W_exact = NULL;

        plt::title("Solution of the differential equation at a the fixed position "+std::to_string(pos.at(value_pos)));
        plt::xlabel("Time");
        plt::ylabel("W ("+std::to_string(pos.at(value_pos))+",j)");
        plt::show();
    }

    else if (fix == TIME){

        //the fixed time index must be smaller than n

        for(int i = 0; i < m+1; i++){
            W->push_back(w.at(i).at(value_pos));
            W_exact->push_back(w_exact.at(i).at(value_pos));
    }

        plt::plot(pos, *W);
        plt::plot(pos, *W_exact);

        delete W;
        delete W_exact;
        W = NULL;
        W_exact = NULL;

        plt::title("Solution of the differential equation for the fixed time "+std::to_string(Time.at(value_pos)));
        plt::xlabel("Position");
        // Consider using sstream
        plt::ylabel("W (i,"+std::to_string(Time.at(value_pos))+")");
        plt::show();
        
    }
}

void graphics::plot_heatmap(const ExactCompare& compare_object) const{
    /*  This function plots the difference between the matrix W and the exact solution as a heatmap
    */
    std::vector <std::vector <float>> w = sol_object.getW();
    std::vector <std::vector <float>> *w_exact = new std::vector <std::vector <float>> (compare_object.getW());

    std::vector <float> Time = sol_object.getTime();
    std::vector <float> pos = sol_object.getPositions();

    for(int i = 0; i < pos.size(); i++){
      for(int j=0; j < Time.size(); j++){
        w_exact->at(i).at(j) = w_exact->at(i).at(j)- w.at(i).at(j); 
      }
    }

    //we plot the matrix W as a heatmap
    // we adjust the size of the figure

    const size_t x_divisions = (pos.size() > 50) ? (pos.size()-1)/10 : (pos.size()-1)/2;
    const size_t t_divisions = (Time.size() > 50) ? (Time.size()-1)/10 : (Time.size()-1)/2;

    plt::figure_size(1200, 780);
    plt::imshow(*w_exact, {{"cmap","PRGn"}});


    delete w_exact;
    w_exact = NULL;
    //we adjust the ticks to fit the figure

    //we adjust the ticks to fit the figure
    std::vector <float> *timeTicksPtr = new std::vector <float> (int(Time.size()/t_divisions) + 1, 0);
    std::vector <float> *posTicksPtr = new std::vector <float> (int(pos.size()/x_divisions) + 1, 0);

    std::vector <std::string> xlabels(int(pos.size()/x_divisions) + 1);
    std::vector <std::string> tlabels(int(Time.size()/t_divisions) + 1);
   

    for (int i = 0; i < int(Time.size()/t_divisions) + 1 ; i++){
      tlabels.at(i) = std::to_string(Time.at(t_divisions*i));
      timeTicksPtr->at(i) = i * t_divisions;
    }

    for (int j = 0; j < int(pos.size()/x_divisions) + 1; j++){
      xlabels.at(j) = std::to_string(pos.at(x_divisions*j));
      posTicksPtr->at(j) = j * x_divisions;
    }


    plt::xticks(*timeTicksPtr, tlabels);
    plt::yticks(*posTicksPtr, xlabels);


    //we add a colorbar
    plt::colorbar();
    plt::show();

    delete timeTicksPtr;
    delete posTicksPtr;
    timeTicksPtr = NULL; posTicksPtr = NULL;

}

