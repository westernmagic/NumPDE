#pragma once
#include <Eigen/Core>
#include <cassert>
#include <stdexcept>
#include <tuple>

//! The gradient of the shape function (on the reference element)
//!
//! We have three shape functions
//!
//! @param i integer between 0 and 2 (inclusive). Decides which shape function to return.
//! @param x x coordinate in the reference element.
//! @param y y coordinate in the reference element.
inline Eigen::Vector2d gradientLambda(const int i, double x, double y) {
	// (write your solution here)
	std::ignore = x;
	std::ignore = y;
	assert(0 <= i && i <= 2);
	switch (i) {
		case 0:
			return Eigen::Vector2d(-1, -1);
		case 1:
			return Eigen::Vector2d(1, 0);
		case 2:
			return Eigen::Vector2d(0, 1);
		default:
			throw std::domain_error("i not in {0,1,2}");
	}

	return Eigen::Vector2d(0, 0); //remove when implemented
}
