#include "editor.h"
#include "gui.h"
#include "physic_circle_editable.h"
#include "physic_box_editable.h"
#include "physic_distance_join_editable.h"
#include "physic_revolute_joint_editable.h"

int main(int argc, char *args[])
{
    Editor editor;

    if (!editor.Init())
        return 1;

    Engine::Run();

    return 0;
}


Editor::Editor():
    ground_body_(nullptr)
{
}

bool Editor::Init()
{
    if (!Engine::Init("Game editor", 1920, 1080, CAMERA_SCALE))
        return false;

    if (!Gui::Set_font("./res/Roboto-Regular.ttf", 0.18f * Engine::Get_dpi()))
        return false;

    if (!Engine::Init_physics(vec2(0, 10)))
        return false;

    Engine::Set_callback_frame(this, &Editor::Loop);
    Engine::Set_callback_window_resize(this, &Editor::On_window_resize);
    Engine::Set_callback_mouse_down(this, &Editor::On_mouse_down);
    Engine::Set_callback_mouse_up(this, &Editor::On_mouse_up);
    Engine::Set_callback_mouse_move(this, &Editor::On_mouse_move);

    texture_btn_box    = Engine::Load_texture("./res/phy_box.png");
    texture_btn_join   = Engine::Load_texture("./res/phy_join.png");
    texture_btn_play   = Engine::Load_texture("./res/phy_play.png");
    texture_btn_pause  = Engine::Load_texture("./res/phy_pause.png");
    texture_btn_circle = Engine::Load_texture("./res/phy_circle.png");
	texture_btn_rev_joint = Engine::Load_texture("./res/phy_rev_joint.png");

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
	Gui::Create_same_line(node_phys_objects);
	Gui::Create_image_button(texture_btn_rev_joint->id, BTN_SIZE, BTN_SIZE, node_phys_objects).Set_click(this, &Editor::Button_phy_rev_join_click);
   
	label_fps = &Gui::Create_label(*tools_window);

	On_window_resize(Engine::Get_surface_width(), Engine::Get_surface_height());
    return true;
}

void Editor::Loop(Uint32 now)
{
    label_fps->SetText("FPS: %u Count objects: %u", Engine::Get_fps(), Engine::Get_count_game_objects());
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
	Physic_box_editable* object = new Physic_box_editable();
    vec2 center = Engine::s2w(Engine::Get_surface_width() * 0.5f, Engine::Get_surface_height() * 0.5f);
    object->Set_pos(center);
    object->Show();
}

void Editor::Button_phy_circle_click(Base_control& sender)
{
	Physic_circle_editable* circle = new Physic_circle_editable();
	vec2 center = Engine::s2w(Engine::Get_surface_width() * 0.5f, Engine::Get_surface_height() * 0.5f);
	circle->Set_pos(center);
	circle->Show();
}

void Editor::Button_phy_join_click(Base_control& sender)
{
	Physic_distance_join_editable* object = new Physic_distance_join_editable();
	vec2 center = Engine::s2w(Engine::Get_surface_width() * 0.5f, Engine::Get_surface_height() * 0.5f);
	object->Connect_at_points(center - vec2(100 * Engine::Get_camera_scale(), 0), center + vec2(100 * Engine::Get_camera_scale(), 0));
    object->Show();
}


void Editor::Button_phy_rev_join_click(Base_control& sender)
{
	vec2 center = Engine::s2w(Engine::Get_surface_width() * 0.5f, Engine::Get_surface_height() * 0.5f);
	Physic_revolute_joint_editable* object = new Physic_revolute_joint_editable();
	object->Connect_at_point(center);
	object->Show();
}

void Editor::Exit_click(const std::string&)
{
    Engine::Stop();
}

void Editor::On_mouse_down(float x, float y, float b)
{
    if (b = SDL_BUTTON_LEFT && !Engine::Physic_paused()) {
        vec2 drag_pos(x, y);
        b2Body* body = Engine::Get_body_at_point(drag_pos);
        if (body) {
            drag_joint_ = Create_mouse_joint(body, drag_pos);
            body->SetAwake(true);
        }
    }
}


void Editor::On_mouse_up(float x, float y, float b)
{
    if (drag_joint_) {
        Engine::Get_world().DestroyJoint(drag_joint_);
        drag_joint_ = nullptr;
    }
}


void Editor::On_mouse_move(float x, float y)
{
    if (drag_joint_) {
        drag_joint_->SetTarget(vec2(x, y));
    }
}

void Editor::Update_phy_wall(float w, float h)
{
    float hw = (w * 0.5f) * Engine::Get_camera_scale();
    float hh = (h * 0.5f) * Engine::Get_camera_scale();
    // Define the ground body.
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(hw, hh);
    if (ground_body_ == nullptr) ground_body_ = Engine::Get_world().CreateBody(&body_def);
    else  ground_body_->DestroyFixture(ground_body_->GetFixtureList());

    b2EdgeShape shape;
    shape.Set(vec2(-hw, hh), vec2(hw, hh));
    ground_body_->CreateFixture(&shape, 0);
    shape.Set(vec2(-hw, -hh), vec2(-hw, hh));
    ground_body_->CreateFixture(&shape, 0);
    shape.Set(vec2(hw, -hh), vec2(hw, hh));
    ground_body_->CreateFixture(&shape, 0);
 }

b2MouseJoint* Editor::Create_mouse_joint(b2Body* body, vec2 target)
{
    b2MouseJointDef def;
    def.bodyA = ground_body_;
    def.bodyB = body;
    def.target = target;
    def.collideConnected = true;
    def.maxForce = 100.0f * body->GetMass();
    return (b2MouseJoint*)Engine::Get_world().CreateJoint(&def);
}
