#pragma once
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <vector>

#include "stiffness_matrix.hpp"

//----------------AssembleMatrixBegin----------------
//! Assemble the stiffness matrix
//! for the linear system.
//!
//!
//! @param[in] vertices a list of triangle vertices
//! @param[in] triangles a list of triangles
SparseMatrix assembleStiffnessMatrix(
    const Eigen::MatrixXd &vertices,
    const Eigen::MatrixXi &triangles) {
	SparseMatrix         A(vertices.rows(), vertices.rows());
	std::vector<Triplet> triplets;
	const int            numberOfElements = triangles.rows();

	for (int i = 0; i < numberOfElements; ++i) {
		auto &indexSet = triangles.row(i);

		const auto &a = vertices.row(indexSet(0));
		const auto &b = vertices.row(indexSet(1));
		const auto &c = vertices.row(indexSet(2));

		Eigen::Matrix3d stiffnessMatrix;
		computeStiffnessMatrix(stiffnessMatrix, a, b, c);

		for (int n = 0; n < 3; ++n) {
			for (int m = 0; m < 3; ++m) {
				auto triplet = Triplet(indexSet(n), indexSet(m), stiffnessMatrix(n, m));
				triplets.push_back(triplet);
			}
		}
	}

	A.setFromTriplets(triplets.begin(), triplets.end());

	return A;
}
//----------------AssembleMatrixEnd----------------
