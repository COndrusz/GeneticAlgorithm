/** Header for the unit class
 * 
 * 
 */

#pragma once

class CUnit {
 public:
  // Constructor
  CUnit();
  // Constructor with parameters
  CUnit(int conc, int inter, int tails);

  //index of the unit to which this unit’s concentrate stream is connected 
  int conc_num;
  //index of the unit to which this unit’s intermediate stream is connected 
  int inter_num;
  //index of the unit to which this unit’s tailings stream is connected 
  int tails_num;
  //A Boolean that is changed to true if the unit has been seen 
  bool mark = false;

  //parameters for inputs flow rate:
  double feed_rate_G = 0.0;
  double feed_rate_W = 0.0;

  //parameters for calculating the material recovery
  double k_cG = 0.004; // s^-1 Gerardium recovery constant in high grade
  double k_cW = 0.0002; //s^-1 Water recovery constant in high grade
  double k_iG = 0.008; //s^-1 Gerardium recovery constant in intermediate grade
  double k_iW = 0.001; // Water recovery constant in intermediate grade
  double residence_time; // average residence time of the unit

  //Constants for model:
  static constexpr double density = 3000; // kg/m^3
  static constexpr double volume = 10; // m^3
  static constexpr double solid_fraction = 0.1; // fraction of solid in the feed

  //Function to calculate the recovery of the unit
  double Calculate_RHG(){
    return k_cG * residence_time / (1 + k_cG * residence_time + k_iG * residence_time);
  }

  double Calculate_RHW(){
    return k_cW * residence_time / (1 + k_cW * residence_time + k_iW * residence_time);
  }

  double Calculate_RIG(){
    return k_iG * residence_time / (1 + k_cG * residence_time + k_iG * residence_time);
  }

  double Calculate_RIW(){
    return k_iW * residence_time / (1 + k_cW * residence_time + k_iW * residence_time);
  }

  // Function to calculate resident time
  void Calculate_ResidenceTime(double total_feed_rate){
    if(total_feed_rate > 0){
      residence_time = volume * solid_fraction / (total_feed_rate / density);
    } else {
      residence_time = 0;
    }
  };

  // Calculate the concentrate flow rate
  double calculate_CG(){
    return feed_rate_G * Calculate_RHG();
  }

  double calculate_CW(){
    return feed_rate_W * Calculate_RHW();
  }

  double calculate_IG(){
    return feed_rate_G * Calculate_RIG();
  }

  double calculate_IW(){
    return feed_rate_W * Calculate_RIW();
  }

  // Calculate the tailings flow rate
  double calculate_TG(){
    return feed_rate_G - calculate_CG() - calculate_IG();
  }

  double calculate_TW(){
    return feed_rate_W - calculate_CW() - calculate_IW();
  }
};

