#pragma once
#include "base_shape.h"

class Line_segment_shape : virtual public Base_shape
{
public:
	Line_segment_shape();
	virtual ~Line_segment_shape() {};
	virtual void Set_line(const vec2& a, const vec2& b);
	virtual bool Point_in_shape(const vec2& p) const override;
};