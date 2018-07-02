#pragma once

#include <Box2D/Box2D.h>
#include "support_line.h"
#include "physic_object.h"

class Phy_join : public Physic_object
{
public:
    Phy_join();
    void Update(Uint32);
    void Set_line(const vec2& a, const vec2& b);
private:
    b2Joint* joint;
private:
    void On_changed();
    void Update_body();
};
