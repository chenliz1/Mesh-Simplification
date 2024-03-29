#include "triangle_area_normal.h"
#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  Eigen::RowVector3d cross = (a - b).cross(a - c);
  Eigen::RowVector3d result = (cross.norm() / 2.0) * cross.normalized();
  ////////////////////////////////////////////////////////////////////////////
  return result;
}
