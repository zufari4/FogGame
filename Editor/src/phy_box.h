#pragma once
#include <Box2D/Box2D.h>
#include "game_object.h"
#include "support_rectangle.h"

class PhyBox : public SupportRectangle
{
public:
    PhyBox();
    void OnChanged();
    void Update(Uint32);
private:
    vec2 oldp;
    b2Body* body;
    b2PolygonShape shape;
    b2Fixture* fixture;   
};