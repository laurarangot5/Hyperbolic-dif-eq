#pragma once
#include "HyperbolicSolver.h"
#include "ExactCompare.h"

class graphics{
    public:
        graphics(const HyperbolicSolver&);
        void plot_slice(short int, float) const;
        void plot_slice(const ExactCompare&, short int, float) const;
        void plot_heatmap() const;
        void plot_heatmap(const ExactCompare&) const;
    private:
        const HyperbolicSolver& sol_object;
};
