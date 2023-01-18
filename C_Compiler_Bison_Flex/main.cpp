#include <vector>
#include <iostream>
using namespace std;

enum A
{
    AA
};

enum B
{
    BB
};
int main()
{
    A a = AA;
    if (a == A)
    {
        printf("BB");
    }
    else
    {
        printf("AA");
    }
}