#include "main_menu.h"

Main_menu::Main_menu():
    Base_control()
{

}

void Main_menu::Render()
{
    if (ImGui::BeginMainMenuBar()) 
    {
        for (const auto& menu : menus)
        {
            if (ImGui::BeginMenu(menu.first.c_str()))
            {
                for (const auto& item : menu.second)
                {
                    if (ImGui::MenuItem(item.c_str())) {
                        On_click_item(item);
                    }
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndMainMenuBar();
    }
}

float Main_menu::Get_height()
{
    return ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();
}

void Main_menu::On_click_item(const std::string& item)
{
    if (callbacks[item]) {
        callbacks[item](item);
    }
}
