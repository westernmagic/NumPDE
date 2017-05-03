#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <igl/boundary_facets.h>

//! Creates a list of boundary edges for the given triangular mesh
Eigen::MatrixXi getBoundaryEdges(const Eigen::MatrixXd &vertices,
                                 const Eigen::MatrixXi &triangles) {
	Eigen::MatrixXi boundaryEdgeIndices;
	igl::boundary_facets(triangles, boundaryEdgeIndices);
	return boundaryEdgeIndices;
}