#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int minutes = seconds/60;
  int hours = minutes / 60;

  int seconds_r = seconds%60;
  int minutes_r = minutes%60; 
  std::stringstream date;
  
  date << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << minutes_r << ":"<< std::setw(2) << seconds_r;
    
  return date.str();
}