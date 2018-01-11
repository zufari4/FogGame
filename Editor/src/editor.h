#pragma once
#include <stdio.h>
#include <imgui.h>
#include <SDL.h>
#include <Box2D/Box2D.h>
#include "engine.h"
#include "base_class.h"
#include "phy_box.h"
#include "phy_circle.h"
#include "phy_join.h"

class Editor: public Base_class
{
private:
    Texture* texture_btn_box;
    Texture* texture_btn_join;
    Texture* texture_btn_play;
    Texture* texture_btn_pause;
    Texture* texture_btn_circle;
    float    surf_width;
    float    surf_height;
    b2Body*  ground_body;
public:
    Editor();
    bool Init();
    void Run();
    void Loop(Uint32);
    void On_window_resize(float w, float h);
    void Draw_gui();
    void Button_phy_box_click();
    void Button_phy_run_click();
    void Button_phy_circle_click();
    void Button_phy_join_click();
    void Exit_click();
private:
    void Update_phy_wall(float w, float h);
};
