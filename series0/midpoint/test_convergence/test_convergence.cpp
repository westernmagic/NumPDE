#include "midpoint.hpp" // To use our library
#include "writer.hpp"   // This is the output function to write to file

// We store our results in a vector
#include <vector>

// On some platforms we need to add this in order
// to get M_PI defined
#define _USE_MATH_DEFINES

// for our usual math functions and constants
#include <math.h>

double f(double x) {
	return sin(M_PI * x);
}

int main(int, char **) {
	// (write your solution here)

	return 0;
}
