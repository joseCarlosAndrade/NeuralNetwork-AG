#include <iostream>
#include <Eigen/Core> 


using namespace std;

int main() {
    Eigen::VectorXi indices = Eigen::VectorXi::LinSpaced(playsProbs.rows(), 0, playsProbs.rows() - 1);
    auto data = indices.data();
}