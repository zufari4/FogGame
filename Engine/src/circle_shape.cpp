#include "circle_shape.h"
#include "engine.h"

Circle_shape::Circle_shape():
	Base_shape(),
	radius_(40.0f * Engine::Get_camera_scale())
{
	Make_circle_vertexes(0, 0, radius_, CIRCLE_QUALITY);
}

void Circle_shape::Set_radius(float val)
{
	radius_ = val;
	Make_circle_vertexes(pos_.x, pos_.y, radius_, CIRCLE_QUALITY);
}

bool Circle_shape::Point_in_shape(const vec2& p) const
{
	return (pos_ - p).LengthSquared() < (radius_*radius_);
}

float Circle_shape::Get_radius() const
{
	return radius_;
}

void Circle_shape::Make_circle_vertexes(double cx, double cy, double r, int num_segments)
{
	vertex_.clear();
	double theta = 3.14159265 * 2.0 / double(num_segments);
	double c = cos(theta);
	double s = sin(theta);
	double t;
	double x = r;//we start at angle = 0 
	double y = 0;

	for (int ii = 0; ii < num_segments; ii++) {
		vertex_.emplace_back((float)(x + cx), (float)(y + cy));
		//apply the rotation matrix                          
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
}