#pragma once
#include "coordinate_transform.hpp"
#include "integrate.hpp"
#include "shape.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <functional>

//----------------compVectorBegin----------------
//! Evaluate the load vector on the triangle spanned by
//! the points (a, b, c).
//!
//! Here, the load vector is a vector $(v_i)$ of
//! three components, where
//!
//! $$v_i = \int_{K} \lambda_i^K(x, y) f(x, y) \; dV$$
//!
//! where $K$ is the triangle spanned by (a, b, c).
//!
//! @param[out] loadVector should be a vector of length 6.
//!                        At the end, will contain the integrals above.
//!
//! @param[in] a the first corner of the triangle
//! @param[in] b the second corner of the triangle
//! @param[in] c the third corner of the triangle
//! @param[in] f the function f (LHS).
template <class Vector, class Point>
void computeLoadVector(Vector &     loadVector,
                       const Point &a,
                       const Point &b,
                       const Point &c,
                       const std::function<double(double, double)> &f) {
	Eigen::Matrix2d coordinateTransform = makeCoordinateTransform(b - a, c - a);
	double          volumeFactor        = std::abs(coordinateTransform.determinant());
	// (write your solution here)
	loadVector.resize(6);

	for (int i = 0; i < 6; ++i) {
		auto ff = [&](double x, double y) -> double {
			Eigen::Vector2d transformedPoint = coordinateTransform * Eigen::Vector2d(x, y) + a.transpose();

			return f(transformedPoint.x(), transformedPoint.y()) * shapefun(i, x, y) * volumeFactor;
		};

		loadVector(i) = integrate(ff);
	}
}
//----------------compVectorEnd----------------
