#include "editor.h"

int main(int, char**)
{
    Editor editor;

    if (!editor.Init())
        return 1;

    editor.Run();

    return 0;
}


Editor::Editor():
    ground_body(nullptr)
{
}

bool Editor::Init()
{
    if (!engine.Init("Game editor", 1024, 768, SDL_WINDOW_MAXIMIZED| SDL_WINDOW_RESIZABLE))
        return false;

    if (!engine.Set_gui_font("./res/Roboto-Regular.ttf", engine.Get_dpi() * 0.2f))
        return false;

    if (!engine.Init_physics(vec2(0, 10)))
        return false;

    engine.Set_callback_frame(this, &Editor::Loop);
    engine.Set_callback_window_resize(this, &Editor::On_window_resize);

    texture_btn_box   = engine.Load_texture("./res/phy_box.png");
    texture_btn_join  = engine.Load_texture("./res/phy_join.png");
    texture_btn_play  = engine.Load_texture("./res/phy_play.png");
    texture_btn_pause = engine.Load_texture("./res/phy_pause.png");
    texture_btn_circle = engine.Load_texture("./res/phy_circle.png");

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

void Editor::On_window_resize(int w, int h)
{
    surf_width  = float(w);
    surf_height = float(h);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    Update_phy_wall((float)w, (float)h);
}

void Editor::Draw_gui()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                Exit_click();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    float y_offset = engine.Get_main_menu_height();
    ImGui::SetNextWindowPos(ImVec2(0, y_offset), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, surf_height-y_offset), ImGuiCond_Always);

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

    if (ImGui::CollapsingHeader("Create object", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::TreeNode("Physics objects"))
        {
            if (ImGui::ImageButton((ImTextureID)texture_btn_box->id, v)) Button_phy_box_click();
            ImGui::SameLine();
            if (ImGui::ImageButton((ImTextureID)texture_btn_circle->id, v)) Button_phy_circle_click();
            ImGui::SameLine();
            if (ImGui::ImageButton((ImTextureID)texture_btn_join->id, v)) Button_phy_join_click();
            ImGui::TreePop();
        }
    }

    ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
    ImGui::End();
}

void Editor::Button_phy_run_click()
{
    if (engine.phy_pause)
        engine.Start_physics();
    else engine.Pause_physics();
}

void Editor::Button_phy_box_click()
{
    Phy_box* object = new Phy_box();
    vec2 center(surf_width / 2, surf_height / 2);
    object->Set_pos(center);
    object->Show();
}

void Editor::Button_phy_circle_click()
{
    Phy_circle* object = new Phy_circle();
    vec2 center(surf_width / 2, surf_height / 2);
    object->Set_pos(center);
    object->Show();
}


void Editor::Button_phy_join_click()
{
    Phy_join* object = new Phy_join();
    vec2 center(surf_width / 2, surf_height / 2);
    object->Set_line(center - vec2(10, 0), center + vec2(10, 0));
    object->Show();
}

void Editor::Exit_click()
{
    engine.Stop();
}

void Editor::Update_phy_wall(float w, float h)
{
    // Define the ground body.
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(p2m(w / 2.0f), p2m(h));
    if (ground_body == nullptr)
        ground_body = engine.Create_body(body_def);
    else {
        ground_body->DestroyFixture(ground_body->GetFixtureList());
    }
    b2EdgeShape shape;
    shape.Set(vec2(-w, 0.0), vec2(w, 0.0));
    ground_body->CreateFixture(&shape, 0.0f);
}