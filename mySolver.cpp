#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// Find roots of a function, choosing an appropriate numerical method.
// inputs: equation type (polynomial, sin, cos, tan, exponential, ln),
//         solver (bisection, newton, false position)
//          constant(s), and interval [a, b]

int main(int argc, char** argv) {
    std::string equationType;
    std::string solver;
    std::vector<double> constants;
    double a, b;

    if (argc > 1) {
        equationType = argv[1];
        solver = argv[2];
        // Parse constants
        for (int i = 3; i < argc - 2; ++i) {
            constants.push_back(std::atof(argv[i]));
        }
        a = std::atof(argv[argc - 2]);
        b = std::atof(argv[argc - 1]);
        
        // run each solver based on the input, with the provided constants and interval [a, b]
        // construct arguments string for the solver: "a b <constants vector>"
        std::string arguments;
        arguments = std::to_string(a) + " " + std::to_string(b);
            for (double c : constants) {
                arguments += " " + std::to_string(c);
            }
        // vanity print of the constructed arguments string
        std::string vanityArugments = "a = " + std::to_string(a) + ", b = " + std::to_string(b) + ", constants =";
        for (double c : constants) {
            vanityArugments += " " + std::to_string(c);
        }
        if (solver == "bisection") {
            // Call bisection method
            // std::system(("./bisection " + arguments).c_str());
            cout << "Running bisection with arguments: " << vanityArugments << endl;

        } else if (solver == "newton") {
            // Call Newton's method
            cout << "Running newton with arguments: " << vanityArugments << endl;
        } else if (solver == "false position") {
            // Call false position method
            cout << "Running false position with arguments: " << vanityArugments << endl;
        } else {
            std::cerr << "Unknown solver: " << solver << std::endl;
        }
        return 0;
        
    }
    else {
        std::cerr << "Usage: " << argv[0] << " <equationType> <solver> <constants...> <a> <b>" << std::endl;
        return 1;
    }
}