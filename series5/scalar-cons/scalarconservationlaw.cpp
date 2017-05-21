#include "writer.hpp"
#include <Eigen/Core>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <tuple>

//----------------GodunovBegin----------------
/// @param[in] N the number of grid points, NOT INCLUDING BOUNDARY POINTS
/// @param[in] T the final time at which to compute the solution
/// @param[in] f flux function, as function
/// @param[in] df derivative of flux function, as function
/// @param[in] u0 the initial conditions, as function
/// @param[out] u solution at time T
/// @param[out] X Grid Points
void Godunov(int N, double T, const std::function<double(double)> &f, const std::function<double(double)> &df, const std::function<double(double)> &u0, Eigen::VectorXd &u, Eigen::VectorXd &X) {
	// Create space discretization for interval [-2,2]
	// (write your solution here)
	double dx = 4.0 / (N + 1);
	u.resize(N + 2);
	X.setLinSpaced(N + 2, -2, 2);

	// The Godunov flux
	// (write your solution here)
	// $F_{j + \frac{1}{2}}^n = \max(f(max(U_j^n, \omega)), f(min(U_{j + 1}^n, \omega)))$
	// where $\omega$ minimum of $f$
	auto F = [&f](double a, double b) -> double {
		using std::max;
		using std::min;
		// TODO: find minimum of f
		double omega{0};
		return max(f(max(a, omega)), f(min(b, omega)));
	};

	//setup vectors to store (old) solution
	// (write your solution here)
	u = X.unaryExpr(u0);
	Eigen::VectorXd u_old{u};

	// choose dt such that if obeys CFL condition
	// (write your solution here)
	double t = 0;

	//Please uncomment the next line:
	while (t <= T) {
		// Update dT according to current CFL condition
		// (write your solution here)
		// $\increment t = \frac{\increment x}{2 \max_j \abs{f'(U_j^n)}$
		double dt = dx / (2 * u.unaryExpr([&df](double x) -> double {
			                       return std::abs(df(x));
			                     }).maxCoeff());

		// Update current time
		// (write your solution here)
		t += dt;

		// Update the internal values of u
		// (write your solution here)
		// $U_j^{n + 1} = U_j^n - \frac{\increment t}{\increment x} \left( F_{j + \frac{1}{2}}^n - F_{j - \frac{1}{2}}^n \right)$
		std::swap(u, u_old);
		for (int i = 1; i < N + 1; ++i) {
			u(i) = u_old(i) - dt / dx * (F(u_old(i), u_old(i + 1)) - F(u_old(i - 1), u_old(i)));
		}

		// Update boundary with non-reflecting Neumann bc
		// (write your solution here)
		u(0)     = u(1);
		u(N + 1) = u(N);

		//Please uncomment the next line:
	}
}
//----------------GodunovEnd----------------

//----------------convGodBegin----------------
//! Computes error for a range of cell lengths and stores them to error vectors
/// @param[in] T the final time at which to compute the solution
/// @param[in] f flux function, as function
/// @param[in] df derivative of flux function, as function
/// @param[in] u0 the initial conditions, as function
/// @param[in] uex exact solution
/// @param[in] baseName string containing name to save the computed errors and resolution
void GodunovConvergence(double T, const std::function<double(double)> &f, const std::function<double(double)> &df, const std::function<double(double)> &u0, const std::function<double(double, double)> &uex, const std::string &baseName) {
	std::vector<int>    resolutions = {100, 200, 400, 800, 1600};
	std::vector<double> L1_errors;
	std::vector<double> Linf_errors;

	for (auto &N : resolutions) {
		// find approximate solution using Godunov scheme
		// (write your solution here)
		Eigen::VectorXd u;
		Eigen::VectorXd X;
		Godunov(N, T, f, df, u0, u, X);

		// compute errors and push them bach to the corresponfing error vectors
		// (write your solution here)
		Eigen::VectorXd errors = (u - X.unaryExpr([&uex, &T](double x) -> double {
			                         return uex(x, T);
			                       })).cwiseAbs();
		L1_errors.emplace_back(errors.sum());
		Linf_errors.emplace_back(errors.maxCoeff());
	}

	writeToFile(baseName + "_L1errors_Godunov.txt", L1_errors);
	writeToFile(baseName + "_Linferrors_Godunov.txt", Linf_errors);
	writeToFile(baseName + "_resolutions.txt", resolutions);
}
//----------------convGodEnd----------------

