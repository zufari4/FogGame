#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include "draw_object.h"

typedef enum {
    otUnknown,
	otPhysicShape,
	otPhysicJoin
} Object_type;

class Game_object: virtual public Draw_object
{
public:
    Game_object(Object_type type);
    virtual ~Game_object() {};
    virtual void Update(Uint32) {};
    virtual void On_mouse_move(float, float) {};
    virtual void On_mouse_down(float, float, int) {};
    virtual void On_mouse_up(float, float, int) {};
	Object_type  Get_type() const { return type_; };
	virtual bool Cursor_enter(const vec2&) const { return false; };
	virtual b2Body* Get_body() const { return nullptr; };
protected:
	Object_type type_;
};