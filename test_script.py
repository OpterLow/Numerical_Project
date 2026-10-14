#Sub process is like a header file
import subprocess

#Defining a run_solver function that takes 3 parameters: "problem", "solver", and "args"
def run_solver(problem, solver, args):
	#cmd is a PYTHON LIST(strings), including the program filepath, problem string, solver string, and then
	#it concatenates the list(map(str, args)). Map turns the arr of ints args into string arr, then list turns it into a PYTHON LIST
	cmd = ["./mySolver", problem, solver] + list(map(str, args))
	#subprocess.run waits for the subprocess to run then captures the output as text strings
	result = subprocess.run(cmd, capture_output=True, text=True)
	//if result is not success print error
	if result.returncode != 0:
		print("Error:", result.stderr)
	#strips and removes 
	return result.stdout.strip()

# Example: polynomial x^2 - x - 2 = 0, interval [1,3]
out = run_solver("POLY", "BiSec", [1, -1, -2, 1, 3])
print("Solver output:", out)
