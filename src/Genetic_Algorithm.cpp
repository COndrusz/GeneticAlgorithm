#include <stdio.h>
#include <cmath>
#include <array>
//#include <omp.h>

#include <chrono>

#include <iostream>
#include <algorithm>

#include <fstream>
#include <filesystem>

#include "Genetic_Algorithm.h"
#include "CSimulator.h"
#include "CCircuit.h"



int max_value = 0;

/**
 * @brief Output the best value of each generation to a file.
 *
 * This function writes the best value of each generation to a file. The file is saved in the data folder and is named output.csv.
 * 
 *
 * @param filename The name of the file to write the output to.
 * @param generation_list A list of the generation numbers.
 * @param best_values_list A list of the best values of each generation.
 */
// write the output to a file
void write_output(const string &filename, vector<int> generation_list, vector<double> best_values_list)
{
  // Create the data folder if it doesn't exist

  filesystem::create_directory("data");

  // Open the file in the data folder
  ofstream file("../data/" + filename);

  // Check if the file is open
  if (!file.is_open()) {
      cerr << "Failed to open file for writing." << std::endl;
      return;
  }

  // Write the header
  file << "Generation,Best Value\n";

  // Write the data
  for (size_t i = 0; i < generation_list.size(); ++i) {
      cout << generation_list[i] << "," << best_values_list[i] << "\n";
      file << generation_list[i] << "," << best_values_list[i] << "\n";
  }

  // Close the file
  file.close();

  // Confirm that the file has been written
  cout << "Output written to data/" << filename << std::endl;
}

bool all_true(int vector_size, int * vector) {
  return true;
}
/**
 * @brief Optimizes an input vector using a genetic algorithm based on a fitness function and validity checks.
 *
 * This function simulates a genetic algorithm process to find the optimal vectore to maximize a given function. It generates an initial population,
 * evaluates fitness, selects parents, generates children, and mutates them across several generations until the maximum number
 * of iterations is reached or improvement stalls. The final best solution found replaces the original input vector.
 *
 * @param vector_size Size of the input vector.
 * @param input_vector Pointer to the input vector that will be optimized.
 * @param func A function that evaluates the fitness of the vector.
 * @param validity A function that checks the validity of the vector.
 * @param parameters Struct containing parameters for the genetic algorithm (e.g., population size, mutation rate).
 * @return int Returns 0 if the optimization completes before reaching the maximum iteration limit, 1 otherwise.
 */
int optimize(int vector_size, int * input_vector, double (&func) (int, int*),
                           bool (&validity) (int, int*),
                           struct Algorithm_Parameters parameters) {
  // Initializing variables                        
  vector<vector<int>> population;
  vector<vector<int>> new_population;
  vector<int> current_best;
  pair<int, int> parent_pair;
  vector<double> fitness;
  bool stalled = false;
  

  // lists used for output generation
  vector<int> generation_list;
  vector<double> best_values_list;
  

  Circuit circuit = Circuit((vector_size-1) / 3);
  // calculate the maximum value
  max_value = (vector_size -1)/3 + 2;
  // cout << "max_value" << max_value<< endl;
  
  /*
  cout << "printing the vector" << endl;
  for (int i = 0; i < vector_size; ++i) {
      cout << input_vector[i] << " ";
  }
  cout << endl;
  */

  //cout << "Started optimizing" << endl;
  // Generate the initial population 
  auto start = std::chrono::high_resolution_clock::now();
  population = generate_population(vector_size, circuit, parameters);
  auto end = chrono::high_resolution_clock::now();
  
  double old_best_value = func(vector_size, input_vector);;
  double new_best_value = func(vector_size, input_vector);

  chrono::duration<double> elapsed_seconds = end-start;
  cout << "Time to generate population: " << elapsed_seconds.count() << "s\n";


  int current_generation = 0;
  int stall_count = 0;
  start = chrono::high_resolution_clock::now();
  do
  { 
    // Run the genetic algorithm process
    int best_index = 0;
    // Calculate the fitness of the parents to use in the selection of parents
    fitness = evaluate_parents(population, current_best, best_index, func);
    for (int child_count = 0; child_count < parameters.population_size;)
    {
      // select a pair of parent and create children based on them
      // only add valid children to the new population
      parent_pair = select_parents(fitness, parameters);
      int children = generate_children(stalled, new_population, population[parent_pair.first], population[parent_pair.second], circuit, parameters);
      child_count += children;
    }
    // Add the best vector from the previous generation to the new generation unaltered
    new_population.push_back(current_best);

    // check if the new best value is better than the previous best and swap if it is
    // if not add to the stall count
    double value = func(current_best.size(), current_best.data());
    cout << "\rGeneration " << current_generation << " best value " << value << flush;
    if (value > new_best_value)
    {
      new_best_value = value;
      stall_count = 0;
      stalled=false;
      //generation_list.push_back(current_generation);
      //best_values_list.push_back(new_best_value);
    }else
    {stall_count++;}
    // change new and old population and clear new population for the next cycle
    population.swap(new_population);
    new_population.clear();
    // check if the calculation has stalled
    if (stall_count >= parameters.stall_length){
      stalled = true;
    }
  }

  while (parameters.max_iterations > current_generation++ && stall_count < 250);
  cout << endl;
  end = std::chrono::high_resolution_clock::now();
  generation_list.push_back(current_generation);
  best_values_list.push_back(new_best_value);

  elapsed_seconds = end-start;
  std::cout << "Time to run simulation: " << elapsed_seconds.count() << "s\n";
  
  

  // Update the vector with the best solution found
  for (int i = 0; i < current_best.size(); i++)
    input_vector[i] = current_best[i];

  cout << "Output vector" << endl;
  for (int i = 0; i < current_best.size(); i++)
    cout << input_vector[i] << " ";
  cout << endl;
  
  double final_value = func(vector_size, input_vector);
  cerr << "Final score " << final_value << endl;


  // write_output("genetic_crossover_rate_.csv", generation_list, best_values_list);
  //write_output("genetic_cross_type_multipoint.csv", generation_list, best_values_list);


  if (current_generation >= parameters.max_iterations)
    return 1;

  return 0;

}

