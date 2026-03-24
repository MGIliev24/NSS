#pragma once

static unsigned long int g_seed = 1234567;
inline void setSeed(unsigned int s) { g_seed = s ? s : 1; }
inline int getRandomInt(int lo, int hi) {
    g_seed = (g_seed * 1103515245UL + 12345UL) % 2147483647UL;
    return lo + (int)(g_seed % (unsigned)(hi - lo + 1));
}
