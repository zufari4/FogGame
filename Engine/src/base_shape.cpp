#include "base_shape.h"
#include "engine.h"

Base_shape::Base_shape():
    Draw_object()
{
}

void Base_shape::Move(const vec2& delta)
{
    pos_ += delta;
    for (size_t i = 0; i < vertex_.size(); ++i)
        vertex_[i] += delta;
}


void Base_shape::Draw() const
{
	glBegin(GL_LINE_LOOP);
	for (const auto& v : vertex_)
		glVertex2f(v.x, v.y);
	glEnd();
}

void Base_shape::Set_pos(const vec2& newpos)
{
	Move(newpos - pos_);   
}


void Base_shape::Set_pos(const vec2& newpos, float angle)
{
	const vec2 delta = newpos - pos_;
	pos_ = newpos;
	/*for (size_t i = 0; i < vertex_.size(); ++i)
		vertex_[i] = vertex_identity_ + delta;*/
}

void Base_shape::Rotate(float delta_rad)
{
	if (delta_rad != 0.0f) {
		angle_ += delta_rad;

		float cc = cosf(delta_rad);
		float ss = sinf(delta_rad);
		float x;

		for (size_t i = 0; i < vertex_.size(); ++i) {
			vec2& v = vertex_[i];
			v -= pos_;
			x = v.x * cc - v.y * ss;
			v.y = (v.x * ss + v.y * cc) + pos_.y;
			v.x = x + pos_.x;
		}
	}
}

const vec2& Base_shape::Get_vertex(int idx) const
{
    return vertex_[idx];
}


const std::vector<vec2>& Base_shape::Get_vertexes() const
{
	return vertex_;
}

bool Base_shape::Point_in_shape(const vec2& p) const
{
	if (vertex_.size() < 3)
		return false;
	bool c = false;
	for (size_t i = 0, j = vertex_.size() - 1; i < vertex_.size(); j = i++) {
		if (((vertex_[i].y > p.y) != (vertex_[j].y > p.y)) &&
			(p.x < (vertex_[j].x - vertex_[i].x) * (p.y - vertex_[i].y) / (vertex_[j].y - vertex_[i].y) + vertex_[i].x))
			c = !c;
	}
	return c;
}
