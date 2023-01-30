#ifndef __OPTIMIZER__
#define __OPTIMIZER__
#include <string>
#include <vector>
using namespace std;
class Optimizer
{
public:
    Optimizer(){};
    void optimize();
    vector<string> split(string s);
};
#endif

// Need to remove dead codes