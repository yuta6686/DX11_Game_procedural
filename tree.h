#pragma once
#include "imodel.h"
class Tree :
    public IModel
{
private:
    const std::string _name = "tree";
public:

    // IModel ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui() override;
};

