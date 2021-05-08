#pragma once

// that is wrong.
class IClientThinkable
{
public:
	// Gets at the containing class...
	virtual void* GetIClientUnknown() = 0;

	virtual void				ClientThink() = 0;
	virtual void* GetThinkHandle() = 0;
	virtual void				SetThinkHandle(void* hThink) = 0;
};