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
	triplets.reserve(numberOfElements * 3 * 3);
	for (int i = 0; i < numberOfElements; ++i) {
		auto &indexSet = triangles.row(i);

		const auto &a = vertices.row(indexSet(0));
		const auto &b = vertices.row(indexSet(1));
		const auto &c = vertices.row(indexSet(2));

		Eigen::Matrix3d massMatrix;
		computeMassMatrix(massMatrix, a, b, c);

		for (int n = 0; n < 3; ++n) {
			for (int m = 0; m < 3; ++m) {
				triplets.emplace_back(indexSet(n), indexSet(m), massMatrix(n,m));
			}
		}
	}

	M.setFromTriplets(triplets.begin(), triplets.end());

	return M;
}
//----------------AssembleMatrixEnd----------------
