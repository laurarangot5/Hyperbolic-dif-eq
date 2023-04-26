#pragma once
#include "HyperbolicSolver.h"

class ExactCompare{
    public:
        ExactCompare(const HyperbolicSolver&, const float (*)(float, float));
        void print_comp_table(short int, float) const;
        void calculateValues();

    private:
        const HyperbolicSolver& sol_object;
        const float (*exact_solution)(float, float);
        std::vector <float> tiempos;
        std::vector <float> posiciones;
	std::vector <std::vector <float>> aproximaciones;
        std::vector <std::vector <float>> w;
};
