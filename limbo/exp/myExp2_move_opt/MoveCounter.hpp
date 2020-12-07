#pragma once
#include <numeric>
#include <cmath>
#include <algorithm>
#include <vector>

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