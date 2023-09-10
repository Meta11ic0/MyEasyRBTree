#include <iostream>
using namespace std;
#include <vector>
#include "MyRBTree.h"

int main()
{
    MyRBTree TreeA;
    vector<int> vec={41,38,31,12,19,8};
    for(int i : vec)
    {
        TreeA.InsertNode(i);
    }
    TreeA.DeleteNode(38);
    getchar();
    return 0;
}