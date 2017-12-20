#pragma once

#include <Box2D/Box2D.h>
#include "game_object.h"
#include <vector>

class Support_object : public Game_object
{
protected:
    std::vector<vec2> vertices;
public:
    Support_object();
    void Move(const vec2& delta);
    void Set_pos(const vec2& p);
    void Rotate(float delta_rad);
protected:
    virtual void On_changed();
    void Draw_shape();
    bool Point_in_shape(const vec2& p);
};