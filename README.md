# State-Estimation-for-Traffic-Lights-with-Countdown-Timers
This is a project page of the paper "A VT-HMM-based Framework for Countdown Timer Traffic Light State Estimation".
This paper has been submitted to IEEE Transactions on Intelligent Transportation Systems (IEEE TITS) and is currently under review.
This work aims to estimate the color and digit of traffic lights with countdown timers, using a Variable Transition Hidden Markov Model (VT-HMM) with a dynamic state transtion matrix design.

## Dataset


## State Estimator (C++11)
This code is in the folder countdown_timer_estimator.

1. Environments
    * The code is tested cross different systems, including: 
        * Ubuntu 18.04, 64-bit, 16G RAM, Intel Corei5-8600K
        * Ubuntu 20.04, 64-bit, 16G RAM, AMD Ryzen 5 5600X
        * macOS Monterey, 64-bit, 16G RAM, Apple M1 Pro

2. Prerequisites
    * Eigen3, for matrix calculation
    * Protobuf3, for parameter system
    * OpenMP, for CPU parallel acceleration (optimal)

3. Setup
* Clone the repository
    ```
    git clone https://github.com/ShuyangUni/countdown-timer-traffic-light-estimation.git
    ```

* Change the offline convolution file path
    ```
    % line 9, countdown_timer_estimator/config/hsmm_parameter_proto.config
    str_file_distribution: "${Your Repository Root}/countdown-timer-traffic-light-estimation/countdown_timer_estimator/config/distribution.txt""
    ```

* Build the code
    ```
    cd countdown-timer-traffic-light-estimation/countdown_timer_estimator
    mkdir build
    cd build

    % ignore the error report of protobuf cpp header, at the first time
    cmake ..
    make
    ```
    or build with OpenMP
    ```
    cmake -DUSE_OPENMP=on ..
    make
    ```

* Run the code
    ```
    % ./apps/demo_single_sequence [proto config] [dataset folders]
    ./apps/demo_single_sequence ../config/hsmm_parameter_proto.config ../../udi_cttl_dataset/0_offset/01
    ```
* Running Example

## Digit Classifier (Python)

## License
The source code is released under MIT license.

