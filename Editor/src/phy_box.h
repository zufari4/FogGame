#pragma once
#include <Box2D/Box2D.h>
#include "game_object.h"
#include "support_rectangle.h"

class Phy_box : public Support_rectangle
{
public:
    Phy_box();
    void On_changed();
    void Update(Uint32);
private:
    vec2    oldp;
    b2Body* body;
    b2PolygonShape shape;
    b2Fixture* fixture;   
};