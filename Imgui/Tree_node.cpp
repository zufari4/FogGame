#include "Tree_node.h"

Tree_node::Tree_node(const char* label, Base_control& parent) :
    Base_control(parent),
    label_(label)
{
}

void Tree_node::Render()
{
    if (ImGui::TreeNode(label_.c_str())) {
        for (const auto& child : childs) {
            child->Render();
        }
        ImGui::TreePop();
    }
}