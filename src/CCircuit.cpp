#include <vector>
#include <iostream>
#include <cstdlib>
#include <queue>

#include <stdio.h>
#include <CUnit.h>
#include <CCircuit.h>

using namespace std;

/**
 * @brief Constructs a new Circuit object.
 *
 * This constructor creates a new Circuit object with a specified number of units. 
 * It initializes the 'units' member variable to a vector of 'CUnit' objects of size 'num_units'.
 *
 * @param num_units The number of units in the circuit.
 */
Circuit::Circuit(int num_units){
  this->units.resize(num_units);
  this->num_units = num_units;
  this->next_feed_G.resize(num_units);
  this->next_feed_W.resize(num_units);
}

/**
 * @brief Marks a unit in the circuit and recursively marks connected units.
 *
 * This function marks a unit as visited in the circuit. If the unit has already been marked,
 * the function returns immediately. Otherwise, it marks the unit and then recursively calls
 * itself for each connected unit that is not an outlet of the circuit.
 *
 * @param unit_num The index of the unit to mark.
 */
void Circuit::mark_units(int unit_num) {

  if (this->units[unit_num].mark) return;

  this->units[unit_num].mark = true;

  //If we have seen this unit already exit
  //Mark that we have now seen the unit

  //If conc_num does not point at a circuit outlet recursively call the function
  if (this->units[unit_num].conc_num<this->units.size()) {
    mark_units(this->units[unit_num].conc_num);
  } else {
    //cerr << "Concentrate stream is connected to conc outlet." << endl;
    }
  
  //If inter_num does not point at a circuit outlet recursively call the function
  if (this->units[unit_num].inter_num<this->units.size()) {
    mark_units(this->units[unit_num].inter_num);
  } else {
    //cerr << "Intermediate stream is connected to one outlet." << endl;
  }
  //If tails_num does not point at a circuit outlet recursively call the function 

  if (this->units[unit_num].tails_num<this->units.size()) {
    mark_units(this->units[unit_num].tails_num); 
  } else {
    //cerr << "Tails stream is connected to tails outlet." << endl;
  }
}

/**
 * @brief Checks the validity of a circuit.
 * 
 * This function checks the validity of a circuit based on the connections 
 * specified in the input vector. The vector should contain a sequence of
 * integers representing the connections between units in the circuit. The
 * function performs several checks to ensure that the circuit is valid,
 * including checking for self-recycle, checking that all output streams do
 * not point to the same unit, and checking that all units are reachable from
 * the starting unit. 
 * If the circuit passes all checks, the function returns true; 
 * otherwise, it returns false.
 * 
 * @param vector_size The size of the input vector.
 * @param circuit_vector The input vector containing the connections between units.
*/
bool Circuit::Check_Validity(int vector_size, int *circuit_vector) {
    // Check if the vector size is valid
    if (vector_size < 4 || (vector_size - 1) % 3 != 0) {
        return false;
    }

    int num_units = (vector_size - 1) / 3;  // (10-1)/3 in this example

    // Set up all units' connections
    for (int i = 0; i < (vector_size-1) / 3; ++i) {
        // Add 1 to skip feed unit
        this->units[i].conc_num = circuit_vector[1 + 3 * i];
        this->units[i].inter_num = circuit_vector[1 + 3 * i + 1];
        this->units[i].tails_num = circuit_vector[1 + 3 * i + 2];
        this->units[i].mark = false;

        // Check the range of conc_num, inter_num, and tails_num
        // The range should be [0, num_units] for conc_num and inter_num
        // The range should be [0, num_units + 1] for tails_num, except for the last unit
        if (
          this->units[i].conc_num < 0  || this->units[i].conc_num > num_units||
            this->units[i].inter_num < 0 || this->units[i].inter_num > num_units + 1||
            this->units[i].tails_num < 0 || this->units[i].tails_num > num_units + 1 ||
            this->units[i].tails_num == num_units) {
            return false;
        }
    }

    // Check for self-recycle and all output streams pointing to the same unit
    if (!check_no_self_recycle(this->units) || !check_no_all_same_destination(this->units)) {
        return false;
    }

    // Define outlets (Feed -> unit 0, unit 1, unit 2, ...)// e.g. unit 3 and unit 4 are outlets
    // Check if all units can reach the outlet stream concentrate
    if (!isReachable(num_units, num_units, this->units)) {
        return false;
    }

    // Check if all units can reach the outlet stream tailings
    if (!isReachable(num_units + 1, num_units, this->units)) {
        return false;
    }

    // Mark all units accessible from the starting unit (the feed unit)
    if (circuit_vector[0] < 0 || circuit_vector[0] >= num_units) {
        return false;
    }
    this->mark_units(circuit_vector[0]);

    // Check which units have been marked as visited
    bool all_accessible = true;
    for (int i = 0; i < this->units.size(); i++) {
        if (this->units[i].mark) {
          //cout << "Unit " << i << " is accessible." << endl;
        } else {
          //cout << "Unit " << i << " is not accessible." << endl;
            all_accessible = false;
        }
    }

    // Check if all units are accessible
    if (!all_accessible) {
        return false;
    }

    return true; // If all checks pass, the circuit is valid
}

