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
  total_error_ = 0.0;
  // The coefficients are just set to dummy values
  Kp_ = 0.0;
  Ki_ = 0.0;
  Kd_ = 0.0;

  total_num_steps_ = 0;
  initial_ = true;
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  Kp_ = Kp;
  Ki_ = Ki;
  Kd_ = Kd;
}

double PID::Control(double cte) {

  // Update the P, I, and D error terms
  UpdateError(cte);
  total_num_steps_ += 1;

  // Compute the steering angle and return it.
  // Limit the steering angle to be within [-1,1].
  return max(-1.0, min(1.0, -Kp_ * p_error_ - Ki_ * i_error_ - Kd_ * d_error_));
}

void PID::UpdateError(double cte) {

  if(initial_) {
    p_error_ = cte;
    i_error_ += cte;
    d_error_ = 0.0;
    total_error_ += cte * cte;
    initial_ = false;
    //std::cout << "First time!" << std::endl;
    //std::cout << "p_error_: " << p_error_ << "\t" << "i_error_: " << i_error_ << "\t" << "d_error_: " << d_error_ << std::endl;
  } else {
    i_error_ += cte;
    d_error_ = cte - p_error_;
    p_error_ = cte;
    total_error_ += cte * cte;
    //std::cout << "p_error_: " << p_error_ << "\t" << "i_error_: " << i_error_ << "\t" << "d_error_: " << d_error_ << std::endl;
  }

}

void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  // Reset the errors
  p_error_ = 0.0;
  i_error_ = 0.0;
  d_error_ = 0.0;
  // Reset the simulator
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

int PID::TotalSteps() {
  return total_num_steps_;
}

double PID::TotalError() {
  return total_error_;
}

