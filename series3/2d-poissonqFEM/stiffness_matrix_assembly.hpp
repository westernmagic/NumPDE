#pragma once
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <vector>

#include "stiffness_matrix.hpp"

//! Sparse Matrix type. Makes using this type easier.
typedef Eigen::SparseMatrix<double> SparseMatrix;

//! Used for filling the sparse matrix.
typedef Eigen::Triplet<double> Triplet;

//----------------AssembleMatrixBegin----------------
//! Assemble the stiffness matrix
//! for the linear system
//!
//! @param[out] A will at the end contain the Galerkin matrix
//! @param[in] vertices a list of triangle vertices
//! @param[in] dofs a list of the dofs' indices in each triangle
template <class Matrix>
void assembleStiffnessMatrix(Matrix &A, const Eigen::MatrixXd &vertices, const Eigen::MatrixXi &dofs, const int &N) {
	const int numberOfElements = dofs.rows();
	A.resize(N, N);

	std::vector<Triplet> triplets;

	triplets.reserve(numberOfElements * 6 * 10);
	// (write your solution here)
	A.setFromTriplets(triplets.begin(), triplets.end());
}
//----------------AssembleMatrixEnd----------------
