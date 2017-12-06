#include "phy_box.h"
#include "engine.h"

PhyBox::PhyBox():
    SupportRectangle()
{
    body =  NULL;
    fixture = NULL;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    oldp = vec2(p2m(pos.x), p2m(pos.y));
    bodyDef.position = oldp;
    body = Engine.CreateBody(&bodyDef);
    SetRect(vec2(0, 0), vec2(10, 10));
    sqared = false;
}

void PhyBox::OnChanged()
{
    bool prevRunned = !Engine.phyPause;

    Engine.PausePhysics();

    body->SetActive(false);
    body->SetLinearVelocity(b2Vec2_zero);
    body->SetAngularVelocity(0.0f);

    oldp = vec2(p2m(pos.x), p2m(pos.y));
    body->SetTransform(oldp, 0.0f);
    angle = 0;

    vec2 chanVert[4];
    vec2  v;
   
    v = a - pos;  chanVert[0] = vec2(p2m(v.x), p2m(v.y));
    v = b - pos;  chanVert[1] = vec2(p2m(v.x), p2m(v.y));
    v = c - pos;  chanVert[2] = vec2(p2m(v.x), p2m(v.y));
    v = d - pos;  chanVert[3] = vec2(p2m(v.x), p2m(v.y));
   
    shape.Set(chanVert, 4);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.6f;
    if (fixture) body->DestroyFixture(fixture);
    fixture = body->CreateFixture(&fixtureDef);
   
    body->SetActive(true);
    if (prevRunned)
        Engine.StartPhysics();
}

void PhyBox::Update(Uint32 ticks)
{
    vec2 newpos = body->GetPosition();
    vec2 delta = phyScale * (newpos - oldp);
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
