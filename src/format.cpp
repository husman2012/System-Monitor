#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    long minutes = seconds/60;
    int hours = minutes / 60;

    int seconds_r = seconds%60;
    int minutes_r = minutes%60; 

    string date = std::to_string(hours) + ":" + std::to_string(minutes_r) + ":" + std::to_string(seconds_r);
    return date; 
    }