# Bayesian Optimization for peak detector in C++
Looking for best parameters for peak detector in C++

## Basic workflow in this repo
Code to generate analysis and figure could be found in this [notebook](./workflow_in_nutshell.ipynb)
1. Generate periodic time-series for training and test set1
2. Compile C++ code into executable
3. Tune three parameters of peak detector based on training set via limbo library, and save the optimal parameter to txt file
4. run this optimal peak detector on test set1. As expected, peak detector predicts the number of peaks quite well
5. run this peak detector on test set2 w/ totally different intrinsic properties. Almost lose its performance. This result shows that re-tuning is necessary when faced w/ diffferent scenario. There is no "one size fits all"!
 

## Reference
1. [LIMBO: bayesian optimization in C++]()
2. [NLOPT library]()
3. 