#pragma once

#include "base_shape.h"
#include <vector>

#define EDIT_POINT_SIZE 20.0f

class Editing_shape : virtual public Base_shape
{
public:
	Editing_shape();
	virtual ~Editing_shape() {};
protected:
	void On_mouse_move(float x, float y);
	void On_mouse_down(float x, float y, int b);
	void On_mouse_up(float x, float y, int b);
	virtual void On_drag_object(const vec2& delta);
	virtual void On_drag_point(const vec2& pos);
	virtual void On_stop_drag_object();
	virtual void On_stop_drag_vertex();
	virtual void Update_focused_vertex(const vec2& point);
	bool Point_in_vertex(const vec2& point, const vec2& vertex) const;

	int  focused_vertex_;
private:
	bool drag_object_;
	bool drag_point_;
	vec2 drag_start_;
};