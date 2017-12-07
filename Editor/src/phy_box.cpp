#include "phy_box.h"
#include "engine.h"

Phy_box::Phy_box():
    Support_rectangle()
{
    body =  NULL;
    fixture = NULL;
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    oldp = vec2(p2m(pos.x), p2m(pos.y));
    body_def.position = oldp;
    body = engine.Create_body(body_def);
    Set_rect(vec2(0, 0), vec2(10, 10));
}

void Phy_box::On_changed()
{
    bool prev_runned = !engine.phy_pause;

    engine.Pause_physics();

    body->SetActive(false);
    body->SetLinearVelocity(b2Vec2_zero);
    body->SetAngularVelocity(0.0f);

    oldp = vec2(p2m(pos.x), p2m(pos.y));
    body->SetTransform(oldp, 0.0f);
    angle = 0.0f;

    vec2 chanVert[4];
    vec2  v;
   
    v = a - pos;  chanVert[0] = vec2(p2m(v.x), p2m(v.y));
    v = b - pos;  chanVert[1] = vec2(p2m(v.x), p2m(v.y));
    v = c - pos;  chanVert[2] = vec2(p2m(v.x), p2m(v.y));
    v = d - pos;  chanVert[3] = vec2(p2m(v.x), p2m(v.y));
   
    shape.Set(chanVert, 4);
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

void Phy_box::Update(Uint32 ticks)
{
    vec2 newpos = body->GetPosition();
    vec2 delta  = phy_scale * (newpos - oldp);
    oldp = newpos;
    float newangle = body->GetAngle();

    a += delta;
    b += delta;
    c += delta;
    d += delta;
    pos += delta;
    Rotate(newangle - angle);
    angle = newangle;
}
