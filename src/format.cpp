#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hours;
    long minutes;
    int seconds_;
    string elapsed_time;
    hours = seconds/3600;
    minutes = (seconds - (hours*3600))/60; //check
    seconds_ = seconds - (minutes*60) - (hours*3600);
    elapsed_time = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds_);
    return elapsed_time;


}