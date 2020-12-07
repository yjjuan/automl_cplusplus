#include "MoveCounter.hpp"  
#include "MoveTimer.hpp"
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
    //std::cout << "Part2: Left lag region. " << std::endl; 
    //std::cout << "i" << i <<std::endl; 
    //std::cout << "y.size() = " << y.size() << std::endl;
    //std::cout << "signals.size() = " << signals.size() << std::endl;
    //std::cout << "filteredY.size() = " << avgFilter.size() << std::endl;
    //std::cout << "avgFilter.size() = " << avgFilter.size() << std::endl;
    //std::cout << "stdFilter.size() = " << stdFilter.size() << std::endl;
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

/*
class online_counter:

    def __init__(self, array, lag, threshold, influence):
        self.y = list(array)
        self.length = len(self.y)
        self.lag = lag
        self.threshold = threshold
        self.influence = influence
        self.signals = [0] * len(self.y)
        self.filteredY = np.array(self.y).tolist()
        self.avgFilter = [0] * len(self.y)
        self.stdFilter = [0] * len(self.y)
        self.avgFilter[self.lag - 1] = np.mean(self.y[0:self.lag]).tolist()
        self.stdFilter[self.lag - 1] = np.std(self.y[0:self.lag]).tolist()
        self.cycles_count = 0
        self.prev_status = queue.Queue(3)
        for i in range(3):
            self.prev_status.put(0)
        self.current_status = 0

    def update(self, new_value):
        self.y.append(new_value)
        i = len(self.y) - 1
        self.length = len(self.y)
        if i < self.lag:
            return 0
        elif i == self.lag:
            self.signals = [0] * len(self.y)
            self.filteredY = np.array(self.y).tolist()
            self.avgFilter = [0] * len(self.y)
            self.stdFilter = [0] * len(self.y)
            self.avgFilter[self.lag - 1] = np.mean(self.y[0:self.lag]).tolist()
            self.stdFilter[self.lag - 1] = np.std(self.y[0:self.lag]).tolist()
            return 0

        self.signals += [0]
        self.filteredY += [0]
        self.avgFilter += [0]
        self.stdFilter += [0]

        if abs(self.y[i] - self.avgFilter[i - 1]) > self.threshold * self.stdFilter[i - 1]:
            if self.y[i] > self.avgFilter[i - 1]:
                self.signals[i] = 1
            else:
                self.signals[i] = -1

            self.filteredY[i] = self.influence * self.y[i] + (1 - self.influence) * self.filteredY[i - 1]
            self.avgFilter[i] = np.mean(self.filteredY[(i - self.lag):i])
            self.stdFilter[i] = np.std(self.filteredY[(i - self.lag):i])
        else:
            self.signals[i] = 0
            self.filteredY[i] = self.y[i]
            self.avgFilter[i] = np.mean(self.filteredY[(i - self.lag):i])
            self.stdFilter[i] = np.std(self.filteredY[(i - self.lag):i])

        ## Count the cycles
        ## This strategy assume little noise within each domain
        self.current_status = self.signals[i]
        if self.current_status != self.prev_status.queue[-1]:
            self.prev_status.get()
            self.prev_status.put(self.current_status)
            #print(self.prev_status.queue)
            if list(self.prev_status.queue) == [1,0,-1]:
                self.cycles_count += 1
                #self.prev_status = list() # Reset prev_status after one complete cycle detected

        return self.signals[i]

    def count(self):

        return self.cycles_count
*/