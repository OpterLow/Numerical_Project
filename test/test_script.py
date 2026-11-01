import math
import os
import random
import subprocess
import sys

# The solver binary lives in the project root, one level above this script
SOLVER = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "mySolver")


# 1. Runner Function: Invokes C/C++ executable via subprocess
def run_raw(argv):
    """Runs the solver with the given arguments; returns (exit code, stdout, stderr)."""
    result = subprocess.run([SOLVER] + [str(a) for a in argv], capture_output=True, text=True)
    return result.returncode, result.stdout.strip(), result.stderr.strip()


def run_solver(problem, solver, args):
    code, out, err = run_raw([problem, solver] + list(args))
    if code != 0:
        print(f"Error executing {problem} {solver}: {err}")
        return None
    return out


# 2. Input Generator: Generates test parameters with domain constraints
def arg_generator(problem):
    if problem == "POLY":
        root = round(random.uniform(-2, 2), 2)
        coeffs = [1, -root, 1, -root]
        a = root - random.uniform(0.5, 2)
        b = root + random.uniform(0.5, 2)
        return coeffs + [round(a, 2), round(b, 2)]

    elif problem == "COS":
        c = round(random.uniform(-0.9, 0.9), 2)
        root = math.acos(c)
        a = max(0.0, root - 0.5)
        b = min(math.pi, root + 0.5)
        return [c, round(a, 2), round(b, 2)]

    elif problem == "SIN":
        c = round(random.uniform(-0.9, 0.9), 2)
        root = math.asin(c)
        a = max(-math.pi / 2, root - 0.5)
        b = min(math.pi / 2, root + 0.5)
        return [c, round(a, 2), round(b, 2)]

    elif problem == "TAN":
        c = round(random.uniform(-5, 5), 2)
        root = math.atan(c)
        a = max(0.9 * (-math.pi / 2), root - 0.5)
        b = min(0.9 * (math.pi / 2), root + 0.5)
        return [c, round(a, 2), round(b, 2)]

    elif problem == "EXP":
        c = round(random.uniform(0.5, 5), 2)
        root = math.log(c)
        a = round(root - 0.5, 2)
        b = round(root + 0.5, 2)
        return [c, a, b]

    elif problem == "LOG":
        c = round(random.uniform(-5, 5), 2)
        root = math.exp(c)
        # scale the interval with the root so tiny roots (very negative c) stay bracketed
        return [c, root / 2, root * 2]


# 3. Evaluator: Computes residual f(x) to verify solver accuracy
def func_evaluater(problem, x, args):
    if problem == "POLY":
        coeffs = args[:-2]
        degree = len(coeffs) - 1
        return sum(c * (x ** (degree - i)) for i, c in enumerate(coeffs))

    elif problem == "COS":
        c = args[0]
        return math.cos(x) - c

    elif problem == "SIN":
        c = args[0]
        return math.sin(x) - c

    elif problem == "TAN":
        c = args[0]
        return math.tan(x) - c

    elif problem == "EXP":
        c = args[0]
        return math.exp(x) - c

    elif problem == "LOG":
        c = args[0]
        return math.log(x) - c

    return 0.0


GENERAL_CASES_PER_PROBLEM = 5
RESIDUAL_LIMIT = 1e-8
PI = math.pi

# (name, problem, args, expected root, solvers that are expected to report failure)
VALID_CORNER_CASES = [
    ("root at left endpoint", "POLY", [1, -2, 2, 5], 2.0, []),
    ("root at right endpoint", "POLY", [1, -2, -1, 2], 2.0, []),
    ("tiny interval", "POLY", [1, -2, 1.999999, 2.000001], 2.0, []),
    ("degree-5 polynomial", "POLY", [1, -1, 5, -5, 4, -4, 0, 3], 1.0, []),
    ("zero derivative at the start point", "POLY", [1, 0, 0, -1, -2, 2], 1.0, ["Newton1"]),
    ("COS root at the midpoint", "COS", [0, 0, 3.141592653589793], PI / 2, []),
    ("SIN root at 0", "SIN", [0, -1, 1], 0.0, []),
    ("TAN near the asymptote (steep curve)", "TAN", [1000, 1.5, 1.5707], math.atan(1000), ["FalsePos", "Newton1", "Newton2"]),
    ("EXP very wide interval (slow false position)", "EXP", [5, -20, 20], math.log(5), ["FalsePos"]),
    ("LOG very small root (Newton leaves the domain)", "LOG", [-10, 1e-6, 1], math.exp(-10), ["Newton1", "Newton2"]),
]

