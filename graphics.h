#include "HyperbolicSolver.h"

class graphics{
    public:
        graphics(const HyperbolicSolver&);
        void plot_slice(short int, float) const;
        void plot_heatmap() const;

    private:
        const HyperbolicSolver& sol_object;
};
