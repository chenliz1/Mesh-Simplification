#ifndef TRIANGLE_PLANE_H
#define TRIANGLE_PLANE_H
#include <Eigen/Core>

// Inputs:
//   a  3D position of the first corner as a **row vector**
//   b  3D position of the second corner as a **row vector**
//   c  3D position of the third corner as a **row vector**
// Returns the plane parameters abcd as 4D row vector
Eigen::RowVector4d triangle_plane(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c);
#endif