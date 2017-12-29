#include "game_object.h"
#include "engine.h"

Game_object::Game_object():
    pos(b2Vec2_zero), angle(0), visible(false), selected(false), type(otUnknown)
{
    engine.Add_game_object(this);
}

void Game_object::Move(const vec2& delta)
{
    pos += delta;
    for (size_t i =0; i < vertices.size(); ++i)
        vertices[i] += delta;
}

void Game_object::Set_pos(const vec2& p)
{
    Move(p - pos);
}

void Game_object::Rotate(float delta_rad)
{
    if (delta_rad == 0.0f)
        return;
    angle += delta_rad;

    float cc = cosf(delta_rad);
    float ss = sinf(delta_rad);
    float x;

    for (size_t i = 0; i < vertices.size(); ++i) {
        vec2& v = vertices[i];
        v -= pos;
        x = v.x * cc - v.y * ss;
        v.y = (v.x * ss + v.y * cc) + pos.y;
        v.x = x + pos.x;
    }
}

vec2 Game_object::Get_vertex(int idx)
{
    return vertices[idx];
}

float Game_object::Get_angle()
{
    return angle;
}