//----------------LFBegin----------------
/// @param[in] N the number of grid points, NOT INCLUDING BOUNDARY POINTS
/// @param[in] T the final time at which to compute the solution
/// @param[in] f flux function, as function
/// @param[in] df derivative of flux function, as function
/// @param[in] u0 the initial conditions, as function
/// @param[out] u solution at time T
/// @param[out] X Grid Points
void LaxFriedrichs(int N, double T, const std::function<double(double)> &f, const std::function<double(double)> &df, const std::function<double(double)> &u0, Eigen::VectorXd &u, Eigen::VectorXd &X) {
	std::ignore = df;
	// Create space discretization for interval [-2,2]
	// (write your solution here)
	double CFL = 0.5;
	double dx  = 4.0 / (N + 1);

	//setup vectors to store solution
	// (write your solution here)
	X.setLinSpaced(N + 2, -2, 2);
	u = X.unaryExpr(u0);
	Eigen::VectorXd u_old{u};

	// choose dt such that if obeys CFL condition
	// (write your solution here)
	double t  = 0;
	double dt = CFL * dx;

	// The Lax-Friedrichs flux
	// (write your solution here)
	auto F = [&](double a, double b) -> double {
		return (f(a) + f(b)) / 2 - dx / (2 * dt) * (b - a);
	};

	//Please uncomment the next line:
	while (t <= T) {
		// Update dT according to current CFL condition
		// (write your solution here)

		// Update current time
		// (write your solution here)
		t += dt;

		// Update the internal values of u
		// (write your solution here)
		std::swap(u, u_old);
		for (int i = 1; i < N + 1; ++i) {
			u(i) = u_old(i) - dt / dx * (F(u_old(i), u_old(i + 1)) - F(u_old(i - 1), u_old(i)));
		}

		// Update boundary with non-reflecting Neumann bc
		// (write your solution here)
		u(0)     = u(1);
		u(N + 1) = u(N);

		//Please uncomment the next line:
	}
}
//----------------LFEnd----------------

//----------------convLFBegin----------------
//! Computes error for a range of cell lengths and stores them to error vectors
/// @param[in] T the final time at which to compute the solution
/// @param[in] f flux function, as function
/// @param[in] df derivative of flux function, as function
/// @param[in] u0 the initial conditions, as function
/// @param[in] uex exact solution
/// @param[in] baseName string containing name to save the computed errors and resolution
void LFConvergence(double T, const std::function<double(double)> &f, const std::function<double(double)> &df, const std::function<double(double)> &u0, const std::function<double(double, double)> &uex, const std::string &baseName) {
	std::vector<int>    resolutions = {100, 200, 400, 800, 1600};
	std::vector<double> L1_errors;
	std::vector<double> Linf_errors;

	for (auto &N : resolutions) {
		// find approximate solution using Lax-Friedrichs scheme
		// (write your solution here)
		Eigen::VectorXd u;
		Eigen::VectorXd X;
		LaxFriedrichs(N, T, f, df, u0, u, X);

		// compute errors and push them bach to the corresponfing error vectors
		// (write your solution here)
		Eigen::VectorXd errors = (u - X.unaryExpr([&](double x) -> double {
			return uex(x, T);
		})).cwiseAbs();
		L1_errors.emplace_back(errors.sum());
		Linf_errors.emplace_back(errors.maxCoeff());
	}

	writeToFile(baseName + "_L1errors_LF.txt", L1_errors);
	writeToFile(baseName + "_Linferrors_LF.txt", Linf_errors);
	writeToFile(baseName + "_resolutions.txt", resolutions);
}
//----------------convLFEnd----------------

/* Fluxes for Burgers' equation */
double fBurgers(double u) {
	return std::pow(u, 2) / 2.;
}

double dfBurgers(double u) {
	return u;
}

/* Initial data and exact solutions for Burgers' equation  */
// i)
double U0i(double x) {
	if (x < 0.)
		return 1.;
	else
		return 0.;
}
double Uexi(double x, double t) {
	if (x < 0.5 * t)
		return 1.;
	else
		return 0.;
}

