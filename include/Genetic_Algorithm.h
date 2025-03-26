/** Header for the Genetic Algorithm library
 *
*/

#pragma once
#include <vector>

#include "CCircuit.h"

using namespace std;

struct Algorithm_Parameters{
    int max_iterations;
    // other parameters for your algorithm
    int population_size;
    double cross_probability;
    double mutation_rate;   
    int stall_length;
    double stall_mutation_rate;
    double cross_stall_rate;    
};

#define DEFAULT_ALGORITHM_PARAMETERS Algorithm_Parameters{10000, 2000, 0.9, 0.015, 10, 0.7, 0.2}

bool all_true(int vector_size, int * vector);

int optimize(int vector_size, int * vector,
                double (&func) (int, int*),
                bool (&validity) (int, int*)=all_true,
                struct Algorithm_Parameters parameters=DEFAULT_ALGORITHM_PARAMETERS
                );

// Other functions and variables


// generating the initial population, where each individual is a vector of integers
vector<vector<int>> generate_population(int vector_size, Circuit circuit, struct Algorithm_Parameters parameters=DEFAULT_ALGORITHM_PARAMETERS);

// parent selector
pair<int, int> select_parents(vector<double> fitness, struct Algorithm_Parameters parameters=DEFAULT_ALGORITHM_PARAMETERS);

// evaluate parents returns vector of doubles
vector<double> evaluate_parents(vector<vector<int>> parents, vector<int> &current_best, int &best_index, double (&func) (int, int*));


// child generator
int generate_children(bool stalled, vector<vector<int>> &new_population, vector<int> parent1, vector<int> parent2, Circuit circuit, Algorithm_Parameters parameters=DEFAULT_ALGORITHM_PARAMETERS);
// crossover
vector<vector<int>> crossover(vector<int> parent1, vector<int> parent2, string type, struct Algorithm_Parameters parameters=DEFAULT_ALGORITHM_PARAMETERS);

//crossover helper functions
pair<vector<int>, vector<int>> uniform_cross(vector<int> parent1, vector<int> parent2);
pair<vector<int>, vector<int>> one_point_cross(vector<int> parent1, vector<int> parent2);
pair<vector<int>, vector<int>> two_point_cross(vector<int> parent1, vector<int> parent2);
pair<vector<int>, vector<int>> multipoint_cross(vector<int> parent1, vector<int> parent2);

vector<int> substitution(vector<int> child, double mutation_rate);
vector<int> inversion(vector<int> child, double mutation_rate);
vector<int> value_adjustment(vector<int> child, double mutation_rate);

// mutation
vector<int> mutate(bool stalled, vector<int> child, double mutation_rate, double stall_mutation_rate);