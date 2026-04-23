#include <stdint.h>
#include "src/gf.cpp"

extern "C" uint16_t gf_mul_bridge(uint16_t a, uint16_t b)
{
    return gf_mul(a, b);
}