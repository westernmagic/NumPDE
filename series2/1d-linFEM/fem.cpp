#include "writer.hpp"
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <cmath>
#include <iostream>
#include <stdexcept>

//! Sparse Matrix type. Makes using this type easier.
typedef Eigen::SparseMatrix<double> SparseMatrix;

//! Used for filling the sparse matrix.
typedef Eigen::Triplet<double> Triplet;

//! Vector type
typedef Eigen::VectorXd Vector;

//! Our function pointer, typedef'd to make it easier to use
typedef double (*FunctionPointer)(double);

//! Create the Stiffness matrix for 1D with boundary terms
//! @param[out] A will be the Galerkin matrix (as in the exercise)
//! @param[in] N as in the exercise
//! @param[in] dx the cell length
void createStiffnessMatrixWithBoundary(SparseMatrix &A, int N, double dx) {
	std::vector<Triplet> triplets;
	A.resize(N + 2, N + 2);

	// Reserve the space we will allocate
	triplets.reserve((N + 2) + 2 * N + 2);

	// (write your solution here)
	A.setZero();
	for (int i = 0; i < N + 2; i++) {
		triplets.push_back(Triplet(i, i, 2 / dx));
		if (i >= 1) {
			triplets.push_back(Triplet(i, i - 1, -1 / dx));
		}
		if (i <= N + 1) {
			triplets.push_back(Triplet(i, i + 1, -1 / dx));
		}
	}
	A.setFromTriplets(triplets.begin(), triplets.end());
}

//! Creates the right hand side for the finite element method in the exericse
//! @param[out] rhs the resulting right hand side (or phi in the exercise)
//! @param[in] f the function pointer to f
//! @param[in] dx the cell length
//! @param[in] x the x points
void createRHS(Vector &rhs, FunctionPointer f, int N, double dx, const Vector &x) {
	rhs.resize(N + 2);

	// (write your solution here)
}

//! Solve the equation
//!
//!    $-u''(x) = f(x)$
//!
//! using FEM on the interval $[a,b]$.
//!
//! @param[out] u at the end, will have all the values of u
//! @param[out] x will be the x points
//! @param[in] f should be a pointer to the function f
//! @param[in] N number of inner cells to use
//! @param[in] a endpoint on left side
//! @param[in] b endpoint on right side
//! @param[in] ua boundary value at a
//! @param[in] ub boundary value at b
void femSolve(Vector &u, Vector &x, FunctionPointer f, int N, double a, double b, double ua = 0.0, double ub = 0.0) {
	double dx = (b - a) / (N + 1);

	// Fill x vector
	x.setLinSpaced(N + 2, a, b);

	SparseMatrix A;
	createStiffnessMatrixWithBoundary(A, N, dx);

	Vector phi;
	createRHS(phi, f, N, dx, x);

	// (write your solution here)

	u.resize((N + 2));
	u.setZero();

	// Do boundary conditions
	// (write your solution here)

	//solve inner system
	// (write your solution here)
}

void computeWithoutBoundaryValues() {
	Vector u;
	Vector x;
	femSolve(u, x, std::sin, 100, -M_PI, M_PI);

	writeToFile("u_wo_bc_fem.txt", u);
	writeToFile("x_wo_bc_fem.txt", x);
}

void computeWithBoundaryValues() {
	Vector u;
	Vector x;
	femSolve(u, x, std::cos, 100, -M_PI, M_PI, -1.0, 1.0 / 2.0);

	writeToFile("u_w_bc_fem.txt", u);
	writeToFile("x_w_bc_fem.txt", x);
}

int main(int, char **) {
	computeWithoutBoundaryValues();
	computeWithBoundaryValues();
}
