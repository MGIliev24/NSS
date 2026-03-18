#include <cmath>
#include "randomizer.h"

unsigned long int currentSeedValue = 1234567;

void setSeed(unsigned int newSeed)
{
    if (newSeed == 0)
    {
        newSeed = 1;
    }
    currentSeedValue = newSeed;
}

int getRandomInt(int minValue, int maxValue)
{
    currentSeedValue = (currentSeedValue * 1103515245 + 12345) % 2147483647;
    int range = maxValue - minValue + 1;
    int value = (int)(currentSeedValue % range);
    return minValue + value;
}

