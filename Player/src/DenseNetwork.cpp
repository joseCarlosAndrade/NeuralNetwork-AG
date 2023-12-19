#include "DenseNetwork.h"

void DenseNetwork::Init(vector<int>& layers, vector<vector<double>>& parameters) {
    this->layers = layers;

    int numLayers = layers.size();
    for(int i=0 ; i<numLayers-2 ; i++) {
        this->net.add_layer(new FullyConnected<ReLU>(layers[i], layers[i+1]));
    }
    this->net.add_layer(new FullyConnected<Softmax>(layers[numLayers-2], layers[numLayers-1]));

    this->net.init();
    this->net.set_parameters(parameters);
}

DenseNetwork::DenseNetwork(vector<int>& layers) {
    vector<vector<double>> parameters;
    
    int numLayers = layers.size();
    for(int i=0 ; i<numLayers-1 ; i++) {
        parameters.push_back(vector<double>());
        int numParams = layers[i] * layers[i+1] + layers[i+1];
        for(int j=0 ; j<numParams ; j++) {
            double random = (double)rand() / (double)RAND_MAX;
            parameters[i].push_back(random - 0.5);
        }
    }

    this->Init(layers, parameters);
}

DenseNetwork::DenseNetwork(vector<int>& layers, vector<vector<double>>& parameters) {
    this->Init(layers, parameters);
}

DenseNetwork::DenseNetwork(const string& filename) {
    vector<int> layers;
    vector<vector<double>> parameters;

    ifstream file(filename);
    if(!file.is_open()) {
        cerr << "Error opening file for reading: " << filename << endl;
        return;
    }

    string line;

    getline(file, line);
    istringstream iss(line);
    int numNeurons;
    while(iss >> numNeurons) {
        layers.push_back(numNeurons);
    }

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

    this->Init(layers, parameters);
}

vector<int> DenseNetwork::GetLayers() {
    return this->layers;
}

vector<vector<double>> DenseNetwork::GetParameters() {
    return this->net.get_parameters();
}

void DenseNetwork::SetParameters(vector<vector<double>>& parameters) {
    this->net.set_parameters(parameters);
}

MatrixXd DenseNetwork::Predict(MatrixXd& input) {
    return this->net.predict(input);
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