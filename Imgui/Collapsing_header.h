#pragma once
#include "base_control.h"
#include "tree_node.h"

class Collapsing_header: public Base_control
{
public:
    Collapsing_header(const char* label, ImGuiTreeNodeFlags flags, Base_control& parent);
    void Render() override;
    Tree_node& AddNode(const char* label);
protected:
    std::string label_;
    ImGuiTreeNodeFlags flags_;
};



