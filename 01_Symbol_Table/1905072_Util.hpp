#ifndef __UTIL__
#define __UTIL__

#include <vector>
#include <string>

namespace Util
{
    std::vector<std::string> split(const std::string &line, char delm = ' ');
};

#endif