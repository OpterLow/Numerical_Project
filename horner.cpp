#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


int main(int argc, char** argv) {

//Make a vector for our coefficients and the quotient
vector<int> coeffs, quotient;
//This x is what we are solving the function for i.e p(x) = y and p'(x) = z
int x = atoi(argv[1]);
int p;

//fill coeffs vector
for(int i = 2; i < argc; i++) {
		//i dont know if i can do int* argv[] in the beginning or if all keyboard input is read as char so imma just ascii to int it yk? XD
	coeffs.push_back(atoi(argv[i]));
}

//get first element of coeffs is the first element of the quotient
quotient.push_back(coeffs[0]);

//get p(x) and fill quotient vector
for(int i = 1; i < static_cast<int>(coeffs.size()); i++) {
//so you take the coefficient, 
	quotient.push_back(coeffs[i] + (x * quotient[i-1]));
}

p = quotient.back(); //The last element of the quotient vector is actually the solution for p(x)
quotient.pop_back(); //Delete the solution for p(x) because we already stored it in p
cout << "The result of the polynomial p(" << x << ") is " << p << endl;


//if user wants to get the quotient
cout << "Would you like the quotient? (Y for yes, anything else for no)" << endl;
string want_quotient;
cin >> want_quotient;
if(want_quotient == "Y") {
	for(int i = 0; i < static_cast<int>(quotient.size()); i++) {
	cout << quotient[i];
		if(i != static_cast<int>(quotient.size()) - 1)
		cout << ", ";
	}
cout << endl;
}
else{
return 0;
}
return 0;
}

//The output of the quotient can be fed back into this file to get the solution of p'(x)
