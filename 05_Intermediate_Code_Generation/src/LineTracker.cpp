/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include "../include/LineTracker.hpp"
#include "../include/Util.hpp"
#include <string>
LineTracker::LineTracker(int start_line)
{
    this->line_count = start_line;
}

int LineTracker::getLineNumber()
{
    return line_count;
}

void LineTracker::handleNewLine()
{
    line_count++;
}

void LineTracker::handleString(std::string text)
{
    line_count += Util::getStringLineCount(text) - 1;
}

void LineTracker::handleSingleComment(std::string text)
{
    line_count += Util::getSingleCommentLineCount(text) - 1;
}

void LineTracker::handleMultiComment(std::string text)
{
    line_count += Util::getMultiCommentLineCount(text) - 1;
}