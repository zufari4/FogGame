#include "line_segment_shape.h"
#include "engine.h"

Line_segment_shape::Line_segment_shape():
	Base_shape()
{
	vertex_.resize(2);
	Set_line(vec2_zero, Engine::Scale_vec2(200.0f, 0.0f));
}

void Line_segment_shape::Set_line(const vec2& a, const vec2& b)
{
	vertex_[0] = a;
	vertex_[1] = b;
	pos_ = 0.5f * (a + b);
}

bool Line_segment_shape::Point_in_shape(const vec2& p) const
{
	vec2 l = vertex_[1] - vertex_[0];
	if (l.x == 0.0f || l.y == 0.0f)
		return true;
	float d = ((p.x - vertex_[0].x) / l.x) - ((p.y - vertex_[0].y) / l.y);
	return fabsf(d) < 0.03f;
}
