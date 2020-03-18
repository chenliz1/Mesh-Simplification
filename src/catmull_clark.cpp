#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (num_iters == 0) {
    return;
  }
  SV = V;
  SF = F;
  using namespace std;
  using namespace Eigen;

  
  //Ref:
  //https://rosettacode.org/wiki/Catmull%E2%80%93Clark_subdivision_surface
  //https://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object
  unordered_map<int, RowVector3d> face_point;
  unordered_map<int, set<int>> touching_point;
  unordered_map<int, set<int>> touching_face;
  unordered_map<string, RowVector3d> edge_points;
  unordered_map<string, vector<int>> edge_faces;
  
  for (int i = 0; i < F.rows(); i++) { //maps of relationships
    RowVector3d face_center(0, 0, 0);
    
    for (int j = 0; j < F.cols(); j++) { //As readme said assume quad
      face_center += V.row(F(i, j));
      touching_point[F(i, j)].insert(F(i, (j + 1) % 4));
      touching_face[F(i, j)].insert(i);

      string e1 = to_string(F(i, j)) + "," + to_string(F(i, (j + 1) % 4));
      string e2 = to_string(F(i, (j + 1) % 4)) + "," + to_string(F(i, j));
      
      edge_faces[e1].push_back(i);
      edge_faces[e2].push_back(i);
    }

    face_center /= 4.0;
    face_point[i] = face_center;
  }


  //edge points table
  for (int i = 0; i < F.rows(); i++) { //maps of relationships
    for (int j = 0; j < F.cols(); j++) { //As readme said assume quad
      string e1 = to_string(F(i, j)) + "," + to_string(F(i, (j + 1) % 4));
      string e2 = to_string(F(i, (j + 1) % 4)) + "," + to_string(F(i, j));
      RowVector3d edge_p1 = V.row(F(i, j)) + V.row(F(i, (j + 1) % 4));

      RowVector3d edge_p2 = V.row(F(i, (j + 1) % 4)) + V.row(F(i, j));
      for (int k = 0; k < edge_faces[e1].size(); k++) {
        edge_p1 += face_point[(edge_faces[e1])[k]];
      }
      for (int k = 0; k < edge_faces[e2].size(); k++) {
        edge_p2 += face_point[(edge_faces[e2])[k]];
      }
      edge_points[e1] = edge_p1 / 4.0;
      edge_points[e2] = edge_p2 / 4.0;

    }
  }

  //https://stackoverflow.com/questions/27404811/append-column-to-matrix-using-eigen-library
  SV.resize(0, V.cols());//hard to decide the size of the SV
  SF.resize(F.rows() * 4, F.cols());

  for (int i = 0; i < F.rows(); i++) {
    for (int j = 0; j < F.cols(); j++) {
      set<int>::iterator itr;
      //move original point P
      RowVector3d P_original = V.row(F(i, j));
      double n = touching_face[F(i, j)].size();
      double n_p = touching_point[F(i, j)].size();
      RowVector3d F_avg(0, 0, 0);
      itr = touching_face[F(i, j)].begin();
      while (itr != touching_face[F(i, j)].end()) {
        F_avg += face_point[*itr];
        itr ++;
      }
      F_avg =  F_avg / n;

      RowVector3d R_avg(0, 0, 0);
      itr = touching_point[F(i, j)].begin();
      while (itr != touching_point[F(i, j)].end()) {
        R_avg += (V.row(F(i, j)) + V.row(*itr)) / 2.0;
        itr ++;
      }
      R_avg = R_avg / n_p;

      RowVector3d P_new = (F_avg + 2.0 * R_avg + (n - 3.0) * P_original) / n;

      //face point
      RowVector3d face_p = face_point[i];

      //edge points
      RowVector3d edge_p1 = V.row(F(i, j)) + V.row(F(i, (j + 1) % 4));
      RowVector3d edge_p2 = V.row(F(i, j)) + V.row(F(i, (j + 3) % 4));
      string str_k1 = to_string(F(i, j)) + "," + to_string(F(i, (j + 1) % 4));
      string str_k2 = to_string(F(i, j)) + "," + to_string(F(i, (j + 3) % 4));
      
      edge_p1 = edge_points[str_k1];
      edge_p2 = edge_points[str_k2];
      

      //Ref: https://codeyarns.com/2016/02/16/how-to-compare-eigen-matrices-for-equality/
      MatrixXd new_face_mat(4, 3);
      new_face_mat << P_new, edge_p1, face_p, edge_p2;
      RowVector4i flags(0, 0, 0, 0);
      RowVector4i new_face;
      for (int k = 0; k < F.cols(); k++) {

        for (int l = 0; l < SV.rows(); l++) {
          if ( SV.row(l).isApprox(new_face_mat.row(k)) ){
            new_face(k) = l; //if the point present already
            flags(k) = 1;
            break;
          }
        }

        if (flags(k) == 0) {
          SV.conservativeResize(SV.rows() + 1, NoChange);
          SV.row(SV.rows() - 1) = new_face_mat.row(k);
          new_face(k) = SV.rows() - 1;
          flags(k) = 1;
        }  
      }
      SF.row(i * 4 + j) = new_face;
    }
  }
  MatrixXd temp_SV = SV;
  MatrixXi temp_SF = SF;

  catmull_clark(temp_SV, temp_SF, num_iters - 1, SV, SF);
  

  ////////////////////////////////////////////////////////////////////////////
}
