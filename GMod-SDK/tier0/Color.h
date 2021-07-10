#pragma once
#include <cstdint>

struct Color
{
    uint8_t color[4];
    float fCol[4];
    int r, g, b, a;
    bool rainbow;

    Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
        color[0] = R;
        color[1] = G;
        color[2] = B;
        color[3] = A;
        r = R; g = G; b = B; a = A;
        fCol[0] = (float)R/255.f; fCol[1] = (float)G / 255.f; fCol[2] = (float)B / 255.f; fCol[3] = (float)A / 255.f;
		rainbow = false;
    }
    Color(uint8_t R, uint8_t G, uint8_t B) {
        color[0] = R;
        color[1] = G;
        color[2] = B;
        color[3] = 255;
        r = R; g = G; b = B; a = 255;
        fCol[0] = (float)R / 255.f; fCol[1] = (float)G / 255.f; fCol[2] = (float)B / 255.f; fCol[3] = 1.f;
		rainbow = false;
    }
    bool operator == (const Color& other)
    {
        return fCol[0] == other.fCol[0] && fCol[1] == other.fCol[1] && fCol[2] == other.fCol[2] && fCol[3] == other.fCol[3];
    }
    bool operator != (const Color& other)
    {
        return !(*this == other);
    }
	static Color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color(
				(uint8_t)(brightness * 255),
				(uint8_t)(t * 255),
				(uint8_t)(p * 255)
			);
		}
		else if (h < 2)
		{
			return Color(
				(uint8_t)(q * 255),
				(uint8_t)(brightness * 255),
				(uint8_t)(p * 255)
			);
		}
		else if (h < 3)
		{
			return Color(
				(uint8_t)(p * 255),
				(uint8_t)(brightness * 255),
				(uint8_t)(t * 255)
			);
		}
		else if (h < 4)
		{
			return Color(
				(uint8_t)(p * 255),
				(uint8_t)(q * 255),
				(uint8_t)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return Color(
				(uint8_t)(t * 255),
				(uint8_t)(p * 255),
				(uint8_t)(brightness * 255)
			);
		}
		else
		{
			return Color(
				(uint8_t)(brightness * 255),
				(uint8_t)(p * 255),
				(uint8_t)(q * 255)
			);
		}
	}
	// wip
    /*void RandomizeIfNeeded()
    {
        if (rainbow)
        {
			static float rainbowFl;
			rainbowFl += 0.005f;
			if (rainbowFl > 1.f) rainbowFl = 0.f;
			*this = FromHSB(rainbowFl, 1.f, 1.f);
        }
    }*/
};