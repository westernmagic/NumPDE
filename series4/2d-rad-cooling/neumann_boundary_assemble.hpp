#pragma once
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <vector>
#include "neumann_boundary.hpp"
//----------------AssembleNeumannBegin----------------
//! Adds the contribution of the boundary to the stiffness matrix.
//! 
//! @note This should only be called for the *boundary* edges
//!
//! @param[in] edges a list of boundary edges
//! @param[in] vertices a list of vertices
//! @param[in] gamma the boundary parameter gamma
SparseMatrix assembleBoundaryMatrix(
    const Eigen::MatrixXd& vertices,
    const Eigen::MatrixXi& edges,
    double gamma)
{
    SparseMatrix B(vertices.rows(), vertices.rows());
    std::vector<Triplet> triplets;
    const int numberOfElements = edges.rows();

// (write your solution here)
    B.setFromTriplets(triplets.begin(), triplets.end());
    return B;
}
//----------------AssembleMatrixEnd----------------
