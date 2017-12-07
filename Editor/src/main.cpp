#include "editor.h"

int main(int, char**)
{
    Editor editor;

    if (!editor.Init())
        return 1;

    editor.Run();

    return 0;
}

bool Editor::Init()
{
    if (!engine.Init("Game editor", 1024, 768, SDL_WINDOW_MAXIMIZED| SDL_WINDOW_RESIZABLE))
        return false;

    if (!engine.Set_gui_font("./res/Roboto-Regular.ttf", 21))
        return false;

    if (!engine.Init_physics(vec2(0, 10)))
        return false;

    engine.Set_callback_frame(this, &Editor::Loop);
    engine.Set_callback_mouse_down(this, &Editor::On_mouse_down);
    engine.Set_callbac_mouse_up(this, &Editor::On_mouse_up);
    engine.Set_callback_mouse_move(this, &Editor::On_mouse_move);
    engine.Set_callback_window_resize(this, &Editor::On_window_resize);

    texture_btn_box   = engine.Load_texture("./res/phy_box.png");
    texture_btn_join  = engine.Load_texture("./res/phy_join.png");
    texture_btn_play  = engine.Load_texture("./res/phy_play.png");
    texture_btn_pause = engine.Load_texture("./res/phy_pause.png");

    float w = (float)engine.Get_surface_width();
    float h = (float)engine.Get_surface_height();
    // Define the ground body.
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(p2m(w/2.0f), p2m(h));
    b2Body* ground_body = engine.Create_body(body_def);
    b2EdgeShape shape;
    shape.Set(vec2(-w, 0.0), vec2(w, 0.0));
    ground_body->CreateFixture(&shape, 0.0f);

    return true;
}

void Editor::Run()
{
    engine.phy_pause = true;
    engine.Run();
}

void Editor::Loop(Uint32 now)
{
    Draw_gui();
}

void Editor::On_mouse_down(int x, int y, int button)
{
    //rect->Show();
    //rect->a = vec2(x, y);
}

void Editor::On_mouse_up(int x, int y, int button)
{
    //rect->Hide();
}

void Editor::On_mouse_move(int x, int y)
{
    //rect->b = vec2(x, y);
}

void Editor::On_window_resize(int w, int h)
{
    surf_width  = w;
    surf_height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Editor::Draw_gui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, (float)surf_height), ImGuiCond_Always);

    ImGui::Begin("Main", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    ImVec2 v(48, 48);
    if (engine.phy_pause) {
        if (ImGui::ImageButton((ImTextureID)texture_btn_play->id, v))
            Button_phy_run_click();
    }
    else {
        if (ImGui::ImageButton((ImTextureID)texture_btn_pause->id, v))
            Button_phy_run_click();
    }
    if (ImGui::CollapsingHeader("Create object", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::TreeNode("Physics objects")) 
        {
            
            if (ImGui::ImageButton((ImTextureID)texture_btn_box->id, v)) {
                Button_phy_box_click();
            }

            ImGui::SameLine();
            ImGui::ImageButton((ImTextureID)texture_btn_join->id, v);
            ImGui::TreePop();
        }
    }

    ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
    ImGui::End();
}

void Editor::Button_phy_box_click()
{
    Phy_box* box = new Phy_box();
    vec2 center((float)engine.Get_surface_width()/2, (float)engine.Get_surface_height() / 2);
    box->Set_rect(center - vec2(100, 100), center + vec2(100, 100));
    box->Show();
}

void Editor::Button_phy_run_click()
{
    if (engine.phy_pause)
        engine.Start_physics();
    else engine.Pause_physics();
}
