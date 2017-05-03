#pragma once
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <vector>

#include "mass_matrix.hpp"

//----------------AssembleMatrixBegin----------------
//! Assemble the mass matrix
//! for the linear system.
//!
//!
//! @param[out] triplets will at the end contain the Galerkin matrix
//! @param[in] vertices a list of triangle vertices
//! @param[in] triangles a list of triangles
SparseMatrix assembleMassMatrix(
    const Eigen::MatrixXd &vertices,
    const Eigen::MatrixXi &triangles) {
	std::vector<Triplet> triplets;
	const int            numberOfElements = triangles.rows();
	SparseMatrix         M(vertices.rows(), vertices.rows());

	// (write your solution here)

	M.setFromTriplets(triplets.begin(), triplets.end());

	return M;
}
//----------------AssembleMatrixEnd----------------
