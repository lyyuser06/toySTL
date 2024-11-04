#include "Vector.h"
#include <iostream>

using namespace std;

int main() 
{
    Vector<int> v1;
    for(int i = 0; i < 10; i++)
        v1.insertItem(i);
    for(auto it = v1.begin();)
}