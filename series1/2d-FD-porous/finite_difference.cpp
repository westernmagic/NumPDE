#include "writer.hpp"
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <array>
#include <cmath>
#include <iostream>
#include <iostream>
#include <stdexcept>
#include <tuple>

//! Sparse Matrix type. Makes using this type easier.
typedef Eigen::SparseMatrix<double> SparseMatrix;

//! Used for filling the sparse matrix.
typedef Eigen::Triplet<double> Triplet;

//! Vector type
typedef Eigen::VectorXd Vector;

//! Our function pointer, typedef'd to make it easier to use
typedef double (*FunctionPointer)(double, double);

//----------------poissonBegin----------------
//! Create the Poisson matrix for 2D finite difference.
//! @param[out] A will be the Poisson matrix (as in the exercise)
//! @param[in] N number of elements in the x-direction
void createPorousMediaMatrix2D(SparseMatrix &A, FunctionPointer sigma, int N, double dx) {
	std::vector<Triplet> triplets;
	A.resize(N * N, N * N);
	triplets.reserve(5 * N * N - 4 * N);

	// Fill up triples

	// (write your solution here)
	A.setZero();
	std::array<double, 5> ss;
	auto s = [&ss](int i, int j) -> double {
		if (i == 0 && j == 0) {
			return ss[0];
		} else if (i == -1 && j == 0) {
			return ss[1];
		} else if (i == 1 && j == 0) {
			return ss[2];
		} else if (i == 0 && j == -1) {
			return ss[3];
		} else if (i == 0 && j == 1) {
			return ss[4];
		} else {
			throw std::runtime_error("s indices out of bounds.");
		}
	};

	for (int i = 0; i < N * N; i++) {
		int ii = i / N + 1;
		int jj = i % N + 1;
		ss     = {
		    sigma(ii * dx, jj * dx),
		    sigma((ii - 1) * dx, jj * dx),
		    sigma((ii + 1) * dx, jj * dx),
		    sigma(ii * dx, (jj - 1) * dx),
		    sigma(ii * dx, (jj + 1) * dx)};

		// u_{i,j}
		triplets.push_back(Triplet(i, i, 4 * s(0, 0)));
		if (i % N != 0) { // u_{i,j-1}
			triplets.push_back(Triplet(i, i - 1, -1 / 4.0 * (1 * s(0, -1) + 4 * s(0, 0) - s(0, 1))));
		}
		if (i % N != N - 1) { // u_{i,j+1}
			triplets.push_back(Triplet(i, i + 1, -1 / 4.0 * (-1 * s(0, -1) + 4 * s(0, 0) + s(0, 1))));
		}
		if (i >= N) { // u_{i-1,j}
			triplets.push_back(Triplet(i, i - N, -1 / 4.0 * (-1 * s(-1, 0) + 4 * s(0, 0) + s(1, 0))));
		}
		if (i < N * N - N) { // u_{i+1,j}
			triplets.push_back(Triplet(i, i + N, -1 / 4.0 * (1 * s(-1, 0) + 4 * s(0, 0) - s(1, 0))));
		}
	}

	A.setFromTriplets(triplets.begin(), triplets.end());
}
//----------------poissonEnd----------------

//----------------RHSBegin----------------
//! Create the Right hand side for the 2D finite difference
//! @param[out] rhs will at the end contain the right hand side
//! @param[in] f the right hand side function f
//! @param[in] N the number of points in the x direction
//! @param[in] dx the cell width
void createRHS(Vector &rhs, FunctionPointer f, int N, double dx) {
	rhs.resize(N * N);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			const double x = (i + 1) * dx;
			const double y = (j + 1) * dx;
			rhs[i * N + j] = dx * dx * f(x, y);
		}
	}
}
//----------------RHSEnd----------------

//----------------solveBegin----------------
//! Solve the Poisson equation in 2D
//! @param[in] f the function pointer to f
//! @param[in] N the number of points to use (in x direction)
//!
//! @returns the approximate solution u
Vector poissonSolve(FunctionPointer f, FunctionPointer sigma, int N) {
	Vector u;
	double dx = 1.0 / (N + 1);

	// Compute A, rhs and u
	// (write your solution here)
	SparseMatrix A;
	createPorousMediaMatrix2D(A, sigma, N, dx);

	Vector rhs;
	createRHS(rhs, f, N, dx);

	Eigen::SparseLU<SparseMatrix> solver;
	solver.compute(A);

	if (solver.info() != Eigen::Success) {
		throw std::runtime_error("Could not decompose the matrix.");
	}

	u.resize((N + 2) * (N + 2));
	u.setZero();

	Vector innerU = solver.solve(rhs);

	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			u[i * (N + 2) + j] = innerU[(i - 1) * N + (j - 1)];
		}
	}

	return u;
}
//----------------solveEnd----------------

//! Gives the Right hand side F at the point x, y
double F(double x, double y) {
	return 4 * M_PI * M_PI * sin(2 * M_PI * x) * sin(2 * M_PI * y) * (4 * cos(2 * M_PI * x) * cos(2 * M_PI * y) + M_PI);
}

//----------------convergenceBegin----------------
//! Gives the exact solution at the point x,y
double exactSolution(double x, double y) {
	// (write your solution here)
	return sin(2 * M_PI * x) * sin(2 * M_PI * y);
	//return 0; //remove when implemented
	//return 1.0/ (4 * M_PI * M_PI) * sin(2*M_PI*x); // constant solution
}

void convergeStudy(FunctionPointer F, FunctionPointer sigma) {
	const int startK = 3;
	const int endK   = 10;

	Vector errors(endK - startK);
	Vector resolutions(errors.size());
	for (int k = startK; k < endK; ++k) {
		const int N = 1 << k; // 2^k

		// (write your solution here)
		resolutions[k - startK] = N;
		Vector u;
		u            = poissonSolve(F, sigma, N);
		double error = 0;
		for (int i = 1; i < N + 2; i++) {
			for (int j = 1; j < N + 2; j++) {
				double e = abs(u[i * (N + 2) + j] - exactSolution(i / double(N + 2), j / double(N + 2)));
				if (e > error) {
					error = e;
				}
			}
		}
		errors[k - startK] = error;
	}

	writeToFile("errors.txt", errors);
	writeToFile("resolutions.txt", resolutions);
}
//----------------convergenceEnd----------------

int main(int, char **) {
	auto sigmaCos = [](double x, double y) {
		return M_PI / 2. + cos(2 * M_PI * x) * cos(2 * M_PI * y);
	};

	auto sigmaConstant = [](double x, double y) {
		std::ignore = x;
		std::ignore = y;
		return 1.0;
	};
	std::ignore = sigmaConstant;
	auto u      = poissonSolve(F, sigmaCos, 500);
	//auto u = poissonSolve(F, sigmaConstant, 500);
	writeToFile("u_fd.txt", u);

	convergeStudy(F, sigmaCos);
}
