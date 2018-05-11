#include "phy_box.h"
#include "engine.h"

Phy_box::Phy_box():
    Phy_body_object()
{
    support_object = new Support_rectangle();
    support_object->Set_callback_change(this, &Phy_box::On_changed);
    pos = support_object->Get_pos();
    angle = support_object->Get_angle();
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    oldp = vec2(pos.x, pos.y);
    body_def.position = oldp;
    body = Engine::Get_world().CreateBody(&body_def);
    shape = new b2PolygonShape();

    Update_body();
}

Phy_box::~Phy_box()
{
    delete shape;
}

void Phy_box::On_changed()
{
    pos = support_object->Get_pos();
    angle = support_object->Get_angle();
    Update_body();
}

void Phy_box::Update(Uint32 ticks)
{
    vec2 newpos = body->GetPosition();
    float newangle = body->GetAngle();

    vec2 delta  = (newpos - oldp);
    oldp = newpos;
   
    support_object->Move(delta);
    support_object->Rotate(newangle - angle);
    angle = newangle;
}

void Phy_box::Set_rect(const vec2& _min, const vec2& _max)
{
    static_cast<Support_rectangle*>(support_object)->Set_rect(_min, _max);
}

void Phy_box::Update_body()
{
    bool prev_runned = !Engine::Physic_paused();

    Engine::Pause_physics();

    body->SetActive(false);
    body->SetLinearVelocity(b2Vec2_zero);
    body->SetAngularVelocity(0.0f);

    oldp = vec2(pos.x, pos.y);
    body->SetTransform(oldp, 0.0f);
    angle = 0.0f;

    vec2 chanVert[4];
    vec2  v;

    v = support_object->Get_vertex(0) - pos;  chanVert[0] = vec2(v.x, v.y);
    v = support_object->Get_vertex(1) - pos;  chanVert[1] = vec2(v.x, v.y);
    v = support_object->Get_vertex(2) - pos;  chanVert[2] = vec2(v.x, v.y);
    v = support_object->Get_vertex(3) - pos;  chanVert[3] = vec2(v.x, v.y);

    static_cast<b2PolygonShape*>(shape)->Set(chanVert, 4);
    b2FixtureDef fixture_def;
    fixture_def.shape = shape;
    fixture_def.density = 0.5f;
    fixture_def.friction = 0.5f;
    fixture_def.restitution = 0.6f;
    if (fixture) body->DestroyFixture(fixture);
    fixture = body->CreateFixture(&fixture_def);

    body->SetActive(true);
    if (prev_runned)
        Engine::Start_physics();
}
