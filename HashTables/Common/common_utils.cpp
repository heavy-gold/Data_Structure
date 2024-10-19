#include "common_utils.h"
#include <iostream>
#include <limits>

namespace utils
{
    using namespace std;
    bool getIntegerInput(int &value)
    {
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
} // namespace utils
