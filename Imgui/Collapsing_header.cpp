#include "Collapsing_header.h"

Collapsing_header::Collapsing_header(const char* label, ImGuiTreeNodeFlags flags, Base_control& parent):
    Base_control(parent),
    label_(label),
    flags_(flags)
{

}

void Collapsing_header::Render()
{
    if (ImGui::CollapsingHeader(label_.c_str(), flags_)) {
        for (const auto& child : childs) {
            child->Render();
        }
    }
}

Tree_node& Collapsing_header::AddNode(const char* label)
{
    Tree_node* res = new Tree_node(label, *this);
    return *res;
}

