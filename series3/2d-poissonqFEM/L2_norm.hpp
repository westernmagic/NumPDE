#pragma once
#include <functional>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "coordinate_transform.hpp"
#include "integrate.hpp"
#include "shape.hpp"

//----------------L2Begin----------------
//! Computes the L^2 differences between 
//! u1 (considered as coefficients for Quadratic FEM) and u2.
double computeL2Difference(const Eigen::MatrixXd& vertices,
			   const Eigen::MatrixXi& dofs,
			   const Eigen::VectorXd& u1,
			   const std::function<double(double, double)>& u2) 
{
  const int numberOfElements = dofs.rows();

  double error = 0;
  for (int i = 0; i < numberOfElements; ++i) {
    auto& idSet = dofs.row(i);

    const auto& a = vertices.row(idSet(0));
    const auto& b = vertices.row(idSet(1));
    const auto& c = vertices.row(idSet(2));

    auto coordinateTransform = makeCoordinateTransform(b - a, c - a);
    auto volumeFactor = std::abs(coordinateTransform.determinant());

// (write your solution here)
  }

  return std::sqrt(error);
}
//----------------L2End----------------
