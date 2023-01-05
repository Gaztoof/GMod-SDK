#pragma once

#include "../tier0/Vector.h"
#include "../globals.hpp"
#include "../ImGui/imgui.h"
#include "ImGui/imgui-notify/imgui_notify.h"

const char* killMessages[]{
    "Hah, you died!",
    "too bad you're dead",
    "you indirectly got raped by gaztoof",
    "gaztoof indirectly raped ya",
    "lmao you ded",
    "i feel bad for you lmao",
    "get yourself more skills",
    "ez noob",
    "ezzzzz",
    "you might want to check this out: https://www.unknowncheats.me/forum/3137947-post1.html",
    "you got raped by: https://www.unknowncheats.me/forum/3137947-post1.html",
    "i use this: https://www.unknowncheats.me/forum/3137947-post1.html",
    "you got raped by GMOD-SDK",
};
const char* hitMarkers[]{
    "physics/metal/metal_solid_impact_bullet2.wav",
    "training/timer_bell.wav",
};


// https://wiki.facepunch.com/gmod/Game_Events
class DamageEvent : IGameEventListener2
{
public:
    DamageEvent(void) {};
    ~DamageEvent(void) {};
    void FireGameEvent(IGameEvent* event) override
    {
        if (!event)
            return;
        int localPlayerID = EngineClient->GetLocalPlayer();
        int target = EngineClient->GetPlayerForUserID(event->GetInt("userid")); // UserID of the victim
        int attacker = EngineClient->GetPlayerForUserID(event->GetInt("attacker")); // UserID of the attacker

        player_info_s targetInfo;
        player_info_s attackerInfo;
        EngineClient->GetPlayerInfo(target, &targetInfo);
        EngineClient->GetPlayerInfo(attacker, &attackerInfo);

        if (strlen(attackerInfo.name))
        {
            std::string outputString = string_format("%s attacked %s. NEW HP: %i", attackerInfo.name, targetInfo.name, event->GetInt("health"));
            std::cout << outputString.c_str() << std::endl;
            ImGuiToast toast(ImGuiToastType_None, 3000); // <-- content can also be passed here as above
            toast.set_title("Damage-Event");
            toast.set_content(outputString.c_str());
            ImGui::InsertNotification(toast);
        }

        if (target == localPlayerID || attacker != localPlayerID)
            return;

        if (Settings::Misc::hitmarkerSoundEnabled)
            MatSystemSurface->PlaySound(hitMarkers[Settings::Misc::hitmarkerSound]);
        
        Settings::lastHitmarkerTime = EngineClient->Time();
    }
};
class DeathEvent : IGameEventListener2
{
public:
    DeathEvent(void) {};
    ~DeathEvent(void) {};
    void FireGameEvent(IGameEvent* event) override
    {
        if (!event)
            return;
        int localPlayerID = EngineClient->GetLocalPlayer();
        int target = event->GetInt("entindex_killed"); // Entity Index of the victim
        int attacker = event->GetInt("entindex_attacker"); // Entity Index of the attacker

        // event->GetInt("damagebits"), do whatever you want with that i'm lazy rn

        if (target == localPlayerID || attacker != localPlayerID)
            return;

        if (Settings::Misc::killMessage)
        {
            std::string command = "say \"";
            if (Settings::Misc::killMessageOOC)
                command += "/ooc ";
            command += killMessages[rand() % (sizeof(killMessages) / sizeof(uintptr_t))];
            command += "\"";
            EngineClient->ClientCmd_Unrestricted(command.c_str());
        }
    }
};
void ThirdPerson(CViewSetup& view)
{
    trace_t trace;
    Ray_t ray;
    CTraceFilter filter;
    filter.pSkip = localPlayer;
    ray.Init(view.origin, view.origin + ((Globals::lastCmd.viewangles.toVector() * -1) * Settings::Misc::thirdpersonDistance));
    EngineTrace->TraceRay(ray, MASK_SOLID, &filter, &trace);

    view.origin = trace.endpos;
}
void FreeCam(CViewSetup &view, Vector& camPos) 
{
    if (camPos == Vector(0, 0, 0))
        camPos = view.origin;

    float speed = Settings::Misc::freeCamSpeed;

    if (Globals::lastCmd.buttons & IN_SPEED)
        speed *= 5.f;
    if (Globals::lastCmd.buttons & IN_DUCK)
        speed *= 0.5f;
    if (Globals::lastCmd.buttons & IN_JUMP)
        camPos.z += speed;

    if (Globals::lastCmd.buttons & IN_FORWARD)
        camPos += (view.angles.toVector() * speed);

    if (Globals::lastCmd.buttons & IN_BACK)
        camPos -= (view.angles.toVector() * speed);

    if (Globals::lastCmd.buttons & IN_MOVELEFT)
        camPos += (view.angles.SideVector() * speed);

    if (Globals::lastCmd.buttons & IN_MOVERIGHT)
        camPos -= (view.angles.SideVector() * speed);

    view.origin = camPos;
}
void SpectatorList() 
{
    if (!Settings::Misc::drawSpectators || !localPlayer || !localPlayer->IsAlive())
        return;

    ImGui::SetNextWindowSize(ImVec2(200.f, 200.f));
    ImGui::BeginMenuBackground("Spectators window", &Globals::openMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::ColorBar("rainbowBar3", ImVec2(648.f, 2.f));
        std::string names = "";
        for (int i = 0; i < ClientEntityList->GetHighestEntityIndex(); i++)
        {
            C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(i);
            if (entity == nullptr || !entity->IsPlayer() || entity == localPlayer) // https://wiki.facepunch.com/gmod/Enums/TEAM
                continue;
            if (entity->GetObserverTarget() != localPlayer)
                continue;

            player_info_s info;
            EngineClient->GetPlayerInfo(i, &info);

            names += std::string(info.name) + "\n";
        }
        ImGui::GetStyle().ItemSpacing = ImVec2(4, 2);
        ImGui::GetStyle().WindowPadding = ImVec2(4, 4);
        ImGui::SameLine(15.f);
        ImGui::Text(names.c_str());

    }
    ImGui::End();
}
int flagsPrePred = 0;
void QuickStop(CUserCmd* cmd)
{
	if (!Settings::Misc::quickStop || cmd->buttons & (IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT) || !(localPlayer->getFlags() & FL_ONGROUND))
		return;

    Vector velocity = localPlayer->getVelocity();
    float speed = velocity.Length2D();
    if (speed < 15.0f)
        return;

    QAngle direction = velocity.toAngle();
    direction.y = cmd->viewangles.y - direction.y;

    const auto negatedDirection = direction.toVector() * -speed;
    cmd->forwardmove = negatedDirection.x;
    cmd->sidemove = negatedDirection.y;
}
void FlashSpam(CUserCmd* cmd)
{
    if (Settings::Misc::flashlightSpam && InputSystem->IsButtonDown(KEY_F) && !MatSystemSurface->IsCursorVisible())
        cmd->impulse = 100; // FlashLight spam
}
void UseSpam(CUserCmd* cmd)
{
    if (Settings::Misc::useSpam && InputSystem->IsButtonDown(KEY_E) && !MatSystemSurface->IsCursorVisible())
    {
        if(cmd->command_number % 2)
        cmd->buttons |= IN_USE;
        else cmd->buttons &= ~IN_USE;
    }
}
void BunnyHopOptimizer(CUserCmd* cmd)
{
    /*float dStack92 = cmd->viewangles.y;
    float dStack76 = 0.f;
    dStack76 = (dStack76 * 180.f) / M_PI;

    float dStack84 = dStack76 - dStack92;
    float dStack68 = dStack84 + 180.f;
    float dVar17 = dStack68 - 180.f;
    if (180.f <= dVar17)
    {
        dVar17 = dVar17 - 360.f;
    }
    if (dVar17 < 24.f)
    {
        dVar17 = dStack76;
        float dVar18 = dStack92;
        if (180.f < dStack84)
        {
            dVar18 = cmd->viewangles.y;
            if (dStack76 <= dVar18)
                dVar17 = dStack76 + 360.f;
            else dVar18 = dVar18 - 360.f;
        }
        dStack68 = (dVar17 - dVar18) + dVar18 + 180.f;
        cmd->viewangles.y = (dStack68 - 180.f);
    }

    return;

    */
    if (!(localPlayer->getFlags() & FL_ONGROUND))
    {
        cmd->sidemove = -10000.f;
        cmd->forwardmove = 0.f;
        cmd->mousedx = -1.f;
    }
    QAngle viewAngles = cmd->viewangles;
    static QAngle lastViewAng = viewAngles;
    Vector absVel = localPlayer->getVelocity();
    absVel.z = 0;

    if((cmd->sidemove > 0.f && cmd->mousedx > 0.f) || (cmd->sidemove < 0.f && cmd->mousedx < 0.f))
    if ((InputSystem->IsButtonDown(KEY_SPACE) && !(localPlayer->getFlags() & FL_ONGROUND)) && localPlayer->getVelocity().Length() > 50.f && cmd->sidemove != 0.f && absVel.Length() != 0)
    {
        float tickrate = (1.f / GlobalVars->interval_per_tick);
        float strafes = (1.f / GlobalVars->frametime) / tickrate; // framerate / tickrate
        QAngle currVelAng = localPlayer->getVelocity().toAngle();
        QAngle angDiff = (currVelAng - lastViewAng).FixAngles();
        std::cout << "old angDiff: " << angDiff.y << " : absVel: " << absVel.x << " : "<< absVel.y << " : " << absVel.Length() << std::endl;
        angDiff.y = RAD2DEG(asin(32.8f / absVel.Length()));// * 57.29577951308;
        std::cout << "new angDiff: " << angDiff.y << std::endl;
        std::cout << strafes << std::endl;
        if (Settings::Misc::optiRandomization)
            angDiff.y *= (0.6 + (float)(rand()) / ((float)(RAND_MAX / (1.4 - 0.6)))); // Randomization for anticheats

        viewAngles.y += (angDiff.y * (Settings::Misc::optiStrength/100.f));
        viewAngles.y = lastViewAng.y + (angDiff.y * (Settings::Misc::optiStrength / 100.f) / strafes);
        viewAngles.FixAngles();
        //viewAngles = currVelAng;

        cmd->viewangles = viewAngles;
        EngineClient->SetViewAngles(viewAngles);
    }
    //lastViewAng = localPlayer->getVelocity().toAngle();
    lastViewAng = viewAngles;

    return;

    static QAngle previousAngles = cmd->viewangles;
    if (InputSystem->IsButtonDown(KEY_SPACE) && !MatSystemSurface->IsCursorVisible()) {
        float tickrate = (1.f / GlobalVars->interval_per_tick);
        float strafes = (1.f / GlobalVars->frametime) / tickrate; // framerate / tickrate

        auto currVel = localPlayer->getVelocity();
        currVel.z = 0;
        float A = RAD2DEG(atan(32.8f / currVel.Length())); // difference of angle to the next tick's optimal strafe angle
        float D = (0.75* A) / strafes;// optimal number of degrees per strafe given the desired number of strafes per jump, the tickrate of the server, and the current player velocity defined in v_1

        QAngle viewAngles;
        EngineClient->GetViewAngles(viewAngles);
        viewAngles.FixAngles();
        if (currVel.Length())
        {
            float angDiff = 0.f;
            if (!Settings::Misc::optiStyle)
            {
                if (cmd->mousedx < 0.f && (cmd->sidemove < 0.f))
                angDiff = (viewAngles.y) - (previousAngles.y);
                else if (cmd->mousedx > 0.f && (cmd->sidemove > 0.f))
                    angDiff = (previousAngles.y) - (viewAngles.y);
                while (angDiff < 0) angDiff += 360.f;

                if (angDiff < D)
                    angDiff += ((D - angDiff) * (Settings::Misc::optiStrength / 100));
                else if (Settings::Misc::optiClamp) angDiff = D;
            }
            else angDiff = D * (Settings::Misc::optiStrength / 100);

            if(Settings::Misc::optiRandomization)
            angDiff += (0.05 + (float)(rand()) / ((float)(RAND_MAX / (0.1 - 0.05)))); // Randomization for anticheats

            if (!(localPlayer->getFlags() & FL_ONGROUND)) {
                if (cmd->mousedx < 0)
                {
                    cmd->sidemove = -10000.f;
                    cmd->buttons |= IN_MOVELEFT;
                }
                else if (cmd->mousedx > 0) {
                    cmd->sidemove = 10000.f;
                    cmd->buttons |= IN_MOVERIGHT;
                }
            }

            if (cmd->mousedx < 0.f && (cmd->sidemove < 0.f)) { // Left
                viewAngles.y = (previousAngles.y + angDiff);
            }
            else if (cmd->mousedx > 0.f && (cmd->sidemove > 0.f)) { // Right
                viewAngles.y = (previousAngles.y - angDiff);
                angDiff = -angDiff;
            }

            cmd->mousedx = angDiff;
            viewAngles.FixAngles();
            cmd->viewangles = viewAngles;
            EngineClient->SetViewAngles(viewAngles);
        }
    }
    previousAngles = cmd->viewangles;
}
void BunnyHop(CUserCmd* cmd)
{
    int flags = localPlayer->getFlags();
    if (false && Settings::Misc::fastWalk && flags & FL_ONGROUND && (cmd->forwardmove != 0.f && cmd->sidemove == 0.f)) // Fastwalk
    {
        if (cmd->command_number % 2 == 0)
            cmd->sidemove = -5000.f;
        else cmd->sidemove = 5000.f;
    }
    if (InputSystem->IsButtonDown(KEY_SPACE) && !MatSystemSurface->IsCursorVisible() && localPlayer->getMoveType() != MOVETYPE_NOCLIP) {
        if (Settings::Misc::bunnyHop)
        {
            if (!(flagsPrePred & FL_ONGROUND))
                cmd->buttons &= ~IN_JUMP;
            else
                cmd->buttons |= IN_JUMP;
        }
        if ((Settings::Misc::autoStrafe || Settings::Misc::optiAutoStrafe) && !(flags & FL_ONGROUND))
        {
            if (Settings::Misc::autoStrafeStyle == 0 || (Settings::Misc::optiAutoStrafe && Settings::Misc::autoStrafeStyle == 2)) // Legit
            {
                if (!(flags & FL_ONGROUND)) {
                    if (cmd->mousedx > 0.f)
                        cmd->sidemove = 10000.f;
                    else if (cmd->mousedx < 0.f) cmd->sidemove = -10000.f;
                }
            }
            else if (Settings::Misc::autoStrafeStyle == 1) { // Silent-strafe
                if (cmd->mousedx == 0.f)
                {
                    cmd->viewangles.y += (cmd->command_number % 2) ? 1.f : -1.f;
                    cmd->sidemove = (cmd->command_number % 2) ? 10000.f : -10000.f;

                    /*QAngle absVelAng = localPlayer->getVelocity().toAngle();

                    cmd->viewangles.y = absVelAng.y;
                    cmd->viewangles.FixAngles();*/

                }
                else  cmd->sidemove = cmd->mousedx < 0 ? -10000.f : 10000.f;
                if (cmd->sidemove > 0)
                    cmd->buttons |= IN_MOVELEFT;
                else if (cmd->sidemove < 0)cmd->buttons |= IN_MOVERIGHT;

                cmd->viewangles.FixAngles();
            }
        }

        if (!(flags & FL_ONGROUND))
            cmd->buttons &= ~IN_SPEED;
    }

    if (Settings::Misc::autoStrafeStyle == 2) { // Optimizer
        //BunnyHopOptimizer(cmd);
    }
}


