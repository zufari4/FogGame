#pragma once

#include <Box2D/Box2D.h>
#include "support_circle.h"
#include "phy_object.h"

class Phy_circle : public Phy_body_object
{
public:
    Phy_circle();
    ~Phy_circle();
    void  Update(Uint32);
    void  Set_radius(float val);
    float Get_radius();
private:
    vec2    oldp;
protected:
    void On_changed();
    void Update_body();
};
