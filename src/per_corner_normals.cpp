#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);
  using namespace Eigen;
  RowVector3d a, b, c;
  for (int i = 0; i < F.rows(); i++) { 
    a = V.row(F(i, 0));
    b = V.row(F(i, 1));
    c = V.row(F(i, 2));
    RowVector3d n_f = triangle_area_normal(a, b, c).normalized();

    for (int j = 0; j < F.cols(); j++) {
      RowVector3d n_fc(0, 0, 0);
      for (int k = 0; k < VF[F(i, j)].size(); k++) {
        a = V.row(F(VF[F(i, j)][k], 0));
        b = V.row(F(VF[F(i, j)][k], 1));
        c = V.row(F(VF[F(i, j)][k], 2));
        RowVector3d w_norm = triangle_area_normal(a, b, c);
        double dot = n_f.dot(w_norm.normalized()) / (n_f.norm() * w_norm.normalized().norm());
        if (dot >= cos((corner_threshold / 180.0) * M_PI)) {//cos is decreasing function at (0, pi)
          n_fc += w_norm;
        }
      }
      N.row(i * F.cols() + j) = n_fc / n_fc.norm();
    }

  }
  ////////////////////////////////////////////////////////////////////////////
}
