#pragma once
#include <vector>

enum fixed_var{POSITION, TIME};

class HyperbolicSolver{
    public:
        HyperbolicSolver(double (*)(double), double(*)(double),float, float, float, const unsigned int, const unsigned int);

        std::vector <double> getTime() const;
        std::vector <double> getPositions() const;
        std::vector <std::vector <double>> getW() const;

        // Get functions
        int get_m() const;
        int get_n() const;
        float get_alpha() const;
        float get_l() const;
        float get_T() const;

        // Print functions
        void print_m() const;
        void print_n() const;
        void print_alpha() const;
        void print_bounds() const;
        void print_y0() const;
	      void info() const;

        void print_table(short int, float) const;
    
        void savedata(std::string) const;
    private:
        // Solve functions
        void solve(double (*)(double), double(*)(double));
        void setInitialConditions(double (*)(double), double(*)(double));
        void matrixMultiplication();

        float lambda;
        float alpha;
        const unsigned int m;
        const unsigned int n;
        float l;
        float T;
        float h;
        float k;

        std::vector <std::vector <double>> w;
        std::vector <double> tiempos;
        std::vector <double> posiciones;

};
