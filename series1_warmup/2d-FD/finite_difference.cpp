#include <Eigen/Sparse>
#include <iostream>
#include "writer.hpp"
#include <cmath>
#include <Eigen/SparseCholesky>
#include <stdexcept>

//! Sparse Matrix type. Makes using this type easier.
typedef Eigen::SparseMatrix<double> SparseMatrix;

//! Used for filling the sparse matrix.
typedef Eigen::Triplet<double> Triplet;


//! Vector type
typedef Eigen::VectorXd Vector;


//! Our function pointer, typedef'd to make it easier to use
typedef double(*FunctionPointer)(double, double);

//----------------poissonBegin----------------
//! Create the Poisson matrix for 2D finite difference.
//! @param[out] A will be the Poisson matrix (as in the exercise)
//! @param[in] N number of elements in the x-direction
void createPoissonMatrix2D(SparseMatrix& A, int N) {
     // Fill the matrix A using setFromTriplets - method (see other exercise
    // for how to use it).
// (write your solution here)
}
//----------------poissonEnd----------------


//----------------RHSBegin----------------
//! Create the Right hand side for the 2D finite difference
//! @param[out] rhs will at the end contain the right hand side
//! @param[in] f the right hand side function f
//! @param[in] N the number of points in the x direction
//! @param[in] dx the cell width
void createRHS(Vector& rhs, FunctionPointer f, int N, double dx) {
    rhs.resize(N * N);
    // fill up RHS
    // remember that the index (i,j) corresponds to i*N+j
// (write your solution here)
}
//----------------RHSEnd----------------


//----------------solveBegin----------------
//! Solve the Poisson equation in 2D
//! @param[out] u will contain the solution u
//! @param[in] f the function pointer to f
//! @param[in] N the number of points to use (in x direction)
void poissonSolve(Vector& u, FunctionPointer f, int N) {
    // Solve Poisson 2D here
// (write your solution here)
}
//----------------solveEnd----------------


double F(double x, double y) {
    return 8*M_PI*M_PI*sin(2*M_PI*x)*sin(2*M_PI*y);
}



int main(int, char**) {
    Vector u;
    poissonSolve(u, F, 100);
    writeToFile("u_fd.txt", u);
}




