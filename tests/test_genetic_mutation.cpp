#include <iostream>

#include "Genetic_Algorithm.h"


// This answer vector is used in the test function
int test_answer[] = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4};



int main() {
    // set things up
    vector<int> vector1 = {0,1,1,2,2,3,3,0,0,4};  
    vector<int> vector2 = {9,9,9,9,9,9,9,9,9,9};
    vector<int> vector3 = {0,1,2,3,4,5,6,7,8,9};

    cout << "Parent 1: ";
    for (auto gene : vector2)
    {
        cout << gene << " ";
    }
    cout << endl;
    cout << "Parent 2: ";
    for (auto gene : vector3)
    {
        cout << gene << " ";
    }
    cout << "Parent 3: ";
    for (auto gene : vector1)
    {
        cout << gene << " ";
    }
    cout << endl;
    cout << "Checking optimum without validity checker. Vector length 10" << endl;

    // run your code
    vector<int> result;
    cout << "Substitution" << endl;
    result = substitution(vector2, 100.0);

    for (auto gene : result)
    {
        cout << gene << " ";
    }
    cout << endl;
    cout << "Inversion" << endl;
    result = inversion(vector3, 100.0);
    for (auto gene : result)
    {
        cout << gene << " ";
    }
    cout << endl;
    cout << "Value adjustment" << endl;
    result = value_adjustment(vector1, 100.0);
    for (auto gene : result)
    {
        cout << gene << " ";
    }
    cout << endl;
    // Can test other versions

    return 0;
}