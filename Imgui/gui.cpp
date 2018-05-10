#include <vector>
#include "gui.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_freetype.h"

namespace Gui
{
    SDL_Window* window_ = nullptr;
    std::vector<Base_control*> controls;
    float current_font_size_ = 1.0;

    void Init(SDL_Window* window)
    {
        ImGui_ImplSdlGL2_Init(window);
        window_ = window;
        current_font_size_ = ImGui::GetFontSize();
    }

    void Shutdown()
    {
        ImGui_ImplSdlGL2_Shutdown();
    }

    void New_frame()
    {
        ImGui_ImplSdlGL2_NewFrame(window_);
    }

    void Render()
    {
        for (const auto& control : controls)
        {
            control->Render();
        }
        ImGui::Render();
    }

    void ProcessEvent(SDL_Event* event)
    {
        ImGui_ImplSdlGL2_ProcessEvent(event);
    }

    float Get_main_menu_height()
    {
        return ImGui::GetStyle().FramePadding.y * 2 + current_font_size_;
    }

    bool Set_font(const char* filename, float size_in_px)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* font = io.Fonts->AddFontFromFileTTF(filename, size_in_px, NULL, io.Fonts->GetGlyphRangesCyrillic());
        if (font == NULL)
            return false;
        else {
            ImGuiFreeType::BuildFontAtlas(io.Fonts, ImGuiFreeType::RasterizerFlags::ForceAutoHint);
            current_font_size_ = size_in_px;
        }
        return font->IsLoaded();
    }

    void Set_rounding(float val)
    {
        ImGuiStyle* style = &ImGui::GetStyle();
        style->WindowRounding = val;
        style->FrameRounding = val;
        style->ScrollbarRounding = val;
        style->GrabRounding = val;
    }

    float Get_framerate()
    {
        return ImGui::GetIO().Framerate;
    }

    void Add_control(Base_control* control)
    {
        controls.push_back(control);
    }

    Main_menu& Create_main_menu()
    {
        Main_menu* control = new Main_menu();
        Add_control(control);
        return *control;
    }

    Window& Create_window(const std::string& name, float x, float y, float w, float h, int flags)
    {
        Window* control = new Window(name, x, y, w, h, flags);
        Add_control(control);
        return *control;
    }

    Image_button& Create_image_button(unsigned texture, float w, float h, Base_control& parent)
    {
        Image_button* control = new Image_button(texture, parent, w, h);
        return *control;
    }

    Collapsing_header& Create_collapsing_header(const char* label, ImGuiTreeNodeFlags flags, Base_control& parent)
    {
        Collapsing_header* control = new Collapsing_header(label, flags, parent);
        return *control;
    }

    Same_line& Create_same_line(Base_control& parent)
    {
        Same_line* control = new Same_line(parent);
        return *control;
    }

    Label& Create_label(Base_control& parent, const char* text /*= nullptr*/)
    {
        Label* control = new Label(parent, text);
        return *control;
    }
}