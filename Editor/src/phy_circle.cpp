#include "phy_circle.h"
#include "engine.h"

Phy_circle::Phy_circle():
    Support_circle(),
    body(nullptr),
    fixture(nullptr)
{
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    oldp = vec2(p2m(pos.x), p2m(pos.y));
    body_def.position = oldp;
    body = engine.Create_body(body_def);
    Set_radius(20.0);
}

void Phy_circle::Update(Uint32)
{
    vec2 newpos = body->GetPosition();
    vec2 delta  = phy_scale * (newpos - oldp);
    oldp = newpos;
    angle = body->GetAngle();
    Move(delta);
}


void Phy_circle::On_changed()
{
    bool prev_runned = !engine.phy_pause;
    engine.Pause_physics();

    body->SetActive(false);
    body->SetLinearVelocity(b2Vec2_zero);
    body->SetAngularVelocity(0.0f);

    oldp = vec2(p2m(pos.x), p2m(pos.y));
    body->SetTransform(oldp, 0.0f);

    shape.m_radius = p2m(Get_radius());
    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.density = 0.5f;
    fixture_def.friction = 0.5f;
    fixture_def.restitution = 0.6f;
    if (fixture) body->DestroyFixture(fixture);
    fixture = body->CreateFixture(&fixture_def);

    body->SetActive(true);
    if (prev_runned)
        engine.Start_physics();
}
