#pragma once
#include <cassert>
#include <stdexcept>

//! The shape function (on the reference element) for LINEAR FEM.
//!
//! We have three shape functions.
//!
//! lambda(0, x, y) should be 1 in the point (0,0) and zero in (1,0) and (0,1)
//! lambda(1, x, y) should be 1 in the point (1,0) and zero in (0,0) and (0,1)
//! lambda(2, x, y) should be 1 in the point (0,1) and zero in (0,0) and (1,0)
//!
//! @param i integer between 0 and 2 (inclusive). Decides which shape function to return.
//! @param x x coordinate in the reference element.
//! @param y y coordinate in the reference element.
inline double lambda(int i, double x, double y) {
	if (i == 0) {
		return 1 - x - y;
	} else if (i == 1) {
		return x;
	} else {
		return y;
	}
}

//----------------shapefunBegin----------------
//! The shape function (on the reference element) for QUADRATIC FEM
//!
//! We have six shape functions.
//!
//! shapefun(0, x, y) should be 1 in the point (0,0) and zero in the other 5
//! shapefun(1, x, y) should be 1 in the point (1,0) and zero in the other 5
//! shapefun(2, x, y) should be 1 in the point (0,1) and zero in the other 5
//! shapefun(3, x, y) should be 1 in the point (0.5,0) and zero in the other 5
//! shapefun(4, x, y) should be 1 in the point (0.5,0.5) and zero in the other 5
//! shapefun(5, x, y) should be 1 in the point (0,0.5) and zero in the other 5
//!
//! @param i integer between 0 and 5 (inclusive). Decides which shape function to return.
//! @param x x coordinate in the reference element.
//! @param y y coordinate in the reference element.
inline double shapefun(int i, double x, double y) {
	// double value = 0.0;
	// (write your solution here)
	assert(0 <= i && i <= 5);
	switch (i) {
		case 0:
			return (2 * lambda(0, x, y) - 1) * lambda(0, x, y);
		case 1:
			return (2 * lambda(1, x, y) - 1) * lambda(1, x, y);
		case 2:
			return (2 * lambda(2, x, y) - 1) * lambda(2, x, y);
		case 3:
			return 4 * lambda(0, x, y) * lambda(1, x, y);
		case 4:
			return 4 * lambda(1, x, y) * lambda(2, x, y);
		case 5:
			return 4 * lambda(0, x, y) * lambda(2, x, y);
		default:
			throw std::domain_error("i not in {0,1,2,3,4,5}");
	}
	// return value;
}
//----------------shapefunEnd----------------
