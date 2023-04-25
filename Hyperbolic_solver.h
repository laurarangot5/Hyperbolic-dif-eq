#include <vector>

enum fixed_var{POSITION, TIME};

class HyperbolicSolver{
    public:
        HyperbolicSolver(float (*)(float), float (*)(float),float, float, float, const unsigned int, const unsigned int);
        std::vector <float> getTime() const;
        std::vector <float> getPositions() const;
        std::vector <std::vector <float>> getW() const;
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
        unsigned int m;
        unsigned int n;
        std::vector <std::vector <float>> w; //(const unsigned int, std::vector<float>);
        float l;
        float T;
        float h;
        float k;
        std::vector <float> tiempos;
        std::vector <float> posiciones;

};
