#pragma once
#include "imodel.h"
class Torii :
    public IModel
{    
protected:
    float _count = 100;
public:    
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui() override;
};