// ii)
double U0ii(double x) {
	if (x < 0.)
		return 0.;
	else
		return -2.;
}
double Uexii(double x, double t) {
	if (x < -t)
		return 0.;
	else
		return -2.;
}

// iii)
double U0iii(double x) {
	if (x < 0.)
		return 0.;
	else
		return 1.;
}
double Uexiii(double x, double t) {
	if (x < 0)
		return 0.;
	else if (x < t && t < 2)
		return x / t;
	else
		return 1.;
}

// iv)
double U0iv(double x) {
	if (0. < x && x < 1.)
		return 1.;
	else
		return 0.;
}
double Uexiv(double x, double t) {
	if (x <= 0)
		return 0.;
	else if ((x <= t && t <= 2) || (x < std::sqrt(2 * t) && t > 2))
		return x / t;
	else if (t <= 2 && t < x && (x < 1 + t / 2.))
		return 1.;
	else
		return 0.;
}

/* Flux for Buckley-Leverett equation*/
double fBL(double u) {
	return std::pow(u, 2) / (std::pow(u, 2) + std::pow(1 - u, 2));
}

double dfBL(double u) {
	return (2 * u * (u * u + (1 - u) * (1 - u)) - u * u * (2 * u - 2 * (1 - u))) / std::pow(u * u + (1 - u) * (1 - u), 2);
}

/* Initial data for Buckley-Leverett */
double U0BL(double x) {
	if (x < 0.)
		return 0.1;
	else
		return 0.9;
}

int main(int, char **) {
	double T = 0.8;
	int    N = 100;

	Eigen::VectorXd u, X;
	// Test for Burgers with initiald data i
	Godunov(N, T, fBurgers, dfBurgers, U0i, u, X);
	writeToFile("uBi_G.txt", u);
	LaxFriedrichs(N, T, fBurgers, dfBurgers, U0i, u, X);
	writeToFile("uBi_LF.txt", u);

	Godunov(N, T, fBurgers, dfBurgers, U0ii, u, X);
	writeToFile("uBii_G.txt", u);
	LaxFriedrichs(N, T, fBurgers, dfBurgers, U0ii, u, X);
	writeToFile("uBii_LF.txt", u);

	Godunov(N, T, fBurgers, dfBurgers, U0iii, u, X);
	writeToFile("uBiii_G.txt", u);
	LaxFriedrichs(N, T, fBurgers, dfBurgers, U0iii, u, X);
	writeToFile("uBiii_LF.txt", u);

	Godunov(N, T, fBurgers, dfBurgers, U0iv, u, X);
	writeToFile("uBiv_G.txt", u);
	LaxFriedrichs(N, T, fBurgers, dfBurgers, U0iv, u, X);
	writeToFile("uBiv_LF.txt", u);

	// compute convergence for Burgers with initial data i
	GodunovConvergence(T, fBurgers, dfBurgers, U0i, Uexi, "Burgers1");
	LFConvergence(T, fBurgers, dfBurgers, U0i, Uexi, "Burgers1");

	// compute convergence for Burgers with initial data ii
	GodunovConvergence(T, fBurgers, dfBurgers, U0ii, Uexii, "Burgers2");
	LFConvergence(T, fBurgers, dfBurgers, U0ii, Uexii, "Burgers2");

	// compute convergence for Burgers with initial data iii
	GodunovConvergence(T, fBurgers, dfBurgers, U0iii, Uexiii, "Burgers3");
	LFConvergence(T, fBurgers, dfBurgers, U0iii, Uexiii, "Burgers3");

	// compute convergence for Burgers with initial data iv
	GodunovConvergence(T, fBurgers, dfBurgers, U0iv, Uexiv, "Burgers4");
	LFConvergence(T, fBurgers, dfBurgers, U0iv, Uexiv, "Burgers4");

	// Test for Buckley-Leverett
	Godunov(N, T, fBL, dfBL, U0BL, u, X);
	writeToFile("uBL_G.txt", u);
	LaxFriedrichs(N, T, fBL, dfBL, U0BL, u, X);
	writeToFile("uBL_LF.txt", u);
}
