#pragma once

#include <Box2D/Box2D.h>
#include "game_object.h"


class Support_circle : public Game_object
{
private:
    float radius;
public:
    Support_circle();
    void Draw();
    bool Cursor_enter(const vec2& cursor);
    void Set_radius(float val);
    float Get_radius();
    void Move(const vec2& delta);
    void Set_pos(const vec2& p);
private:
    void Get_circle_vertexes(float cx, float cy, float r, int pix_on_step, std::vector<vec2>& out);
    virtual void On_changed() {};
};