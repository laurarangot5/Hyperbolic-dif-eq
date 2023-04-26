#pragma once
#include <vector>

enum fixed_var{POSITION, TIME};

class HyperbolicSolver{
    public:
        HyperbolicSolver(float (*)(float), float (*)(float),float, float, float, const unsigned int, const unsigned int);
        std::vector <float> getTime() const;
        std::vector <float> getPositions() const;
        std::vector <std::vector <float>> getW() const;
        int get_m() const;
        int get_n() const;
        float get_alpha() const;
        float get_l() const;
        float get_T() const;
        void print_m() const;
        void print_n() const;
        void print_alpha() const;
        void print_bounds() const;
        void print_y0() const;
        void print_table(short int, float) const;
    
    private:
        void solve(float (*)(float), float (*)(float));
        void setInitialConditions(float (*)(float), float (*)(float));
        void matrixMultiplication();
        std::vector <float> t;
        std::vector <float> x;
        float lambda;
        float alpha;
        const unsigned int m;
        const unsigned int n;
        std::vector <std::vector <float>> w; //(const unsigned int, std::vector<float>);
        float l;
        float T;
        float h;
        float k;
        std::vector <float> tiempos;
        std::vector <float> posiciones;

};

class graphics{
    public:
        graphics(const HyperbolicSolver&);
        void plot_slice(short int, float) const;
        void plot_heatmap() const;

    private:
        const HyperbolicSolver& sol_object;
};

class ExactCompare{
    public:
        ExactCompare(const HyperbolicSolver&, const float (*)(float, float));
        void print_comp_table(short int, float) const;
        void calculateValues(short int, float);

    private:
        const HyperbolicSolver& sol_object;
        const float (*exact_solution)(float, float);
        std::vector <float> tiempos;
        std::vector <float> posiciones;
        std::vector <float> w;
};
