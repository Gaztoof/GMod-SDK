#pragma once

#include <Windows.h>
#include "../globals.hpp"

constexpr float lisp = 11796120.f; // max value of short * 360

QAngle &BackupCMD(CUserCmd* cmd, bool run = false) {
    static float oldForward;
    static float oldSide;
    static float oldUp;
    static QAngle oldAng;
    if (!run)
    {
        oldForward = cmd->forwardmove;
        oldSide = cmd->sidemove;
        oldUp = cmd->upmove; // wanted to add up fixing but useless when i think of it...
        oldAng = cmd->viewangles;
    }
    else {
        if (localPlayer->getMoveType() == MOVETYPE_NOCLIP || localPlayer->getMoveType() == MOVETYPE_LADDER)
            return oldAng;

        // old = 160
        // new = 30
        //if(x < 0.) return x+360
        //+180
        float deltaYaw = ANG2DEG(cmd->viewangles.y - oldAng.y);

        // V this perfectly explains https://i.imgur.com/8cED0pl.png
        cmd->forwardmove = cos(DEG2RAD(deltaYaw)) * oldForward + cos(DEG2RAD(deltaYaw + 90.f)) * oldSide;
        cmd->sidemove = sin(DEG2RAD(deltaYaw)) * oldForward + sin(DEG2RAD(deltaYaw + 90.f)) * oldSide;
        if ((cmd->forwardmove < 0.001 && cmd->forwardmove > 0) || (cmd->forwardmove > -0.001 && cmd->forwardmove < 0)) cmd->forwardmove = 0;
        if ((cmd->sidemove < 0.001 && cmd->sidemove > 0) || (cmd->sidemove > -0.001 && cmd->sidemove < 0)) cmd->sidemove = 0;
         // ^ this'll make u undetected on a few servers
    }
    return oldAng;
}

// fake doesn't works yet
void StaticPitch(CUserCmd* cmd, bool down)
{
    if (Globals::Untrusted)
    {
        cmd->viewangles.x = down ? -90.f : 90.f;
    }
    else {
        cmd->viewangles.x = down ? -89.f : 89.f;
    }
}
void JitterPitch(CUserCmd* cmd)
{
    cmd->viewangles.x = (rand() % 2) ? -89.f : 89.f;
}
void FastSpin(CUserCmd* cmd)
{
	int random = rand() % 360;
    static float yaw = cmd->viewangles.y;
    yaw += random;
    cmd->viewangles.y += yaw;
}
void SlowSpin(CUserCmd* cmd)
{
    int random = rand() % 10;

    static float yaw = cmd->viewangles.y;
    yaw += random;

    cmd->viewangles.y = yaw;
}
void BackJitter(CUserCmd* cmd)
{
    static float yaw = cmd->viewangles.y;

        yaw += 50.f;
    if (rand() % 50 == 0)
        yaw += 180.f;
    cmd->viewangles.y = yaw;
}
void Inverse(CUserCmd* pCmd)
{
        pCmd->viewangles.y -= 180.f;
}
void Sideways(CUserCmd* cmd)
{
        cmd->viewangles.y -= 90.f;
}

void AntiAimPitch(CUserCmd* cmd, int kind)
{
    if (localPlayer->getMoveType() == MOVETYPE_NOCLIP || localPlayer->getMoveType() == MOVETYPE_LADDER ||cmd->buttons & (IN_USE | IN_ATTACK))
        return;

    switch (kind)
    {
    case 0:
        break;
    case 1:
        StaticPitch(cmd, false);
        break;
    case 2:
        StaticPitch(cmd, true);
        break;
    case 3:
        JitterPitch(cmd);
        break;

    }
}
void AntiAimYaw(CUserCmd* cmd, int kind)
{
    if (localPlayer->getMoveType() == MOVETYPE_NOCLIP || localPlayer->getMoveType() == MOVETYPE_LADDER || cmd->buttons & (IN_USE | IN_ATTACK))
        return;

    switch (kind)
    {
    case 0:
        break;
    case 1:
        FastSpin(cmd);
        break;
    case 2:
        SlowSpin(cmd);
        break;
    case 3:
        BackJitter(cmd);
        break;
    case 4:
        Inverse(cmd);
        break;
    case 5:
        Sideways(cmd);
        break;

    }
}