#include "base_control.h"

Base_control::Base_control():
    parent_(nullptr),
    size_(0,0),
    pos_(0,0)
{
}

Base_control::Base_control(Base_control& parent) : 
    parent_(&parent),
    size_(0, 0),
    pos_(0, 0)
{
    parent_->Add_child(this);
}

Base_control::~Base_control()
{
}

void Base_control::Render()
{
}

void Base_control::SetPos(float x, float y)
{
    pos_ = ImVec2(x, y);
}

void Base_control::SetSize(float w, float h)
{
    size_ = ImVec2(w, h);
}

void Base_control::Add_child(Base_control* child)
{
    childs.push_back(child);
}
