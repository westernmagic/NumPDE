#include "writer.hpp"
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>

//! Sparse Matrix type. Makes using this type easier.
typedef Eigen::SparseMatrix<double> SparseMatrix;

//! Used for filling the sparse matrix.
typedef Eigen::Triplet<double> Triplet;

//! Vector type
typedef Eigen::VectorXd Vector;

//! Create the 1D Poisson matrix
//! @param[out] A will contain the Poisson matrix
//! @param[in] N the number of interior points
void createPoissonMatrix(SparseMatrix &A, int N) {
	// (write your solution here)
}

/// Uses the explicit Euler method to compute u from time 0 to time T
///
/// @param[out] u at all time steps up to time T, each column corresponding to a time step (including the initial condition as first column)
/// @param[out] time the time levels
/// @param[in] u0 the initial data, as column vector
/// @param[in] dt the time step size
/// @param[in] T the final time at which to compute the solution (which we assume to be a multiple of dt)
/// @param[in] N the number of interior grid points
/// @param[in] gL function of time with the Dirichlet condition at left boundary
/// @param[in] gR function of time with the Dirichlet condition at right boundary
///

void explicitEuler(Eigen::MatrixXd &u, Vector &time, const Vector u0, double dt, double T, int N, const std::function<double(double)> &gL, const std::function<double(double)> &gR) {
	const unsigned int nsteps = round(T / dt);
	const double       h      = 1. / (N + 1);
	u.resize(N, nsteps + 1);
	time.resize(nsteps + 1);

	// (write your solution here)
}

/// Uses the Crank-Nicolson method to compute u from time 0 to time T
///
/// @param[out] u at all time steps up to time T, each column corresponding to a time step (including the initial condition as first column)
/// @param[out] time the time levels
/// @param[in] u0 the initial data, as column vector
/// @param[in] dt the time step size
/// @param[in] T the final time at which to compute the solution (which we assume to be a multiple of dt)
/// @param[in] N the number of interior grid points
/// @param[in] gL function of time with the Dirichlet condition at left boundary
/// @param[in] gR function of time with the Dirichlet condition at right boundary
///

void CrankNicolson(Eigen::MatrixXd &u, Vector &time, const Vector u0, double dt, double T, int N, const std::function<double(double)> &gL, const std::function<double(double)> &gR) {
	// (write your solution here)
}

double U0(double x) {
	return 1 + std::min(2 * x, 2 - 2 * x);
}

int main(int, char **) {
	double T  = 0.3;
	double dt = 0.0002; // Change this for explicit / implicit time stepping comparison
	int    N  = 40;
	Vector u0(N);
	double h = 1. / (N + 1);
	/* Initialize u0 */
	for (int i = 0; i < u0.size(); i++)
		u0[i]    = U0(h * (i + 1));
	auto gR    = [](double t) { return std::exp(-10 * t); };
	auto gL    = [](double t) { return std::exp(-10 * t); };
	Eigen::MatrixXd     u_euler;
	Vector              time;
	explicitEuler(u_euler, time, u0, dt, T, N, gL, gR);
	writeToFile("time.txt", time);
	writeMatrixToFile("u_explEuler.txt", u_euler);
	Eigen::MatrixXd u_cn;
	CrankNicolson(u_cn, time, u0, dt, T, N, gL, gR);
	writeMatrixToFile("u_cn.txt", u_cn);
}
