#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
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