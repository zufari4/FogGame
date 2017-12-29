#pragma once

#include <Box2D/Box2D.h>
#include "support_rectangle.h"
#include "phy_object.h"

class Phy_box : public Phy_body_object
{
public:
    Phy_box();
    ~Phy_box();
    void On_changed();
    void Update(Uint32);
    void Set_rect(const vec2& _min, const vec2& _max);
protected:
    void Update_body();
private:
    vec2    oldp;
};