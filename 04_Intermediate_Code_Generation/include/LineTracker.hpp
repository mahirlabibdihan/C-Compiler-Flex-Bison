/**
 * Author: Mahir Labib Dihan
 * Last modified: December 14, 2022
 */

#ifndef __LINE_TRACKER_H
#define __LINE_TRACKER_H 1
#include <string>

class LineTracker
{
    int line_count;

public:
    LineTracker(int start_line = 1);
    int getLineNumber();
    void handleNewLine();
    void handleString(std::string text);
    void handleSingleComment(std::string text);
    void handleMultiComment(std::string text);
};
#endif