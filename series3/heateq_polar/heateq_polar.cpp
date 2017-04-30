#include "writer.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <tuple>
#include <utility>

//----------------stepBegin----------------
//! Does one Forward-Euler timestep of the heat equation
//!
//! @param[out] u at the end, u will contain the values at time t^{n+1}
//! @param[in] uPrevous should contain the values at time t^n
//! @param[in] dr the cell length in r direction
//! @param[in] dt the timestep size
void stepHeatEquation(Eigen::VectorXd &      u,
                      const Eigen::VectorXd &uPrevious,
                      const double           dr,
                      const double           dt) {
	// (write your solution here)
	#pragma omp parallel for if(u.size() > 10000)
	for (int i = 1; i < u.size() - 1; ++i) {
		u(i) = uPrevious(i) + dt / (dr * dr) * ((i + 0.5) * dr * uPrevious(i + 1) - 2 * i * dr * uPrevious(i) + (i - 0.5) * dr * uPrevious(i - 1)) / (i * dr);
	}
	u(0)            = u(1);
	u(u.size() - 1) = 0;
}
//----------------stepEnd----------------

//----------------solveBegin----------------
//! Gives an approximation to the heat equation with the given initial data
//!
//! @param initialData represents the function \tilde{u}_0.
//!
//! @param shouldStop is a function taking as first
//!        parameter the current value of u, and
//!        as second value the current time t.
//!        The simulation should run until shouldStop(u,t) == true. That is
//!
//!        \code{.cpp}
//!        while(!shouldStop(u,t)) { /* Do one more timestep */ }
//!        \endcode
//!
//! @param N the number of inner points
//! @param cfl the constant C with which we choose the timestep size. We set
//!        \code{.cpp}
//!        dt = cfl*dr*dr
//!        \endcode
Eigen::VectorXd solveHeatEquation(const std::function<double(double)> &initialData,
                                  const std::function<bool(const Eigen::VectorXd &, double)> &shouldStop,
                                  const int N,
                                  double    cfl = 0.5) {
	Eigen::VectorXd u1(N + 2), u2(N + 2);
	u1.setZero();

	Eigen::VectorXd &u         = u1;
	Eigen::VectorXd &uPrevious = u2;

	// Set the initial value
	// (write your solution here)

	double t = 0;

	double dr = 1.0 / (N + 1);
	double dt = cfl * dr * dr;

	for (int i = 0; i < u.size() - 1; ++i) {
		u(i) = initialData(i * dr);
	}

	while (!shouldStop(u, t)) {
		// make one step forward.
		// Make sure you swap u and uPrevious
		// accordingly!
		// And update the current time
		// (write your solution here)
		std::swap(u, uPrevious);
		t += dt;
		stepHeatEquation(u, uPrevious, dr, dt);
	}
	// Return the final solution
	return u;
}
//----------------solveEnd----------------

bool stopAtTimeOne(const Eigen::VectorXd &u, double t) {
	std::ignore = u;
	return t > 1;
}

//----------------convergenceBegin----------------
void convergenceStudy() {
	const size_t NReference = (1 << 10) - 2;
	auto initialData        = [](double r) {
		return 1 - r * r * cos(r);
	};

	auto stopAtTime0025 = [](const Eigen::VectorXd &, double t) {
		return t > 0.025;
	};

	std::cout << "Computing reference solution" << std::endl;
	auto uReference = solveHeatEquation(initialData, stopAtTime0025, NReference, 0.5);
	std::cout << "Done computing reference solution" << std::endl;
	std::vector<size_t> resolutions;
	std::vector<double> errors;

	//// NPDE_TEMPLATE_START
	for (int k = 3; k < 10; ++k) {
		const size_t N = (1 << k) - 2;
		auto         u = solveHeatEquation(initialData, stopAtTime0025, N, 0.5);

		double maxError = 0;

		size_t ratioReference = (NReference + 2) / (N + 2);
		for (int i = 0; i < u.rows(); ++i) {
			maxError = std::max(maxError, std::abs(u[i] - uReference[i * ratioReference]));
		}

		resolutions.push_back(N);
		errors.push_back(maxError);
	}
	//// NPDE_TEMPLATE_END
	writeToFile("resolutions.txt", resolutions);
	writeToFile("errors.txt", errors);
}
//----------------convergenceEnd----------------

int main(int, char **) {
	auto initialData = [](double) {
		return 20;
	};

	auto u05 = solveHeatEquation(initialData, stopAtTimeOne, 20, 0.5);
	writeToFile("u_05.txt", u05);

	auto u051 = solveHeatEquation(initialData, stopAtTimeOne, 20, 0.51);
	writeToFile("u_051.txt", u051);

	//----------------maxstopBegin----------------
	// (write your solution here)
	auto stopMax4 = [](const Eigen::VectorXd &u, double t) -> bool {
		if (u.maxCoeff() <= 4.0) {
			std::cout << "Max 4 reached after time t = " << t << std::endl;
			return true;
		}

		return false;
	};

	solveHeatEquation(initialData, stopMax4, 500, 0.5);
	//----------------maxstopEnd----------------

	convergenceStudy();
	return 0;
}
