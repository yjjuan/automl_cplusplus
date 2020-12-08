#pragma once
#include <numeric>
#include <cmath>
#include <algorithm>
#include <vector>

float calculateMean(const std::vector<float>& v){
    // source; https://stackoverflow.com/questions/7616511/calculate-mean-and-standard-deviation-from-a-vector-of-samples-in-c-using-boos/12405793#12405793
    float sum = std::accumulate(std::begin(v), std::end(v), 0.0);
    return  sum / v.size();
};

float calculateStd(const std::vector<float>& v){
    // source: https://stackoverflow.com/questions/7616511/calculate-mean-and-standard-deviation-from-a-vector-of-samples-in-c-using-boos/12405793#12405793
    float accum = 0.0;
    float mean = calculateMean(v);
    std::for_each (std::begin(v), std::end(v), [&](const double d) {
        accum += (d - mean) * (d - mean);
    });

    return sqrt(accum / (v.size()-1));
};

class MoveCounter  
{
	private:
    public:
        std::vector<float> y;
        int length;
        int lag;
        float threshold;
        float influence;
        std::vector<int> signals;
        std::vector<float> filteredY;
        std::vector<float> avgFilter;
        std::vector<float> stdFilter;
        float fps;
        int regionCount = 0;
		int cyclesCount = 0;
        float regionTotalTime = 0.0;
        bool isBurning = true;
        std::vector<int> prevStatus; 
        int currentStatus = 0;
	public:

		MoveCounter(int _lag, float _threshold, float _influence, float _fps);
		~MoveCounter();
        
        int update(float newData);

};