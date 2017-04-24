#pragma once
#include <Eigen/Core>
#include "load_vector.hpp"

//----------------AssembleVectorBegin----------------
//! Assemble the load vector into the full right hand side
//! for the linear system
//!
//! @param[out] F will at the end contain the RHS values for each vertex.
//! @param[in] vertices a list of triangle vertices
//! @param[in] dofs a list of the dofs' indices in each triangle
//! @param[in] f the RHS function f.
void assembleLoadVector(Eigen::VectorXd& F,
			const Eigen::MatrixXd& vertices,
			const Eigen::MatrixXi& dofs, const int& N,
			const std::function<double(double, double)>& f)
{
     const int numberOfElements = dofs.rows();

     F.resize(N);
     F.setZero();
// (write your solution here)
}
//----------------AssembleVectorEnd----------------
