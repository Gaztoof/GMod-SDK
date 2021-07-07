#pragma once
#include <cstdint>

struct Color
{
    uint8_t color[4];
    float fCol[4];
    int r, g, b, a;
    Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
        color[0] = R;
        color[1] = G;
        color[2] = B;
        color[3] = A;
        r = R; g = G; b = B; a = A;
        fCol[0] = (float)R/255.f; fCol[1] = (float)G / 255.f; fCol[2] = (float)B / 255.f; fCol[3] = (float)A / 255.f;
    }
    Color(uint8_t R, uint8_t G, uint8_t B) {
        color[0] = R;
        color[1] = G;
        color[2] = B;
        color[3] = 255;
        r = R; g = G; b = B; a = 255;
        fCol[0] = (float)R / 255.f; fCol[1] = (float)G / 255.f; fCol[2] = (float)B / 255.f; fCol[3] = 1.f;
    }
    bool operator == (const Color& other)
    {
        return fCol[0] == other.fCol[0] && fCol[1] == other.fCol[1] && fCol[2] == other.fCol[2] && fCol[3] == other.fCol[3];
    }
    bool operator != (const Color& other)
    {
        return !(*this == other);
    }
};