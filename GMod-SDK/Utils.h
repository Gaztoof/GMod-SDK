#pragma once
#include "math_pfns.h"
#include "Color.h"
#include "globals.h"
#include <math.h>
Color rainbowColor(float speed) noexcept
{
        return Color(std::sin(speed * GlobalVars->realtime) * 0.5f + 0.5f,
        std::sin(speed * GlobalVars->realtime + 2 * PI / 3) * 0.5f + 0.5f,
        std::sin(speed * GlobalVars->realtime + 4 * PI / 3) * 0.5f + 0.5f);
}
