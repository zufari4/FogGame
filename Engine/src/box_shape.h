#pragma once
#include "base_shape.h"

class Box_shape : virtual public Base_shape
{
public:
	Box_shape();
	virtual ~Box_shape() {};
	virtual void Set_rect(const vec2& _min, const vec2& _max);
protected:
	void Centering_pos();
};
