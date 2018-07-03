#pragma once
#include "physic_object.h"

class Physic_revolute_joint : virtual public Physic_object
{
public:
	Physic_revolute_joint();
	virtual ~Physic_revolute_joint();
	virtual void Connect_at_point(const vec2& a);
protected:
	b2Joint* joint_;
};