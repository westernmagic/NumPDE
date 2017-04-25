#pragma once
#include "shape.hpp"
#include <Eigen/Core>

//! The gradient of the shape function (on the reference element) for LINEAR FEM
//!
//! We have three shape functions
//!
//! @param i integer between 0 and 2 (inclusive). Decides which shape function to return.
//! @param x x coordinate in the reference element.
//! @param y y coordinate in the reference element.
inline Eigen::Vector2d gradientLambda(const int i, double x, double y) {
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
	Eigen::Vector2d value;
	// (write your solution here)
	return value;
}
//----------------gradshapefunEnd----------------
