#include "CUnit.h"
#include "CCircuit.h"
#include "CSimulator.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>

// Default parameters for circuit evaluation
struct Circuit_Parameters default_circuit_parameters = {1e-6, 1000};

// Dummy answer vector for testing
int dummy_answer_vector[] = {0, 1, 2, 2, 3, 4, 2, 1, 4, 4, 5, 4, 4, 1, 2, 6};

/**
 * @brief Evaluates the performance of a circuit based on the provided circuit vector and parameters.
 * 
 * This function takes a circuit vector and returns a performance value. The performance is calculated
 * based on the concentrate and waste streams. The function runs for a specified number of iterations or
 * until the change in performance is below the tolerance threshold.
 * 
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector The vector representing the circuit.
 * @param parameters The parameters for the circuit evaluation.
 * @return double The performance value of the circuit.
 */
double Evaluate_Circuit(int vector_size, int* circuit_vector, struct Circuit_Parameters parameters) {
  int Unit_Size = int(vector_size-1) / 3;
  Circuit circuit(Unit_Size);
  circuit.setup_connections(circuit_vector, vector_size);
 
  double Performance = 0;
 
  for (int i = 0; i < parameters.max_iterations; i++) {
    double total_concentrate = circuit.concentrate_G + circuit.concentrate_W;
    circuit.update_flows();
    double new_total_concentrate = circuit.concentrate_G + circuit.concentrate_W;
 
    Performance = circuit.concentrate_G*100 - circuit.concentrate_W*300;
 
    if (new_total_concentrate != total_concentrate) {
      double difference = new_total_concentrate - total_concentrate;
 
      if (difference <= parameters.tolerance){
 
        return Performance;
        break;
      }
    }
  }
  return -67500.0;
}

/**
 * @brief Evaluates the recovery of a circuit based on the provided circuit vector and parameters.
 * 
 * This function takes a circuit vector and returns a recovery value. The recovery is calculated
 * based on the concentrate stream. The function runs for a specified number of iterations or
 * until the change in recovery is below the tolerance threshold.
 * 
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector The vector representing the circuit.
 * @param parameters The parameters for the circuit evaluation.
 * @return double The recovery value of the circuit.
 */
double Evaluate_Circuit_Recovery(int vector_size, int* circuit_vector, struct Circuit_Parameters parameters) {
  int Unit_Size = int(vector_size-1) / 3;
  Circuit circuit(Unit_Size);
  circuit.setup_connections(circuit_vector, vector_size);
 
  double Recovery = 0;
 
  for (int i = 0; i < parameters.max_iterations; i++) {
    double total_concentrate = circuit.concentrate_G + circuit.concentrate_W;
    circuit.update_flows();
    double new_total_concentrate = circuit.concentrate_G + circuit.concentrate_W;
    Recovery = circuit.concentrate_G/10;
    if (new_total_concentrate != total_concentrate) {
      double difference = new_total_concentrate - total_concentrate;
      if (difference < parameters.tolerance){
        return Recovery;
        break;
      }
    }
  }
  return Recovery;
}

/**
 * @brief Evaluates the grade of a circuit based on the provided circuit vector and parameters.
 * 
 * This function takes a circuit vector and returns a grade value. The grade is calculated
 * based on the concentrate and waste streams. The function runs for a specified number of iterations or
 * until the change in grade is below the tolerance threshold.
 * 
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector The vector representing the circuit.
 * @param parameters The parameters for the circuit evaluation.
 * @return double The grade value of the circuit.
 */