/**
 * @brief Generates the initial population of vectors for the genetic algorithm.
 *
 * Initializes the population for the genetic algorithm. Each vector within the population is generated to meet
 * specific validity criteria as determined by the circuit validity function. Random values are assigned to each element
 * of the vector except the first, which is set to zero. There is an additional check to ensure that no unit is looping
 * back on itself
 *
 * @param vector_size The size of vectors in the population.
 * @param circuit An instance of the Circuit class used for validating the vectors.
 * @param parameters The parameters of the genetic algorithm including population size.
 * @return vector<vector<int>> Returns a population of valid vectors.
 */
vector<vector<int>> generate_population(int vector_size, Circuit circuit, Algorithm_Parameters parameters)
{
  vector<vector<int>> population(parameters.population_size);
  bool condition = false;
  int pop_size = 0;
  // add vectors to the population until the desired size is reached
  for (int i = 0; i < parameters.population_size; i++)
  {
    vector<int> individual;
    do
    {
      individual = vector<int>(vector_size);
      // start with each circuit feeding into 0
      individual[0] = 0;
      // give all other connections random values
      for (int j = 1; j < vector_size; j++)
      {
        int value = (rand() % max_value);
        if (value != (j-1)/3)
        {
          individual[j] = value;
        } else
        {
          individual[j] = (value +1) % max_value;
        }
      }
      // check that the generated circuit is valid
      condition = circuit.Check_Validity(individual.size(), individual.data());
    } while (!condition);

    population[i] = individual;
  }
  return population;
}

/**
 * @brief Selects a parent index for breeding based on a weighted probability distribution of fitness scores.
 *
 * This function uses the fitness scores of each vector in the population to determine the likelihood of each vector
 * being selected as a parent. The method involves computing a cumulative distribution of fitness scores, then selecting
 * a parent based on random sampling from this distribution. The function ensures that vectors with higher fitness
 * have a higher chance of being selected, promoting the propagation of favorable genes.
 *
 * @param sum_of_fitness The sum of all fitness scores in the current population, used to normalize the probabilities.
 * @param fitness A vector of doubles representing the fitness scores of each individual vector in the population.
 * @return int Returns the index of the selected parent vector based on the weighted fitness probability.
 */
int weighted_parent(double sum_of_fitness, vector<double> fitness)
{
  // get an index using the weighted fitness of each vector
  int rnd = rand() % fitness.size();
  for (int i = 0; i < fitness.size(); i++)
    if(rnd < fitness[i])
    {
      return i;
    }

  return rnd;
}

/**
 * @brief Selects pairs of parent vectors for breeding based on their fitness scores.
 *
 * This function uses a weighted probability method to select two parents from the current population. 
 * The fitness of each vector influences its likelihood of being chosen as a parent.
 *
 * @param fitness A vector of doubles representing the fitness of each vector in the population.
 * @param parameters Struct containing parameters for the genetic algorithm, including selection details.
 * @return pair<int, int> Returns a pair of indices representing the selected parents from the population.
 */
