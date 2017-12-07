#pragma once
#include <stdio.h>
#include <imgui.h>
#include <SDL.h>
#include <Box2D/Box2D.h>
#include "engine.h"
#include "base_class.h"
#include "phy_box.h"

class Editor: public Base_class
{
private:
    Texture* texture_btn_box;
    Texture* texture_btn_join;
    Texture* texture_btn_play;
    Texture* texture_btn_pause;
    int      surf_width;
    int      surf_height;
public:
    Editor() {};
    bool Init();
    void Run();
    void Loop(Uint32);
    void On_mouse_down(int x, int y, int button);
    void On_mouse_up(int x, int y, int button);
    void On_mouse_move(int x, int y);
    void On_window_resize(int w, int h);
    void Draw_gui();
    void Button_phy_box_click();
    void Button_phy_run_click();
};
