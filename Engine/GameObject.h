#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <Box2D/Box2D.h>
#include "BaseClass.h"
typedef b2Vec2 vec2;

class GameObject: public BaseClass
{
protected:
    vec2 pos;
    float angle;
public:
    bool visible;
    bool selected;
    GameObject() : pos(b2Vec2_zero), angle(0), visible(false), selected(false) {};
    virtual ~GameObject() {};
    void Hide() { visible = false; };
    void Show() { visible = true; };
    vec2 GetPos() { return pos; };
    virtual void Draw() {};
    virtual void Update(Uint32 ticks) {};
    virtual bool PointInRect(const vec2& point) { return false; };
    virtual void OnMouseMove(int, int) {};
    virtual void OnMouseDown(int, int, int) {};
    virtual void OnMouseUp(int, int, int) {};
};