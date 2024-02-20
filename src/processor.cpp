#include "processor.h"
#include <string>
#include <vector>
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    int user, nice ,system, idle, iowait, irq ,softirq ,steal, guest, guest_nice = 0;
    std::vector<std::string> cpuVals = LinuxParser::CpuUtilization();
    int i = 0;
    /*user = std::stoi(cpuVals.at(i++));
    nice = std::stoi(cpuVals.at(i++));
    system = std::stoi(cpuVals.at(i++));
    idle = std::stoi(cpuVals.at(i++));
    iowait = std::stoi(cpuVals.at(i++));
    irq = std::stoi(cpuVals.at(i++));
    softirq = std::stoi(cpuVals.at(i++));
    steal = std::stoi(cpuVals.at(i++));
    guest = std::stoi(cpuVals.at(i++));
    guest_nice = std::stoi(cpuVals.at(i++));
*/
    idle_ = idle_ + iowait_;
    idle = idle + iowait;
    int prevNonIdle = user_ + nice_ + system_ + irq_ + softirq_ + steal_;
    int nonIdle = user + nice + system + irq + softirq + steal;

    int prevTotal = idle_ + prevNonIdle;
    int total = idle + nonIdle;

    int totalD = total - prevTotal;
    int idleD = idle - idle_;

    float cpuUtil = (totalD - idleD) / totalD;
    
    return cpuUtil; 
}