#include "processor.h"
#include <vector>
#include <string>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    //total jiffies / active jiffies /idle jiffies/
    vector<string> cpu = LinuxParser::CpuUtilization();

     //assumption: utilzation = active/total
     utilization_ = stof(cpu[1])/stof(cpu[2]); 
    
     return utilization_;

 }