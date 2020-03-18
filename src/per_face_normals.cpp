#include "per_face_normals.h"
#include "triangle_area_normal.h"

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  N = Eigen::MatrixXd::Zero(F.rows(),3);
  Eigen::RowVector3d area_normal;
  Eigen::RowVector3d a, b, c;
  for (int i = 0; i < F.rows(); i++) {
    a = V.row(F(i, 0));
    b = V.row(F(i, 1));
    c = V.row(F(i, 2));
    area_normal = triangle_area_normal(a, b, c);
    N.row(i) = area_normal.normalized();
  }
  ////////////////////////////////////////////////////////////////////////////
}
