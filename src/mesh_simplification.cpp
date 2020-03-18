#include "mesh_simplification.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

void q_slim(
    const Eigen::MatrixXd & V,
    const Eigen::MatrixXi & F,
    const int num_iters,
    Eigen::MatrixXd & SV,
    Eigen::MatrixXi & SF)
{
    if (num_iters == 0) {
        return;
    }
    SV = V;
    SF = F;
    using namespace std;
    using namespace Eigen;

    



}