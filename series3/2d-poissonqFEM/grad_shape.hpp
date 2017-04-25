#pragma once
#include "shape.hpp"
#include <Eigen/Core>
#include <tuple>

//! The gradient of the shape function (on the reference element) for LINEAR FEM
//!
//! We have three shape functions
//!
//! @param i integer between 0 and 2 (inclusive). Decides which shape function to return.
//! @param x x coordinate in the reference element.
//! @param y y coordinate in the reference element.
inline Eigen::Vector2d gradientLambda(const int i, double x, double y) {
	std::ignore = x;
	std::ignore = y;

	return Eigen::Vector2d(-1 + (i > 0) + (i == 1),
	                       -1 + (i > 0) + (i == 2));
	return Eigen::Vector2d(0, 0); //remove when implemented
}

//----------------gradshapefunBegin----------------
//! The gradient of the shape function (on the reference element) for QUADRATIC FEM
//!
//! We have six shape functions
//!
//! @param i integer between 0 and 5 (inclusive). Decides which shape function to return.
//! @param x x coordinate in the reference element.
//! @param y y coordinate in the reference element.
inline Eigen::Vector2d gradientShapefun(const int i, double x, double y) {
	// Eigen::Vector2d value;
	// (write your solution here)
	assert(0 <= i && i <= 5);
	switch (i) {
		case 0:
			return Eigen::Vector2d(-3 + 4 * x + 4 * y, -3 + 4 * x + 4 * y);
		case 1:
			return Eigen::Vector2d(4 * x - 1, 0);
		case 2:
			return Eigen::Vector2d(0, 4 * y - 1);
		case 3:
			return Eigen::Vector2d(4 - 8 * x - 4 * y, -4 * x);
		case 4:
			return Eigen::Vector2d(4 * y, 4 * x);
		case 5:
			return Eigen::Vector2d(-4 * y, 4 - 4 * x - 8 * y);
		default:
			throw std::domain_error("i not in {0,1,2,3,4,5}");
	}
	//return value;
}
//----------------gradshapefunEnd----------------
