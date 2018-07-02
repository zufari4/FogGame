#include "physic_distance_join.h"
#include "engine.h"

Physic_distance_join::Physic_distance_join():
	Physic_object(),
	joint_(nullptr)
{

}

Physic_distance_join::~Physic_distance_join()
{
	if (joint_) {
		Engine::Get_world().DestroyJoint(joint_);
		joint_ = nullptr;
	}
}

void Physic_distance_join::Connect_at_points(const vec2& a, const vec2& b)
{
	if (joint_) {
		Engine::Get_world().DestroyJoint(joint_);
		joint_ = nullptr;
	}

	b2Body* body1 = Engine::Get_body_at_point(a);
	b2Body* body2 = Engine::Get_body_at_point(b);

	if (body1 != nullptr && body2 != nullptr && body1 != body2) {
		b2DistanceJointDef jointDef;
		jointDef.Initialize(body1, body2, a, b);
		jointDef.collideConnected = true;
		jointDef.frequencyHz = 4.0f;
		jointDef.dampingRatio = 0.5f;
		joint_ = Engine::Get_world().CreateJoint(&jointDef);
	}
}
