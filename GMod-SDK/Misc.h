#pragma once

#include "Vector.h"
#include "globals.h"
#include "ImGui/imgui.h"

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
    "physics/metal/metal_solid_impact_bullet2",
    "buttons/arena_switch_press_02",
    "training/timer_bell",
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

        if (target == localPlayerID || EngineClient->GetPlayerForUserID(event->GetInt("attacker")) != localPlayerID)
            return;

        if (Settings::Misc::hitmarkerSoundEnabled)
        {
            std::string command = "play \"";
            command += hitMarkers[Settings::Misc::hitmarkerSound];
            command += "\"";
            EngineClient->ClientCmd_Unrestricted(command.c_str());
        }
        
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
        // event->GetInt("damagebits"), do whatever you want with that i'm lazy rn

        if (target == localPlayerID || event->GetInt("entindex_attacker") != localPlayerID)
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
    ray.Init(view.origin, view.origin + ((view.angles.toVector() * -1) * Settings::Misc::thirdpersonDistance));
    EngineTrace->TraceRay(ray, MASK_SOLID, &filter, &trace);

    view.origin = trace.endpos;
}
void FreeCam(CViewSetup &view, Vector& camPos) 
{
    if (camPos == Vector(0, 0, 0))
        camPos = view.origin;

    float speed = Settings::Misc::freeCamSpeed;

    if (Settings::lastCmd.buttons & IN_SPEED)
        speed *= 5.f;
    if (Settings::lastCmd.buttons & IN_DUCK)
        speed *= 0.5f;
    if (Settings::lastCmd.buttons & IN_JUMP)
        camPos.z += speed;

    if (Settings::lastCmd.buttons & IN_FORWARD)
        camPos += (view.angles.toVector() * speed);

    if (Settings::lastCmd.buttons & IN_BACK)
        camPos -= (view.angles.toVector() * speed);

    if (Settings::lastCmd.buttons & IN_MOVELEFT)
        camPos += (view.angles.SideVector() * speed);

    if (Settings::lastCmd.buttons & IN_MOVERIGHT)
        camPos -= (view.angles.SideVector() * speed);

    view.origin = camPos;
}
void SpectatorList() 
{
    if (!Settings::Misc::drawSpectators || !localPlayer || !localPlayer->IsAlive())
        return;

    ImGui::SetNextWindowSize(ImVec2(200.f, 200.f));
    ImGui::BeginMenuBackground("Spectators window", &Settings::openMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar);
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
    if (Settings::Misc::flashlightSpam && InputSystem->IsButtonDown(KEY_F))
        cmd->impulse = 100; // FlashLight spam
}
void UseSpam(CUserCmd* cmd)
{
    if (Settings::Misc::useSpam && InputSystem->IsButtonDown(KEY_E))
    {
        if(cmd->command_number % 2)
        cmd->buttons |= IN_USE;
        else cmd->buttons &= ~IN_USE;
    }
}
void BunnyHop(CUserCmd* cmd)
{
    if (InputSystem->IsButtonDown(KEY_SPACE)) {
        int flags = localPlayer->getFlags();
        if (Settings::Misc::bunnyHop)
        {
            if (!(flags & FL_ONGROUND))
                cmd->buttons &= ~IN_JUMP;
            else
                cmd->buttons |= IN_JUMP;
        }
        if (Settings::Misc::autoStrafe && !(flags & FL_ONGROUND))
        {
            if (Settings::Misc::autoStrafeStyle == 0) // Legit
            {
                if (!(flags & FL_ONGROUND)) {
                    cmd->sidemove = cmd->mousedx < 0 ? -450.f : 450.f;
                }
            }
            else if (Settings::Misc::autoStrafeStyle == 1) { // Silent-strafe
                if (cmd->mousedy == 0.f)
                {
                    cmd->viewangles.y += (cmd->command_number % 2) ? 1.f : -1.f;
                    cmd->sidemove = (cmd->command_number % 2) ? 450.f : -450.f;
                }
                else  cmd->sidemove = cmd->mousedx < 0 ? -450.f : 450.f;
            }
            else if (Settings::Misc::autoStrafeStyle == 2) { // Rage-strafe
                


            }
        }

        if (!(flags & FL_ONGROUND))
            cmd->buttons &= ~IN_SPEED;
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