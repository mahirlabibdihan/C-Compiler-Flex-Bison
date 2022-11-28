/**
 * Author: Mahir Labib Dihan
 * Last modified: November 25, 2022
 */

#ifndef _UTIL_H
#define _UTIL_H
#include <string>

namespace Util
{
    int countTokens(const std::string &line, char delim = ' ');
    std::string *split(const std::string &line, char delim = ' ');
};

#endif