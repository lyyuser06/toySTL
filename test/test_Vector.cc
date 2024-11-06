#include "Vector.h"
#include <iostream>

using namespace std;

int main() 
{
    Vector<int> v1;
    for(int i = 0; i < 10; i++)
        v1.insertItem(i);
    int i = 0;
    for(auto it = v1.begin(); it != v1.end(); ++it)
    {
        cout << *(it) << endl;
        cout << "---------------" << endl;
        cout << v1[i] << endl;
        i++;
    }

    v1.put(1, 0);
    v1.removeItem(7, 9);
    v1.removeItem(5);
    v1.insertItem(6, 12);

    i = 0;
    for(auto it = v1.begin(); it != v1.end(); ++it)
    {
        cout << (*it) << endl;
        cout << "------" << endl;
        cout << v1.get(i) << endl;
        i++;
    }

    return 0;
}