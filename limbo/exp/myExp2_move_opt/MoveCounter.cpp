#include "MoveCounter.hpp"  
#include <iostream>
#include <vector>


MoveCounter::MoveCounter(int _lag, float _threshold, float _influence, float _fps)
{
    // Parameters set by user
    lag = _lag;
    threshold = _threshold;
    influence = _influence;
    fps = _fps;

    // 
    for (int i=1; i<3; i++) y.push_back(0.f);
    length = lag;
    
    for (int i=0; i<lag; i++) signals.push_back(0);
    for (int i=0; i<lag; i++) filteredY.push_back(0.f);
    for (int i=0; i<lag; i++) avgFilter.push_back(0.f);
    for (int i=0; i<lag; i++) stdFilter.push_back(0.f);
    for (int i=0; i<3; i++) prevStatus.push_back(0);

    std::cout << "MoveCounter created!" << std::endl;

}

MoveCounter::~MoveCounter()
{
    std::cout << "MoveCounter detroyed!" << std::endl;
}

int MoveCounter::update(float newData)
{
    y.push_back(newData);
    int i = y.size() - 1;
    if (i < lag){return 0;}
    else if(i == lag){
        signals.push_back(0);
        filteredY.push_back(newData);
        avgFilter.push_back(0.0);
        std::for_each(avgFilter.begin(), avgFilter.end()-1, [&](float &n){ n = calculateMean(y); });
        stdFilter.push_back(0.0);
        std::for_each(stdFilter.begin(), stdFilter.end()-1, [&](float &n){ n = calculateStd(y); });

        return 0;
    }

    if (std::abs(y[i] - avgFilter[i - 1]) > threshold * stdFilter[i - 1])
    {
        if (y[i] > avgFilter[i - 1])
        {
            signals.push_back(1); //# Positive signal
        }
        else
        {
            signals.push_back(-1); //# Negative signal
        }
        //Make influence lower
        filteredY.push_back(influence* y[i] + (1 - influence) * filteredY[i - 1]);
    }
    else
    {
        signals.push_back(0); //# No signal
        filteredY.push_back(y[i]);
    }
    //Adjust the filters
    std::vector<float> subVec(filteredY.begin() + i - lag, filteredY.begin() + i);
    avgFilter.push_back(calculateMean(subVec));
    stdFilter.push_back(calculateStd(subVec));   

    // Count the cycles
    // This strategy assume little noise within each domain
    currentStatus = signals[i];

    // Switch on: identify the start of burning region.
    if (currentStatus != prevStatus[2]){
        prevStatus.erase(prevStatus.begin());
        prevStatus.push_back(currentStatus);    

        if (prevStatus[0] == 1 && prevStatus[1] == 0 && prevStatus[2] == -1) {cyclesCount += 1;}   

        }
        
    return currentStatus;
}
