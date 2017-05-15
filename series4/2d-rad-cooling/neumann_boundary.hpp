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
				return lambda(i, (1 + t) / 2, 0) * lambda(j, (1 - t) / 2, 0);
			};

			boundaryMatrix(i, j) = integrate1d(f) * gamma / (2 * (b-a).norm());
		}
	}
}
