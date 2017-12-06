#pragma once

#include <Box2D/Box2D.h>
#include "game_object.h"

#define POINT_SIZE 20.0f

class SupportRectangle : public GameObject
{
protected:
    int  selectedVertex;
    bool dragPoint;
    bool dragRect;
    vec2 a;
    vec2 b;
    vec2 c;
    vec2 d;
    vec2 dragStart;
    virtual void OnMouseMove(int x, int y);
    virtual void OnMouseDown(int x, int y, int b);
    virtual void OnMouseUp(int x, int y, int b);
    bool InPoint(const vec2& point, const vec2& cursor);
    void CallCenter(vec2& center);
    
    virtual void OnChanged() {};
public:
    bool sqared;
    SupportRectangle();
    virtual void SetRect(const b2Vec2& _min, const b2Vec2& _max);
    void Draw();
    void Rotate(float deltaRad);
    virtual bool PointInRect(const vec2& point);
};

