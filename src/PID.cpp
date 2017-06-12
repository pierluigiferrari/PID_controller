#include <iostream>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
  p_error_ = 0.0;
  i_error_ = 0.0;
  d_error_ = 0.0;
  // The coefficients are just set to dummy values
  Kp_ = 0.0;
  Ki_ = 0.0;
  Kd_ = 0.0;

  initial_ = true;
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  Kp_ = Kp;
  Ki_ = Ki;
  Kd_ = Kd;
}

double PID::SteeringAngle(double cte) {

  // Update the P, I, and D error terms
  UpdateError(cte);

  // Compute the steering angle and return it.
  // Limit the steering angle to be within [-1,1].
  return max(-1.0, min(1.0, -Kp_ * p_error_ - Ki_ * i_error_ - Kd_ * d_error_));
}

void PID::UpdateError(double cte) {

  if(initial_) {
    p_error_ = cte;
    i_error_ += cte;
    d_error_ = 0.0;
    initial_ = false;
    //std::cout << "First time!" << std::endl;
    //std::cout << "p_error_: " << p_error_ << "\t" << "i_error_: " << i_error_ << "\t" << "d_error_: " << d_error_ << std::endl;
  } else {
    i_error_ += cte;
    d_error_ = cte - p_error_;
    p_error_ = cte;
    //std::cout << "p_error_: " << p_error_ << "\t" << "i_error_: " << i_error_ << "\t" << "d_error_: " << d_error_ << std::endl;
  }

}

double PID::TotalError() {
}

