#pragma once

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>
//! Sparse Matrix type. Makes using this type easier.
typedef Eigen::SparseMatrix<double> SparseMatrix;

//! Used for filling the sparse matrix.
typedef Eigen::Triplet<double> Triplet;
#include "boundary.hpp"
#include "mass_matrix_assembly.hpp"
#include "neumann_boundary_assemble.hpp"
#include "stiffness_matrix_assembly.hpp"

//! Evolves the solution in time using the DIRK2 method.
//!
//! @param vertices the list of vertices that build the triangular mesh
//! @param triangles the list of indices that represent the triangular mesh
//! @param u0 the initial data
//! @param gamma the parameter gamma (has to do with the boundary conditions)
//! @param m number of timesteps to perform
//! @returns a pair which contains as first parameter the solution at time = 1,
//!          and second parameter the energy evolving over time.
std::pair<Eigen::VectorXd, std::vector<double>> radiativeTimeEvolutionImplicit(const Eigen::MatrixXd &vertices,
                                                                               const Eigen::MatrixXi &triangles,
                                                                               const Eigen::VectorXd &u0,
                                                                               const double           gamma,
                                                                               const int              m) {
	std::vector<double> energy;
	Eigen::VectorXd     u(u0.size());
	u = u0;

	double dt     = 1.0 / m;
	double lambda = 1 - 0.5 * std::sqrt(2);

	// Get the edges, this is used to compute the neumann boundary matrix
	Eigen::MatrixXi edges = getBoundaryEdges(vertices, triangles);

	// Define the needed matrices. Note that these are constant in time,
	// so they can be defined before the time loop. Also set up the solver
	// (write your solution here)

	SparseMatrix M = assembleMassMatrix(vertices, triangles);
	SparseMatrix A = assembleStiffnessMatrix(vertices, triangles);
	SparseMatrix B = assembleBoundaryMatrix(vertices, edges, gamma);
	A += B;

	Eigen::SimplicialLDLT<SparseMatrix> Solver;
	Solver.compute(M + dt * lambda * A);

	if (Solver.info() != Eigen::Success) {
		throw std::runtime_error("Could not decompose matix for SDIRK");
	}

	auto solveY1 = [&](const Eigen::VectorXd &mu) -> Eigen::VectorXd {
		return Solver.solve(M * mu);
	};

	auto solveY2 = [&](const Eigen::VectorXd &mu, const Eigen::VectorXd &Y1) -> Eigen::VectorXd {
		return Solver.solve(M * mu - dt * (1-lambda) * A * Y1);
	};

	Eigen::SimplicialLDLT<SparseMatrix> SolverM;
	SolverM.compute(M);

	if (SolverM.info() != Eigen::Success) {
		throw std::runtime_error("Could not decompose matrix M");
	}

	Eigen::VectorXd Y1(u0.rows());
	Eigen::VectorXd Y2(u0.rows());
	for (int timestep = 0; timestep < m; ++timestep) {
		// Do one step forward in time
		// (write your solution here)
		Y1 = solveY1(u);
		Y2 = solveY2(u, Y1);
		u = SolverM.solve(M * u - dt * A * ( (1 - lambda) * Y1 + lambda * Y2)).eval();
		// Compute the energy for this level
		energy.push_back(u.sum() / u.rows());
	}

	return std::make_pair(u, energy);
}
