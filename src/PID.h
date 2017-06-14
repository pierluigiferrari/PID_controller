#ifndef PID_H
#define PID_H

#include <uWS/uWS.h>

class PID {
public:
  /*
  * Errors
  */
  double p_error_;
  double i_error_;
  double d_error_;

  // Store the total squared cross-track error accumulated since initialization of the controller
  double total_error_;

  // The total number of steering commands since initialization of the controller
  int total_num_steps_;

  /*
  * Coefficients
  */ 
  double Kp_;
  double Ki_;
  double Kd_;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  double Control(double cte);

  void Restart(uWS::WebSocket<uWS::SERVER> ws);

  /*
  * Return the total squared cross-track error since initialization of the controller.
  */
  double TotalError();

  /*
   * Return the total number of steps since initialization of the controller.
   */
  int TotalSteps();

private:

  // True if this PID object has not received a CTE before.
  bool initial_;
};

#endif /* PID_H */
