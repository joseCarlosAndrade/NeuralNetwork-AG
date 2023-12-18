#include "DenseNetwork.h"
#include <cstdlib> 

DenseNetwork::DenseNetwork(vector<int>& layers) {
    this->layers = layers;

    int numLayers = layers.size();
    for(int i=0 ; i<numLayers-2 ; i++) {
        this->net.add_layer(new FullyConnected<ReLU>(layers[i], layers[i+1]));
    }
    this->net.add_layer(new FullyConnected<Softmax>(layers[numLayers-2], layers[numLayers-1]));
    
    this->net.init(0, 0.01, static_cast<unsigned int>(std::time(nullptr)));
}

DenseNetwork::DenseNetwork(vector<int>& layers, vector<vector<double>>& parameters)
: DenseNetwork(layers) {
    this->net.set_parameters(parameters);
}

DenseNetwork::DenseNetwork(tuple<vector<int>, vector<vector<double>>> netInfo)
: DenseNetwork(get<0>(netInfo), get<1>(netInfo)) {
    
}

vector<vector<double>> DenseNetwork::GetParameters() {
    return this->net.get_parameters();
}

void DenseNetwork::SetParameters(vector<vector<double>>& parameters) {
    this->net.set_parameters(parameters);
}

tuple<vector<int>, vector<vector<double>>> DenseNetwork::LoadFrom(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        cerr << "Error opening file for reading: " << filename << endl;
        return make_tuple(vector<int>(), vector<vector<double>>());
    }

    string line;

    getline(file, line);
    istringstream iss(line);
    vector<int> layers;
    int numNeurons;
    while(iss >> numNeurons) {
        layers.push_back(numNeurons);
    }

    vector<vector<double>> parameters;
    while(getline(file, line)) {
        istringstream iss(line);
        vector<double> layerParams;
        double param;
        while(iss >> param) {
            layerParams.push_back(param);
        }
        parameters.push_back(std::move(layerParams));
    }

    file.close();

    return make_tuple(layers, parameters);
}

void DenseNetwork::SaveAs(const string& filename) {
    ofstream file(filename);
    if(!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    for(const auto& numNeurons : this->layers) {
        file << numNeurons << ' ';
    }
    file << '\n';

    for(const auto& layerParams : this->net.get_parameters()) {
        for (const auto& param : layerParams) {
            file << param << ' ';
        }
        file << '\n';
    }

    file.close();
}

DenseNetwork DenseNetwork::operator+(const DenseNetwork& other) {
    if(this->layers != other.layers) {
        cerr << "Vectors must have the same size for element-wise addition." << endl;
        return *this;
    }

    vector<vector<double>> params1 = this->net.get_parameters();
    vector<vector<double>> params2 = other.net.get_parameters();

    vector<vector<double>> resultParams;
    
    for(size_t i=0 ; i<params1.size() ; i++) {
        resultParams.push_back(vector<double>());
        for(size_t j=0 ; j<params1[i].size() ; j++) {
            resultParams[i].push_back(params1[i][j] + params2[i][j]);
        }
    }

    return DenseNetwork(this->layers, resultParams);
}

DenseNetwork DenseNetwork::operator-(const DenseNetwork& other) {
    if(this->layers != other.layers) {
        cerr << "Vectors must have the same size for element-wise addition." << endl;
        return *this;
    }

    vector<vector<double>> params1 = this->net.get_parameters();
    vector<vector<double>> params2 = other.net.get_parameters();

    vector<vector<double>> resultParams;
    
    for(size_t i=0 ; i<params1.size() ; i++) {
        resultParams.push_back(vector<double>());
        for(size_t j=0 ; j<params1[i].size() ; j++) {
            resultParams[i].push_back(params1[i][j] - params2[i][j]);
        }
    }

    return DenseNetwork(this->layers, resultParams);
}

DenseNetwork DenseNetwork::operator*(double k) {
    vector<vector<double>> params = this->net.get_parameters();

    vector<vector<double>> resultParams;
    
    for(size_t i=0 ; i<params.size() ; i++) {
        resultParams.push_back(vector<double>());
        for(size_t j=0 ; j<params[i].size() ; j++) {
            resultParams[i].push_back(params[i][j] * k);
        }
    }

    return DenseNetwork(this->layers, resultParams);
}

DenseNetwork DenseNetwork::operator/(double k) {
    vector<vector<double>> params = this->net.get_parameters();

    vector<vector<double>> resultParams;
    
    for(size_t i=0 ; i<params.size() ; i++) {
        resultParams.push_back(vector<double>());
        for(size_t j=0 ; j<params[i].size() ; j++) {
            resultParams[i].push_back(params[i][j] / k);
        }
    }

    return DenseNetwork(this->layers, resultParams);
}

DenseNetwork::~DenseNetwork() {

}