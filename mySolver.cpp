#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// Find roots of a function, choosing an appropriate numerical method.
// inputs: equation type (polynomial, sin, cos, tan, exponential, ln),
//         solver (bisection, newton, false position)
//          constant(s), and interval [a, b]

int main(int argc, char** argv) {
    string equationType;
    string solver;
    vector<double> constants;
    double a, b;

    if (argc > 1) {
        equationType = argv[1];
        solver = argv[2];
        // Parse constants
        for (int i = 3; i < argc - 2; ++i) {
            constants.push_back(atof(argv[i]));
        }
        a = atof(argv[argc - 2]);
        b = atof(argv[argc - 1]);
        
        // run each solver based on the input, with the provided constants and interval [a, b]
        // construct arguments string for the solver: "a b <equationType> <constants vector>"
        string arguments;
        arguments = to_string(a) + " " + to_string(b) + " " + equationType;
        for (double c : constants) {
            arguments += " " + to_string(c);
        }

        // vanity print of the constructed arguments string
        string vanityArugments = "a = " + to_string(a) + ", b = " + to_string(b) + ", equationType = " + equationType + ", constants =";
        for (double c : constants) {
            vanityArugments += " " + to_string(c);
        }
        
        if (solver == "bisection") {
            // Call bisection method
            // system(("./bisection " + arguments).c_str());
            cout << "Running bisection with arguments: " << vanityArugments << endl;

        } else if (solver == "newton") {
            // Call Newton's method
            cout << "Running newton with arguments: " << vanityArugments << endl;
        } else if (solver == "false position") {
            // Call false position method
            cout << "Running false position with arguments: " << vanityArugments << endl;
        } else {
            cerr << "Unknown solver: " << solver << endl;
        }
        return 0;
        
    }
    else {
        cerr << "Usage: " << argv[0] << " <equationType> <solver> <constants...> <a> <b>" << endl;
        return 1;
    }
}