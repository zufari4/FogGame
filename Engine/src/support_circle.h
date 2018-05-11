#pragma once

#include "support_object.h"

class Support_circle : public Support_object
{
public:
    Support_circle();
    void  Draw();
    bool  Cursor_enter(const vec2& cursor);
    void  Set_radius(float val);
    float Get_radius();
private:
    float radius_;
    int  selected_vertex_;
    bool drag_point_;
    virtual void On_mouse_move(float x, float y) override;
    virtual void On_mouse_down(float x, float y, int b) override;
    virtual void On_mouse_up(float x, float y, int b) override;
    bool  Point_in_shape(const vec2& p) override;
    void Get_circle_vertexes(double cx, double cy, double r, int pix_on_step, std::vector<vec2>& out);
};