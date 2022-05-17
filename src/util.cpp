#include "util.hpp"

std::ostream& PrintMultipleTimes(std::ostream& os,
                                 char ch,
                                 unsigned freq) {
    for (unsigned i = 0; i < freq; ++i) {
        os << ch;
    }                                 
    return os;
}