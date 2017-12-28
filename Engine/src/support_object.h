#pragma once

#include <Box2D/Box2D.h>
#include "game_object.h"
#include <vector>

#define POINT_SIZE 10.0f
#define CIRCLE_STEP 5
#define LINE_WIDTH 2.0f

class Support_object : public Game_object
{
protected:
    std::vector<vec2> vertices;
    bool is_drag;
    vec2 drag_start;
public:
    Support_object();
    void Move(const vec2& delta);
    void Set_pos(const vec2& p);
    void Rotate(float delta_rad);
protected:
    virtual void On_changed();
    virtual bool Point_in_shape(const vec2& p);
    virtual void On_mouse_move(int x, int y);
    virtual void On_mouse_down(int x, int y, int b);
    virtual void On_mouse_up(int x, int y, int b);
    void Draw_shape();
};