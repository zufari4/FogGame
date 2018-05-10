#pragma once
#include "base_control.h"

class Tree_node : public Base_control
{
public:
    Tree_node(const char* label, Base_control& parent);
    void Render() override;
protected:
    std::string label_;
};