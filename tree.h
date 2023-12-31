#pragma once
#include "imodel.h"
class Tree :
    public IModel
{
private:
    const std::string _name = "tree";
public:

    // IModel を介して継承されました
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui() override;
};

