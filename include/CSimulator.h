/** header file for the circuit simulator
 * 
 * This header file defines the function that will be used to evaluate the circuit
*/

#pragma once
#include <string>

struct Circuit_Parameters{
    double tolerance;
    int max_iterations;
    // other parameters for your circuit simulator       
};
struct Unit_parameter{
  double tau;
  double CG;
  double CW;
  double IG;
  double IW;
  double TG;
  double TW;
  double RHG;
  double RHW;
  double RIG;
  double RIW;
};

double Evaluate_Circuit(int vector_size, int *circuit_vector, struct Circuit_Parameters parameters);
double Evaluate_Circuit(int vector_size, int *circuit_vector);
double Evaluate_Circuit_Recovery(int vector_size, int* circuit_vector);
double Evaluate_Circuit_Grade(int vector_size, int* circuit_vector);
void Evaluate_Circuit_Cell_Calculator(struct Unit_parameter &parameters);
void Save_ResultToTxt(const std::string& filename, int vector_size, int* circuit_vector, double performance, double recovery, double grade);