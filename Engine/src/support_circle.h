#pragma once

#include "support_object.h"

class Support_circle : public Support_object
{
private:
    float radius;
public:
    Support_circle();
    void  Draw();
    bool  Cursor_enter(const vec2& cursor);
    void  Set_radius(float val);
    float Get_radius();
private:
    void Get_circle_vertexes(float cx, float cy, float r, int pix_on_step, std::vector<vec2>& out);
};