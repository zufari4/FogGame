#include "phy_object.h"

Phy_object::Phy_object():
    Game_object(),
    support_object(nullptr)
{
    type = otPhysic;
}

vec2 Phy_object::Get_vertex(int idx)
{
    return support_object->Get_vertex(idx);
}

void Phy_object::Hide()
{
    Game_object::Hide();
    support_object->Hide();
}

void Phy_object::Show()
{
    Game_object::Show();
    support_object->Show();
}

void Phy_object::Set_pos(const vec2& newpos)
{
    Game_object::Set_pos(newpos);
    support_object->Set_pos(newpos);
}

void Phy_object::Move(const vec2& delta)
{
    Game_object::Move(delta);
    support_object->Move(delta);
}

void Phy_object::Rotate(float delta_rad)
{
    Game_object::Rotate(delta_rad);
    support_object->Rotate(delta_rad);
}

Phy_body_object::Phy_body_object():
    Phy_object(),
    body(nullptr),
    shape(nullptr),
    fixture(nullptr)
{
    type = otPhysicBody;
}

b2Body* Phy_body_object::Get_body()
{
    return body;
}

b2Fixture* Phy_body_object::Get_fixture()
{
    return fixture;
}

b2Shape* Phy_body_object::Get_shape()
{
    return shape;
}

bool Phy_body_object::TestPoint(const vec2& p)
{
    return fixture->TestPoint(p2mv(p));
}
