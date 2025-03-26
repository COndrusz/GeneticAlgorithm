#include <cmath>
#include <iostream>

#include "CSimulator.h"

/**
 * @brief Main function to test the Evaluate_Circuit, Evaluate_Circuit_Recovery, and Evaluate_Circuit_Grade functions.
 * 
 * This function sets up a dummy vector representing a circuit and uses it to test the performance,
 * recovery, and grade calculations against expected values. It also tests the cell calculator
 * function for individual cell outputs.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int Returns 0 on success, 1 on failure.
 */
int main(int argc, char* argv[]) {
    // Dummy vector. Replace in your code with the actual circuit vector.
    int vec1[] = {0, 1, 3, 2, 4, 4, 3, 1, 3, 6, 1, 1, 0, 5, 1, 1};

    // Test value based on stub Evaluate_Circuit function.
    // Replace with actual performance value.
    std::cout << "Compare Final Outputs to the sample case:\n";
    double performance = Evaluate_Circuit(16, vec1);
    double recovery = Evaluate_Circuit_Recovery(16, vec1);
    double grade = Evaluate_Circuit_Grade(16, vec1);

    double tol = 1.0e-2;

    if (std::fabs(performance - 167.379) < tol) {
        std::cout << "performance value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(recovery - 0.202836) < tol) {
        std::cout << "recovery value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(grade - 0.977224) < tol) {
        std::cout << "grade value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    std::cout << "Compare one cell output to the example calculation:\n";

    Unit_parameter parameters;
    Evaluate_Circuit_Cell_Calculator(parameters);

    if (std::fabs(parameters.CG - 1.04) < tol) {
        std::cout << "mass flowrate of high grade concentrate gerardium value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.CW - 0.53) < tol) {
        std::cout << "mass flowrate of high grade concentrate waste value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.IG - 0.26) < tol) {
        std::cout << "mass flowrate of intermediate grade concentrate gerardium value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.IW - 0.79) < tol) {
        std::cout << "mass flowrate of intermediate grade concentrate waste value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.TG - 8.7) < tol) {
        std::cout << "mass flowrate of tailing gerardium value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.TW - 88.67) < tol) {
        std::cout << "mass flowrate of tailing waste value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.tau - 30) < tol) {
        std::cout << "residence time value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.RHG - 0.104) < tol) {
        std::cout << "recovery of high grade concentrate gerardium value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.RHW - 0.0059) < tol) {
        std::cout << "recovery of high grade concentrate waste value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.RIG - 0.026) < tol) {
        std::cout << "recovery of intermediate grade concentrate gerardium value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    if (std::fabs(parameters.RIW - 0.0089) < tol) {
        std::cout << "recovery of intermediate grade concentrate waste value test pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }
}
