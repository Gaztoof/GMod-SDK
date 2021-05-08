#pragma once

enum ShouldTransmitState_t
{
	SHOULDTRANSMIT_START = 0,	// The entity is starting to be transmitted (maybe it entered the PVS).

	SHOULDTRANSMIT_END		// Called when the entity isn't being transmitted by the server.
							// This signals a good time to hide the entity until next time
							// the server wants to transmit its state.
};

// NOTE: All of these are commented out; NotifyShouldTransmit actually
// has all these in them. Left it as an enum in case we want to go back though
enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,	// indicates it was created +and+ entered the pvs
//	DATA_UPDATE_ENTERED_PVS,
DATA_UPDATE_DATATABLE_CHANGED,
//	DATA_UPDATE_LEFT_PVS,
//	DATA_UPDATE_DESTROYED,		// FIXME: Could enable this, but it's a little worrying
								// since it changes a bunch of existing code
};
class IClientNetworkable
{
public:
	virtual void * GetIClientUnknown() = 0;
	virtual void* GetClientClass() = 0;
	virtual void			NotifyShouldTransmit(ShouldTransmitState_t state) = 0;

	virtual void			OnPreDataChanged(DataUpdateType_t updateType) = 0;
	virtual void			OnDataChanged(DataUpdateType_t updateType) = 0;

	virtual void			PreDataUpdate(DataUpdateType_t updateType) = 0;
	virtual void			PostDataUpdate(DataUpdateType_t updateType) = 0;
};
