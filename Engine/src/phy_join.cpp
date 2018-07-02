#include "phy_join.h"
#include "engine.h"

Phy_join::Phy_join():
    Physic_object(),
    joint(nullptr)
{
    support_object = new Support_line();
    support_object->Set_callback_change(this, &Phy_join::On_changed);

    Update_body();
}

void Phy_join::Update(Uint32)
{
    if (joint) {
        static_cast<Support_line*>(support_object)->Set_line(joint->GetAnchorA(), joint->GetAnchorB(), false);
    }
}

void Phy_join::Set_line(const vec2& a, const vec2& b)
{
    static_cast<Support_line*>(support_object)->Set_line(a, b, true);
}

void Phy_join::On_changed()
{
    Update_body();
}

void Phy_join::Update_body()
{
    bool prev_runned = !Engine::Physic_paused();
    Engine::Pause_physics();

    if (joint) {
        Engine::Get_world().DestroyJoint(joint);
        joint = nullptr;
    }

    b2Body* body1 = Engine::Get_body_at_point(support_object->Get_vertex(0));
    b2Body* body2 = Engine::Get_body_at_point(support_object->Get_vertex(1));

    if (body1 != nullptr && body2 != nullptr && body1 != body2) {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(body1, body2, support_object->Get_vertex(0), support_object->Get_vertex(1));
        jointDef.collideConnected = true;
        jointDef.frequencyHz = 4.0f;
        jointDef.dampingRatio = 0.5f;
        joint = Engine::Get_world().CreateJoint(&jointDef);
    }

    if (prev_runned) {
        Engine::Start_physics();
    }
}
