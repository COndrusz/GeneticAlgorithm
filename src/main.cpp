#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "CSimulator.h"
#include "Genetic_Algorithm.h"


int main(int argc, char * argv[])
{

    // set things up
    // int vector[16] = {0, 1, 1, 2, 2, 3, 3, 0, 4, 1, 0, 2, 6, 5, 0, 6};
    int vector[64] = {0, 1, 3, 2, 4, 4, 3, 1, 3, 6, 1, 1, 0, 5, 1, 1,1,2,3,4,5,6,7,8,9,1,2,3,1,2,3};


    // const Circuit circuit(8);

    // run your code
    optimize(64, vector, Evaluate_Circuit);
    // or
    // optimize(11, vector, Evaluate_Circuit, Circuit::Check_Validity)
    // etc.
    double grade=Evaluate_Circuit_Grade(64, vector);
    double recov= Evaluate_Circuit_Recovery(64, vector);
    std::cout<< "Recovery " << recov<<std::endl;
    std::cout <<  "Grade " <<grade<< std::endl;
    double performance=Evaluate_Circuit(64, vector);
    Save_ResultToTxt("../output.txt", 64, vector, performance, recov, grade);


    return 0;
}
