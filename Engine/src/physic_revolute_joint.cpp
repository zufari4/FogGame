#include "physic_revolute_joint.h"
#include "engine.h"

Physic_revolute_joint::Physic_revolute_joint():
	Physic_object(),
	joint_(nullptr)
{

}

Physic_revolute_joint::~Physic_revolute_joint()
{
	if (joint_) {
		Engine::Get_world().DestroyJoint(joint_);
		joint_ = nullptr;
	}
}

void Physic_revolute_joint::Connect_at_point(const vec2& a)
{
	if (joint_) {
		Engine::Get_world().DestroyJoint(joint_);
		joint_ = nullptr;
	}

	std::vector<b2Body*> bodies = Engine::Get_bodies_at_point(a);

	if (bodies.size() > 1) {
		b2RevoluteJointDef jointDef;
		jointDef.Initialize(bodies[0], bodies[1], a);
		jointDef.collideConnected = false;
		joint_ = Engine::Get_world().CreateJoint(&jointDef);
	}
}
