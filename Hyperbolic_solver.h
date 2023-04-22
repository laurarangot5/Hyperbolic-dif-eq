#include <vector>

enum fixed_var{POSITION, TIME};

class HyperbolicSolver{
    public:
        HyperbolicSolver(float (*)(float), float (*)(float),float, float, float, const unsigned int, const unsigned int);
        std::vector <float> getTime();
        std::vector <float> getPositions();
        std::vector <std::vector <float>> getW();
        void print_m();
        void print_n();
        void print_alpha();
        void print_bounds();
        void print_y0();
        void print_table(short int, float);
    
    private:
        void solve(float (*)(float), float (*)(float));
        void setInitialConditions(float (*)(float), float (*)(float));
        void matrixMultiplication();
        std::vector <float> t;
        std::vector <float> x;
        float lambda;
        float alpha;
        static const unsigned int m;
        static const unsigned int n;
        std::vector <std::vector <float>> w;
        float l;
        float T;
        float h;
        float k;
        std::vector <float> tiempos;
        std::vector <float> posiciones;

};