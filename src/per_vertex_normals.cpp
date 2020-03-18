#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include <unordered_map>
#include <set>
void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  using namespace std;
  using namespace Eigen;

  unordered_map<int, set<int>> touching_face;

  for (int i = 0; i < F.rows(); i++) {//assume all vertex connected
    for (int j = 0; j < F.cols(); j++) { 
      touching_face[F(i, j)].insert(i);
    }
  }
  RowVector3d a, b, c;
  for (int i = 0; i < V.rows(); i++) { 

    RowVector3d w_norm(0, 0, 0);
    set<int>::iterator itr = touching_face[i].begin();
    while (itr != touching_face[i].end()) {
      a = V.row(F(*itr, 0));
      b = V.row(F(*itr, 1));
      c = V.row(F(*itr, 2));
      w_norm += triangle_area_normal(a, b, c);

      itr ++;
    }
    N.row(i) = w_norm / w_norm.norm();
  }

  ////////////////////////////////////////////////////////////////////////////
}
