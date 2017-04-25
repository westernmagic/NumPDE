#pragma once
#include "coordinate_transform.hpp"
#include "integrate.hpp"
#include "shape.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <functional>

//----------------H1Begin----------------
//! Computes the H^1 differences between
//! u1 (considered as coefficients for Quadratic FEM) and u2grad.
double computeH1Difference(const Eigen::MatrixXd &vertices,
                           const Eigen::MatrixXi &dofs,
                           const Eigen::VectorXd &u1,
                           const std::function<Eigen::Vector2d(double, double)> &u2grad) {
	const int numberOfElements = dofs.rows();

	double error = 0;
	for (int i = 0; i < numberOfElements; ++i) {
		auto &idSet = dofs.row(i);

		const auto &a = vertices.row(idSet(0));
		const auto &b = vertices.row(idSet(1));
		const auto &c = vertices.row(idSet(2));

		auto            coordinateTransform = makeCoordinateTransform(b - a, c - a);
		auto            volumeFactor        = std::abs(coordinateTransform.determinant());
		Eigen::Matrix2d elementMap          = coordinateTransform.inverse().transpose();

		// (write your solution here)
	}

	return std::sqrt(error);
}
//----------------H1End----------------
