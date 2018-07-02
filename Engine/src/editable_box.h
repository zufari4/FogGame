#pragma once
#include "box_shape.h"
#include "editing_shape.h"

class Editable_box : virtual public Box_shape, virtual public Editing_shape
{
public:
	Editable_box();
	virtual ~Editable_box() {};
	virtual bool Point_in_shape(const vec2& p) const override;
};