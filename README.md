# PID Controller
This is a simple PID controller implementation in C++. The program is for use with the simulator linked below.

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets): Handles the communication between the program and the simulator.
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x.
* The simulator which you can download from [here](https://github.com/udacity/self-driving-car-sim/releases).

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`.

## The PID Components

The controller computes scalar control commands using an observed scalar error based on the following three additive components:

1. The proportional (P) component: Acts proportionally to the observed error value, i.e. the larger the error value, the larger the absolute control command value.
2. The integral (I) component: Acts using the sum of all past observed errors, i.e. the greater the imbalance between negative and positive past observed errors, the larger the absolute control command value.
3. The differential (D) component: Acts using the change rate of the error, i.e. the more the error changes between the last and the current time step, the larger the absolute control command value.

## The PID Coefficients for the steering controller

The strength of the influence of each of the three components on the control command value (the steering angle in this case) is determined by its respective coefficient.

I tuned the coefficients manually according to the following reasoning and trial and error.

### Initial coefficient values

1. P-coefficient: The cross-track error is measured in meters and the maximum absolute steering value is 1. Using the heuristic that a deviation from the target path by 3 meters (which is a large deviation given the width of a normal lane) should result in a rather strong steering value of 0.6, I used an initial value of 0.2 for this coefficient.
2. I-coefficient: Since the cross-track error is measured every 0.1 seconds, the integral error can get large very quickly. I started out with a somewhat arbitrary value of 0.0001 for this coefficient.
3. D-coefficient: The change in the error within 0.1 seconds will be small in most situations, therefore I somewhat arbitrarily chose the initial value to be 10 times the P-coefficient to 2.0.

### Tuning and final values

The initial coefficient values worked sufficiently well, but the car constantly slightly overshot the target path and the car corrected back to the target path to drastically.

In order to get the car to convert back to the target path more smoothly, I gradually decreased the proportional coefficient.

In order to reduce the overshooting, I gradually increased the differential coefficient.

Of course not only the the absolute P- and D-coefficients matter, but also their relation. I ended up with a P-coefficient of 0.08 and a D-coefficient of 2.5, i.e. with the differential component over 30 times larger than the proportional component. Increasing the integral coefficient by a factor of 10 to 0.001 had a minor effect.

The coefficients chosen above lead to a satisfactorily smooth behavior in the simulator, however, a to-do and next step is to fine-tune the coefficients systematically using an optimization algorithm.

## The PID Coefficients for the throttle controller

For the throttle controller I used the same initial coefficients as for the steering controller and didn't experiment much with them afterwards. The car seems to accelerate and decelerate in a sensical way.
