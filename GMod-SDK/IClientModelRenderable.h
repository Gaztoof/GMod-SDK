#pragma once

class IClientModelRenderable
{
public:
    virtual bool GetRenderData(void* pData, void* nCategory) = 0;
};
