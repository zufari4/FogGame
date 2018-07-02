#pragma once
#include "physic_object.h"

class Physic_distance_join : virtual public Physic_object
{
public:
	Physic_distance_join();
	virtual ~Physic_distance_join();
	virtual void Connect_at_points(const vec2& a, const vec2& b);
protected:
	b2Joint* joint_;
};