#include "same_line.h"

Same_line::Same_line(Base_control& parent):
    Base_control(parent)
{

}

void Same_line::Render()
{
    ImGui::SameLine();
}
