#include "PID.h"

#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->i_error = 0;
  this->p_error = 0;
  this->d_error = 0;
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
}

void PID::UpdateError(double cte) {
  const double last_error = p_error;
  p_error = cte;
  i_error += cte;
  d_error = cte - last_error;
}

double PID::TotalError() {
  const double p_term = Kp * p_error;
  const double i_term = Ki * i_error;
  const double d_term = Kd * d_error;
  const double sum = p_error + i_error + d_error;
  const double total = p_term + i_term + d_term;

  return total;
}

