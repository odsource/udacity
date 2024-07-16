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

Process::Process(int pid, std::string user, std::string command) : pid_(pid), user_(user), command_(command) {
    CpuUtilization();
    Ram();
    UpTime();
}

int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    string line;
    std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid_) + LinuxParser::kStatFilename);
    if (filestream.is_open()) {
        while(std::getline(filestream, line)) {

        }
    }
    return 0; 
}

// Done: Return the command that generated this process
string Process::Command() { return command_; }

// Done: Return this process's memory utilization
string Process::Ram() {     
    return LinuxParser::Ram(pid_); 
}

// Done: Return the user (name) that generated this process
string Process::User() { 
    return user_; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(pid_); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }