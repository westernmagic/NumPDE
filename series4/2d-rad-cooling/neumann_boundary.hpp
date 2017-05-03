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
}
