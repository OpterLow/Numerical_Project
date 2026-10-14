import subprocess

def run_solver(problem, solver, args):
	cmd = ["./mySolver", problem, solver] + list(map(str, args))
	result = subprocess.run(cmd, capture_output=True, text=True)
	if result.returncode != 0:
		print("Error:", result.stderr)
	return result.stdout.strip()

# Example: polynomial x^2 - x - 2 = 0, interval [1,3]
out = run_solver("POLY", "BiSec", [1, -1, -2, 1, 3])
print("Solver output:", out)
