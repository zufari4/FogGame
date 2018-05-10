#include "editor.h"
#include "gui.h"

int main(int, char**)
{
    Editor editor;

    if (!editor.Init())
        return 1;

    Engine::Run();

    return 0;
}


Editor::Editor():
    ground_body(nullptr)
{
}

bool Editor::Init()
{
    if (!Engine::Init("Game editor", 1024, 768, CAMERA_SCALE, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE))
        return false;

    if (!Gui::Set_font("./res/Roboto-Regular.ttf", 0.18f * Engine::Get_dpi()))
        return false;

    if (!Engine::Init_physics(vec2(0, 10)))
        return false;

    Engine::Set_callback_frame(this, &Editor::Loop);
    Engine::Set_callback_window_resize(this, &Editor::On_window_resize);

    texture_btn_box    = Engine::Load_texture("./res/phy_box.png");
    texture_btn_join   = Engine::Load_texture("./res/phy_join.png");
    texture_btn_play   = Engine::Load_texture("./res/phy_play.png");
    texture_btn_pause  = Engine::Load_texture("./res/phy_pause.png");
    texture_btn_circle = Engine::Load_texture("./res/phy_circle.png");

    Main_menu& main_menu = Gui::Create_main_menu();
    main_menu.AddMenu("File", "Exit", this, &Editor::Exit_click);

    tools_window = &Gui::Create_window("Tools", 0, Gui::Get_main_menu_height(), 400, Engine::Get_surface_height() - Gui::Get_main_menu_height(),
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    play_btn = &Gui::Create_image_button(texture_btn_play->id, BTN_SIZE, BTN_SIZE, *tools_window);
    play_btn->Set_click(this, &Editor::Button_phy_run_click);
    
    Collapsing_header& header_create_objects = Gui::Create_collapsing_header("Create object", ImGuiTreeNodeFlags_DefaultOpen, *tools_window);
    Tree_node& node_phys_objects = header_create_objects.AddNode("Physics objects");
    Gui::Create_image_button(texture_btn_box->id, BTN_SIZE, BTN_SIZE, node_phys_objects).Set_click(this, &Editor::Button_phy_box_click);
    Gui::Create_same_line(node_phys_objects);
    Gui::Create_image_button(texture_btn_circle->id, BTN_SIZE, BTN_SIZE, node_phys_objects).Set_click(this, &Editor::Button_phy_circle_click);
    Gui::Create_same_line(node_phys_objects);
    Gui::Create_image_button(texture_btn_join->id, BTN_SIZE, BTN_SIZE, node_phys_objects).Set_click(this, &Editor::Button_phy_join_click);

    label_fps = &Gui::Create_label(*tools_window);
    return true;
}

void Editor::Loop(Uint32 now)
{
    label_fps->SetText("FPS: %u", Engine::Get_fps());
}

void Editor::On_window_resize(float w, float h)
{
    Engine::Setup_camera(w, h, CAMERA_SCALE);
    tools_window->SetPos(0, Gui::Get_main_menu_height());
    tools_window->SetSize(400, Engine::Get_surface_height() - Gui::Get_main_menu_height());
    Update_phy_wall(w, h);
}

void Editor::Button_phy_run_click(Base_control& sender)
{
    if (Engine::Physic_paused()) {
        Engine::Start_physics();
        play_btn->Set_texture(texture_btn_pause->id);
    }
    else {
        Engine::Pause_physics();
        play_btn->Set_texture(texture_btn_play->id);
    }
}

void Editor::Button_phy_box_click(Base_control& sender)
{
    Phy_box* object = new Phy_box();
    vec2 center(Engine::Get_surface_width() * Engine::Get_camera_scale() * 0.5f, Engine::Get_surface_height() * Engine::Get_camera_scale() * 0.5f);
    object->Set_pos(center);
    object->Show();
}

void Editor::Button_phy_circle_click(Base_control& sender)
{
    Phy_circle* object = new Phy_circle();
    vec2 center(Engine::Get_surface_width() * Engine::Get_camera_scale() * 0.5f, Engine::Get_surface_height() * Engine::Get_camera_scale() * 0.5f);
    object->Set_pos(center);
    object->Show();
}


void Editor::Button_phy_join_click(Base_control& sender)
{
    Phy_join* object = new Phy_join();
    vec2 center(Engine::Get_surface_width() * Engine::Get_camera_scale() * 0.5f, Engine::Get_surface_height() * Engine::Get_camera_scale() * 0.5f);
    object->Set_line(center - vec2(10 * Engine::Get_camera_scale(), 0), center + vec2(10 * Engine::Get_camera_scale(), 0));
    object->Show();
}

void Editor::Exit_click(const std::string&)
{
    Engine::Stop();
}

void Editor::Update_phy_wall(float w, float h)
{
    w *= Engine::Get_camera_scale();
    h *= Engine::Get_camera_scale();
    // Define the ground body.
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(w / 2.0f, h);
    if (ground_body == nullptr)
        ground_body = Engine::Get_world().CreateBody(&body_def);
    else {
        ground_body->DestroyFixture(ground_body->GetFixtureList());
    }
    b2EdgeShape shape;
    shape.Set(vec2(-w, 0.0), vec2(w, 0.0));
    ground_body->CreateFixture(&shape, 0.0f);
}