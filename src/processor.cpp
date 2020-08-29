#include "processor.h"
#include <vector>
#include <string>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;


float Processor::Utilization() { 
    
    vector<string> cpu = LinuxParser::CpuUtilization();

     // utilization = active/total
     utilization_ = stof(cpu[1])/stof(cpu[2]); 
    
     return utilization_;

 }