void PrePredOptimizer(CUserCmd* cmd)
{
    if (localPlayer->getMoveType() == MOVETYPE_LADDER || localPlayer->getMoveType() == MOVETYPE_NOCLIP)
        return;

    flagsPrePred = localPlayer->getFlags();

    if (!(InputSystem->IsButtonDown(KEY_SPACE) || cmd->buttons & IN_JUMP) || localPlayer->getFlags() & FL_ONGROUND)
        return;
    cmd->sidemove = (cmd->command_number % 2) ? 10000.f : -10000.f;
    cmd->forwardmove = 0.f;

}
void PostPredOptimizer(CUserCmd* cmd)
{
    if (localPlayer->getMoveType() == MOVETYPE_LADDER || localPlayer->getMoveType() == MOVETYPE_NOCLIP)
        return;

    if (!(flagsPrePred & FL_ONGROUND) && localPlayer->getFlags() & FL_ONGROUND)
    {
        cmd->buttons &= ~IN_DUCK;
        cmd->buttons |= IN_JUMP;
    }
    else if(!(localPlayer->getFlags() & FL_ONGROUND)/* && !(flagsPrePred & FL_ONGROUND)*/)
        cmd->buttons |= IN_DUCK;

    //if ((cmd->sidemove > 0.f && cmd->mousedx > 0.f) || (cmd->sidemove < 0.f && cmd->mousedx < 0.f))
    if ((InputSystem->IsButtonDown(KEY_SPACE) && !(localPlayer->getFlags() & FL_ONGROUND)) && localPlayer->getVelocity().Length() > 50.f && cmd->sidemove != 0.f)
    {
        QAngle viewAngles = cmd->viewangles;
        QAngle currVelAng = localPlayer->getVelocity().toAngle();
        viewAngles.y = currVelAng.y;
        viewAngles.FixAngles();
        //viewAngles = currVelAng;

        cmd->viewangles = viewAngles;
        EngineClient->SetViewAngles(viewAngles);
    }
}

