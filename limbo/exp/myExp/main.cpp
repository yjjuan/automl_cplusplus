#include <iostream>
#include  <cmath>
#include "MoveCounter.hpp"
#include "fstream"
#include "sstream"
#include <string>

// you can also include <limbo/limbo.hpp> but it will slow down the compilation
#include <limbo/bayes_opt/boptimizer.hpp>


using namespace limbo;
using namespace std;

struct data{
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


double countLoss(MoveCounter& mc, double groundTruth)
{
    std::vector<float> memoryWindow;
    for (int i=1; i<=10; i++) memoryWindow.push_back(0.f);
    double loss;

    // Read csv data
    std::vector<data> input = LoadData("../../../../training_set1.csv");
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
    loss = std::abs(mc.cyclesCount - groundTruth);
    return loss;
}

struct Params {
    struct bayes_opt_boptimizer : public defaults::bayes_opt_boptimizer {
    };

// depending on which internal optimizer we use, we need to import different parameters
#ifdef USE_NLOPT
    struct opt_nloptnograd : public defaults::opt_nloptnograd {
    };
#elif defined(USE_LIBCMAES)
    struct opt_cmaes : public defaults::opt_cmaes {
    };
#else
    struct opt_gridsearch : public defaults::opt_gridsearch {
    };
#endif

    // enable / disable the writing of the result files
    struct bayes_opt_bobase : public defaults::bayes_opt_bobase {
        BO_PARAM(int, stats_enabled, true);
    };

    // no noise
    struct kernel : public defaults::kernel {
        BO_PARAM(double, noise, 1e-9);
    };

    struct kernel_maternfivehalves : public defaults::kernel_maternfivehalves {
    };

    // we use 10 random samples to initialize the algorithm
    struct init_randomsampling {
        BO_PARAM(int, samples, 10);
    };
    struct opt_rprop : public defaults::opt_rprop {
    };
    // we stop after  iterations
    struct stop_maxiterations {
        BO_PARAM(int, iterations, 30);
    };

    // we use the default parameters for acqui_ucb
    //struct acqui_ucb : public defaults::acqui_ucb {
    struct acqui_ucb{
        BO_PARAM(double, alpha, 100.0);
    };

};

struct Eval {
    // number of input dimension (x.size())
    BO_PARAM(size_t, dim_in, 3);
    // number of dimensions of the result (res.size())
    BO_PARAM(size_t, dim_out, 1);

    // the function to be optimized
    Eigen::VectorXd operator()(const Eigen::VectorXd& x) const
    {
        std::cout << "====================================" << std::endl;
        
        MoveCounter mc(1 + static_cast<int>(120*x(2)), 5*x(0), x(1), 30);
        std::cout << "lag = " << 1 + static_cast<int>(120*x(2))<< "; threshold = " << 5*x(0) << "; influence = " << x(1)<< std::endl;

        //MoveTimer mt(1 + static_cast<int>(120*x(2)), 10*x(0), x(1), 30);
        //std::cout << "lag = " << 1 + static_cast<int>(120*x(2))<< "; threshold = " << 10*x(0) << "; influence = " << x(1)<< std::endl;
        double gt = 10.0;  // ground truth
        double y = -1*countLoss(mc, gt);
        //double y = -1*timeLoss(mt);
        std::cout << "Detected peaks = " << mc.cyclesCount<< std::endl;
        return tools::make_vector(y);
    }
};

int main()
{
    // we use the default acquisition function / model / stat / etc.
    bayes_opt::BOptimizer<Params> boptimizer;
    // run the evaluation
    boptimizer.optimize(Eval());
    // the best sample found
    std::cout << "Best sample: " << boptimizer.best_sample()(0) << " - Best observation: " << boptimizer.best_observation()(0) << std::endl;
    
    // write the found paramter into txt file
    return 0;
}
