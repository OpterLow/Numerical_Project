import math
import random
import subprocess


# 1. Runner Function: Invokes C/C++ executable via subprocess
def run_solver(problem, solver, args):
	#change name of ./mySolver to the program name we are using
    cmd = ["./mySolver", problem, solver] + list(map(str, args))
	#eats the output and checks it against da math fr fr
    result = subprocess.run(cmd, capture_output=True, text=True)

    if result.returncode != 0:
        print(f"Error executing {problem} {solver}: {result.stderr.strip()}")
        return None

    return result.stdout.strip()


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
        a = max(0.01, round(root - 0.5, 2))
        b = round(root + 0.5, 2)
        return [c, a, b]


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

    print("=== Starting Solver Verification Harness ===")
	#for each problem, run the arg generator with the problem and print the problem and args
    for prob in problems:
        args = arg_generator(prob)
        print(f"\nProblem: {prob:<5} | Arguments: {args}")
		
        for solver in solvers:
            out = run_solver(prob, solver, args)

            if out:
                try:
					#compare the outputted root to the computed root in here
                    computed_root = float(out)
                    residual = func_evaluater(prob, computed_root, args)
                    print(
                        f"  [{solver:<18}] Root: {computed_root:10.6f} | f(root): {residual:10.2e}"
                    )
                except ValueError:
                    print(
                        f"  [{solver:<18}] Output parsing failed. Raw output: '{out}'"
                    )
            else:
                print(f"  [{solver:<18}] No output received")