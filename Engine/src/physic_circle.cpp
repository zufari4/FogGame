#include "physic_circle.h"
#include "engine.h"

Physic_circle::Physic_circle():
    Physic_object()
{
    b2BodyDef body_def;
    body_def.type     = b2_dynamicBody;
    body_def.position = b2Vec2_zero;
    body_ = Engine::Get_world().CreateBody(&body_def);

	circle_shape_ = new b2CircleShape();
	shape_ = circle_shape_;
	fixture_def_.shape = shape_;
	fixture_def_.density = 0.5f;
	fixture_def_.friction = 0.5f;
	fixture_def_.restitution = 0.6f;

	Set_body_radius(40 * Engine::Get_camera_scale());
}


Physic_circle::~Physic_circle()
{
	if (shape_) {
		delete shape_;
	}
}

void Physic_circle::Set_body_radius(float val)
{
	body_->SetActive(false);

	circle_shape_->m_radius = val;
	if (fixture_) {
		body_->DestroyFixture(fixture_);
	}
	fixture_ = body_->CreateFixture(&fixture_def_);

	body_->SetActive(true);
}

float Physic_circle::Get_body_radius() const
{
	return circle_shape_->m_radius;
}


