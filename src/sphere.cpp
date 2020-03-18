#include "sphere.h"
#include <iostream>
#include <cmath>
void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  //Ref: 
  //https://stackoverflow.com/questions/10473852/convert-latitude-and-longitude-to-point-in-3d-space

  V.resize((num_faces_u + 1) * (num_faces_v + 1), 3);
  F.resize(num_faces_u * num_faces_v, 4);
  UV.resize((num_faces_u + 1) * (num_faces_v + 1), 2);
  UF.resize(num_faces_u * num_faces_v, 4);
  NV.resize((num_faces_u + 1) * (num_faces_v + 1), 3);
  NF.resize(num_faces_u * num_faces_v, 4);

  double nu, nv, x, y, z;
  for (int i = 0; i < (num_faces_u + 1); i++) {
    for (int j = 0; j < (num_faces_v + 1); j++) {
      nu = (i * 1.0) / (num_faces_u * 1.0);
      nv = (j * 1.0) / (num_faces_v * 1.0);
      //https://www.mathworks.com/help/aeroblks/llatoecefposition.html
      //latitude's range is -90deg to 90deg and
      //Longitude's range from -180deg to 180deg
      //so minus 0.5 to nu and nv to shift degree 
      // Ref: https://www.adelaide.edu.au/mathslearning/handouts/useful-trig-identities.pdf
      //sin(x-0.5pi) = -cos(x), cos(x-pi) = -cos(x)
      x = std::cos(M_PI * (nv - 0.5)) * std::cos(2.0 * M_PI * (nu - 0.5)); 
      //sin(x-0.5pi) = -cos(x), sin(x-pi) = -sin(x)
      y = std::cos(M_PI * (nv - 0.5)) * std::sin(2.0 * M_PI * (nu - 0.5));
      //cos(x-0.5pi) = sin(x)
      z = std::sin(M_PI * (nv - 0.5));
      V.row(i * (num_faces_v + 1) + j) = Eigen::RowVector3d(x, y, z);
      UV.row(i * (num_faces_v + 1) + j) = Eigen::RowVector2d(nu, nv);
      NV.row(i * (num_faces_v + 1) + j) = Eigen::RowVector3d(x, y, z).normalized();
    }
  }

  for (int i = 0; i < num_faces_u; i++) {
    for (int j = 0; j < num_faces_v; j++) {
      int top = i * (num_faces_v + 1) + j;
      int bot = (i + 1) * (num_faces_v + 1) + j;

      F.row(i * (num_faces_v) + j) = Eigen::RowVector4i(top, top + 1, bot + 1, bot);
      UF.row(i * (num_faces_v) + j) = Eigen::RowVector4i(top, top + 1, bot + 1, bot);
      NF.row(i * (num_faces_v) + j) = Eigen::RowVector4i(top, top + 1, bot + 1, bot);
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
