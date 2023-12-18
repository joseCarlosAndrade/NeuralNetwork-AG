#ifndef DENSENETWORK_H
#define DENSENETWORK_H

#include <string>
#include <vector>
#include <memory>
#include <Eigen/Core> 
#include "MiniDNN.h" 

using namespace std;
using namespace Eigen;
using namespace MiniDNN;

class DenseNetwork {
    private:
        Network net;
        vector<int> layers;
    
    public:
        DenseNetwork(vector<int>& layers);
        DenseNetwork(vector<int>& layers, vector<vector<double>>& parameters);
        DenseNetwork(tuple<vector<int>, vector<vector<double>>> netInfo);

        vector<vector<double>> GetParameters();
        void SetParameters(vector<vector<double>>& parameters);

        static tuple<vector<int>, vector<vector<double>>> LoadFrom(const string& filename);
        void SaveAs(const string& filename);

        DenseNetwork operator+(const DenseNetwork& other);
        DenseNetwork operator-(const DenseNetwork& other);
        DenseNetwork operator*(double k);
        DenseNetwork operator/(double k);

        ~DenseNetwork();
};

#endif 