void PrePrediction(CUserCmd* cmd)
{
    if (Settings::Misc::autoStrafeStyle == 2)
        PrePredOptimizer(cmd);

    flagsPrePred = localPlayer->getFlags();
}
void PostPrediction(CUserCmd* cmd)
{
    if (Settings::Misc::autoStrafeStyle == 2)
        PostPredOptimizer(cmd);

    if (!Settings::Misc::edgeJump) return;
    int flags = localPlayer->getFlags();
    if (localPlayer->getMoveType() == MOVETYPE_LADDER || localPlayer->getMoveType() == MOVETYPE_NOCLIP)
        return;
    if (flagsPrePred & FL_ONGROUND && !(flags & FL_ONGROUND))
        cmd->buttons |= IN_JUMP;

    if ( cmd->buttons & IN_JUMP) // Crouchboost
    {
        if(!(flagsPrePred & FL_ONGROUND))
            cmd->buttons |= IN_DUCK;

        if (!(flagsPrePred & FL_ONGROUND) && flags & FL_ONGROUND && cmd->buttons & IN_DUCK)
            cmd->buttons &= ~IN_DUCK;
    }
}

void DoMisc(CUserCmd* cmd)
{
    if (localPlayer->getMoveType() == MOVETYPE_NOCLIP || localPlayer->getMoveType() == MOVETYPE_LADDER)
        return;
    QuickStop(cmd);
    FlashSpam(cmd);
    UseSpam(cmd);
    BunnyHop(cmd);
}