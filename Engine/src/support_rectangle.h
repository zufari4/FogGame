#pragma once

#include "support_object.h"

class Support_rectangle: public Support_object
{
public:
    bool sqared;
protected:
    int  selected_vertex;
    bool drag_point;
public:
    Support_rectangle();
    void Draw();
    virtual void Set_rect(const vec2& _min, const vec2& _max);
    virtual bool Cursor_enter(const vec2& cursor);
private:
    virtual void On_mouse_move(int x, int y);
    virtual void On_mouse_down(int x, int y, int b);
    virtual void On_mouse_up(int x, int y, int b);
    bool In_point(const vec2& point, const vec2& cursor);
    vec2 Calc_center();    
};

