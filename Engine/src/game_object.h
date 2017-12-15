#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include <Box2D/Box2D.h>
#include "base_class.h"

typedef b2Vec2 vec2;
#define POINT_SIZE 10.0f
#define CIRCLE_STEP 4

class Game_object: public Base_class
{
public:
    bool visible;
    bool selected;
protected:
    vec2  pos;
    float angle;
    std::vector<vec2> vertices;
public:
    Game_object();
    virtual ~Game_object() {};
    virtual void Hide() { visible = false; };
    virtual void Show() { visible = true;  };
    virtual void Set_pos(const vec2& newpos) { pos = newpos; }
    virtual vec2 Get_pos() { return pos; };
    virtual void Draw() {};
    virtual void Update(Uint32 ticks) {};
    virtual bool Cursor_enter(const vec2& /*cursor*/) { return false; };
    virtual void On_mouse_move(int, int) {};
    virtual void On_mouse_down(int, int, int) {};
    virtual void On_mouse_up(int, int, int) {};
};