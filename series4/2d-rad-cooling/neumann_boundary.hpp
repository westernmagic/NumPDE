#pragma once
#include "coordinate_transform.hpp"
#include "grad_shape.hpp"
#include "integrate.hpp"
#include "shape.hpp"
#include <Eigen/Core>

//! Makes the matrix corresponding to the neumann boundary conditions
//!
template <class MatrixType, class Point>
void computeBoundaryMatrix(MatrixType & boundaryMatrix,
                           const Point &a,
                           const Point &b,
                           double       gamma) {
	// (write your solution here)
	boundaryMatrix.resize(2, 2);

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			auto f = [&](double t) -> double {
				return lambda(i, t / 2.0 + 1, 0) * lambda(j, t / 2.0 + 1, 0);
			};

			double scaling_factor = (b - a).norm() / 2.0;
			boundaryMatrix(i, j) = scaling_factor * gamma * integrate1d(f);
		}
	}
}
