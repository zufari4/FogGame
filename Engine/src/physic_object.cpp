#include "physic_object.h"

Physic_object::Physic_object():
    Base_class(),
	body_(nullptr),
	fixture_(nullptr),
	shape_(nullptr)
{
}

b2Body* Physic_object::Get_body() const
{
    return body_;
}

b2Fixture* Physic_object::Get_fixture() const
{
    return fixture_;
}

b2Shape* Physic_object::Get_shape() const
{
    return shape_;
}

bool Physic_object::TestPoint(const vec2& p) const
{
	return fixture_ ? fixture_->TestPoint(p) : false;
}

void Physic_object::Set_body_pos(const vec2& newpos)
{
	if (body_) {
		body_->SetTransform(newpos, body_->GetAngle());
	}
}

const vec2& Physic_object::Get_body_pos()
{
	if (body_) {
		return body_->GetPosition();
	}
	else {
		return b2Vec2_zero;
	}
}

float Physic_object::Get_body_angle() const
{
	return body_ ? body_->GetAngle() : 0.0f;
}