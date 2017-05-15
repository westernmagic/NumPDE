#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <igl/boundary_facets.h>
#include <tuple>

//! Creates a list of boundary edges for the given triangular mesh
Eigen::MatrixXi getBoundaryEdges(const Eigen::MatrixXd &vertices,
                                 const Eigen::MatrixXi &triangles) {
	std::ignore = vertices;

	Eigen::MatrixXi boundaryEdgeIndices;
	igl::boundary_facets(triangles, boundaryEdgeIndices);
	return boundaryEdgeIndices;
}
