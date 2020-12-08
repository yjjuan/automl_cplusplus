#include <iostream>
#include  <cmath>
#include "MoveCounter.hpp"
#include "fstream"
#include "sstream"
#include <string>

using namespace std;

struct data {
        float t;
        float x;
    };

int CountInstances(string fileName) {
    fstream handler;
    handler.open(fileName);
    string line;

    int numInstances = 0;

    while (handler.eof() != true) {
        getline(handler, line);

        if (line != "") {
            numInstances++;
        }
    }
    handler.close();

    return numInstances;
}

std::vector<data> LoadData(string fileName) {
    fstream handler;
    handler.open(fileName);
    int datasetSize = CountInstances(fileName);
    std::vector<data> X;

    for (int i = 0; i < datasetSize; i++) {
        string line;
        getline(handler, line);
        stringstream linestream(line);
        string dataPortion;

        if (line != "") {
            getline(linestream, dataPortion, ',');
            float _t = stof(dataPortion);
            getline(linestream, dataPortion, ' ');
            float _x = stof(dataPortion);


            data newData = {_t, _x};

            X.push_back(newData);
        }
    }
    handler.close();

    return X;
}

std::vector<float> LoadParam(string fileName) {
    fstream handler;
    handler.open(fileName);
    std::vector<float> X;

    string line;
    getline(handler, line);
    stringstream linestream(line);
    string dataPortion;

    getline(linestream, dataPortion, ',');
    X.push_back(stof(dataPortion));
    getline(linestream, dataPortion, ',');
    X.push_back(stof(dataPortion));
    getline(linestream, dataPortion, ' ');
    X.push_back(stof(dataPortion));

    handler.close();

    return X;
}

int main(int argc, char **argv)
{
    // read the paramters in txt file
    std::string s1(argv[1]);
    std::cout << "s1 = " << s1 << std::endl;
    std::vector<float> params = LoadParam(s1);
    MoveCounter mc(params[0], params[1], params[2], 30);
    
    std::vector<float> memoryWindow;
    for (int i=1; i<=10; i++) memoryWindow.push_back(0.f);

    // Read csv data
    std::string s2(argv[2]);
    std::cout << "s2 = " << s2 << std::endl;
    std::vector<data> input = LoadData(s2);
    std::cout << "Finish reading data!" << std::endl;

    int status;
    // Start measuring time

    for (int i =0; i < input.size(); i++){    


        // Update memoryWindow
        memoryWindow.erase(memoryWindow.begin());
        memoryWindow.push_back(input[i].x);

        // Make inference
        status = mc.update(calculateMean(memoryWindow));

    };
    std::cout << "# of move detect = " << mc.cyclesCount << std::endl;

   return 0;
}
