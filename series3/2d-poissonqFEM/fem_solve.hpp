#pragma once
#include "dirichlet_boundary.hpp"
#include "dofs.hpp"
#include "load_vector_assembly.hpp"
#include "stiffness_matrix_assembly.hpp"
#include <Eigen/Core>
#include <igl/slice.h>
#include <igl/slice_into.h>
#include <string>

typedef Eigen::VectorXd Vector;

//----------------solveBegin----------------
//! Solve the FEM system.
//!
//! @param[out] u will at the end contain the FEM solution.
//! @param[in] quadraticDofs containing mesh data
//! @param[in] f the RHS f (as in the exercise)
//! return number of degrees of freedom (without the boundary dofs)
int solveFiniteElement(Vector &     u,
                       const QDofs &quadraticDofs,
                       const std::function<double(double, double)> &f) {
	// get quadratic dofs
	Eigen::MatrixXi qdof;
	int             N = quadraticDofs.get_dofs(qdof);

	// get mesh vertices
	const Eigen::MatrixXd &vertices = quadraticDofs.get_vertices();

	SparseMatrix A;
	// (write your solution here)
	assembleStiffnessMatrix(A, vertices, qdof, N);

	Vector F;
	// (write your solution here)
	assembleLoadVector(F, vertices, qdof, N, f);

	u.resize(N);
	u.setZero();
	Eigen::VectorXi interiorDofs;

	auto zerobc = [](double x, double y) { return 0; };
	// set homogeneous Dirichlet Boundary conditions
	setDirichletBoundary(u, interiorDofs, quadraticDofs, zerobc);
	F -= A * u;

	SparseMatrix AInterior;
	igl::slice(A, interiorDofs, interiorDofs, AInterior);
	Eigen::SimplicialLDLT<SparseMatrix> solver;

	Vector FInterior;
	igl::slice(F, interiorDofs, FInterior);

	//initialize solver for AInterior
	// (write your solution here)
	solver.compute(AInterior);

	if (solver.info() != Eigen::Success) {
		throw std::runtime_error("Could not decompose the matrix");
	}

	//solve interior system
	// (write your solution here)
	Vector uInterior = solver.solve(FInterior);
	igl::slice_into(uInterior, interiorDofs, u);

	return interiorDofs.size();
}
//----------------solveEnd----------------