pair<int, int> select_parents(vector<double> fitness, struct Algorithm_Parameters parameters)
{
  // choose two parents to potentially crossover
  int new_generation_size = 0;
  double sum_of_fitness = 0;
  for (int i = 0; i < fitness.size(); i++)
    sum_of_fitness += fitness[i];

  // Return the selected parents
  return make_pair(weighted_parent(sum_of_fitness, fitness), weighted_parent(sum_of_fitness, fitness));
}

/**
 * @brief Evaluates the fitness of each vector in the current population and identifies the best one.
 *
 * The function calculates the fitness for each vector in the population using a provided fitness function.
 * It updates the best vector found in the current generation based on the highest fitness score.
 *
 * @param parents A reference to the vector of parent vectors.
 * @param current_best A reference to the vector which will store the best vector of the current generation.
 * @param best_index A reference to an integer to store the index of the best vector.
 * @param func A function pointer to the fitness function used to evaluate vectors.
 * @return vector<double> Returns a vector of fitness scores corresponding to each parent vector.
 */
vector<double> evaluate_parents(vector<vector<int>> parents, vector<int> &current_best, int &best_index, double (&func) (int, int*))
{
  double current_value = 0;
  vector<double> fitness(parents.size());
  // evaluate the fitness of all vectors in the current generation
  #pragma omp parallel for private(current_value) schedule(dynamic)
  for (int i = 0; i < parents.size(); i++)
  {
    current_value = func(parents[i].size(), parents[i].data());
    fitness[i] = current_value;
  }
  // find the index and corresponding vector that have the highest fitness
  
  best_index = distance(fitness.begin(), max_element(fitness.begin(), fitness.end()));
  current_best = parents[best_index];
  
  return fitness;
}

/**
 * @brief Mutates a vector based on a mutation rate, with increased mutation rates if improvements have stalled.
 *
 * This function applies mutations to a vector, potentially altering its elements to explore new genetic combinations.
 * The type and intensity of mutations may increase if progress towards optimization has stalled. Note it is possible for
 * more than one mutation to take place on the same vector.
 *
 * @param stalled Boolean flag indicating whether the optimization has stalled.
 * @param child The vector to mutate.
 * @param mutation_rate The base rate of mutation.
 * @param stall_mutation_rate The increased mutation rate to apply if stalled.
 * @return vector<int> Returns the mutated vector.
 */

vector<int> mutate(bool stalled, vector<int> child, double mutation_rate, double stall_mutation_rate)
{
  // make mutations more aggressive if the improvement has stalled
  if (stalled){
    mutation_rate = stall_mutation_rate;
  }
  // substitution
  if (mutation_rate > (rand() % 1000) / 1000.0)
  {
    // substitute a random gene with a random value
    int mutation_index = rand() % child.size();
    child[mutation_index] = rand() % max_value;
  }
  // inversion
  if (mutation_rate > (rand() % 1000) / 1000.0)
  {
    // take a section of the child and invert it
    int mutation_index = rand() % (child.size()/2);
    int inversion_size =  rand() % (child.size()-mutation_index);
    reverse(child.begin() + mutation_index, child.begin() + mutation_index + inversion_size);
  }
  // value adjustment
  if (mutation_rate > (rand() % 1000) / 1000.0)
  {
    int mutation_index = rand() % child.size();
    int mutation_size = rand() % (child.size()-mutation_index);
    // add 1 to a section of the vector
    for (int i =0; i<mutation_size; i++)
    {
      int index = (mutation_index + i) % child.size();
      child[index] = (child[index] + 1) %max_value;
    }
  }
  // value adjustment down
  if (mutation_rate > (rand() % 1000) / 1000.0)
  {
    int mutation_index = rand() % child.size();
    int mutation_size = rand() % (child.size()-mutation_index);
    // subtract 1 from a section of the vector
    for (int i =0; i<mutation_size; i++)
    {
      int index = (mutation_index + i) % child.size();
      child[index] = (child[index] - 1) %max_value;
    }
  }

  return child;
}
/**
 * @brief Generates children from selected parent vectors, applying crossover and mutation operations.
 *
 * This function performs crossover and mutation to generate new vectors from the selected parents. 
 * It further ensures that only valid vectors are added to the new population.
 *
 * @param stalled Boolean flag indicating whether the optimization has stalled.
 * @param new_population Reference to the vector that will hold the new population.
 * @param parent1 First parent vector.
 * @param parent2 Second parent vector.
 * @param circuit An instance of the Circuit class used for validating the vectors.
 * @param parameters The parameters of the genetic algorithm, including crossover probability and mutation rates.
 * @return int The number of valid children added to the new population.
 */
