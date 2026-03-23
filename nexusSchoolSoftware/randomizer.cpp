#include "randomizer.h"

// Default seed — overwritten by setSeed() before any calls to getRandomInt()
static unsigned long int currentSeedValue = 1234567;

void setSeed(unsigned int newSeed)
{
    if (newSeed == 0) newSeed = 1;  // Zero breaks the LCG, so clamp to 1
    currentSeedValue = newSeed;
}

// Linear Congruential Generator — produces a pseudo-random int in [minValue, maxValue]
int getRandomInt(int minValue, int maxValue)
{
    currentSeedValue = (currentSeedValue * 1103515245 + 12345) % 2147483647;
    int range = maxValue - minValue + 1;
    int value = (int)(currentSeedValue % range);
    return minValue + value;
}