double Evaluate_Circuit_Grade(int vector_size, int* circuit_vector, struct Circuit_Parameters parameters) {
  int Unit_Size = int(vector_size-1) / 3;
  Circuit circuit(Unit_Size);
  circuit.setup_connections(circuit_vector, vector_size);
 
  double Grade = 0;
 
  for (int i = 0; i < parameters.max_iterations; i++) {
    double total_concentrate = circuit.concentrate_G + circuit.concentrate_W;
    circuit.update_flows();
    double new_total_concentrate = circuit.concentrate_G + circuit.concentrate_W;
    Grade = circuit.concentrate_G / (circuit.concentrate_W+ circuit.concentrate_G);
    if (new_total_concentrate != total_concentrate) {
      double difference = new_total_concentrate - total_concentrate;
      if (difference < parameters.tolerance){
        return Grade;
        break;
      }
    }
  }
  return Grade;
}

/**
 * @brief Calculates the parameters of a single unit in the circuit.
 * 
 * This function calculates various parameters of a single unit in the circuit, including
 * residence time, concentrate and waste flows, and recovery values for different grades.
 * The results are stored in the provided parameters structure.
 * 
 * @param parameters A reference to a Unit_parameter structure to store the calculated values.
 */
void Evaluate_Circuit_Cell_Calculator(Unit_parameter &parameters) {
  CUnit unit;
  unit.feed_rate_G = 10;
  unit.feed_rate_W = 90;
  double total_feed = unit.feed_rate_G+unit.feed_rate_W;
  unit.Calculate_ResidenceTime(total_feed);
  parameters.tau = unit.residence_time;
  parameters.CG = unit.calculate_CG();
  parameters.CW = unit.calculate_CW();
  parameters.IG = unit.calculate_IG();
  parameters.IW = unit.calculate_IW();
  parameters.TG = unit.calculate_TG();
  parameters.TW = unit.calculate_TW();
  parameters.RHG = unit.Calculate_RHG();
  parameters.RHW = unit.Calculate_RHW();
  parameters.RIG = unit.Calculate_RIG();
  parameters.RIW = unit.Calculate_RIW();
}

/**
 * @brief Saves the evaluation results to a text file.
 * 
 * This function writes the input circuit vector and the calculated performance, recovery, 
 * and grade values to a text file with the specified filename.
 * 
 * @param filename The name of the file to save the results to.
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector The vector representing the circuit.
 * @param performance The performance value of the circuit.
 * @param recovery The recovery value of the circuit.
 * @param grade The grade value of the circuit.
 */
void Save_ResultToTxt(const std::string& filename, int vector_size, int* circuit_vector, double performance, double recovery, double grade){
  std::ofstream out_file(filename, std::ios::out); // Open the file for writing

  if (!out_file) {
    std::cerr << "Error opening file"<< filename << std::endl;
    return;
  }

  // Write the input vector to the file
  out_file << "Input vector: ";
  for (int i = 0; i < vector_size; i++) {
    out_file << circuit_vector[i] << " ";
  }
  out_file << std::endl;

  // Write the performance, recovery, and grade to the file
  out_file << "Performance: " << performance << std::endl;
  out_file << "Recovery: " << recovery << std::endl;
  out_file << "Grade: " << grade << std::endl;

  out_file.close(); // Close the file
}

// Overloaded functions using default circuit parameters

/**
 * @brief Evaluates the performance of a circuit using default parameters.
 * 
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector The vector representing the circuit.
 * @return double The performance value of the circuit.
 */
double Evaluate_Circuit(int vector_size, int* circuit_vector){
    return Evaluate_Circuit(vector_size, circuit_vector, default_circuit_parameters);
};

/**
 * @brief Evaluates the recovery of a circuit using default parameters.
 * 
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector The vector representing the circuit.
 * @return double The recovery value of the circuit.
 */
double Evaluate_Circuit_Recovery(int vector_size, int* circuit_vector){
    return Evaluate_Circuit_Recovery(vector_size, circuit_vector, default_circuit_parameters);
};

/**
 * @brief Evaluates the grade of a circuit using default parameters.
 * 
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector The vector representing the circuit.
 * @return double The grade value of the circuit.
 */
double Evaluate_Circuit_Grade(int vector_size, int* circuit_vector){
    return Evaluate_Circuit_Grade(vector_size, circuit_vector, default_circuit_parameters);
};
