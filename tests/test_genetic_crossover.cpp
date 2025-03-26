#include <iostream>

#include "Genetic_Algorithm.h"


// This answer vector is used in the test function
int test_answer[] = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4};



int main() {
    // set things up
    vector<int> vector1 = {0,1,1,2,2,3,3,0,0,4};  
    vector<int> vector2 = {9,9,9,9,9,9,9,9,9,9};

    cout << "Parent 1: ";
    for (auto gene : vector1)
    {
        std::cout << gene << " ";
    }
    cout << endl;
    cout << "Parent 2: ";
    for (auto gene : vector2)
    {
        std::cout << gene << " ";
    }
    cout << endl;



    std::cout << "Checking optimum without validity checker. Vector length 10" << std::endl;

    // run your code
    vector<vector<int>> result;
    cout << "Uniform crossover" << endl;
    result = crossover(vector1, vector2, "uniform");
    for (int child = 0; child < result.size(); child++)
    {
        cout << "Child " << child << ": ";
        for (auto gene : result[child])
        {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }
    cout << endl;
    

    cout << "One Point crossover" << endl;
    result = crossover(vector1, vector2, "one_point");
    for (int child = 0; child < result.size(); child++)
    {
        cout << "Child " << child << ": ";
        for (auto gene : result[child])
        {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }
    cout << endl;


    cout << "Two Point crossover" << endl;
    result = crossover(vector1, vector2, "two_point");
    for (int child = 0; child < result.size(); child++)
    {
        cout << "Child " << child << ": ";
        for (auto gene : result[child])
        {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }
    cout << endl;

    cout << "Multi Point crossover" << endl;
    result = crossover(vector1, vector2, "multipoint");
    for (int child = 0; child < result.size(); child++)
    {
        cout << "Child " << child << ": ";
        for (auto gene : result[child])
        {
            std::cout << gene << " ";
        }
        std::cout << std::endl;
    }
    cout << endl;



    return 0;
}