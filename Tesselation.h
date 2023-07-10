#pragma once
#include "ipolygon.h"
class Tesselation :
    public IPolygon
{


public:    
    virtual void InitInside() override;

    virtual void UninitInside() override;

    virtual void Update() override;

    virtual void DrawShadow() override;

    virtual void DrawImgui() override;

};

