#include "physic_box.h"
#include "engine.h"

Physic_box::Physic_box():
    Physic_object()
{
	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2_zero;
	body_ = Engine::Get_world().CreateBody(&body_def);

	box_shape_ = new b2PolygonShape();
	shape_ = box_shape_;
	fixture_def_.shape = shape_;
	fixture_def_.density = 0.5f;
	fixture_def_.friction = 0.5f;
	fixture_def_.restitution = 0.4f;

	Set_body_rect(b2Vec2_zero, Engine::s2w(80.0f, 80.0f));
}

Physic_box::~Physic_box()
{
    delete shape_;
}


void Physic_box::Set_body_rect(const vec2& _min, const vec2& _max)
{
	body_->SetActive(false);

	vec2 chan_vert[4];
	if (_max.Length() < _min.Length()) {
		chan_vert[0] = _max;
		chan_vert[2] = _min;
	}
	else {
		chan_vert[0] = _min;
		chan_vert[2] = _max;
	}
	chan_vert[1]  = vec2(chan_vert[2].x, chan_vert[0].y);
	chan_vert[3]  = vec2(chan_vert[0].x, chan_vert[2].y);
	min_vertex_   = chan_vert[0];
	max_vertex_   = chan_vert[2];
	vec2 center   = Calc_center(chan_vert);
	chan_vert[0] -= center;
	chan_vert[1] -= center;
	chan_vert[2] -= center;
	chan_vert[3] -= center;
	body_->SetTransform(center, 0.0f);
	box_shape_->Set(chan_vert, 4);

	if (fixture_) {
		body_->DestroyFixture(fixture_);
	}
	fixture_ = body_->CreateFixture(&fixture_def_);

	body_->SetActive(true);
}


vec2 Physic_box::Calc_center(const vec2(&vertex)[4])
{
	vec2 p1 = 0.5 * (vertex[0] + vertex[1]);
	vec2 p2 = 0.5 * (vertex[3] + vertex[2]);
	vec2 p3 = 0.5 * (vertex[0] + vertex[3]);
	vec2 p4 = 0.5 * (vertex[1] + vertex[2]);

	// Store the values for fast access and easy
	// equations-to-code conversion
	double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return b2Vec2_zero;

	// Get the x and y
	double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	double x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	double y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines
	if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
		x < std::min(x3, x4) || x > std::max(x3, x4)) return b2Vec2_zero;
	if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
		y < std::min(y3, y4) || y > std::max(y3, y4)) return b2Vec2_zero;

	// Return the point of intersection
	return vec2(static_cast<float>(x), static_cast<float>(y));
}