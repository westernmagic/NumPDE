#include "writer.hpp"
#include <Eigen/Core>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
//! Vector type
typedef Eigen::VectorXd Vector;

/// Uses forward Euler and upwind finite differences to compute u from time 0 to time T
/// Propagation of information is assumed to be from left to right
///
/// @param[out] u solution at all time steps up to time T, each column corresponding to a time step (including the initial condition as first column)
/// @param[out] time the time levels
/// @param[in] u0 the initial conditions, as column vector
/// @param[in] dt the time step size
/// @param[in] T the final time at which to compute the solution (which we assume to be a multiple of dt)
/// @param[in] N the number of grid points, INCLUDING BOUNDARY POINTS
/// @param[in] a the advection velocity
///
void SimpleUpwindFD(Eigen::MatrixXd &u, Vector &time, const Vector u0, double dt, double T, int N, const std::function<double(double)> &a) {
	const unsigned int nsteps = round(T / dt);
	const double       dx     = 1. / (N - 1);
	u.resize(N, nsteps + 1);
	time.resize(nsteps + 1);

	// (write your solution here)
	u.col(0) = u0;
	time(0)  = 0;
	for (unsigned int t = 0; t < nsteps - 1; ++t) {
		time(t + 1) = (t + 1) * dt;
		for (int x = 1; x < N - 2; ++x) {
			u(x, t + 1) = u(x, t) - dt * (std::max(a(x / dx), 0.0) * (u(x, t) - u(x - 1, t)) / dx - std::min(a(x / dx), 0.0) * (u(x + 1, t) - u(x, t)) / dx);
		}
		u(0, t + 1)     = u(N - 2, t + 1);
		u(N - 1, t + 1) = u(1, t + 1);
	}
}

/// Uses forward Euler and upwind finite differences to compute u from time 0 to time T
///
/// @param[out] u solution at all time steps up to time T, each column corresponding to a time step (including the initial condition as first column)
/// @param[out] time the time levels
/// @param[in] u0 the initial conditions, as column vector
/// @param[in] dt the time step size
/// @param[in] T the final time at which to compute the solution (which we assume to be a multiple of dt)
/// @param[in] N the number of grid points, INCLUDING BOUNDARY POINTS
/// @param[in] a the advection velocity
///

void UpwindFD(Eigen::MatrixXd &u, Vector &time, const Vector u0, double dt, double T, int N, const std::function<double(double)> &a) {
	//const unsigned int nsteps = round(T / dt);
	//const double       dx     = 1. / (N - 1);
	//u.resize(N, nsteps + 1);
	//time.resize(nsteps + 1);

	// (write your solution here)
	SimpleUpwindFD(u, time, u0, dt, T, N, a);
}

///
/// Uses forward Euler and centered finite differences to compute u from time 0 to time T
///
/// @param[out] u solution at all time steps up to time T, each column corresponding to a time step (including the initial condition as first column)
/// @param[out] time the time levels
/// @param[in] u0 the initial conditions, as column vector
/// @param[in] dt the time step size
/// @param[in] T the final time at which to compute the solution (which we assume to be a multiple of dt)
/// @param[in] N the number of grid points, INCLUDING BOUNDARY POINTS
/// @param[in] a the advection velocity
///

void CenteredFD(Eigen::MatrixXd &u, Vector &time, const Vector u0, double dt, double T, int N, const std::function<double(double)> &a) {
	const unsigned int nsteps = round(T / dt);
	const double       dx     = 1. / (N - 1);
	u.resize(N, nsteps + 1);
	time.resize(nsteps + 1);

	/* Initialize u */
	u.col(0) << u0;
	time[0] = 0;
	// (write your solution here)
	for (unsigned int t = 0; t < nsteps; ++t) {
		for (int x = 1; x < N - 1; ++x) {
			u(x, t + 1) = u(x, t) / dt - a(x / dx) * (u(x + 1, t) - u(x - 1, t)) / (2 * dx);
		}
		u(0, t + 1)     = u(N - 2, t + 1);
		u(N - 1, t + 1) = u(1, t + 1);
	}
}

/* Initial condition: rectangle */
double U0(double x) {
	if (x < 0.25 || x > 0.75)
		return 0;
	else
		return 2.;
}

int main(int, char **) {
	double T  = 2.;
	double dt = 0.002; // Change this for timestep comparison
	int    N  = 101;

	auto a = [](double x) {
		return std::sin(2 * M_PI * x);
	};

	Vector u0(N);
	double h = 1. / (N - 1);
	/* Initialize u0 */
	for (int i = 0; i < u0.size(); i++)
		u0[i]    = U0(h * (double) i);

	Eigen::MatrixXd u_simpleupwind;
	Vector          time_simpleupwind;
	SimpleUpwindFD(u_simpleupwind, time_simpleupwind, u0, dt, T, N, a);
	writeToFile("time_simpleupwind.txt", time_simpleupwind);
	writeMatrixToFile("u_simpleupwind.txt", u_simpleupwind);

	Eigen::MatrixXd u_upwind;
	Vector          time_upwind;
	UpwindFD(u_upwind, time_upwind, u0, dt, T, N, a);
	writeToFile("time_upwind.txt", time_upwind);
	writeMatrixToFile("u_upwind.txt", u_upwind);

	Eigen::MatrixXd u_centered;
	Vector          time_centered;
	CenteredFD(u_centered, time_centered, u0, dt, T, N, a);
	writeToFile("time_centered.txt", time_centered);
	writeMatrixToFile("u_centered.txt", u_centered);
}
