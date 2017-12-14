#pragma once
#include <Box2D/Box2D.h>
#include "game_object.h"
#include "support_circle.h"

class Phy_circle : public Support_circle
{
public:
    Phy_circle();
    void Update(Uint32);
private:
    vec2    oldp;
    b2Body* body;
    b2CircleShape shape;
    b2Fixture* fixture;
private:
    void On_changed();
};
