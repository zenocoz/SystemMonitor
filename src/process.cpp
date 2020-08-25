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
    /*vector<int> pids = LinuxParser::Pids();
    for (auto i : pids) { 
        string line;
        string key;
        string value;
        string temp = to_string(pids[i]);
        std::ifstream filestream(kProcDirectory + temp + kStatusFilename);
        if (filestream.is_open()) {
            while(getline(filestream, line)) {
                std::replace(line.begin(), line.end(), ':', ' ');
                std::istringstream linestream(line);
                while (linestream >> key >> value) {
                    if (key == "State" && value == "R") {
                        //state = value;//TODO check if needed
                        pid_ = pids[i];
                    } else break;
                }
            }
        }
        
    }*/
    return pid_;
 }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::ActiveJiffies(pid_)/LinuxParser::Jiffies(); }

string Process::Command() { return LinuxParser::Command(pid_); }
    
string Process::Ram() { return LinuxParser::Ram(pid_); }

string Process::User() { return LinuxParser::User(pid_); }

long int Process::UpTime() { return LinuxParser::UpTime(pid_); } //TODO add Time function

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return cpu_utilization > a.cpu_utilization; }