/**
 * @brief Checks if there is any self-recycle in the circuit.
 *
 * This function checks whether any unit in the circuit has an output that is connected to itself.
 * A unit is considered to have a self-recycle if its concentrate, intermediate, or tailings output
 * is connected to itself.
 *
 * @param units The vector of units in the circuit.
 * @return true if there is no self-recycle in the circuit, false otherwise.
 */
bool Circuit::check_no_self_recycle(const vector<CUnit>& units) {
    for (size_t i = 0; i < units.size(); ++i) {
        if (units[i].conc_num == i || units[i].inter_num == i || units[i].tails_num == i) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Checks if all units in the circuit are reachable from a given start unit.
 *
 * This function uses a breadth-first search algorithm to check whether all units in the circuit
 * are reachable from a given start unit. A unit is considered reachable if there is a path from
 * the start unit to the unit through the connections between units.
 *
 * @param start The index of the start unit.
 * @param num_units The number of units in the circuit.
 * @param units The vector of units in the circuit.
 * @return true if all units are reachable from the start unit, false otherwise.
 */
bool Circuit::isReachable(int start, int num_units, vector<CUnit>& units) {
    vector<bool> reachable(num_units, false);
    queue<int> bfs_queue;
    bfs_queue.push(start);

    while (!bfs_queue.empty()) {
        int current = bfs_queue.front();
        bfs_queue.pop();

        for (int i = 0; i < num_units; ++i) {
            if (!reachable[i]) {
                if ((units[i].conc_num == current) ||
                    (units[i].inter_num == current) ||
                    (units[i].tails_num == current)) {
                    reachable[i] = true;
                    bfs_queue.push(i);
                }
            }
        }
    }

    for (int i = 0; i < num_units; ++i) {
        if (!reachable[i]) {
            //cout << "Unit " << i << " is the first unit that cannot reach outlet stream " << start << "." << endl;
            return false;
        }
    }

    return true;
}

/**
 * @brief Checks if there is any unit in the circuit where all output streams point to the same unit.
 *
 * This function checks whether any unit in the circuit has all its output streams (concentrate, intermediate, 
 * and tailings) pointing to the same unit.
 *
 * @param units The vector of units in the circuit.
 * @return true if there is no unit where all output streams point to the same unit, false otherwise.
 */
bool Circuit::check_no_all_same_destination(const vector<CUnit>& units) {
    for (const auto& unit : units) {
        if ((unit.conc_num == unit.inter_num && unit.inter_num == unit.tails_num) ||
            (unit.conc_num == unit.tails_num)) {
            return false; // Here all output streams point to the same unit
        }
    }
    return true;
}

/**
 * @brief Sets up the connections in the circuit based on the provided array.
 *
 * This function sets up the connections between the units in the circuit based on the provided array.
 * It interprets the first element of the array as the initial index and the rest of the array as
 * triples representing the connections for each unit.
 *
 * @param array The array representing the circuit connections.
 * @param array_size The size of the array.
 */
void  Circuit::setup_connections(int* array, int array_size) {
  // The first element of the vector indicates the starting unit
  this->initial_index = array[0];
  // Process the rest of the vector as conncetion triples
  for (int i = 1; i < array_size; i+=3) {
    int unitIndex = (i - 1) / 3;
    if (unitIndex < num_units){

      // Set the connections based on the vector values
      this->units[unitIndex].conc_num = array[i];
      this->units[unitIndex].inter_num = array[i + 1];
      this->units[unitIndex].tails_num = array[i + 2];

      // Check for special cases where the flow should go to concentrate or tailings
      if(array[i] == this->num_units) {
        //Direct the flow to concentrate
        this->units[unitIndex].conc_num = -1; // -1 indicates that the flow should go to concentrate
      }
      if(array[i] == this->num_units + 1){
        //Direct the flow to tailings
        this->units[unitIndex].conc_num = -2; // -2 indicates that the flow should go to tailings
      }
      if(array[i + 1] == this->num_units){
        //Direct the flow to concentrate
        this->units[unitIndex].inter_num = -1; // -1 indicates that the flow should go to concentrate
      }
      if(array[i + 1] == this->num_units + 1){
        //Direct the flow to tailings
        this->units[unitIndex].inter_num = -2; // -2 indicates that the flow should go to tailings
      }
      if(array[i + 2] == this->num_units){
        //Direct the flow to concentrate
        this->units[unitIndex].tails_num = -1; // -1 indicates that the flow should go to concentrate
      }
      if(array[i + 2] == this->num_units + 1){
        //Direct the flow to tailings
        this->units[unitIndex].tails_num = -2; // -2 indicates that the flow should go to tailings
      }
    }
  }
}

/**
 * @brief Updates the flows in the circuit.
 *
 * This function calculates and updates the flows in the circuit based on the current state of the units.
 * It calculates the output of each unit and updates the feed rates for the next iteration.
 */
void Circuit::update_flows(){
  std::vector<double> next_feed_G(num_units, 0);
  std::vector<double> next_feed_W(num_units, 0);
    
  concentrate_G = 0;
  concentrate_W = 0;
  tails_G = 0;
  tails_W = 0;

  //Calculate every output of the streams and update the next feed
  for (int i = 0; i < this->num_units; ++i){
    CUnit &unit = this->units[i];
    
    if(i == this->initial_index){
      unit.feed_rate_G += 10;
      unit.feed_rate_W += 90;
    }
    double total_feed = unit.feed_rate_G + unit.feed_rate_W;
    unit.Calculate_ResidenceTime(total_feed);

    //Calculate the Output of the unit
    double CG = unit.calculate_CG();
    double CW = unit.calculate_CW();
    double IG = unit.calculate_IG();
    double IW = unit.calculate_IW();
    double TG = unit.calculate_TG();
    double TW = unit.calculate_TW();

    //Update the next feed
    // Concentrate flow
    if(unit.conc_num >=0 && unit.conc_num < num_units){
      next_feed_G[unit.conc_num] += CG;
      next_feed_W[unit.conc_num] += CW;
    } else if (unit.conc_num == -1){ //Concentrate
      concentrate_G += CG;
      concentrate_W += CW;
    } else if (unit.conc_num == -2){ //Tailings
      tails_G += CG;
      tails_W += CW;
    }

    // Intermediate flow
    if(unit.inter_num >=0 && unit.inter_num < num_units){
      next_feed_G[unit.inter_num] += IG;
      next_feed_W[unit.inter_num] += IW;
    } else if (unit.inter_num == -1){ //Concentrate
      concentrate_G += IG;
      concentrate_W += IW;
    } else if (unit.inter_num == -2){ //Tailings
      tails_G += IG;
      tails_W += IW;
    }

    // Tailings flow
    if(unit.tails_num >=0 && unit.tails_num < num_units){
      next_feed_G[unit.tails_num] += TG;
      next_feed_W[unit.tails_num] += TW;
    } else if (unit.tails_num == -1){ //Concentrate
      concentrate_G += TG;
      concentrate_W += TW;
    } else if (unit.tails_num == -2){ //Tailings
      tails_G += TG;
      tails_W += TW;
    }
  }

  //Update all feed_rate_G and feed_rate_W for the next iteration
  for (int i = 0; i < this->num_units; ++i){
    this->units[i].feed_rate_G = next_feed_G[i];
    this->units[i].feed_rate_W = next_feed_W[i];
  }
}
