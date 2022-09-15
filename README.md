# State-Estimation-for-Traffic-Lights-with-Countdown-Timers
This is a project page of the paper "A VT-HMM-based Framework for Countdown Timer Traffic Light State Estimation".
This paper has been submitted to IEEE Transactions on Intelligent Transportation Systems (IEEE TITS) and is currently under review.
This work aims to estimate the color and digit of traffic lights with countdown timers, using a Variable Transition Hidden Markov Model (VT-HMM) with a dynamic state transtion matrix design.

## Dataset
Our toy dataset is collected under the help from [Unity-Drive Innovation Technology Co., Ltd.](https://www.unity-drive.com) (UDI).
Since the scenarios involve customers' information, 
we cannot provide the raw images for the detection tasks.
We crop the images according to the detection boxes 
and use these regions as the inputs for our classifiers.

We collected a toy dataset with $10$ sequences, a total frame of $1702$ image. 
The first $7$ sequences are collected by 
a Sensing SG2-AR0231C-0202-GMSL-H30S camera, attached to
our autonomous vehicle platform. 
The rest $3$ sequences are captured by a smartphone in Shenzhen, China.
Both devices works at the capture frequency of $10Hz$.
The dataset only contains the countdown timers with double-digit, which means all the image patches have at most 2 digits, on tens and units places respectively.
The dataset into two levels according to scenario settings 
and data collection quality:
* The normal part includes Sequence $01$, $05$, $06$, $08$, $09$, and $10$. The regions of countdown timers are over $40 \times 40$ pixels, and the digits are clear to be recognized.
* The hard part contains Sequence $02$, $03$, $04$, and $07$, and is challenging for the classification task. The countdown timer regions are small since the ego-vehicle is far from the traffic lights. Some pictures are blurred because of lighting or the ego vehicle's motion.

We also simulate the errors of the input bounding boxes. We add random pixel offsets on the detection ground truth, with different magnitudes of 0-pixel, 3-pixel and 5-pixel errors, respectively.

The dataset is in the folder [udi_cttl_dataset](./udi_cttl_dataset/). 
It contains 3 subdirectories, for the input with 0, 3, 5-pixel random offsets.
Each subdirectory has 10 sequences, 
and each sequence folder contains the corresponding image patches 
named by their sequence numbers.
Each sequence folder also contains:
* [classification.txt](./udi_cttl_dataset/0_offset/01/classification.txt), the inputs for our state estimator, derived from our classifiers. The format of each line is (sequence number, color observation, tens place observation, units place observation).
* [gt.txt](./udi_cttl_dataset/0_offset/01/gt.txt), the ground truth of the sequence. The format of each line is (sequence number, color ground truth, number display ground truth).
* [timestamp.txt](./udi_cttl_dataset/0_offset/01/timestamp.txt), the timestamps of the sequence. The format of each line is (sequence number, timestamp).

## State Estimator (C++11)
The state estimator is the core part of this paper. Its input is the color and digit classification sequences from our classifiers. It outputs the optimal estimates of countdown timer traffic light states over time.
This code is in the folder [countdown_timer_estimator](./countdown_timer_estimator/).

1. Environments
    * The code is tested cross different systems, including 
        * Ubuntu 18.04, 64-bit, 16G RAM, Intel Corei5-8600K
        * Ubuntu 20.04, 64-bit, 16G RAM, AMD Ryzen 5 5600X
        * macOS Monterey, 64-bit, 16G RAM, Apple M1 Pro

2. Prerequisites
    * Eigen3, for matrix calculation
    * Protobuf3, for parameter file loading
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
    * The running results are displayed in real time on the terminal.
    * Before runing the sequence, parameter loading information is given.
    ```
    load hsmm parameter from Protobuf...
    proto file filepath: ../config/hsmm_parameter_proto.config
    --------------------------------------------------
    Basic Parameters:
        hz_:10
        interval_:0.1
        res_:0.01
        d_:1
        sigma_:0.1
        max_n_:5
        n_state_:300
        n_obs_:484
        n_d_sample_:13
        alpha_:4
    --------------------------------------------------
    ```
    * When the system is running, the input/output results are given.
    ```
    [Info]: main(): processing...../../udi_cttl_dataset/0_offset/01
    % sequence, timing, ground truth, input from classifiers, output from estimator.
    % The ground truth/input format: <color, tens place, units place>
    % The output format: <color, tens place, units place>, Duration sampling ID
    % null input is marked as [].
    seq:  22391, comsumption:  0.028ms, gt: <    red,  2,  1 >, obz: <    red,  2,  1 >, result: <    red,  2,  1 >, 1
    seq:  22392, comsumption: 51.580ms, gt: <    red,  2,  1 >, obz: <    red,  2,  1 >, result: <    red,  2,  1 >, 2
    seq:  22393, comsumption: 35.075ms, gt: <    red,  2,  1 >, obz: <    red,  2,  1 >, result: <    red,  2,  1 >, 3
    seq:  22394, comsumption: 38.399ms, gt: <    red,  2,  1 >, obz: <    red,  2,  1 >, result: <    red,  2,  1 >, 4
    seq:  22395, comsumption: 36.425ms, gt: <    red,  2,  1 >, obz: <    red,  2,  1 >, result: <    red,  2,  1 >, 5
    seq:  22396, comsumption: 38.370ms, gt: <    red,  2,  0 >, obz: <    red,  2,  0 >, result: <    red,  2,  0 >, 1
    seq:  22397, comsumption: 36.237ms, gt: <    red,  2,  0 >, obz: <    red,  2,  0 >, result: <    red,  2,  0 >, 2
    seq:  22398, comsumption: 38.524ms, gt: <    red,  2,  0 >, obz: <    red,  2,  0 >, result: <    red,  2,  0 >, 3
    seq:  22399, comsumption: 37.595ms, gt: <    red,  2,  0 >, obz: <    red,  2,  0 >, result: <    red,  2,  0 >, 4
    seq:  22400, comsumption: 35.898ms, gt: <    red,  2,  0 >, obz: <    red,  2,  0 >, result: <    red,  2,  0 >, 5
    ...
    ```
    * When finishing a sequence, statistical results are given.
    ```
    Total sequence number: 412
    Classification:
        color: 412/1.000, value: 394/0.956, total: 394/0.956.
        color: 50/1.000, value: 50/1.000, total: 50/1.000.
    Estimation:
        color: 412/1.000, value: 392/0.951, total: 392/0.951.
        color: 50/1.000, value: 50/1.000, total: 50/1.000.
    Color input counting per class:
    201 211   0
    Confusion matrix of color input:
    201   0   0
    0 211   0
    0   0   0
    Digit input counting per class:
    165 239 131  39  39  39  47  47  39  39
    Confusion matrix of digit input:
    164   0   0   0   0   0   1   0   0   0
    0 238   1   0   0   0   0   0   0   0
    0   0 131   0   0   0   0   0   0   0
    0   0   0  39   0   0   0   0   0   0
    0   0   0   0  39   0   0   0   0   0
    0   0   0   0   0  39   0   0   0   0
    0   0   0   0   0   0  47   0   0   0
    0   0   0   0   0   0  16  31   0   0
    0   0   0   0   0   0   0   0  39   0
    0   0   0   0   0   0   0   0   0  39
    Color output counting per class:
    201 211   0
    Confusion matrix of color output:
    201   0   0
    0 211   0
    0   0   0
    Digit output counting per class:
    165 239 131  39  39  39  47  47  39  39
    Confusion matrix of digit output:
    165   0   0   0   0   0   0   0   0   0
    0 239   0   0   0   0   0   0   0   0
    0   0 131   0   0   0   0   0   0   0
    0   0   0  39   0   0   0   0   0   0
    0   0   0   0  39   0   0   0   0   0
    0   0   0   0   0  39   0   0   0   0
    0   0   0   0   0   2  45   0   0   0
    0   0   0   0   0   0  11  29   7   0
    0   0   0   0   0   0   0   0  39   0
    0   0   0   0   0   0   0   0   0  39
    --------------------------------------------------
    ```

## Digit Classifier (Python)
The digit classifier is one of the preceding modules of our state estimator. Its input is the detection region of countdown timers, and it output the digit classes on both tens and units places.
This code is in the folder [digit_classifer](./digit_classifier/).

1. Environments
    * The code is tested cross different systems, including 
        * Ubuntu 18.04, 64-bit, 16G RAM, Intel Corei5-8600K
        * Ubuntu 20.04, 64-bit, 16G RAM, AMD Ryzen 5 5600X
        * macOS Monterey, 64-bit, 16G RAM, Apple M1 Pro

2. Prerequisites
    * numpy
    ```
    pip3 install numpy
    ```
    * torch
    ```
    pip3 install torch
    ```
    * pillow
    ```
    pip3 install pillow
    ```
    * torchvision
    ```
    pip3 install torchvision
    ```
    * opencv
    ```
    pip3 install opencv-python
    ```

## License
The source code is released under MIT license.

