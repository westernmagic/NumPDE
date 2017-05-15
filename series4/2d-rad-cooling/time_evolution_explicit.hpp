#pragma once

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>

#include "boundary.hpp"
#include "mass_matrix_assembly.hpp"
#include "neumann_boundary_assemble.hpp"
#include "stiffness_matrix_assembly.hpp"

//! Evolves the solution in time using the explicit Forward Euler scheme
//!
//! @param vertices the list of vertices that build the triangular mesh
//! @param triangles the list of indices that represent the triangular mesh
//! @param u0 the initial data
//! @param gamma the parameter gamma (has to do with the boundary conditions)
//! @param m number of timesteps to perform
//! @returns a pair which contains as first parameter the solution at time = 1,
//!          and second parameter the energy evolving over time.
std::pair<Eigen::VectorXd, std::vector<double>> radiativeTimeEvolutionExplicit(const Eigen::MatrixXd &vertices,
                                                                               const Eigen::MatrixXi &triangles,
                                                                               const Eigen::VectorXd &u0,
                                                                               const double           gamma,
                                                                               const int              m) {
	std::vector<double> energy;
	Eigen::VectorXd     u(u0.size());
	u = u0;

	double dt = 1.0 / m;

	// Get the edges, this is used to compute the neumann boundary matrix
	Eigen::MatrixXi edges = getBoundaryEdges(vertices, triangles);

	// Define the needed matrices and solvers
	SparseMatrix M = assembleMassMatrix(vertices, triangles);
	SparseMatrix A = assembleStiffnessMatrix(vertices, triangles);
	SparseMatrix B = assembleBoundaryMatrix(vertices, edges, gamma);
	A += B;

	Eigen::SimplicialLDLT<SparseMatrix> SolverM;
	SolverM.compute(M);

	if (SolverM.info() != Eigen::Success) {
		throw std::runtime_error("Could not decompose matrix M");
	}

	// (write your solution here)
	for (int timestep = 0; timestep < m; ++timestep) {
		// Step the solution forward in time
		// (write your solution here)
		u += SolverM.solve(-1.0 * dt * A * u).eval();

		energy.push_back(u.sum() / u.rows());
	}

	return std::make_pair(u, energy);
}
