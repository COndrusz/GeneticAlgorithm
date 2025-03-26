#include <iostream>

#include "Genetic_Algorithm.h"


// This answer vector is used in the test function
int test_answer[] = {2, 1, 1, 2, 0, 3, 2, 0, 4, 4};

// mock test function for genetic algorithm
double test_function(int vector_size, int * vector) {

    double result = 600;
    for (int i = 0; i < vector_size; i++) {
        result -= (vector[i]-test_answer[i])*(vector[i]-test_answer[i]);
        }

    return result;
    
    }


int main() {
    // set things up
    int vector1[] = {0,1,1,2,2,3,3,0,0,4};  

    std::cout << "Checking optimum without validity checker. Vector length 10" << std::endl;
    
    // run your code
    optimize(10, vector1, test_function);
    // you could test the quality of your answer here.

    std::cout << "Optimum vector found." << std::endl;

    // Can test other versions

    return 0;
}