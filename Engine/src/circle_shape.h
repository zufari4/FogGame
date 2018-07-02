#pragma once
#include "base_shape.h"
#define CIRCLE_QUALITY 19

class Circle_shape: virtual public Base_shape
{
public:
	Circle_shape();
	virtual ~Circle_shape() {};
	float Get_radius() const;
	virtual void  Set_radius(float val);
	virtual bool  Point_in_shape(const vec2& p) const override;
protected:
	float radius_;
	void  Make_circle_vertexes(double cx, double cy, double r, int num_segments);
};