#pragma once
#include "single_model.h"
class ToriiHull :
    public SingleModel
{
public:

    virtual void Init() override;
    
    virtual void Update() override;

    virtual void DrawImgui() override;

};

