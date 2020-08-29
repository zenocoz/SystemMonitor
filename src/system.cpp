#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

using namespace LinuxParser;

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() { 
    vector<int> pids = LinuxParser::Pids();
    for (auto i : pids) {
        processes_.push_back(Process(pids[i]));
    }   
    return processes_; 
}

string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

//Returns the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }