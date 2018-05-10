#include "window.h"

Window::Window(const std::string& name, float x, float y, float w, float h, int flags):
    Base_control(),
    name_(name),
    flags_(flags)
{
    SetPos(x, y);
    SetSize(w, h);
}

void Window::Render()
{
    ImGui::SetNextWindowPos(pos_, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size_, ImGuiCond_Always);
    ImGui::Begin(name_.c_str(), NULL, flags_);
    for (const auto& child : childs) {
        child->Render();
    }
    ImGui::End();
}
