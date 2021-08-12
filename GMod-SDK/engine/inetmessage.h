#pragma once
#include "CNetChan.h"
#include "../tier1/bitbuf.h"
class CNetChan;
class INetMessage
{
public:
	virtual	~INetMessage() {};

	// Use these to setup who can hear whose voice.
	// Pass in client indices (which are their ent indices - 1).

	virtual void	SetNetChannel(CNetChan* netchan) = 0; // netchannel this message is from/for
	virtual void	SetReliable(bool state) = 0;	// set to true if it's a reliable message

	virtual bool	Process(void) = 0; // calles the recently set handler to process this message

	virtual	bool	ReadFromBuffer(bf_read*buffer) = 0; // returns true if parsing was OK
	virtual	bool	WriteToBuffer(bf_write*buffer) = 0;	// returns true if writing was OK

	virtual bool	IsReliable(void) const = 0;  // true, if message needs reliable handling

	virtual int				GetType(void) const = 0; // returns module specific header tag eg svc_serverinfo
	virtual int				GetGroup(void) const = 0;	// returns net message group of this message
	virtual const char* GetName(void) const = 0;	// returns network message name, eg "svc_serverinfo"
	virtual CNetChan* GetNetChannel(void) const = 0;
	virtual const char* ToString(void) const = 0; // returns a human readable string about message content
private:
	bool m_bReliable;
	CNetChan* m_pChan;

};
class CGModNetMessage : public INetMessage
{
public:
	CGModNetMessage(int iChannel, bf_read* pBuf)
		: m_iChannel(iChannel), m_pBuf(pBuf)
	{}
	virtual int GetType() const { return 18; }
	virtual int GetGroup() const { return INetChannelInfo::GENERIC; }
	//virtual const char* GetName() const { return "clc_GMod_ClientToServer"; }
	//virtual const char* ToString() const { return GetName(); }

	virtual bool WriteToBuffer(bf_write&);
public:
	int m_iChannel;
	bf_read* m_pBuf;
};

