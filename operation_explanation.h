#pragma once
#include "game_object.h"
class OperationExplanation :
    public VGameObject
{
private:
    std::string _nodeText, _explanationText;
    bool _isOpen = true;
public:
    // VGameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

