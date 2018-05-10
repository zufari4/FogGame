#pragma once
#include <SDL.h>
#include "base_control.h"
#include "main_menu.h"
#include "window.h"
#include "image_button.h"
#include "collapsing_header.h"
#include "same_line.h"
#include "label.h"

namespace Gui
{
    void  Init(SDL_Window* window);
    void  Shutdown();
    void  New_frame();
    void  Render();
    void  ProcessEvent(SDL_Event* event);
    float Get_main_menu_height();
    bool  Set_font(const char* filename, float size_in_px);
    void  Set_rounding(float val);
    float Get_framerate();
    Main_menu& Create_main_menu();
    Window& Create_window(const std::string& name, float x, float y, float w, float h, int flags);
    Image_button& Create_image_button(unsigned texture, float w, float h, Base_control& parent);
    Collapsing_header& Create_collapsing_header(const char* label, ImGuiTreeNodeFlags flags, Base_control& parent);
    Same_line& Create_same_line(Base_control& parent);
    Label& Create_label(Base_control& parent, const char* text = "");
}