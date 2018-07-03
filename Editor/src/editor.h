#pragma once
#include <stdio.h>
#include <SDL.h>
#include <Box2D/Box2D.h>
#include "engine.h"
#include "gui.h"
#include "base_class.h"

static const float CAMERA_SCALE = 1.0f / 250.0f;
static const float BTN_SIZE = 32.0f;

class Editor: public Base_class
{
private:
    Texture* texture_btn_box;
    Texture* texture_btn_join;
    Texture* texture_btn_play;
    Texture* texture_btn_pause;
    Texture* texture_btn_circle;
	Texture* texture_btn_rev_joint;
    b2Body*  ground_body_;
    Label*   label_fps;
    Window*  tools_window;
    Image_button* play_btn;
public:
    Editor();
    bool Init();
    void Run();
    void Loop(Uint32);
    void On_window_resize(float w, float h);
    void Draw_gui();
    void Button_phy_box_click(Base_control& sender);
    void Button_phy_run_click(Base_control& sender);
    void Button_phy_circle_click(Base_control& sender);
    void Button_phy_join_click(Base_control& sender);
	void Button_phy_rev_join_click(Base_control& sender);
    void Exit_click(const std::string&);
    void On_mouse_down(float x, float y, float b);
    void On_mouse_up(float x, float y, float b);
    void On_mouse_move(float x, float y);
private:
    void Update_phy_wall(float w, float h);
    b2MouseJoint* Create_mouse_joint(b2Body* body, vec2 target);
    b2MouseJoint* drag_joint_ = nullptr;
    b2Body* dummy_body_ = nullptr;
};
