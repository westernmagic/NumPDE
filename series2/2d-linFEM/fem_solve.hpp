#pragma once
#include <Eigen/Core>
#include <string>
#include <igl/readSTL.h>
#include <igl/slice.h>
#include <igl/slice_into.h>
#include "stiffness_matrix_assembly.hpp"
#include "load_vector_assembly.hpp"
#include "dirichlet_boundary.hpp"

typedef Eigen::VectorXd Vector;

//----------------solveBegin----------------
//! Solve the FEM system.
//!
//! @param[out] u will at the end contain the FEM solution.
//! @param[in] vertices list of triangle vertices for the mesh
//! @param[in] triangles list of triangles (described by indices)
//! @param[in] f the RHS f (as in the exercise)
//! @param[in] g the boundary value (as in the exercise)
//! @param[in] sigma the function sigma as in the exercise
//! @param[in] r the parameter r from the lecture notes
//! return number of degrees of freedom (without the boundary dofs)
int solveFiniteElement(Vector& u,
		       const Eigen::MatrixXd& vertices,
		       const Eigen::MatrixXi& triangles,
		       const std::function<double(double, double)>& f,
		       const std::function<double(double, double)>& sigma,		       
		       const std::function<double(double, double)>& g,
		       double r)
{
    SparseMatrix A;
// (write your solution here)
    
    Vector F;
// (write your solution here)
    
    u.resize(vertices.rows());
    u.setZero();
    Eigen::VectorXi interiorVertexIndices;

    // set Dirichlet Boundary conditions
// (write your solution here)
    
    SparseMatrix AInterior;

    igl::slice(A, interiorVertexIndices, interiorVertexIndices, AInterior);
    Eigen::SimplicialLDLT<SparseMatrix> solver;

    Vector FInterior;

    igl::slice(F, interiorVertexIndices, FInterior);

    //initialize solver for AInterior
// (write your solution here)

    //solve interior system
// (write your solution here)

    return interiorVertexIndices.size();

}
//----------------solveEnd----------------
