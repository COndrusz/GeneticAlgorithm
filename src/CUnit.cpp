#include <CUnit.h>

/**
 * @brief Construct a default CUnit::CUnit object
 * 
 * @return CUnit 
*/
CUnit::CUnit() : conc_num(-1), inter_num(-1), tails_num(-1), mark(false) {}

/**
 * @brief Construct a new CUnit::CUnit object with parameters
 * 
 * @param conc 
 * @param inter 
 * @param tails 
 * @return CUnit 
*/
CUnit::CUnit(int conc, int inter, int tails) : conc_num(conc), inter_num(inter), tails_num(tails), mark(false) {}
