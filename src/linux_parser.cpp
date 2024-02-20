#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
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

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
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
  string line;
  string key;
  string value;

  string memTotal;
  string memFree;
  string memAvailable;
  string buffers;

  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  if (filestream.is_open()) {
      while(std::getline(filestream, line)) {
          std::replace(line.begin(), line.end(), ':', ' ');
          std::istringstream linestream(line);
          while (linestream >> key >> value) {
              if (key == "MemTotal") {
                  memTotal = value;
              } else if (key == "MemFree") {
                  memFree = value;
              } else if (key == "MemAvailable") {
                  memAvailable = value;
              } else if (key == "Buffers") {
                  buffers = value;
              }
          }
      }
  }

  return (stof(memTotal) - stof(memFree))/stof(memTotal);// - stof(buffers) - stof(memAvailable);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string totalUptime;

  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
  if (filestream.is_open()) {
      while(std::getline(filestream, line)) {
          std::replace(line.begin(), line.end(), ':', ' ');
          std::istringstream linestream(line);
          linestream >> totalUptime;
      }
  }
  return std::stod(totalUptime); 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return 0; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 
  return 0; 
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  return 0; 
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  return 0; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string tmp;
  vector<string> res;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream) {
      linestream >> tmp;
      res.push_back(tmp);
    }
  }
  return res;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;

  string totalProcesses;

  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  if (filestream.is_open()) {
      while(std::getline(filestream, line)) {
          std::replace(line.begin(), line.end(), ':', ' ');
          std::istringstream linestream(line);
          while (linestream >> key >> value) {
              if (key == "processes") {
                  totalProcesses = value;
              } 
          }
      }
  }
  return std::stoi(totalProcesses, nullptr, 0); //HERE
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;

  string runningProcesses;

  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  if (filestream.is_open()) {
      while(std::getline(filestream, line)) {
          std::replace(line.begin(), line.end(), ':', ' ');
          std::istringstream linestream(line);
          while (linestream >> key >> value) {
              if (key == "procs_running") {
                  runningProcesses = value;
              } 
          }
      }
  }
  int ret = stoi(runningProcesses);
  return 1; //HERE
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string command;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, command);
  }
  return command; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, key, value, ram;

  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
          if (key == "VmSize") {
              ram = value;
          } 
      }
    }
  }
  return ram; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  return string("test"); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  return string("test"); 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  return 0; 
}
