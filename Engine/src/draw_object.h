#pragma once

#include "game_object.h"

class Draw_object : public Game_object
{
protected:
    std::vector<vec2> vertices;
    vec2  pos;
    float angle;
public:
    Draw_object();
    virtual ~Draw_object() {};
    virtual void Set_pos(const vec2& newpos);
    virtual vec2 Get_pos();
    float   Get_angle();
    virtual void Move(const vec2& delta);
    virtual void Rotate(float delta_rad);
    virtual vec2 Get_vertex(int idx);
};