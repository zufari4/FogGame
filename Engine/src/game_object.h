#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include <Box2D/Box2D.h>
#include "base_class.h"

typedef b2Vec2 vec2;

typedef enum {
    otUnknown,
    otSupport,
    otPhysic,
    otPhysicBody
} Object_type;

class Game_object: public Base_class
{
public:
    bool visible;
    bool selected;
protected:
    Object_type type;
    vec2  pos;
    float angle;
    std::vector<vec2> vertices;
public:
    Game_object();
    virtual ~Game_object() {};
    virtual void Hide() { visible = false; };
    virtual void Show() { visible = true;  };
    virtual void Set_pos(const vec2& newpos);
    virtual vec2 Get_pos() { return pos; };
    virtual void Move(const vec2& delta);
    virtual void Rotate(float delta_rad);
    virtual void Draw() {};
    virtual void Update(Uint32 ticks) {};
    virtual bool Cursor_enter(const vec2& /*cursor*/) { return false; };
    virtual void On_mouse_move(int, int) {};
    virtual void On_mouse_down(int, int, int) {};
    virtual void On_mouse_up(int, int, int) {};
    virtual vec2 Get_vertex(int idx);
    Object_type  Get_type() { return type; };
    float Get_angle();
};