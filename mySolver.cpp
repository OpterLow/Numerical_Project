#include <iomanip>
#include <iostream>
#include "config.h"
#include "algorithms.h"

using namespace std;

// usage: ./mySolver problem solver constants... a b
// problems: POLY, COS, SIN, TAN, EXP, LOG  (POLY: cn ... c0 a b; others: c a b)
// solvers: BiSec, FalsePos, Newton1, Newton2, Bracket-Newton1, Bracket-Newton2
//          where Newton1 uses analytic derivative and Newton2 uses numeric derivative
// output (stdout): "<root> <iterations>"; errors go to stderr with exit code 1

int main(int argc, char** argv) {
    AppConfig config;
    string error;

    if (!parseArguments(argc, argv, config, error) || !validateConfig(config, error)) {
        cerr << "Error: " << error << "\n";
        cerr << "Usage: " << argv[0] << " <POLY|COS|SIN|TAN|EXP|LOG> <solver> <constants...> <a> <b>\n";
        return 1;
    }

    SolverResult result;
    if (config.solver == "bisec") {
        result = runBisection(config);
    } else if (config.solver == "falsepos") {
        result = runFalsePosition(config);
    } else if (config.solver == "newton1") {
        result = runNewton(config, DERIV_ANALYTIC);
    } else if (config.solver == "newton2") {
        result = runNewton(config, DERIV_NUMERIC);
    } else if (config.solver == "bracket-newton1") {
        result = runBracketNewton(config, DERIV_ANALYTIC);
    } else {
        result = runBracketNewton(config, DERIV_NUMERIC);
    }

    if (!result.converged) {
        cerr << "Error: solver did not converge\n";
        return 1;
    }

    cout << setprecision(15) << result.root << " " << result.iterations << endl;
    return 0;
}
