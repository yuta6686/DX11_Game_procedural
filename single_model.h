#pragma once
#include "imodel.h"
class SingleModel :
    public IModel
{   
public:

    virtual void Init() = 0;

    virtual void Uninit() override;

    virtual void Update()=0;

    virtual void Draw() override;

    virtual void DrawImgui()=0;

protected:
    void InitShader(const char* VS, const char* PS);
    void InitName(std::string name = "unknown");
    void InitTransform();
};

