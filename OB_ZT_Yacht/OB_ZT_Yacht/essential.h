#ifndef ESSENTIAL_H
#define ESSENTIAL_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <ctype.h>
#include <set>
#include <time.h>
#include <random>
using namespace std;
int RandRange(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}
#endif
