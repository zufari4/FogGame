#pragma once

#include "support_object.h"

class Support_line : public Support_object
{
public:
    Support_line();
    void  Draw();
    bool  Cursor_enter(const vec2& cursor);
    void  Set_line(const vec2& a, const vec2& b, bool notify = true);
protected:
    int  selected_vertex;
    bool drag_point;
protected:
    bool Point_on_line(const vec2& point);
private:
    virtual void On_mouse_move(int x, int y);
    virtual void On_mouse_down(int x, int y, int b);
    virtual void On_mouse_up(int x, int y, int b);
};