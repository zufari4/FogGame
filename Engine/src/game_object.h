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
public:
    Game_object();
    virtual ~Game_object() {};
    virtual void Update(Uint32 ticks) {};
    virtual void On_mouse_move(float, float) {};
    virtual void On_mouse_down(float, float, int) {};
    virtual void On_mouse_up(float, float, int) {};
    virtual void Draw() {};
    virtual void Hide();
    virtual void Show();
    Object_type  Get_type();
    virtual bool Cursor_enter(const vec2&);
};