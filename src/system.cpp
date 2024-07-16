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
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Done: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    std::vector<int> pidList = LinuxParser::Pids();
    for (int pid: pidList) {
        std::string cmd = LinuxParser::Command(pid);
        std::string usr = LinuxParser::User(pid);
        Process p(pid, usr, cmd);
        processes_.push_back(p);
    }
    return processes_;
}

// Done: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    if (kernel_.empty()) {
        kernel_ = LinuxParser::Kernel();
    }
    return kernel_; 
}

// Done: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
}

// Done: Return the operating system name
std::string System::OperatingSystem() { 
    if (os_.empty()) {
        os_ = LinuxParser::OperatingSystem();
    }
    return os_; 
}

// Done: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses();
}

// Done: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses();
}

// Done: Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::UpTime(); 
}
