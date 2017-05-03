#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>
//! Sparse Matrix type. Makes using this type easier.
typedef Eigen::SparseMatrix<double> SparseMatrix;

//! Used for filling the sparse matrix.
typedef Eigen::Triplet<double> Triplet;
#include "igl/edge_lengths.h"
#include "igl/readMESH.h"
#include "stiffness_matrix.hpp"
#include "time_evolution_explicit.hpp"
#include "time_evolution_implicit.hpp"
#include "writer.hpp"
#include <sstream>

int main(int, char **) {
	try {
		Eigen::MatrixXd vertices;
		Eigen::MatrixXi triangles;
		Eigen::MatrixXi tetrahedra;

		igl::readMESH(NPDE_DATA_PATH "square_3.mesh", vertices, tetrahedra, triangles);
		writeMatrixToFile("vertices.txt", vertices);
		writeMatrixToFile("triangles.txt", triangles);

		Eigen::MatrixXd edgeLengths;
		igl::edge_lengths(vertices, triangles, edgeLengths);
		double dx = edgeLengths.minCoeff();

		double gamma = 1;

		// We want dt to scale roughly as dx to make sure
		// the error of the time discretization scales in the same
		// manner as the spatial discretization.
		int m = std::ceil(1 / dx);

		Eigen::VectorXd u0(vertices.rows());
		u0.setOnes();
		auto uImplicit = radiativeTimeEvolutionImplicit(vertices, triangles, u0, gamma, m);

		writeToFile("energy_implicit.txt", uImplicit.second);
		writeToFile("u_implicit.txt", uImplicit.first);

		auto uExplicitNoCfl = radiativeTimeEvolutionExplicit(vertices, triangles, u0, gamma, m);

		writeToFile("energy_explicit_no_cfl.txt", uExplicitNoCfl.second);
		writeToFile("u_explicit_no_cfl.txt", uExplicitNoCfl.first);

		auto uExplicitCfl = radiativeTimeEvolutionExplicit(vertices, triangles, u0, gamma, std::ceil(std::pow(4.0 / dx, 2)));

		writeToFile("energy_explicit_cfl.txt", uExplicitCfl.second);
		writeToFile("u_explicit_cfl.txt", uExplicitCfl.first);

	} catch (std::runtime_error &e) {
		std::cerr << "An error occurred. Error message: " << std::endl;
		std::cerr << "    \"" << e.what() << "\"" << std::endl;
		return EXIT_FAILURE;
	} catch (...) {
		std::cerr << "An unknown error occurred." << std::endl;
		throw;
	}

	return EXIT_SUCCESS;
}
