#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >>  kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float mem_total;
  float mem_free;
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      //std::replace(line.begin(), line.end(), ' ', '_');
      //std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          mem_total = std::stof(value);
        } 
        if (key == "MemFree") {
          mem_free = std::stof(value);
        }
      }
    }
  }
  return mem_total - mem_free;
}
  
// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string uptime_s, idle_time_s;
  long uptime;
  long idle_time;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()) {
  std::getline(stream, line);
  std::istringstream linestream(line);
  linestream >> uptime_s >> idle_time_s;
  }
  uptime = std::stol(uptime_s);
  idle_time = std::stol(idle_time_s);
  return uptime;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  vector<string> tokens;
  string line;
  string s;
  long jiffies = 0;
  std::ifstream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> s) {
      tokens.push_back(s);
    }
    tokens.erase(tokens.begin());
    for (auto i : tokens) {
      long num = std::stol(i);
      jiffies += num;
    }
  }
return jiffies;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  //all the other jiffies except idle and iowait
  vector<string> tokens;
  string line;
  string s;
  long active_jiffies = 0;
  std::ifstream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> s) {
      tokens.push_back(s);
    }
    tokens.erase(tokens.begin()+4);
    tokens.erase(tokens.begin()+5);
    tokens.erase(tokens.begin());
    for (auto i : tokens) {
      long num = std::stol(i);
      active_jiffies += num;
    }
  }
return active_jiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  // idle and iowait (4 and 5) double check!
  vector<string> tokens;
  string line;
  string s;
  long idle_jiffies = 0;
  long jiffies = 0;
  std::ifstream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> s) {
      tokens.push_back(s);
    }
    idle_jiffies = std::stol(tokens[4]) + std::stol(tokens[5]);
  }
return idle_jiffies;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
//active/total
//store all the jiffies
vector <string> cpu;
string total_jiffies = to_string(Jiffies());
string active_jiffies = to_string(ActiveJiffies());
string idle_jiffies = to_string(IdleJiffies());
cpu.push_back(total_jiffies);
cpu.push_back(active_jiffies);
cpu.push_back(idle_jiffies);    
return cpu;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int total_processes;
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          //std::replace(value.begin(), value.end(), '_', ' ');
          total_processes = std::stoi(value);
        } 
      }
    }
  }
  return total_processes;
 }

int LinuxParser::RunningProcesses() {
  int running_processes;
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          running_processes = std::stoi(value);
        } 
      }
    }
  }
  return running_processes;
}
string LinuxParser::Command(int pid) { 
  string line;
  string pid_ = to_string(pid);
  std::ifstream filestream(kProcDirectory + pid_ + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }
  return line;
}

string LinuxParser::Ram(int pid) { 
  string pid_ = to_string(pid);
  string line;
  string key;
  string value;
  string ram;
  std::ifstream filestream(kProcDirectory + pid_ + kStatusFilename);
  if (filestream.is_open()) {
     while (getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize") {
          ram = value;
          break;
        }
      }
    }
  float ram_ = stof(ram) * 0.001;
  ram = to_string(ram_);
  ram.erase(ram.end()-5, ram.end());
  }
  return ram;
 }

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  string pid_ = to_string(pid);
  string line;
  string key;
  string value;
  string uid;
  std::ifstream filestream(kProcDirectory + pid_ + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >>value) { 
        if (key == "Uid") {
          std::replace(value.begin(), value.end(), '_', ' ');
          std::istringstream uid_stream(value);
          uid_stream >> uid;
          break;
        } 
      }
    }
  }
  return uid;
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string user;
  string uid = LinuxParser::Uid(pid);
  string line;
  string key;
  string value;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), 'x', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (value == uid) {
          user = key;
          break;
        } 
      }
    } 
  }
  return user;
}

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  vector<string> tokens;
  long uptime;
  string pid_ = to_string(pid);
  string line;
  string value;
  std::ifstream filestream (kProcDirectory + pid_ + kStatFilename); 
  if (filestream.is_open()) {
    getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream >> value) {
    tokens.push_back(value);
    } 
    uptime = stol(tokens[23])/sysconf(_SC_CLK_TCK);
}
return uptime;
}