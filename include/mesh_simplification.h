#ifndef MESH_SIMPLIFICATION_H
#define MESH_SIMPLIFICATION_H
#include <Eigen/Core>

// Inputs:
//   V  #V by 3 list of vertex positions
//   F  #F by 4 list of quad mesh indices into V
//   num_iters  number of iterations
// Outputs:
//   SV  #SV by 3 list of vertex positions
//   SF  #SF by 4 list of quad mesh indices into SV
// 
void q_slim(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF);
#endif