# (description, full argument list)
INVALID_CASES = [
    ("no arguments", []),
    ("no constants (POLY)", ["POLY", "BiSec", 0, 3]),
    ("missing interval end", ["COS", "BiSec", 0.4, 0]),
    ("too many constants (COS)", ["COS", "BiSec", 0.4, 1, 0, 3]),
    ("non-numeric constant", ["POLY", "BiSec", 1, "x", -2, 1, 3]),
    ("non-numeric interval", ["COS", "BiSec", 0.4, "a", 3]),
    ("nan constant", ["COS", "BiSec", "nan", 0, 3]),
    ("unknown problem", ["FOO", "BiSec", 0.4, 0, 3]),
    ("unknown solver", ["COS", "Secant", 0.4, 0, 3]),
    ("a equals b", ["COS", "BiSec", 0.4, 1, 1]),
    ("a greater than b", ["POLY", "BiSec", 1, -1, -2, 3, 1]),
    ("no sign change (POLY)", ["POLY", "BiSec", 1, -1, -2, 3, 5]),
    ("zero leading coefficient", ["POLY", "BiSec", 0, 1, -2, 0, 5]),
    ("COS c above 1", ["COS", "BiSec", 2, 0, 3]),
    ("SIN c below -1", ["SIN", "BiSec", -1.5, -1, 1]),
    ("COS interval outside [0, pi]", ["COS", "BiSec", 0.4, 0, 3.2]),
    ("SIN interval outside [-pi/2, pi/2]", ["SIN", "BiSec", 0.5, -2, 1]),
    ("TAN interval reaches pi/2", ["TAN", "BiSec", 1, 0, PI / 2]),
    ("EXP with c = 0", ["EXP", "BiSec", 0, -1, 1]),
    ("EXP with negative c", ["EXP", "BiSec", -2, -1, 1]),
    ("LOG interval with a = 0", ["LOG", "BiSec", 1, 0, 5]),
    ("LOG interval with a < 0", ["LOG", "BiSec", 1, -1, 5]),
    ("no sign change (EXP)", ["EXP", "BiSec", 5, 3, 4]),
]


# 4. Main Test Driver Loop
if __name__ == "__main__":
    problems = ["POLY", "COS", "SIN", "TAN", "EXP", "LOG"]
    solvers = [
        "BiSec",
        "FalsePos",
        "Newton1",
        "Newton2",
        "Bracket-Newton1",
        "Bracket-Newton2",
    ]

    random.seed(3340)  # fixed seed so the report results are reproducible
    results = []  # (suite, description, passed)
    stats = {s: {"runs": 0, "passed": 0, "iters": [], "resid": []} for s in solvers}

    # ---- Suite 1: general (random) cases ----
    print("=== Suite 1: general cases (random inputs, residual must be < 1e-8) ===")
    for prob in problems:
        for _ in range(GENERAL_CASES_PER_PROBLEM):
            args = arg_generator(prob)
            print(f"\nProblem: {prob:<5} | Arguments: {args}")
            for solver in solvers:
                code, out, err = run_raw([prob, solver] + args)
                ok, detail = False, "no output"
                if code == 0:
                    try:
                        root_text, iter_text = out.split()
                        root, iters = float(root_text), int(iter_text)
                        residual = func_evaluater(prob, root, args)
                        ok = abs(residual) < RESIDUAL_LIMIT
                        detail = f"root {root:12.8f} | f(root) {residual:9.2e} | iterations {iters}"
                        stats[solver]["iters"].append(iters)
                        stats[solver]["resid"].append(abs(residual))
                    except ValueError:
                        detail = f"could not parse output '{out}'"
                else:
                    detail = f"exit code {code}: {err}"
                stats[solver]["runs"] += 1
                stats[solver]["passed"] += ok
                results.append(("general", f"{prob} {solver} {args}", ok))
                print(f"  {'PASS' if ok else 'FAIL'} [{solver:<16}] {detail}")

    # ---- Suite 2: corner cases that should succeed ----
    print("\n=== Suite 2: corner cases that should succeed (root within 1e-6) ===")
    for name, prob, args, expected, failing in VALID_CORNER_CASES:
        print(f"\n{name}: {prob} {args}")
        for solver in solvers:
            code, out, err = run_raw([prob, solver] + args)
            if solver in failing:
                ok = code != 0
                detail = "reported failure as expected" if ok else "unexpectedly succeeded"
            elif code == 0:
                root = float(out.split()[0])
                ok = abs(root - expected) < 1e-6
                detail = f"root {root:.10f} (expected {expected:.10f})"
            else:
                ok, detail = False, f"exit code {code}: {err}"
            results.append(("corner-valid", f"{name} / {solver}", ok))
            print(f"  {'PASS' if ok else 'FAIL'} [{solver:<16}] {detail}")

    # ---- Suite 3: malformed input that must be rejected ----
    print("\n=== Suite 3: malformed input (must exit with code 1 and an Error message) ===")
    for name, argv in INVALID_CASES:
        code, out, err = run_raw(argv)
        ok = code == 1 and "Error" in err and out == ""
        results.append(("invalid", name, ok))
        message = err.splitlines()[0] if err else "(no error message)"
        print(f"  {'PASS' if ok else 'FAIL'} {name:<38} -> {message}")

    # ---- Summary (good for the report) ----
    print("\n=== Solver comparison on general cases ===")
    print(f"{'Solver':<18}{'Passed':>10}{'Avg iterations':>17}{'Max iterations':>16}{'Max |f(root)|':>16}")
    for solver in solvers:
        st = stats[solver]
        avg = sum(st["iters"]) / len(st["iters"]) if st["iters"] else float("nan")
        worst = max(st["iters"]) if st["iters"] else 0
        resid = max(st["resid"]) if st["resid"] else float("nan")
        print(f"{solver:<18}{str(st['passed']) + '/' + str(st['runs']):>10}{avg:>17.1f}{worst:>16}{resid:>16.2e}")

    print("\n=== Test summary ===")
    for suite in ("general", "corner-valid", "invalid"):
        suite_results = [r for r in results if r[0] == suite]
        print(f"{suite:<14}{sum(r[2] for r in suite_results)}/{len(suite_results)} passed")
    total_passed = sum(r[2] for r in results)
    print(f"{'TOTAL':<14}{total_passed}/{len(results)} passed")
    sys.exit(0 if total_passed == len(results) else 1)