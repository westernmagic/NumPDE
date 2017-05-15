#pragma once
#include "neumann_boundary.hpp"
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <vector>
//----------------AssembleNeumannBegin----------------
//! Adds the contribution of the boundary to the stiffness matrix.
//!
//! @note This should only be called for the *boundary* edges
//!
//! @param[in] edges a list of boundary edges
//! @param[in] vertices a list of vertices
//! @param[in] gamma the boundary parameter gamma
SparseMatrix assembleBoundaryMatrix(
    const Eigen::MatrixXd &vertices,
    const Eigen::MatrixXi &edges,
    double                 gamma) {
	SparseMatrix         B(vertices.rows(), vertices.rows());
	std::vector<Triplet> triplets;
	const int            numberOfElements = edges.rows();

	// (write your solution here)
	for (int i = 0; i < numberOfElements; ++i) {
		auto indexSet = edges.row(i);

		const auto &a = vertices.row(indexSet(0));
		const auto &b = vertices.row(indexSet(1));

		Eigen::Matrix2d boundaryMatrix;
		computeBoundaryMatrix(boundaryMatrix, a, b, gamma);

		for (int n = 0; n < 2; ++n) {
			for (int m = 0; m < 2; ++m) {
				triplets.emplace_back(indexSet(n), indexSet(m), boundaryMatrix(n, m));
			}
		}
	}

	B.setFromTriplets(triplets.begin(), triplets.end());
	return B;
}
//----------------AssembleMatrixEnd----------------
