#include "timerutils.h"

#include <sstream>
#include <iomanip>

namespace csplit {
namespace core {

std::string TimerUtils::microseconds2string(std::chrono::microseconds input, bool displayMicroseconds)
{
    using std::chrono::duration_cast;
    auto hours = duration_cast<std::chrono::hours>(input);
    input -= hours;
    auto minutes = duration_cast<std::chrono::minutes>(input);
    input -= minutes;
    auto seconds = duration_cast<std::chrono::seconds>(input);
    input -= seconds;
    auto milliseconds = duration_cast<std::chrono::milliseconds>(input);
    input -= milliseconds;

    std::stringstream ss;
    ss.fill('0');
    ss << hours.count() << ":" << std::setw(2)
       << minutes.count() << ":" << std::setw(2)
       << seconds.count() << "." << std::setw(3)
       << milliseconds.count() << "." << std::setw(3)
       << input.count();
    
    return ss.str();
}

} // end namespace core
} // end namespace csplit