#pragma once
#include "constant_function.hpp"
#include "coordinate_transform.hpp"
#include "grad_shape.hpp"
#include "integrate.hpp"
#include "shape.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>

//----------------compMatrixBegin----------------
//! Evaluate the stiffness matrix on the triangle spanned by
//! the points (a, b, c).
//!
//! Here, the stiffness matrix A is a 3x3 matrix
//!
//! $$A_{ij} = \int_{K} ( sigma(x,y) \nabla \lambda_i^K(x, y) \cdot  \nabla \lambda_j^K(x, y)\; + r \lambda_i^K(x,y)\lambda_j^K(x,y) )dV$$
//!
//! where $K$ is the triangle spanned by (a, b, c).
//!
//! @param[out] stiffnessMatrix should be a 3x3 matrix
//!                        At the end, will contain the integrals above.
//!
//! @param[in] a the first corner of the triangle
//! @param[in] b the second corner of the triangle
//! @param[in] c the third corner of the triangle
//! @param[in] sigma the function sigma as in the exercise
//! @param[in] r the parameter r as in the exercise
template <class MatrixType, class Point>
void computeStiffnessMatrix(MatrixType & stiffnessMatrix,
                            const Point &a,
                            const Point &b,
                            const Point &c,
                            const std::function<double(double, double)> &sigma = constantFunction,
                            const double r = 0) {
	Eigen::Matrix2d coordinateTransform = makeCoordinateTransform(b - a, c - a);
	double          volumeFactor        = std::abs(coordinateTransform.determinant());

	Eigen::Matrix2d elementMap = coordinateTransform.inverse().transpose();
	// (write your solution here)
	stiffnessMatrix.resize(3, 3);

	auto PhiK = [&](const Eigen::Vector2d &x) -> Eigen::Vector2d {
		return coordinateTransform * x + a.transpose();
	};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			auto f = [&](double x, double y) -> double {
				Eigen::Vector2d transformedPoint = PhiK(Eigen::Vector2d(x,y));

				return (sigma(transformedPoint.x(), transformedPoint.y()) * (elementMap * gradientLambda(i, x, y)).dot(elementMap * gradientLambda(j, x, y)) + r * lambda(i, x, y) * lambda(j, x, y)) * volumeFactor;
			};
			stiffnessMatrix(i, j) = integrate(f);
		}
	}
}
//----------------compMatrixEnd----------------
