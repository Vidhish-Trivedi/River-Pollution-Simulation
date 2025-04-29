#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// Struct to hold initial conditions
struct InitialConditions {
    int idx;             // Testcase id
    double c;            // River velocity
    double mu;           // Pollutant decay rate
    double gamma_source; // Pollutant source strength at x=0
    double x_max;        // Length of river to simulate
    double t_target;     // Time at which solution is evaluated
    int N;               // Number of spatial steps
};

// Unit step function
int U(double val) {
    return (val >= 0) ? 1 : 0;
}

// Function to compute pollutant concentration at (x, t)
double pollutant_concentration(double x, double t, const InitialConditions& ic) {
    double argument = t - (x / ic.c);
    return ic.gamma_source * U(argument) * exp(-ic.mu * x / ic.c);
}

// List of test cases with different initial conditions
vector<InitialConditions> test_cases = {
    {0, 1.0, 0.1, 5.0, 100.0, 0.0, 1000}, // Test case 1
    {1, 1.0, 0.1, 5.0, 100.0, 20.0, 1000}, // Test case 1
    {2, 0.8, 0.05, 4.0, 80.0, 15.0, 800},  // Test case 2
    {3, 1.2, 0.2, 6.0, 120.0, 25.0, 1200}, // Test case 3
    {4, 1.5, 0.15, 7.0, 150.0, 30.0, 1500} // Test case 4
};

int main() {
    for (const InitialConditions& ic : test_cases) {
        // Discretized spatial domain
        vector<double> x(ic.N + 1);
        vector<double> rho(ic.N + 1); // pollutant concentration

        double dx = ic.x_max / ic.N;

        // Initialize x and rho
        for (int i = 0; i <= ic.N; ++i) {
            x[i] = i * dx;
            rho[i] = pollutant_concentration(x[i], ic.t_target, ic);
        }

        // Output results to a CSV file
        string fname = "pollutant_traveling_wave_" + to_string(ic.idx) + ".csv";
        system("mkdir -p Results");
        ofstream outfile("Results/" + fname);
        outfile << "x,pollutant_concentration\n";
        for (int i = 0; i <= ic.N; ++i) {
            outfile << x[i] << "," << rho[i] << "\n";
        }
        outfile.close();
        cout << "Simulation complete. Results saved to " + fname + ".\n";
    }

    return 0;
}
