#pragma once

#include <Box2D/Box2D.h>
#include "game_object.h"

class Support_rectangle: public Game_object
{
public:
    bool sqared;
protected:
    int  selected_vertex;
    bool drag_point;
    bool drag_rect;
    vec2 a;
    vec2 b;
    vec2 c;
    vec2 d;
    vec2 drag_start;
public:
    Support_rectangle();
    void Draw();
    void Rotate(float delta_rad);
    virtual void Set_rect(const vec2& _min, const vec2& _max);
    virtual bool Point_in_rect(const vec2& point);
    virtual bool Cursor_enter(const vec2& cursor);
private:
    virtual void On_mouse_move(int x, int y);
    virtual void On_mouse_down(int x, int y, int b);
    virtual void On_mouse_up(int x, int y, int b);
    virtual void On_changed() {};
    bool In_point(const vec2& point, const vec2& cursor);
    vec2 Calc_center();    
};

