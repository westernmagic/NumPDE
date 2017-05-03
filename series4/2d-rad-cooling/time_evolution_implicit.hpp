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

	Eigen::VectorXd k1(u0.rows());
	Eigen::VectorXd k2(u0.rows());
	for (int timestep = 0; timestep < m; ++timestep) {
		// Do one step forward in time
		// (write your solution here)

		// Compute the energy for this level
		energy.push_back(u.sum() / u.rows());
	}

	return std::make_pair(u, energy);
}
