#pragma once
#include "imgui.h"
#include <vector>

class Base_control
{
public:
    Base_control();
    Base_control(Base_control& parent);
    virtual ~Base_control();
    virtual void Render();
    virtual void SetPos(float x, float y);
    virtual void SetSize(float w, float h);
    void Add_child(Base_control* child);
protected:
    Base_control* parent_;
    std::vector<Base_control*> childs;
    ImVec2 size_;
    ImVec2 pos_;
};