int generate_children(bool stalled, vector<vector<int>> &new_population, vector<int> parent1, vector<int> parent2, Circuit circuit, Algorithm_Parameters parameters)
{
  double crossover_rate = parameters.cross_probability;
  if (stalled){
    crossover_rate = parameters.cross_stall_rate;
  }
  int count = 0;
  // Decide if parents crossover and create new vectors before applying mutations
  // only add valid circuits to the new generation
  if (crossover_rate > (rand() % 100) / 100.0)
  {
    vector<vector<int>> children = crossover(parent1, parent2, "multipoint", parameters);
    for (auto child : children)
    {
      child = mutate(stalled, child, parameters.mutation_rate, parameters.stall_mutation_rate);
      if (circuit.Check_Validity(child.size(), child.data()))
      {
        new_population.push_back(child);
        count++;
      }
    }
  }
  else
  {
    parent1 = mutate(stalled, parent1, parameters.mutation_rate, parameters.stall_mutation_rate);
    if (circuit.Check_Validity(parent1.size(), parent1.data()))
      {
        new_population.push_back(parent1);
        count++;
      }
    parent2 = mutate(stalled, parent2, parameters.mutation_rate, parameters.stall_mutation_rate);
    if (circuit.Check_Validity(parent2.size(), parent2.data()))
      {
        new_population.push_back(parent2);
        count++;
      }
  }
  return count;
}
/**
 * @brief Performs genetic crossover between two parent vectors based on a specified type or randomly selects a crossover type.
 *
 * This function chooses a crossover strategy (uniform, one-point, two-point, or multipoint) to combine genetic material
 * from two parent vectors. The choice of crossover strategy can be specified or randomly determined, affecting how segments
 * of the parents' vectors are mixed to produce new child vectors.
 *
 * @param parent1 The first parent vector from which genetic material is taken.
 * @param parent2 The second parent vector from which genetic material is taken.
 * @param type A string specifying the type of crossover; if "random", a method is randomly selected.
 * @param parameters Struct containing parameters for the genetic algorithm, influencing how crossover is performed.
 * @return vector<vector<int>> Returns two new child vectors resulting from the crossover operation.
 */
vector<vector<int>> crossover(vector<int> parent1, vector<int> parent2, string type, Algorithm_Parameters parameters)
{
  pair<vector<int>, vector<int>> new_children;

  // if the type is random, select a random crossover function, otherwise select the type that was given
  if (type == "random")
  {
    int random = rand() % 4;
    if (random == 0)
      new_children = uniform_cross(parent1, parent2);
    else if (random == 1)
      new_children = one_point_cross(parent1, parent2);
    else if (random == 2)
      new_children = two_point_cross(parent1, parent2);
    else
      new_children = multipoint_cross(parent1, parent2);
  }
  else if (type == "one_point")
    new_children = one_point_cross(parent1, parent2);
  else if (type == "two_point")
    new_children = two_point_cross(parent1, parent2);
  else if (type == "multipoint")
    new_children = multipoint_cross(parent1, parent2);
  else if (type == "uniform")
    new_children = uniform_cross(parent1, parent2);

  // return child1 and child2 in a vector
  vector<vector<int>> children = vector<vector<int>>{new_children.first, new_children.second};
  
  return children;
}
/**
 * @brief Performs a uniform crossover between two parent vectors, randomly exchanging genes.
 *
 * In uniform crossover, each gene (vector element) from the parents has a 50% chance of being swapped. This method
 * provides a high degree of mixing and can generate highly varied offspring. Each gene is considered independently,
 * making it possible to achieve diverse genetic combinations.
 *
 * @param parent1 First parent vector for crossover.
 * @param parent2 Second parent vector for crossover.
 * @return pair<vector<int>, vector<int>> Returns a pair of child vectors, each containing mixed genes from both parents.
 */
pair<vector<int>, vector<int>> uniform_cross(vector<int> parent1, vector<int> parent2)
{
  // uniform, take two from one, two from other until end
  // actually just takes one from parent1 and one from parent2 till the end
  // vice verca for the second child
  vector<int> child1(parent1.size());
  vector<int> child2(parent2.size());

  for (int i = 1; i <= parent1.size(); i++)
  {
    if (i % 2)
    {
      child1[i - 1] = parent1[i - 1];
      child2[i - 1] = parent2[i - 1];
    }
    else
    { 
      child1[i - 1] = parent2[i - 1];
      child2[i - 1] = parent1[i - 1];
    }
  }

  return make_pair(child1, child2);
}
/**
 * @brief Executes a one-point crossover between two parent vectors.
 *
 * This function selects a random point in the vector, and all the genes (vector elements) beyond that point are swapped
 * between the two parents. This results in two offspring, each sharing a block of genes with each parent.
 *
 * @param parent1 First parent vector for crossover.
 * @param parent2 Second parent vector for crossover.
 * @return pair<vector<int>, vector<int>> Returns two child vectors, each inheriting a contiguous block of genes from both parents.
 */
