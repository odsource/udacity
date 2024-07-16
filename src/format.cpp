#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;

#define HOUR 3600
#define MINUTES 60

string Format::ElapsedTime(long seconds) { 
    int rest = seconds;
    int hours = rest / HOUR;
    rest -= hours * HOUR;
    int minutes = rest / MINUTES;
    rest -= minutes * MINUTES;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours 
        << ":" << std::setfill('0') << std::setw(2) << minutes 
        << ":" << std::setfill('0') << std::setw(2) << rest; 
    return ss.str(); 
}