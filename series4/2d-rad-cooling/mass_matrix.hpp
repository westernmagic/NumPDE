#pragma once
#include "coordinate_transform.hpp"
#include "grad_shape.hpp"
#include "integrate.hpp"
#include "shape.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>

//----------------compMatrixBegin----------------
//! Evaluate the mass matrix on the triangle spanned by
//! the points (a, b, c).
//!
//! Here, the stiffness matrix A is a 3x3 matrix
//!
//! $$A_{ij} = \int_{K} ( \lambda_i^K(x, y)  \lambda_j^K(x, y) dV$$
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
void computeMassMatrix(MatrixType & massMatrix,
                       const Point &a,
                       const Point &b,
                       const Point &c) {
	Eigen::Matrix2d coordinateTransform = makeCoordinateTransform(b - a, c - a);
	double          volumeFactor        = std::abs(coordinateTransform.determinant());

	for (int i = 0; i < 3; ++i) {
		for (int j = i; j < 3; ++j) {
			massMatrix(i, j) = integrate2d([&](double x, double y) {

				auto lambdaI = lambda(i, x, y);
				auto lambdaJ = lambda(j, x, y);

				return volumeFactor * (lambdaI * lambdaJ);

			});
		}
	}

	// Make symmetric (we did not need to compute these value above)
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < i; ++j) {
			massMatrix(i, j) = massMatrix(j, i);
		}
	}
}
//----------------compMatrixEnd----------------
