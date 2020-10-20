
#include <cstdio>

#include "lightsky/setup/CPU.h"

int main()
{
    constexpr unsigned numCounts = 32;
    int64_t counters[numCounts];

    ls::setup::cpu_read_ticks();

    for (unsigned i = 0; i < numCounts; ++i)
    {
        const int64_t initTime = ls::setup::cpu_read_ticks();
        ls::setup::cpu_yield();

        counters[i] = ls::setup::cpu_read_ticks() - initTime;
    }

    for (unsigned i = 0; i < numCounts; ++i)
    {
        printf("CPU performance timer check %d: %lld\n", i+1, (long long)counters[i]);
    }

    return 0;
}
