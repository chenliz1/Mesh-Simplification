#include "triangle_plane.h"
#include <Eigen/Geometry>

Eigen::RowVector4d triangle_plane(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  Eigen::RowVector3d cross = (a - b).cross(a - c);
  Eigen::RowVector3d result = (cross.norm() / 2.0) * cross.normalized();
  double d = result.dot(b) * -1.0;
  Eigen::RowVector4d plane;
  plane << result, d;
  ////////////////////////////////////////////////////////////////////////////
  return plane;
}
