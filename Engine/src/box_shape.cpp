#include "box_shape.h"

Box_shape::Box_shape():
	Base_shape()
{
	vertex_.resize(4);
	Set_rect(vec2(0.0f, 0.0f), vec2(0.5f, 0.5f));
}

void Box_shape::Set_rect(const vec2& _min, const vec2& _max)
{
	if (_max.Length() < _min.Length()) {
		vertex_[0] = _max;
		vertex_[2] = _min;
	}
	else {
		vertex_[0] = _min;
		vertex_[2] = _max;
	}
	vertex_[1] = vec2(vertex_[2].x, vertex_[0].y);
	vertex_[3] = vec2(vertex_[0].x, vertex_[2].y);
	Centering_pos();
}

void Box_shape::Centering_pos()
{
	vec2 p1 = 0.5 * (vertex_[0] + vertex_[1]);
	vec2 p2 = 0.5 * (vertex_[3] + vertex_[2]);
	vec2 p3 = 0.5 * (vertex_[0] + vertex_[3]);
	vec2 p4 = 0.5 * (vertex_[1] + vertex_[2]);

	// Store the values for fast access and easy
	// equations-to-code conversion
	double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return;

	// Get the x and y
	double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	double x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	double y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines
	if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
		x < std::min(x3, x4) || x > std::max(x3, x4)) return;
	if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
		y < std::min(y3, y4) || y > std::max(y3, y4)) return;

	// Return the point of intersection
	pos_.Set(x, y);
}