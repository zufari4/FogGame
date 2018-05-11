#include "phy_circle.h"
#include "engine.h"

Phy_circle::Phy_circle():
    Phy_body_object()
{
    support_object = new Support_circle();
    support_object->Set_callback_change(this, &Phy_circle::On_changed);

    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    oldp = vec2(pos.x, pos.y);
    body_def.position = oldp;
    body = Engine::Get_world().CreateBody(&body_def);
    shape = new b2CircleShape();

    Update_body();
}

Phy_circle::~Phy_circle()
{
    delete shape;
}

void Phy_circle::Update(Uint32)
{
    vec2 newpos = body->GetPosition();
    float newangle = body->GetAngle();

    vec2 delta = (newpos - oldp);
    oldp = newpos;

    support_object->Move(delta);
    support_object->Rotate(newangle - angle);
    angle = newangle;
}

void Phy_circle::Set_radius(float val)
{
    ((Support_circle*)support_object)->Set_radius(val);
}

float Phy_circle::Get_radius()
{
    return ((Support_circle*)support_object)->Get_radius();
}

void Phy_circle::On_changed()
{
    pos = support_object->Get_pos();
    angle = support_object->Get_angle();
    Update_body();
}

void Phy_circle::Update_body()
{
    bool prev_runned = !Engine::Physic_paused();
    Engine::Pause_physics();

    body->SetActive(false);
    body->SetLinearVelocity(b2Vec2_zero);
    body->SetAngularVelocity(0.0f);

    oldp = vec2(pos.x, pos.y);
    body->SetTransform(oldp, 0.0f);

    static_cast<b2CircleShape*>(shape)->m_radius = static_cast<Support_circle*>(support_object)->Get_radius();
    b2FixtureDef fixture_def;
    fixture_def.shape = shape;
    fixture_def.density = 0.5f;
    fixture_def.friction = 0.5f;
    fixture_def.restitution = 0.6f;
    if (fixture) body->DestroyFixture(fixture);
    fixture = body->CreateFixture(&fixture_def);

    body->SetActive(true);
    if (prev_runned) {
        Engine::Start_physics();
    }
}
