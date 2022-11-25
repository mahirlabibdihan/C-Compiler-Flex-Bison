/**
 * Author: Mahir Labib Dihan
 * Last modified: November 25, 2022
 */

#ifndef _UTIL_H
#define _UTIL_H
#include <vector>
#include <string>

namespace Util
{
    std::vector<std::string> split(const std::string &line, char delm = ' ');
};

#endif