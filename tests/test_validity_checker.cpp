#include <iostream>

#include <CUnit.h>
#include <CCircuit.h>

bool test_check_validity() {
    int valid[] = {0, 1, 2, 2};
    int invalid[] = {0, 1, 0, 2};
    int valid_2[] = {1, 2, 3, 5, 2, 3, 0, 4, 3, 3, 2, 2, 1}; // valid
    int invalid_2[] = {1, 2, 3, 5, 2, 3, 3, 4, 3, 3, 2, 2, 1}; // not unit toward unit 0
    int invalid_3[] = {1, 2, 3, 5, 2, 3, 0, 2, 3, 3, 2, 2, 1}; // not unit can arrive destination 4
    int invalid_4[] = {1, 2, 3, 5, 2, 3, 0, 4, 3, 3, 2, 2, 2}; // unit 3 all to unit 2
    int invalid_5[] = {1, 0, 3, 5, 2, 3, 0, 4, 3, 3, 2, 2, 1}; // unit 0 self recycle
    int invalid_6[] = {1, 2, 3}; // incorrect length (less than 4)
    int invalid_7[] = {1, 2, 3, 5, 2, 3, 0, 4, 3, 3, 2, 2, 1, 1}; // incorrect length (not equals 3n+1)
    int invalid_8[] = {1, 2, 3, 5, 2, 3, 0, 4, 6, 3, 2, 2, 1}; // unit number out of limit num_unit+1 (6)
 
    // valid
	std::cout << "Check_Validity({0, 1, 2, 2}):\n";
    int k1 = (sizeof(valid) / sizeof(valid[0]) -1) /3;
    Circuit circuit1(k1); // Create a circuit with 1 unit (exclude outlet streams units)
    if (circuit1.Check_Validity(sizeof(valid) / sizeof(valid[0]), valid)) // Change the initial size of the array
	    std::cout  << "pass\n";
	else {
	    std::cout << "fail\n";
        return false;
    }

    // invalid (self-cycle)
	std::cout << "Check_Validity({0, 1, 0, 2}):\n";
    int k2 = (sizeof(invalid) / sizeof(invalid[0]) -1) /3;
    Circuit circuit2(k2);
    if (circuit2.Check_Validity(sizeof(invalid) / sizeof(invalid[0]), invalid)) 
    {
        std::cout << "fail\n";
        return false;
    }
    else 
        std::cout << "pass\n";

    // valid (example from lecture slide)
    std::cout << "Check_Validity({1, 2, 3, 5, 2, 3, 0, 4, 3, 3, 2, 2, 1}):\n";
    int k3 = (sizeof(valid_2) / sizeof(valid_2[0]) -1) /3;
    Circuit circuit3(k3); // Create a circuit with 1 unit (exclude outlet streams units)
    if (circuit3.Check_Validity(sizeof(valid_2) / sizeof(valid_2[0]), valid_2)) // Change the initial size of the array
	    std::cout  << "pass\n";
	else {
	    std::cout << "fail\n";
        return false;
    }

    // not unit toward unit 0
    std::cout << "Check_Validity({1, 2, 3, 5, 2, 3, 3, 4, 3, 3, 2, 2, 1}):\n";
    int k4 = (sizeof(invalid_2) / sizeof(invalid_2[0]) -1) /3;
    Circuit circuit4(k4); // Create a circuit with 1 unit (exclude outlet streams units)
    if (!circuit4.Check_Validity(sizeof(invalid_2) / sizeof(invalid_2[0]), invalid_2)) // Change the initial size of the array
	    std::cout << "fail\n";
	else {
	    std::cout << "pass\n";
        return false;
    }

    // not unit can arrive destination 4
    std::cout << "Check_Validity({1, 2, 3, 5, 2, 3, 0, 2, 3, 3, 2, 2, 1}):\n";
    int k5 = (sizeof(invalid_3) / sizeof(invalid_3[0]) -1) /3;
    Circuit circuit5(k5); // Create a circuit with 1 unit (exclude outlet streams units)
    if (!circuit5.Check_Validity(sizeof(invalid_3) / sizeof(invalid_3[0]), invalid_3)) // Change the initial size of the array
	    std::cout << "fail\n";
	else {
	    std::cout << "pass\n";
        return false;
    }

    // unit 3 all to unit 2
    std::cout << "Check_Validity({1, 2, 3, 5, 2, 3, 0, 4, 3, 3, 2, 2, 2}):\n";
    int k6 = (sizeof(invalid_4) / sizeof(invalid_4[0]) -1) /3;
    Circuit circuit6(k6); // Create a circuit with 1 unit (exclude outlet streams units)
    if (!circuit6.Check_Validity(sizeof(invalid_4) / sizeof(invalid_4[0]), invalid_4)) // Change the initial size of the array
	    std::cout << "fail\n";
	else {
	    std::cout << "pass\n";
        return false;
    }

    // unit 0 self recycle
    std::cout << "Check_Validity({1, 0, 3, 5, 2, 3, 0, 4, 3, 3, 2, 2, 1}):\n";
    int k7 = (sizeof(invalid_5) / sizeof(invalid_5[0]) -1) /3;
    Circuit circuit7(k7); // Create a circuit with 1 unit (exclude outlet streams units)
    if (!circuit7.Check_Validity(sizeof(invalid_5) / sizeof(invalid_5[0]), invalid_5)) // Change the initial size of the array
	    std::cout << "fail\n";
	else {
	    std::cout << "pass\n";
        return false;
    }

    // incorrect length (less than 4)
    std::cout << "Check_Validity({1, 2, 3}):\n";
    int k8 = (sizeof(invalid_6) / sizeof(invalid_6[0]) -1) /3;
    Circuit circuit8(k8); // Create a circuit with 1 unit (exclude outlet streams units)
    if (!circuit8.Check_Validity(sizeof(invalid_6) / sizeof(invalid_6[0]), invalid_6)) // Change the initial size of the array
	    std::cout << "fail\n";
	else {
	    std::cout << "pass\n";
        return false;
    }

    // incorrect length (not equals 3n+1) 
    std::cout << "Check_Validity({1, 2, 3, 5, 2, 3, 0, 4, 3, 3, 2, 2, 1, 1}):\n";
    int k9 = (sizeof(invalid_7) / sizeof(invalid_7[0]) -1) /3;
    Circuit circuit9(k9); // Create a circuit with 1 unit (exclude outlet streams units)
    if (!circuit9.Check_Validity(sizeof(invalid_7) / sizeof(invalid_7[0]), invalid_7)) // Change the initial size of the array
	    std::cout << "fail\n";
	else {
	    std::cout << "pass\n";
        return false;
    }

    // unit number out of limit num_unit+1 (6)
    std::cout << "Check_Validity({1, 2, 3, 5, 2, 3, 0, 4, 6, 3, 2, 2, 1}):\n";
    int k10 = (sizeof(invalid_8) / sizeof(invalid_8[0]) -1) /3;
    Circuit circuit10(k10); // Create a circuit with 1 unit (exclude outlet streams units)
    if (!circuit10.Check_Validity(sizeof(invalid_8) / sizeof(invalid_8[0]), invalid_8)) // Change the initial size of the array
	    std::cout << "fail\n";
	else {
	    std::cout << "pass\n";
        return false;
    }
    
    return true;
}

int main(int argc, char * argv[]){
    bool test_validity = test_check_validity();

    if (test_validity)
        return 0; // return 0 if all tests pass
    else
        return 1;

}
