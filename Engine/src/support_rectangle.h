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
    virtual void On_mouse_move(float x, float y) override;
    virtual void On_mouse_down(float x, float y, int b) override;
    virtual void On_mouse_up(float x, float y, int b) override;
    vec2 Calc_center();    
};

