#pragma once
#include "HyperbolicSolver.h"

class ExactCompare{
    public:
        ExactCompare(const HyperbolicSolver&, const float (*)(float, float));
        void print_comp_table(short int, float) const;
        void calculateValues();

        std::vector <float> getTime() const;
        std::vector <float> getPositions() const;
        std::vector <std::vector <float>> getW() const;


    private:
        const HyperbolicSolver& sol_object;
        const float (*exact_solution)(float, float);
        std::vector <float> tiempos;
        std::vector <float> posiciones;
	    std::vector <std::vector <float>> aproximaciones;
        std::vector <std::vector <float>> w;
};

