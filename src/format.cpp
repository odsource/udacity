#include <string>
#include <sstream>

#include "format.h"

using std::string;

#define HOUR 3600
#define MINUTES 60

string Format::ElapsedTime(long seconds) { 
    int hours = seconds/HOUR;
    int rest = seconds - hours*HOUR;
    int minutes = rest / MINUTES;
    rest -= minutes * MINUTES;
    std::stringstream ss;
    ss << hours << ":" << minutes << ":" << rest; 
    return ss.str(); 
}