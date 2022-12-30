#pragma once

class CPrediction 
{
    virtual ~CPrediction(void) = 0;//

    virtual void Init(void) = 0;//
    virtual void Shutdown(void) = 0;//

                                    // Implement IPrediction
public:

    virtual void Update
    (
        int startframe, // World update ( un-modded ) most recently received
        bool validframe, // Is frame data valid
        int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
        int outgoing_command // Last command (most recent) sent to server (un-modded)
    );//

    virtual void PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet);//
    virtual void PostEntityPacketReceived(void);//5
    virtual void PostNetworkDataReceived(int commands_acknowledged);//

    virtual void OnReceivedUncompressedPacket(void);//

                                                    // The engine needs to be able to access a few predicted values
    virtual void GetViewOrigin(Vector& org);//
    virtual void SetViewOrigin(Vector& org);// 9
    virtual void GetViewAngles(Vector& ang);//10
    virtual void SetViewAngles(Vector& ang);// 11

    virtual void GetLocalViewAngles(QAngle& ang);// 12
    virtual void SetLocalViewAngles(QAngle& ang);// 13

    virtual bool InPrediction(void) const;//14
    virtual bool IsFirstTimePredicted(void) const;// 15

    

    virtual int GetIncomingPacketNumber(void) const;//

    virtual void RunCommand(void* player, CUserCmd* cmd, void* moveHelper);//17

    virtual void SetupMove(C_BasePlayer* player, CUserCmd* cmd, void* pHelper, void* move);//18
    virtual void FinishMove(C_BasePlayer* player, CUserCmd* cmd, void* move);//19
    virtual void SetIdealPitch(int nSlot, void* player, const Vector& origin, const Vector& angles, const Vector& viewheight);//20

    virtual void CheckError(int nSlot, void* player, int commands_acknowledged);//
};