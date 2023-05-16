#pragma once
#include "HyperbolicSolver.h"

class ExactCompare{
    public:
        ExactCompare(const HyperbolicSolver&, const double (*)(double, double));
        void print_comp_table(short int, float) const;
        void calculateValues();

        std::vector <double> getTime() const;
        std::vector <double> getPositions() const;
        std::vector <std::vector <double>> getW() const;


    private:
        const HyperbolicSolver& sol_object;
        const double (*exact_solution)(double, double);
        std::vector <double> tiempos;
        std::vector <double> posiciones;
	    std::vector <std::vector <double>> aproximaciones;
        std::vector <std::vector <double>> w;
};

