#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

using namespace LinuxParser;


//Returns Process ID
int Process::Pid() { 
    return pid_;
 }

// Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::ActiveJiffies(pid_)/LinuxParser::Jiffies(); }

string Process::Command() { return LinuxParser::Command(pid_); }
    
string Process::Ram() { return LinuxParser::Ram(pid_); }

string Process::User() { return LinuxParser::User(pid_); }

long int Process::UpTime() { return LinuxParser::UpTime(pid_); } //TODO add Time function

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return cpu_utilization > a.cpu_utilization; }