#ifndef DENSENETWORK_H
#define DENSENETWORK_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <Eigen/Core>
#include "MiniDNN.h" 

using namespace std;
using namespace Eigen;
using namespace MiniDNN;

#define PARAMETERS_DOMAIN 4

class DenseNetwork {
    private:
        Network net;
        vector<int> layers;

        void Init(vector<int>& layers, vector<vector<double>>& parameters);
    
    public:
        DenseNetwork(vector<int>& layers);
        DenseNetwork(vector<int>& layers, vector<vector<double>>& parameters);
        DenseNetwork(const DenseNetwork& network);
        DenseNetwork(const string& filename);

        vector<int> GetLayers();
        vector<vector<double>> GetParameters();
        void SetParameters(vector<vector<double>>& parameters);

        MatrixXd Predict(MatrixXd& input);
        VectorXd Predict(VectorXd& input);

        void SaveAs(const string& filename);

        DenseNetwork operator+(const DenseNetwork& other);
        DenseNetwork operator-(const DenseNetwork& other);
        DenseNetwork operator*(double k);
        DenseNetwork operator/(double k);
        DenseNetwork& operator+=(const DenseNetwork& other);
        DenseNetwork& operator-=(const DenseNetwork& other);
        DenseNetwork& operator*=(double k);
        DenseNetwork& operator/=(double k);

        ~DenseNetwork();
};

#endif 