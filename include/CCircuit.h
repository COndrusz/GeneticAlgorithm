/** Header for the circuit class
 *
 * This header defines the circuit class and its associated functions
 *
*/

#pragma once

#include "CUnit.h"

#include <vector>

using namespace std;

class Circuit {
  public:
    Circuit(int num_units); // Constructor
    bool Check_Validity(int vector_size, int *circuit_vector);  // Check the validity of the circuit
    void setup_connections(int* array, int array_size);
    void update_flows();
    int initial_index;
    double concentrate_G = 0;
    double concentrate_W = 0;
    double tails_G = 0;
    double tails_W = 0;
    std::vector<double> next_feed_G;
    std::vector<double> next_feed_W;
    int count = 0;

  private:
    int num_units;
    void mark_units(int unit_num);  // Mark the units
    std::vector<CUnit> units;  // Vector of CUnit objects

    static bool isReachable(int start, int num_units, vector<CUnit>& units);  // Check if the unit is reachable
    static bool check_no_self_recycle(const vector<CUnit>& units);  // Check if there is no self-recycle
    static bool check_no_all_same_destination(const vector<CUnit>& units);  // Check if there is no all same destination
};