pair<vector<int>, vector<int>> one_point_cross(vector<int> parent1, vector<int> parent2)
{
  // crosses one point of the parent vectors
  // get the crossover point
  int crossover_point = rand() % parent1.size();
  // only crossover the crossover_point
  int temp = parent1[crossover_point];
  parent1[crossover_point] = parent2[crossover_point];
  parent2[crossover_point] = temp;

  return make_pair(parent1, parent2);
}
/**
 * @brief Conducts a two-point crossover between two parent vectors.
 *
 * Two random points are chosen within the vectors, and the genetic material enclosed by these points is swapped between
 * the two parents. This method allows for a more localized alteration of the genetic structure compared to one-point crossover.
 *
 * @param parent1 First parent vector.
 * @param parent2 Second parent vector.
 * @return pair<vector<int>, vector<int>> Returns two new child vectors, each containing segments of genes exchanged between the parents.
 */

pair<vector<int>, vector<int>> two_point_cross(vector<int> parent1, vector<int> parent2)
{
  // Similar to one points, but crossover point is two points wide
  vector<int> points;
  // get the crossover points
  points.push_back(rand() % parent1.size());
  // set the second point to be one higher than the crossover_point1 or the first element depending on the boundary
  points.push_back((points[0]+ 1) % parent1.size());
  int temp;
  // only crossover the crossover_point
  for (int point : points)
  {
    temp = parent1[point];
    parent1[point] = parent2[point];
    parent2[point] = temp;
  }

  return make_pair(parent1, parent2);
}
/**
 * @brief Performs a multipoint crossover on two parent vectors.
 *
 * Several crossover points are randomly determined along the length of the vectors. The genes located at these points
 * are then swapped between the two parents, resulting in a high level of gene shuffling. This approach can create significant
 * genetic diversity within the offspring.
 *
 * @param parent1 First parent vector for crossover.
 * @param parent2 Second parent vector for crossover.
 * @return pair<vector<int>, vector<int>> Returns two child vectors with highly mixed genetic material from both parents.
 */

// Multipoint crossover, select m crossover points and crossover, where m is half the size of the child
pair<vector<int>, vector<int>> multipoint_cross(vector<int> parent1, vector<int> parent2)
{
  // crosses m points of the parent vectors
  vector<int> child1;
  vector<int> child2;
  vector<int> points;
  // get the crossover points, making sure no duplicates are selected
  for (int i = 0; i < parent1.size()/2; i++)
  {
    int point = 0;
    do
    {
      point = rand() % parent1.size();
    } while (find(points.begin(), points.end(), point) != points.end());
    points.push_back(point);
  }
  int temp;
  // only crossover the crossover_point
  for (int point : points)
  {
    temp = parent1[point];
    parent1[point] = parent2[point];
    parent2[point] = temp;
  }
  return make_pair(parent1, parent2);
}


/*
The below mutation functions are for test purposes only and are not intended to be run for any other purpose.
*/
vector<int> substitution(vector<int> child, double mutation_rate)
{
  if (mutation_rate > (rand() % 1000) / 1000.0)
  {
    // substitute a random gene with a random value
    int mutation_index = rand() % child.size();
    child[mutation_index] = rand() % 10;
  }
  return child;
}

vector<int> inversion(vector<int> child, double mutation_rate)
{
  if (mutation_rate > (rand() % 1000) / 1000.0)
  {
    // take a section of the child and invert it
    int mutation_index = rand() % (child.size()/2);
    int inversion_size =  rand() % (child.size()-mutation_index);
    reverse(child.begin() + mutation_index, child.begin() + mutation_index + inversion_size);
  }
  return child;
}

vector<int> value_adjustment(vector<int> child, double mutation_rate)
{
  if (mutation_rate > (rand() % 1000) / 1000.0)
  {
    int mutation_index = rand() % child.size();
    int mutation_size = rand() % (child.size()/2);
    for (int i =0; i<mutation_size; i++)
    {
      int index = (mutation_index + i) % child.size();
      child[index] = (child[index] + 1) %10;
    }
  }
  return child;
}
